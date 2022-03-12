# gameboy-emulator
A Gameboy emulator written in C.

[![Build Status](https://travis-ci.com/THEvang/gameboy-emulator.svg?branch=master)](https://travis-ci.com/THEvang/gameboy-emulator)

## Building

The emulator depends on SDL2 and Ncurses. They can be installed using your system's 
package manager.

`mkdir build && cmake -B build .`
`cd build && make -j7`

