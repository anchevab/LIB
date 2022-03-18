/*
Td5Defs.h -

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

#ifndef Td5Defs_h
#define Td5Defs_h

#define Td5OpenComWelcome  "Td5OpenCom v0.11q"

// Debug mode: enables debug comments on serial monitor.
//#define _DEBUG_

// SD card option: uses too much RAM, enable only with ATMega2560.
#define _USE_SD_

// Bluetooth option.
#define _USE_BLUETOOTH_

// If uncommented shows fault codes full string, otherwise shows fault index.
#define _FAULT_CODES_STRINGS_


#if  defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
  #define LCD_D7                2
  #define LCD_D6                3
  #define LCD_D5                4
  #define LCD_D4                5
  #define lcdBKlightPin         6
  #define LCD_RS                7
  #define LCD_EN                8
  #define ledPin                9
  #define SD_CS                10
  #define MOSI                 11
  #define MISO                 12
  #define SCK                  13
  #define keyPadPowerPin       A0
  #define keyPadButtonsPin     A1
  #define K_OUT                A2  
  #define K_IN                 A3
  #define SDA                  A4
  #define SCL                  A5
#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  #define LCD_D7               40
  #define LCD_D6               38
  #define LCD_D5               36
  #define LCD_D4               34
  #define lcdBKlightPin         2
  #define btEnablePin           7
  #define LCD_RS               22
  #define LCD_EN               24
  #define ledPin               13
  #define SD_CS                53
  #define MOSI                 51
  #define MISO                 50
  #define SCK                  52
  #define keyPadPowerPin        3
  #define keyPadButtonsPin     A1
  #define K_OUT               A15
  #define K_IN                A14
  #define SDA                  20
  #define SCL                  21
#endif


#define LCD_COLUMNS          20
#define LCD_ROWS              4

#define MAX_OPTIONS_PARAMS    3

#define ARRAY_SIZE(x) (sizeof(x) / sizeof(*(x)))

#if  defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
  #define remoteSerial        Serial
#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  #define remoteSerial        Serial1
#endif

#endif
