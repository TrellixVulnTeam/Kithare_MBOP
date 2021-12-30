# Kithare

![Kithare](misc/banner.png)

## About

 Kithare is a statically typed programming language based on [Python](https://www.python.org) and C++. Its syntax is heavily influnced by Python, but the prime programming flow resembles C++. The language itself is designed to be a multi-paradigm, anti-verbose, clean, easily run-able, and easy-to-learn programming language.

## Links and Contact

- [Website](https://kithare.de)
- [Contributing guidelines](https://kithare.de/rules/contribution)
- [Code of conduct](https://kithare.de/rules/conduct)
- [Discord server](https://discord.gg/hXvY8CzS7A)
- [Channel on the /r/ProgrammingLanguages Discord server](https://discord.gg/sggx9T9xsz)

## Supported OSes/distros

- **Windows** is well supported by Kithare; both Windows 10 and Windows 11. Although not tested, Kithare should work well on Windows 7 and above too. Both 32-bit and 64-bit variants are supported on Windows, however, Windows on ARM architecture is not supported yet
- **GNU/Linux** is also well supported by Kithare; primarily Debian and Ubuntu based modern sufficient Linux distros. Kithare supports a range of architectures (x86, x64, armv6, armv7, arm64, s390x and ppc64le).
- **MacOS (Darwin)** machines whose version is 10.9 or above is supported. Kithare supports x86_64 (Intel) architecture and arm64 (Apple Silicon) architecture. In the future, Kithare will also support 'universal' binaries, ones that works on both architectures. These univeral builds are 'fat' builds, one that contains the binaries of both architectures in one binary. The usage of the 'universal' builds are recommended over the usage of the architecture specific builds.

## Installation and Versioning

- **Important note**: The language is still unfinished and there are no stable releases yet.
- Kithare follows semantic versioning system for its releases.
- All releases will be live on the [GitHub releases tab](https://github.com/Kithare/Kithare/releases)
- For people who like to live on the edge, Kithare provides nighly builds, here are some direct download links
    1. [Windows builds (x86/x64)](https://nightly.link/Kithare/Kithare/workflows/windows/main/kithare-windows-installers.zip)
    2. [Linux builds (x86/x64)](https://nightly.link/Kithare/Kithare/workflows/linux/main/kithare-linux-installers.zip)
    3. [Linux multiarch builds (armv6/armv7/arm64/s390x/ppc64le)](https://nightly.link/Kithare/Kithare/workflows/linux-multiarch/main/kithare-linux-multiarch-installers.zip)
    4. [MacOS (Darwin) builds (x64/arm64/universal)](https://nightly.link/Kithare/Kithare/workflows/darwin/main/kithare-darwin-installers.zip)
- For these builds, the version in the installer packages is usually given by `YYYY.MM.DD.HHmm-nightly`. So if the date during the build is 22nd August 2021 and the time is 09:10:36 UTC, then the nightly build version will look like `2021.08.22.0910-nightly`.

## Building

- Kithare uses a python helper script to make building easier. So in order to build Kithare, you need Python v3.6 or above installed.
- For advanced usage, you may checkout the `build.py` file, which contains instructions on how to use the build script to achieve more things.
- A basic HOWTO to building Kithare is given below.

### Setup

#### Windows

- If you are building on Windows, the build script will automatically download and configure the deps. Kithare uses the MinGW compiler, if MinGW is not pre-installed, the buildscript will install it in a sub-directory. This means that on Windows, virtually no pre-build setup is required!

#### Others

- On other platforms, you would need the GCC compiler installed (On Mac, GCC is just a shim for clang).
- Install the development libraries for these: `SDL2`, `SDL2_mixer`, `SDL2_image`, `SDL2_ttf`, `SDL2_net`. You may use your disto's package manager to do this.
- A recommended way to do this on Mac is to use Homebrew. Just run `brew install sdl2 sdl2_image sdl2_mixer sdl2_net sdl2_ttf`.
- On Ubuntu and other debian based systems, you can do `sudo apt-get install libsdl2-dev libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libfreetype6-dev libsdl2-ttf-dev libsdl2-net-dev -y` (These are mostly SDL dependencies).

### Build

- Run `python3 build.py` to build the project. If you are a `make` user, there is a stub `makefile` that calls the python builder.
