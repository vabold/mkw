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
        "lib": "RVL_SDK",
        "mw_version": config.linker_version,
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "RVL_SDK/ai/ai.c"),
            Object(NonMatching, "RVL_SDK/arc/arc.c"),
            Object(NonMatching, "RVL_SDK/ax/AX.c"),
            Object(NonMatching, "RVL_SDK/ax/AXAlloc.c"),
            Object(NonMatching, "RVL_SDK/ax/AXAux.c"),
            Object(NonMatching, "RVL_SDK/ax/AXCL.c"),
            Object(NonMatching, "RVL_SDK/ax/AXOut.c"),
            Object(NonMatching, "RVL_SDK/ax/AXSPB.c"),
            Object(NonMatching, "RVL_SDK/ax/AXVPB.c"),
            Object(NonMatching, "RVL_SDK/ax/AXProf.c"),
            Object(NonMatching, "RVL_SDK/ax/AXComp.c"),
            Object(NonMatching, "RVL_SDK/ax/DSPCode.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXReverbHi.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXReverbHiExp.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXReverbHiExpDpl2.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXDelayExp.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXDelayExpDpl2.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXReverbStdExp.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXReverbStdExpDpl2.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXChorusExp.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXChorusExpDpl2.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXLfoTable.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXSrcCoef.c"),
            Object(NonMatching, "RVL_SDK/axfx/AXFXHooks.c"),
            Object(NonMatching, "RVL_SDK/base/PPCArch.c"),
            Object(NonMatching, "RVL_SDK/bte/gki_buffer.c"),
            Object(NonMatching, "RVL_SDK/bte/gki_time.c"),
            Object(NonMatching, "RVL_SDK/bte/gki_ppc.c"),
            Object(NonMatching, "RVL_SDK/bte/hcisu_h2.c"),
            Object(NonMatching, "RVL_SDK/bte/uusb_ppc.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_dm_cfg.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_hh_cfg.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_sys_cfg.c"),
            Object(NonMatching, "RVL_SDK/bte/bte_hcisu.c"),
            Object(NonMatching, "RVL_SDK/bte/bte_init.c"),
            Object(NonMatching, "RVL_SDK/bte/bte_logmsg.c"),
            Object(NonMatching, "RVL_SDK/bte/bte_main.c"),
            Object(NonMatching, "RVL_SDK/bte/btu_task1.c"),
            Object(NonMatching, "RVL_SDK/bte/bd.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_sys_conn.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_sys_main.c"),
            Object(NonMatching, "RVL_SDK/bte/ptim.c"),
            Object(NonMatching, "RVL_SDK/bte/utl.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_dm_act.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_dm_api.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_dm_main.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_dm_pm.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_hh_act.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_hh_api.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_hh_main.c"),
            Object(NonMatching, "RVL_SDK/bte/bta_hh_utils.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_acl.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_dev.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_devctl.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_discovery.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_inq.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_main.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_pm.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_sco.c"),
            Object(NonMatching, "RVL_SDK/bte/btm_sec.c"),
            Object(NonMatching, "RVL_SDK/bte/btu_hcif.c"),
            Object(NonMatching, "RVL_SDK/bte/btu_init.c"),
            Object(NonMatching, "RVL_SDK/bte/wbt_ext.c"),
            Object(NonMatching, "RVL_SDK/bte/gap_api.c"),
            Object(NonMatching, "RVL_SDK/bte/gap_conn.c"),
            Object(NonMatching, "RVL_SDK/bte/gap_utils.c"),
            Object(NonMatching, "RVL_SDK/bte/hcicmds.c"),
            Object(NonMatching, "RVL_SDK/bte/hidd_api.c"),
            Object(NonMatching, "RVL_SDK/bte/hidd_conn.c"),
            Object(NonMatching, "RVL_SDK/bte/hidd_mgmt.c"),
            Object(NonMatching, "RVL_SDK/bte/hidd_pm.c"),
            Object(NonMatching, "RVL_SDK/bte/hidh_api.c"),
            Object(NonMatching, "RVL_SDK/bte/hidh_conn.c"),
            Object(NonMatching, "RVL_SDK/bte/l2c_api.c"),
            Object(NonMatching, "RVL_SDK/bte/l2c_csm.c"),
            Object(NonMatching, "RVL_SDK/bte/l2c_link.c"),
            Object(NonMatching, "RVL_SDK/bte/l2c_main.c"),
            Object(NonMatching, "RVL_SDK/bte/l2c_utils.c"),
            Object(NonMatching, "RVL_SDK/bte/port_api.c"),
            Object(NonMatching, "RVL_SDK/bte/port_rfc.c"),
            Object(NonMatching, "RVL_SDK/bte/port_utils.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_l2cap_if.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_mx_fsm.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_port_fsm.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_port_if.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_ts_frames.c"),
            Object(NonMatching, "RVL_SDK/bte/rfc_utils.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_api.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_db.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_discovery.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_main.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_server.c"),
            Object(NonMatching, "RVL_SDK/bte/sdp_utils.c"),
            Object(NonMatching, "RVL_SDK/cnt/cnt.c"),
            Object(NonMatching, "RVL_SDK/cx/CXStreamingUncompression.c"),
            Object(NonMatching, "RVL_SDK/cx/CXUncompression.c"),
            Object(NonMatching, "RVL_SDK/darch/darch.c"),
            Object(NonMatching, "RVL_SDK/db/db.c"),
            Object(NonMatching, "RVL_SDK/dsp/dsp.c"),
            Object(NonMatching, "RVL_SDK/dsp/dsp_debug.c"),
            Object(NonMatching, "RVL_SDK/dsp/dsp_task.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvdfs.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvd.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvdqueue.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvderror.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvdidutils.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvdFatal.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvdDeviceError.c"),
            Object(NonMatching, "RVL_SDK/dvd/dvd_broadway.c"),
            Object(NonMatching, "RVL_SDK/enc/encutility.c"),
            Object(NonMatching, "RVL_SDK/enc/encjapanese.c"),
            Object(NonMatching, "RVL_SDK/esp/esp.c"),
            Object(NonMatching, "RVL_SDK/euart/euart.c"),
            Object(NonMatching, "RVL_SDK/exi/EXIBios.c"),
            Object(NonMatching, "RVL_SDK/exi/EXIUart.c"),
            Object(NonMatching, "RVL_SDK/exi/EXICommon.c"),
            Object(NonMatching, "RVL_SDK/fs/fs.c"),
            Object(NonMatching, "RVL_SDK/gx/GXInit.c"),
            Object(NonMatching, "RVL_SDK/gx/GXFifo.c"),
            Object(NonMatching, "RVL_SDK/gx/GXAttr.c"),
            Object(NonMatching, "RVL_SDK/gx/GXMisc.c"),
            Object(NonMatching, "RVL_SDK/gx/GXGeometry.c"),
            Object(NonMatching, "RVL_SDK/gx/GXFrameBuf.c"),
            Object(NonMatching, "RVL_SDK/gx/GXLight.c"),
            Object(NonMatching, "RVL_SDK/gx/GXTexture.c"),
            Object(NonMatching, "RVL_SDK/gx/GXBump.c"),
            Object(NonMatching, "RVL_SDK/gx/GXTev.c"),
            Object(NonMatching, "RVL_SDK/gx/GXPixel.c"),
            Object(NonMatching, "RVL_SDK/gx/GXDraw.c"),
            Object(NonMatching, "RVL_SDK/gx/GXDisplayList.c"),
            Object(NonMatching, "RVL_SDK/gx/GXTransform.c"),
            Object(NonMatching, "RVL_SDK/gx/GXPerf.c"),
            Object(NonMatching, "RVL_SDK/hbm/HBMFrameController.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/HBMAnmController.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/HBMGUIManager.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/HBMController.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/HBMRemoteSpk.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/HBMAxSound.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/HBMBase.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_animation.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_arcResourceAccessor.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_bounding.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_common.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_drawInfo.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_group.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_layout.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_material.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_pane.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_picture.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_resourceAccessor.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_textBox.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/lyt_window.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/math_triangular.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/ut_binaryFileFormat.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/ut_CharStrmReader.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/ut_CharWriter.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/ut_Font.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/ut_LinkList.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/ut_list.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/ut_ResFont.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/ut_ResFontBase.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/ut_TagProcessorBase.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/nw4hbm/ut_TextWriterBase.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/sound/mix.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/sound/syn.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/sound/synctrl.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/sound/synenv.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/sound/synmix.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/sound/synpitch.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/sound/synsample.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/sound/synvoice.cpp"),
            Object(NonMatching, "RVL_SDK/hbm/sound/seq.cpp"),
            Object(NonMatching, "RVL_SDK/ipc/ipcMain.c"),
            Object(NonMatching, "RVL_SDK/ipc/ipcclt.c"),
            Object(NonMatching, "RVL_SDK/ipc/memory.c"),
            Object(NonMatching, "RVL_SDK/ipc/ipcProfile.c"),
            Object(NonMatching, "RVL_SDK/kpad/KPAD.c"),
            Object(NonMatching, "RVL_SDK/mem/mem_heapCommon.c"),
            Object(NonMatching, "RVL_SDK/mem/mem_expHeap.c"),
            Object(NonMatching, "RVL_SDK/mem/mem_frameHeap.c"),
            Object(NonMatching, "RVL_SDK/mem/mem_unitHeap.c"),
            Object(NonMatching, "RVL_SDK/mem/mem_allocator.c"),
            Object(NonMatching, "RVL_SDK/mem/mem_list.c"),
            Object(NonMatching, "RVL_SDK/mtx/mtx.c"),
            Object(NonMatching, "RVL_SDK/mtx/mtxvec.c"),
            Object(NonMatching, "RVL_SDK/mtx/mtx44.c"),
            Object(NonMatching, "RVL_SDK/mtx/vec.c"),
            Object(NonMatching, "RVL_SDK/mtx/quat.c"),
            Object(NonMatching, "RVL_SDK/nand/nand.c"),
            Object(NonMatching, "RVL_SDK/nand/NANDOpenClose.c"),
            Object(NonMatching, "RVL_SDK/nand/NANDCore.c"),
            Object(NonMatching, "RVL_SDK/nand/NANDSecret.c"),
            Object(NonMatching, "RVL_SDK/nand/NANDCheck.c"),
            Object(NonMatching, "RVL_SDK/nand/NANDLogging.c"),
            Object(NonMatching, "RVL_SDK/os/OS.c"),
            Object(NonMatching, "RVL_SDK/os/OSAlarm.c"),
            Object(NonMatching, "RVL_SDK/os/OSAlloc.c"),
            Object(NonMatching, "RVL_SDK/os/OSArena.c"),
            Object(NonMatching, "RVL_SDK/os/OSAudioSystem.c"),
            Object(NonMatching, "RVL_SDK/os/OSCache.c"),
            Object(NonMatching, "RVL_SDK/os/OSContext.c"),
            Object(NonMatching, "RVL_SDK/os/OSError.c"),
            Object(NonMatching, "RVL_SDK/os/OSExec.c"),
            Object(NonMatching, "RVL_SDK/os/OSFatal.c"),
            Object(NonMatching, "RVL_SDK/os/OSFont.c"),
            Object(NonMatching, "RVL_SDK/os/OSInterrupt.c"),
            Object(NonMatching, "RVL_SDK/os/OSLink.c"),
            Object(NonMatching, "RVL_SDK/os/OSMessage.c"),
            Object(NonMatching, "RVL_SDK/os/OSMemory.c"),
            Object(NonMatching, "RVL_SDK/os/OSMutex.c"),
            Object(NonMatching, "RVL_SDK/os/OSReboot.c"),
            Object(NonMatching, "RVL_SDK/os/OSReset.c"),
            Object(NonMatching, "RVL_SDK/os/OSRtc.c"),
            Object(NonMatching, "RVL_SDK/os/OSSync.c"),
            Object(NonMatching, "RVL_SDK/os/OSThread.c"),
            Object(NonMatching, "RVL_SDK/os/OSTime.c"),
            Object(NonMatching, "RVL_SDK/os/OSUtf.c"),
            Object(NonMatching, "RVL_SDK/os/OSIpc.c"),
            Object(NonMatching, "RVL_SDK/os/OSStateTM.c"),
            Object(NonMatching, "RVL_SDK/os/__start.c"),
            Object(NonMatching, "RVL_SDK/os/OSPlayRecord.c"),
            Object(NonMatching, "RVL_SDK/os/OSStateFlags.c"),
            Object(NonMatching, "RVL_SDK/os/OSNet.c"),
            Object(NonMatching, "RVL_SDK/os/OSNandbootInfo.c"),
            Object(NonMatching, "RVL_SDK/os/OSPlayTime.c"),
            Object(NonMatching, "RVL_SDK/os/OSInstall.c"),
            Object(NonMatching, "RVL_SDK/os/OSLaunch.c"),
            Object(NonMatching, "RVL_SDK/os/__ppc_eabi_init.cpp"),
            Object(NonMatching, "RVL_SDK/pad/Padclamp.c"),
            Object(NonMatching, "RVL_SDK/pad/Pad.c"),
            Object(NonMatching, "RVL_SDK/sc/scsystem.c"),
            Object(NonMatching, "RVL_SDK/sc/scapi.c"),
            Object(NonMatching, "RVL_SDK/sc/scapi_prdinfo.c"),
            Object(NonMatching, "RVL_SDK/si/SIBios.c"),
            Object(NonMatching, "RVL_SDK/si/SISamplingRate.c"),
            Object(NonMatching, "RVL_SDK/thp/THPDec.c"),
            Object(NonMatching, "RVL_SDK/thp/THPAudio.c"),
            Object(NonMatching, "RVL_SDK/tpl/TPL.c"),
            Object(NonMatching, "RVL_SDK/usb/usb.c"),
            Object(NonMatching, "RVL_SDK/vi/vi.c"),
            Object(NonMatching, "RVL_SDK/vi/i2c.c"),
            Object(NonMatching, "RVL_SDK/vi/vi3in1.c"),
            Object(NonMatching, "RVL_SDK/wenc/wenc.c"),
            Object(NonMatching, "RVL_SDK/wpad/WPAD.c"),
            Object(NonMatching, "RVL_SDK/wpad/WPADHIDParser.c"),
            Object(NonMatching, "RVL_SDK/wpad/WPADEncrypt.c"),
            Object(NonMatching, "RVL_SDK/wpad/WPADClamp.c"),
            Object(NonMatching, "RVL_SDK/wpad/WPADMem.c"),
            Object(NonMatching, "RVL_SDK/wpad/debug_msg.c"),
            Object(NonMatching, "RVL_SDK/wud/WUD.c"),
            Object(NonMatching, "RVL_SDK/wud/WUDHidHost.c"),
            Object(NonMatching, "RVL_SDK/wud/debug_msg.c"),
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
