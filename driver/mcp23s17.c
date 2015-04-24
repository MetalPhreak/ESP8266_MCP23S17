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


#include "driver/mcp23s17.h"

#define SPI_DEV HSPI

////////////////////////////////////////////////////////////////////////////////
//
// Function Name: mcp23s17_init
//   Description: Initialises SPI hardware for 10MHz operation & configures
//                all attached MCP23S17 devices for individual addressing.
//    Parameters: none
//				 
////////////////////////////////////////////////////////////////////////////////

void mcp23s17_init(){
	//init SPI bus
	spi_init_gpio(SPI_DEV, SPI_CLK_USE_DIV);
	spi_clock(SPI_DEV, 4, 2); //10MHz
	spi_tx_byte_order(SPI_DEV, SPI_BYTE_ORDER_HIGH_TO_LOW);
	spi_rx_byte_order(SPI_DEV, SPI_BYTE_ORDER_HIGH_TO_LOW); 

	SET_PERI_REG_MASK(SPI_USER(SPI_DEV), SPI_CS_SETUP|SPI_CS_HOLD);
	CLEAR_PERI_REG_MASK(SPI_USER(SPI_DEV), SPI_FLASH_MODE);

	//Enable hardware addressing & sequential addressing on all devices
	mcp23s17_REG_SET(IOCON_CTRL, PORTA, SEQOP|HAEN); 
	
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Function Name: mcp23s17_REG_SET
//   Description: Set register value
//    Parameters: ctrl_reg - control register to set
//                port - port to control
//                value - value to set
//				 
////////////////////////////////////////////////////////////////////////////////

void mcp23s17_REG_SET(uint8 ctrl_reg, uint8 port, uint16 value){
	
	uint8 cmd = (0x20|(port>>2))<<1; //0b0100[Address][WRITE]

	if (port & 0x02){
		spi_transaction(SPI_DEV, 8, cmd, 8, ctrl_reg, 16, value, 0, 0);
	} else {
		spi_transaction(SPI_DEV, 8, cmd, 8, ctrl_reg+(port&0x01), 8, value, 0, 0);	
	}	
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Function Name: mcp23s17_REG_GET
//   Description: Get register value
//    Parameters: ctrl_reg - control register to get
//                port - port to control
//				 
////////////////////////////////////////////////////////////////////////////////

uint16 mcp23s17_REG_GET(uint8 ctrl_reg, uint8 port){
	
	uint8 cmd = ((0x20|(port>>2))<<1)|0x01; //0b0100[Address][READ]

	if (port & 0x02){
		return spi_transaction(SPI_DEV, 8, cmd, 8, ctrl_reg, 0, 0, 16, 0);
	} else {
		return (uint16) spi_transaction(SPI_DEV, 8, cmd, 8, ctrl_reg+(port&0x01), 0, 0, 8, 0);	
	}	
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Function Name: mcp23s17_REG_SET_MASK
//   Description: Set register value bits with a mask
//    Parameters: ctrl_reg - control register to set
//                port - port to control
//                value - value to set
//                bitmask - which bits to change
//				 
////////////////////////////////////////////////////////////////////////////////

void mcp23s17_REG_SET_MASK(uint8 ctrl_reg, uint8 port, uint16 value, uint16 bitmask){
	
uint16 current_value = ~bitmask & mcp23s17_REG_GET(ctrl_reg, port);
uint16 set_value = bitmask & value;

	mcp23s17_REG_SET(ctrl_reg, port, current_value|set_value);

}

////////////////////////////////////////////////////////////////////////////////

/*///////////////////////////////////////////////////////////////////////////////
//
// Function Name: func
//   Description: 
//    Parameters: 
//				 
////////////////////////////////////////////////////////////////////////////////

void func(params){

}

///////////////////////////////////////////////////////////////////////////////*/


