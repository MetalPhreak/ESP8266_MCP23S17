/*
* The MIT License (MIT)
* 
* Copyright (c) 2015 David Ogilvy (MetalPhreak)
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/

#ifndef MCP23S17_REGISTER_H
#define MCP23S17_REGISTER_H

// 0b000ADDMP
//      | |^^ Port: 0 = PORTA#; 1 = PORTB#; x = Don't Care for 16bit I/O Setup 
//       ^ ^ Mode: 0 = 8bit; 1 = 16bit
//       ^ Device ADDress: 000 = Chip 0, 001 = Chip 1 ... 111 = Chip 7

#define PORTA0  0x00
#define PORTB0  0x01
#define PORT0   0x02

#define PORTA1  0x04
#define PORTB1  0x05
#define PORT1   0x06

#define PORTA2  0x08
#define PORTB2  0x09
#define PORT2   0x0A

#define PORTA3  0x0C
#define PORTB3  0x0D
#define PORT3   0x0E

#define PORTA4  0x10
#define PORTB4  0x11
#define PORT4   0x12

#define PORTA5  0x14
#define PORTB5  0x15
#define PORT5   0x16

#define PORTA6  0x18
#define PORTB6  0x19
#define PORT6   0x1A

#define PORTA7  0x1C
#define PORTB7  0x1D
#define PORT7   0x1E

//If you only have one device, you can use the below for simplicity. 
//Connect all address pins to ground, or change the below defines to match your address setting.
#define PORTA   PORTA0
#define PORTB   PORTB0
#define PORT    PORT0

#define GPIO0   0x0001
#define GPIO1   0x0002
#define GPIO2   0x0004
#define GPIO3   0x0008
#define GPIO4   0x0010
#define GPIO5   0x0020
#define GPIO6   0x0040
#define GPIO7   0x0080
#define GPIO8   0x0100
#define GPIO9   0x0200
#define GPIO10  0x0400
#define GPIO11  0x0800
#define GPIO12  0x1000
#define GPIO13  0x2000
#define GPIO14  0x4000
#define GPIO15  0x8000

//IOCON.Bank = 0 by default on startup which is better for using 16bit mode (and just as good for 8bit)

//These control register maps are valid only when IOCON.Bank = 0!

//Can use these only with PORTAx/PORTBx respectively
#define IODIRA      0x00
#define IODIRB      0x01
#define IPOLA       0x02
#define IPOLB       0x03
#define GPINTENA    0x04
#define GPINTENB    0x05
#define DEFVALA     0x06
#define DEFVALB     0x07
#define INTCONA     0x08
#define INTCONB     0x09
#define IOCONA      0x0A
#define IOCONB      0x0B
#define GPPUA       0x0C
#define GPPUB       0x0D
#define INTFA       0x0E
#define INTFB       0x0F
#define INTCAPA     0x10
#define INTCAPB     0x11
#define GPIOA       0x12
#define GPIOB       0x13
#define OLATA       0x14
#define OLATB       0x15

//Can use these names for control registers for all PORTAx/PORTBx/PORTx 
#define IODIR_CTRL   0x00
#define IPOL_CTRL    0x02
#define GPINTEN_CTRL 0x04
#define DEFVAL_CTRL  0x06
#define INTCON_CTRL  0x08
#define IOCON_CTRL   0x0A
#define GPPU_CTRL    0x0C
#define INTF_CTRL    0x0E
#define INTCAP_CTRL  0x10
#define GPIO_CTRL    0x12
#define OLAT_CTRL    0x14


//IOCON bits
#define INTPOL  0x02
#define ODR     0x04
#define HAEN    0x08
#define DISSLW  0x10
#define SEQOP   0x20
#define MIRROR  0x40
#define BANK    0x80

#endif

