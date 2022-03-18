/*
Sorryful incomplete hacks to get Arduino 1.5.8 SPI to work with RFduino 2.2
teo20141116.01
*/

/*
 Copyright (c) 2013 OpenSourceRF.com.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * SPI Master library for arduino.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include "variant.h"
#include <stdio.h>

#define SPI_MODE0 0x00
#define SPI_MODE1 0x01
#define SPI_MODE2 0x02
#define SPI_MODE3 0x03

#define SPI_HAS_TRANSACTION 0
#define SPI_HAS_EXTENDED_CS_PIN_HANDLING 0

// hack to add place holders for new or changed features for 1.5.8 SPI
class SPISettings {
public:
        SPISettings(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) {
        }
        SPISettings() { init_AlwaysInline(4000000, MSBFIRST, SPI_MODE0); }

private:
        void init_AlwaysInline(uint32_t clock, BitOrder bitOrder, uint8_t dataMode) __attribute__((__always_inline__)) {
// Not used on RFduino, yet!!!!
	}
};

class SPIClass {
  public:
    SPIClass(NRF_SPI_Type *_spi, int _pinSCK, int _pinMOSI, int _pinMISO);

	byte transfer(uint8_t _data);

	// SPI Configuration methods

	void begin(void);
	void end(void);

	void setBitOrder(BitOrder _bitOrder);
	void setDataMode(uint8_t _dataMode);
        void setFrequency(int _speedKbps);
        void setClockDivider(uint8_t _divider);

        void setCPOL(bool _activeHigh);
        void setCPHA(bool _leading);

        void attachInterrupt(void);
        void detachInterrupt(void);

    // hack to add place holders for new or changed features for 1.5.8  SPI
    void beginTransaction(SPISettings settings) { beginTransaction(PIN_SPI_SS, settings); }
    void beginTransaction(uint8_t pin, SPISettings settings);
    void endTransaction(void);


  private:
	NRF_SPI_Type *spi;
	int pinSCK;
	int pinMOSI;
	int pinMISO;
};

#if SPI_INTERFACES_COUNT > 0
extern SPIClass SPI;
#endif

#endif
