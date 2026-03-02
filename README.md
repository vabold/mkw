Mario Kart Wii
[![Discord Badge]][discord]
=============

[Discord Badge]: https://img.shields.io/discord/727908905392275526?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[discord]: https://discord.gg/hKx3FJJgrV

A work-in-progress decompilation of Mario Kart Wii.

This repository does **not** contain any game assets or assembly whatsoever. An existing copy of the game is required.

Supported versions:

- `RMCP01`: (PAL)

Dependencies
============

Windows
--------

On Windows, it's **highly recommended** to use native tooling. WSL or msys2 are **not** required.  
When running under WSL, [objdiff](#diffing) is unable to get filesystem notifications for automatic rebuilds.

- Install [Python](https://www.python.org/downloads/) and add it to `%PATH%`.
  - Also available from the [Windows Store](https://apps.microsoft.com/store/detail/python-311/9NRWMJP3717K).
- Download [ninja](https://github.com/ninja-build/ninja/releases) and add it to `%PATH%`.
  - Quick install via pip: `pip install ninja`

macOS
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages):

  ```sh
  brew install ninja
  ```

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Linux
------

- Install [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages).

[wibo](https://github.com/decompals/wibo), a minimal 32-bit Windows binary wrapper, will be automatically downloaded and used.

Building
========

- Clone the repository:

  ```sh
  git clone https://github.com/doldecomp/mkw.git
  ```

- Copy your game's disc image to `orig/RMCP01`.
  - Supported formats: ISO (GCM), RVZ, WIA, WBFS, CISO, NFS, GCZ, TGC
  - After the initial build, the disc image can be deleted to save space.

- Configure:

  ```sh
  python configure.py
  ```

- Build:

  ```sh
  ninja
  ```

Contributing
============

Due to the overwhelming majority of the DOL being library code, we will not be accepting external contributions to the DOL. DOL contributors are expected not to use LLMs to assist with library decompilation in any form, including but not limited to bytematching or documentation. This is to ensure that information about the libraries is strictly sourced from user-obtainable releases. This includes:
- Big Brain Academy: Wii Degree (2007)'s debug linker maps
- Tokyo Friend Park II Ketteiban: Minna de Chousen! Taikan Attraction (2009)'s debug build + DWARF info
- Challenge Me: Word Puzzles (2011)'s debug object files + DWARF info (where applicable)

External contributions for the REL are acceptable. REL contributors may use LLMs to assist with matches and documentation. Because pull requests are disabled, it is recommended to fork the repository and ping one of the maintainers in the above Discord server.
