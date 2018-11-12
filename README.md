# Duke Nukem 3D ESP32 Port
An ESP32 port of Duke Nukem 3D - based on the Win/Mac/Linux port: Chocolate Duke3D (https://github.com/fabiensanglard/chocolate_duke3D)

## Requirements
- ESP32 WROVER (4Mb PSRAM)
- An SPI LCD screen - preferable using the ILI9341 chipset
- An SD Card and SPI or SDMMC reader
- Some input buttons
- The data files from Duke Nukem 3D - Atomic Edition (v1.5) or lower (saved on the SD Card under a folder called "duke3d")

## Configuration
Run "make menuconfig" and check the settings under ESP32-DUKE3D platform-specific configuration
![Config Image](https://github.com/jkirsons/Duke3D/raw/master/documents/config.png)

## LEGAL STUFF
"Duke Nukem" is a registered trademark of Apogee Software, Ltd. (a.k.a. 3D Realms).
"Duke Nukem 3D" copyright 1996 - 2003 3D Realms. All trademarks and copyrights reserved.

This repository is split into the following code bases:

### Build Engine
The Build Engine (folder: <b>"components/Engine"</b>) is licensed under the Build License - see BUILDLIC.TXT

       // "Build Engine & Tools" Copyright (c) 1993-1997 Ken Silverman
       // Ken Silverman's official web site: "http://www.advsys.net/ken"
       // See the included license file "BUILDLIC.TXT" for license info.

Most files in this code base have been modified, and do not represent the original content from this author.

### Game Code
The original Duke Nukem Game code (folder: <b>"components/Game"</b>) is licensed under GNU General Public License v2.0 (see LICENSE).

The Chocolate Duke modifications (folder: <b>"components/Game"</b>) were not released with a license, but permission from the author to "do whatever you want with my code" (see https://github.com/fabiensanglard/chocolate_duke3D/issues/48)

Most files in this code base have been modified, and do not represent the original content from these authors.

### SDL Library
The SDL library function wrapper (folder: <b>"components/SDL"</b>) contains parts of the Simple DirectMedia Layer library that is licensed under the ZLIB license (see ZLIB_LICENSE).  

All files in this code base are either new or extensively modified, and do not represent the original SDL Library.

### SPI LCD Functions
The SPI LCD functions (folder: <b>"components/SDL/spi_lcd.c and components/SDL/spi_lcd.h"</b>) are Copyright 2016-2017 Espressif Systems (Shanghai) PTE LTD and licenced under the Apache License 2.0 (see http://www.apache.org/licenses/LICENSE-2.0)

These files have been modified, and do not represent the original content from this author.

### ESP32 Wrapper
Parts by me (folder: <b>"main"</b>) are licensed under GNU General Public License v2.0 (see LICENSE).
