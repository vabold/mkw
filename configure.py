#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "RMCP01",  # 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja",
    metavar="BINARY",
    type=Path,
    help="path to ninja binary (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-2"
config.compilers_tag = "20251118"
config.dtk_tag = "v1.8.3"
config.objdiff_tag = "v3.6.1"
config.sjiswrap_tag = "v1.2.2"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
]
if args.debug:
    config.ldflags.append("-gdwarf-2")
if args.map:
    config.ldflags.append("-listclosure")

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    "-O4,p",
    "-ipa file",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    "-enc SJIS",
    "-i include",
    f"-i build/{config.version}/include",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
]

# Debug flags
if args.debug:
    cflags_base.extend(["-sym dwarf-2", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-sdata 0",
    "-sdata2 0",
]

config.linker_version = "Wii/0x4201_127"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "progress_category": "game",
        "objects": objects,
    }


Matching = True                   # Object matches and should be linked
NonMatching = False               # Object does not match and should not be linked
Equivalent = config.non_matching  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",  # str | List[str]
        "objects": [
            Object(NonMatching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
        ],
    },
    {
        "lib": "EGG",
        "mw_version": config.linker_version,
        "cflags": cflags_base,
        "progress_category": "egg",
        "objects": [
            Object(NonMatching, "egg/core/eggAllocator.cpp"),
            Object(NonMatching, "egg/core/eggArchive.cpp"),
            Object(NonMatching, "egg/prim/eggAssert.cpp"),
            Object(NonMatching, "egg/core/eggAsyncDisplay.cpp"),
            Object(NonMatching, "egg/audio/eggAudio3DActor.cpp"),
            Object(NonMatching, "egg/audio/eggAudioArcPlayerMgr.cpp"),
            Object(NonMatching, "egg/audio/eggAudioExpMgr.cpp"),
            Object(NonMatching, "egg/audio/eggAudioFxMgr.cpp"),
            Object(NonMatching, "egg/audio/eggAudioHeapMgr.cpp"),
            Object(NonMatching, "egg/audio/eggAudioMgr.cpp"),
            Object(NonMatching, "egg/audio/eggAudioRmtSpeakerMgr.cpp"),
            Object(NonMatching, "egg/audio/eggAudioSystem.cpp"),
            Object(NonMatching, "egg/audio/eggAudioUtility.cpp"),
            Object(NonMatching, "egg/math/eggBoundBox.cpp"),
            Object(NonMatching, "egg/gfx/eggCamera.cpp"),
            Object(NonMatching, "egg/gfxe/eggCapTexture.cpp"),
            Object(NonMatching, "egg/core/eggCntFile.cpp"),
            Object(NonMatching, "egg/core/eggColorFader.cpp"),
            Object(NonMatching, "egg/core/eggCompress.cpp"),
            Object(NonMatching, "egg/core/eggController.cpp"),
            Object(NonMatching, "egg/gfxe/eggCpuTexture.cpp"),
            Object(NonMatching, "egg/core/eggDecomp.cpp"),
            Object(NonMatching, "egg/core/eggDisplay.cpp"),
            Object(NonMatching, "egg/core/eggDisposer.cpp"),
            Object(NonMatching, "egg/gfxe/eggDrawGX.cpp"),
            Object(NonMatching, "egg/gfxe/eggDrawPathBase.cpp"),
            Object(NonMatching, "egg/gfxe/eggDrawPathBloom.cpp"),
            Object(NonMatching, "egg/gfxe/eggDrawPathDOF.cpp"),
            Object(NonMatching, "egg/gfxe/eggDrawPathHDR.cpp"),
            Object(NonMatching, "egg/gfxe/eggDrawPathShadowVolume.cpp"),
            Object(NonMatching, "egg/gfxe/eggDrawPathXluSnap.cpp"),
            Object(NonMatching, "egg/core/eggDvdFile.cpp"),
            Object(NonMatching, "egg/core/eggDvdRipper.cpp"),
            Object(NonMatching, "egg/util/eggEffect.cpp"),
            Object(NonMatching, "egg/util/eggEffectCreator.cpp"),
            Object(NonMatching, "egg/util/eggEffectManager.cpp"),
            Object(NonMatching, "egg/util/eggEffectResource.cpp"),
            Object(NonMatching, "egg/util/eggExOneEmitter.cpp"),
            Object(NonMatching, "egg/util/eggExParticleManager.cpp"),
            Object(NonMatching, "egg/util/eggException.cpp"),
            Object(NonMatching, "egg/core/eggExpHeap.cpp"),
            Object(NonMatching, "egg/gfxe/eggFog.cpp"),
            Object(NonMatching, "egg/gfxe/eggFogManager.cpp"),
            Object(NonMatching, "egg/gfxe/eggFrustum.cpp"),
            Object(NonMatching, "egg/gfxe/eggG3DUtility.cpp"),
            Object(NonMatching, "egg/gfxe/eggGXUtility.cpp"),
            Object(NonMatching, "egg/gfxe/eggGfxEngine.cpp"),
            Object(NonMatching, "egg/gfxe/eggGlobalDrawState.cpp"),
            Object(NonMatching, "egg/core/eggGraphicsFifo.cpp"),
            Object(NonMatching, "egg/core/eggHeap.cpp"),
            Object(NonMatching, "egg/gfxe/eggIScnProc.cpp"),
            Object(NonMatching, "egg/gfxe/eggLightManager.cpp"),
            Object(NonMatching, "egg/gfxe/eggLightObject.cpp"),
            Object(NonMatching, "egg/gfxe/eggLightTexture.cpp"),
            Object(NonMatching, "egg/gfxe/eggLightTextureManager.cpp"),
            Object(NonMatching, "egg/prim/eggList.cpp"),
            Object(NonMatching, "egg/math/eggMath.cpp"),
            Object(NonMatching, "egg/math/eggMatrix.cpp"),
            Object(NonMatching, "egg/gfxe/eggModelEx.cpp"),
            Object(NonMatching, "egg/gfxe/eggModelSnapshot.cpp"),
            Object(NonMatching, "egg/util/eggNwc24Manager.cpp"),
            Object(NonMatching, "egg/util/eggOdh.cpp"),
            Object(NonMatching, "egg/core/eggPerfMeter.cpp"),
            Object(NonMatching, "egg/gfxe/eggPostEffectBase.cpp"),
            Object(NonMatching, "egg/gfxe/eggPostEffectBlur.cpp"),
            Object(NonMatching, "egg/gfxe/eggPostEffectBlurGather.cpp"),
            Object(NonMatching, "egg/gfxe/eggPostEffectBlurSimple.cpp"),
            Object(NonMatching, "egg/gfxe/eggPostEffect_unknown.cpp"),
            Object(NonMatching, "egg/gfxe/eggPostEffectHDR.cpp"),
            Object(NonMatching, "egg/gfxe/eggPostEffectMask.cpp"),
            Object(NonMatching, "egg/gfxe/eggPostEffectMaskDOF.cpp"),
            Object(NonMatching, "egg/gfxe/eggPostEffectSimple.cpp"),
            Object(NonMatching, "egg/gfxe/eggPreRenderManager.cpp"),
            Object(NonMatching, "egg/core/eggProcessMeter.cpp"),
            Object(NonMatching, "egg/gfx/eggProjection.cpp"),
            Object(NonMatching, "egg/math/eggQuat.cpp"),
            Object(NonMatching, "egg/util/eggSaveBanner.cpp"),
            Object(NonMatching, "egg/core/eggScene.cpp"),
            Object(NonMatching, "egg/core/eggSceneManager.cpp"),
            Object(NonMatching, "egg/gfxe/eggScnRenderer.cpp"),
            Object(NonMatching, "egg/gfxe/eggScnRootEx.cpp"),
            Object(NonMatching, "egg/gfxe/eggScreen.cpp"),
            Object(NonMatching, "egg/gfxe/eggScreenEffectBase.cpp"),
            Object(NonMatching, "egg/gfxe/eggScreenEffect_unknown.cpp"),
            Object(NonMatching, "egg/gfxe/eggShadowTexture.cpp"),
            Object(NonMatching, "egg/gfxe/eggShadowTextureManager.cpp"),
            Object(NonMatching, "egg/gfxe/eggStateEfb.cpp"),
            Object(NonMatching, "egg/gfxe/eggStateGX.cpp"),
            Object(NonMatching, "egg/util/eggStream.cpp"),
            Object(NonMatching, "egg/core/eggStreamDecomp.cpp"),
            Object(NonMatching, "egg/core/eggSystem.cpp"),
            Object(NonMatching, "egg/core/eggTaskThread.cpp"),
            Object(NonMatching, "egg/gfxe/eggTextureBuffer.cpp"),
            Object(NonMatching, "egg/core/eggThread.cpp"),
            Object(NonMatching, "egg/core/eggUnitHeap.cpp"),
            Object(NonMatching, "egg/math/eggVector.cpp"),
            Object(NonMatching, "egg/core/eggVideo.cpp"),
            Object(NonMatching, "egg/gfx/eggViewport.cpp"),
            Object(NonMatching, "egg/core/eggXfb.cpp"),
            Object(NonMatching, "egg/core/eggXfbManager.cpp"),
        ],
    },
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("sdk", "SDK"),
    ProgressCategory("nw4r", "nw4r"),
    ProgressCategory("egg", "EGG"),
]
config.progress_each_module = False
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
