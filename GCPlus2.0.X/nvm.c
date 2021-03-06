/*
MIT License

Copyright (c) 2020 Aurelio Mannara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

nvm.c: Implements functions to handle internal NVM memories.
*/

#include "main.h"

void NVMUnlock(void) {
    INTCON0bits.GIE = 0;
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
    INTCON0bits.GIE = 1;
}

uint8_t EEPROMReadByte(uint8_t address) {
    NVMCON1 = 0;
    NVMADRL = address;
    NVMCON1bits.RD = 1;
    return NVMDAT;
}

void EEPROMWriteByte(uint8_t address, uint8_t data) {
    NVMCON1 = 0;
    NVMADRL = address;
    NVMDAT = data;
    NVMCON1bits.WREN = 1;
    NVMUnlock();
    while (NVMCON1bits.WR);
    NVMCON1bits.WREN = 0;
}
