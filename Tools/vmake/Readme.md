# VMake: Build system

### Automate the building process for Vircon32 games

Vmake is a program designed to be simple, fast, and comprehensive; its primary purpose is to eliminate the need to create long scripts only to convert files and compile the game.

### How to use

To build a project, vmake will make some assumptions about its folder structure and files:

1. The main C file needs to be called main.c and be in the base folder.
2. The ROM definition file needs to be called romdef.xml and be in the base folder.
3. Textures are PNG files and are all in the base folder. Their names are given as dictated by the paths in <textures> within romdef.xml (e.g: file image.png for /build/image.vtex).
4. Sounds are WAV files and are all in the base folder. Their names are given as dictated by the paths in <sounds> within romdef.xml (e.g: file music.wav for /build/music.vsnd).

To make things easier at the beginning of a project, you can initially use the command 'vmake -c' in order to generate a template for the minimum required files (main.c and romdef.xml). You are then expected to fill romdef.xml with the information for all needed textures and sounds. After this vmake will automatically process them in addition to compiling the code.

## Installation

### 1. Download VMake

You can find pre-built binaries of VMake for Windows and Linux in the `bin` folder.

### 2. Install Vircon32 DevTools

If you already have them installed, skip this part.

Windows:

1. Download the ![DevTools.](https://github.com/vircon32/ComputerSoftware/releases/tag/devtools-v25.10.29)
2. Extract the zip file.
3. Include the path in the environment variables.
4. Reboot.

Linux:

1. Download the ![DevTools.](https://github.com/vircon32/ComputerSoftware/releases/tag/devtools-v25.10.29)
2. Extract the zip file.
3. Install them using your package manager.

It is also recommended to install the Vircon32 Emulator in order to use the quick test feature.

### 3. Install VMake

The VMake installation process is really simple; just copy the VMake executable to the same folder as the devtools.

---

Created by @Palta under the MIT License.
