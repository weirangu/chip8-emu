# CHIP-8 Emulator

A CHIP-8 emulator written in C11. Tested on Windows and Linux.

## Building

Generate a project through CMake, then build. Make sure the below dependencies are satisfied.

#### Dependencies

* SDL2 (>= 2.0.4)

* PkgConfig

## Usage

Run the program with the filename of the CHIP-8 ROM to run as an argument.

Optionally, use the `-s, --speed` flag to set the speed of a single system cycle in ms. The default is 1 ms.

### Controls

As the original CHIP-8 used a hex keypad with unsuitable controls for modern keyboards, the keys are rebound as follows:

|  Original Key | Rebound To |
|---------------|------------|
| 0             | X          |
| 1             | 1          |
| 2             | 2          |
| 3             | 3          |
| 4             | Q          |
| 5             | W          |
| 6             | E          |
| 7             | A          |
| 8             | S          |
| 9             | D          |
| A             | Z          |
| B             | C          |
| C             | 4          |
| D             | R          |
| E             | F          |
| F             | V          |
