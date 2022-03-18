/*
Td5strings.cpp -
 
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

#include <Arduino.h>
#include <avr/pgmspace.h>
#include "td5strings.h"

// Menu texts
PROGMEM const char *_void_menu[] = { };

PROGMEM prog_char menu_header_0[] PROGMEM = "Main Menu";
PROGMEM prog_char menu_header_1[] PROGMEM = "Ecu Menu";
PROGMEM prog_char menu_header_2[] PROGMEM = "Fault Codes Menu";
PROGMEM prog_char menu_header_3[] PROGMEM = "Settings Menu";
PROGMEM const char *menu_header[] = {menu_header_0, menu_header_1, menu_header_2, menu_header_3};

PROGMEM prog_char main_menu_0[] PROGMEM = "Instrument mode";
PROGMEM prog_char main_menu_1[] PROGMEM = "Ecu";
PROGMEM prog_char main_menu_2[] PROGMEM = "Options";
PROGMEM prog_char main_menu_3[] PROGMEM = "Tools";
PROGMEM const char *_main_menu[] = {main_menu_0, main_menu_1, main_menu_2, main_menu_3 };

PROGMEM prog_char sub_menu_0_0[] PROGMEM = "Fuelling";
PROGMEM prog_char sub_menu_0_1[] PROGMEM = "Settings";
PROGMEM prog_char sub_menu_0_2[] PROGMEM = "Input-output";
PROGMEM prog_char sub_menu_0_3[] PROGMEM = "Fault codes";
PROGMEM prog_char sub_menu_0_4[] PROGMEM = "Map";
PROGMEM const char *_sub_menu_0[] = {sub_menu_0_0, sub_menu_0_1, sub_menu_0_2, sub_menu_0_3, sub_menu_0_4 };

// Ecu - Settings
PROGMEM prog_char sub_menu_0_1_0[] PROGMEM = "Read";
PROGMEM prog_char sub_menu_0_1_1[] PROGMEM = "Save to file";
PROGMEM prog_char sub_menu_0_1_2[] PROGMEM = "Restore from file";
PROGMEM const char *_sub_menu_0_1[] = {sub_menu_0_1_0, sub_menu_0_1_1, sub_menu_0_1_2 };

// Ecu - Fault Codes
PROGMEM prog_char sub_menu_0_3_0[] PROGMEM = "Read";
PROGMEM prog_char sub_menu_0_3_1[] PROGMEM = "Reset";
PROGMEM const char *_sub_menu_0_3[] = {sub_menu_0_3_0, sub_menu_0_3_1 };

// Ecu - Map
PROGMEM prog_char sub_menu_0_4_0[] PROGMEM = "Read from Ecu";
PROGMEM prog_char sub_menu_0_4_1[] PROGMEM = "Write to Ecu";
PROGMEM const char *_sub_menu_0_4[] = {sub_menu_0_4_0, sub_menu_0_4_1 };

// Fuelling params
PROGMEM prog_char fuelling_param_0[] PROGMEM = "Speed (km/h)";
PROGMEM prog_char fuelling_param_1[] PROGMEM = "Eng.spd.(rpm)";
PROGMEM prog_char fuelling_param_2[] PROGMEM = "Battery (V)";
PROGMEM prog_char fuelling_param_3[] PROGMEM = "Man.pres.(KPa)";
PROGMEM prog_char fuelling_param_4[] PROGMEM = "Amb.pres.(KPa)";
PROGMEM prog_char fuelling_param_5[] PROGMEM = "MAF (kg/Hr)";
PROGMEM prog_char fuelling_param_6[] PROGMEM = "Thr.pot 1 (V)";
PROGMEM prog_char fuelling_param_7[] PROGMEM = "Thr.pot 2 (V)";
PROGMEM prog_char fuelling_param_8[] PROGMEM = "Thr.pot 3 (V)";
PROGMEM prog_char fuelling_param_9[] PROGMEM = "Thr.supp. (V)";
PROGMEM prog_char fuelling_param_10[] PROGMEM = "EGR mod.(%)";
PROGMEM prog_char fuelling_param_11[] PROGMEM = "EGR inl.(%)";
PROGMEM prog_char fuelling_param_12[] PROGMEM = "TWG (%)";
PROGMEM prog_char fuelling_param_13[] PROGMEM = "Idle spd.(rpm)";
PROGMEM prog_char fuelling_param_14[] PROGMEM = "Coolant t.(C)";
PROGMEM prog_char fuelling_param_15[] PROGMEM = "Air inl.t.(C)";
PROGMEM prog_char fuelling_param_16[] PROGMEM = "Fuel t. (C)";
PROGMEM prog_char fuelling_param_17[] PROGMEM = "Inj.bal.1";
PROGMEM prog_char fuelling_param_18[] PROGMEM = "Inj.bal.2";
PROGMEM prog_char fuelling_param_19[] PROGMEM = "Inj.bal.3";
PROGMEM prog_char fuelling_param_20[] PROGMEM = "Inj.bal.4";
PROGMEM prog_char fuelling_param_21[] PROGMEM = "Inj.bal.5";
PROGMEM const char *fuelling_params[] = { 
  fuelling_param_0, fuelling_param_1, fuelling_param_2, fuelling_param_3, fuelling_param_4,
  fuelling_param_5, fuelling_param_6, fuelling_param_7, fuelling_param_8, fuelling_param_9,
  fuelling_param_10, fuelling_param_11, fuelling_param_12, fuelling_param_13, fuelling_param_14,
  fuelling_param_15, fuelling_param_16, fuelling_param_17, fuelling_param_18, fuelling_param_19,
  fuelling_param_20, fuelling_param_21 };

char fuelling_values[22][6] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };


// Options params
PROGMEM prog_char options_param_0[] PROGMEM = "Startup mode";
PROGMEM prog_char options_param_1[] PROGMEM = "Bluetooth";
PROGMEM prog_char options_param_2[] PROGMEM = "Luminosity";
PROGMEM const char *options_params[] = { options_param_0, options_param_1, options_param_2 };

char options_values[3][6] = { "", "", "" };


// Injector codes
PROGMEM prog_char injector_code_0x00[] PROGMEM = "NC";
PROGMEM prog_char injector_code_0x01[] PROGMEM = "CN";
PROGMEM prog_char injector_code_0x02[] PROGMEM = "NG";
PROGMEM prog_char injector_code_0x03[] PROGMEM = "GN";
PROGMEM prog_char injector_code_0x04[] PROGMEM = "NL";
PROGMEM prog_char injector_code_0x05[] PROGMEM = "LN";
PROGMEM prog_char injector_code_0x06[] PROGMEM = "NN";
PROGMEM prog_char injector_code_0x07[] PROGMEM = "NN";
PROGMEM prog_char injector_code_0x08[] PROGMEM = "NB";
PROGMEM prog_char injector_code_0x09[] PROGMEM = "BN";
PROGMEM prog_char injector_code_0x0A[] PROGMEM = "NF";
PROGMEM prog_char injector_code_0x0B[] PROGMEM = "FN";
PROGMEM prog_char injector_code_0x0C[] PROGMEM = "NH";
PROGMEM prog_char injector_code_0x0D[] PROGMEM = "HB";
PROGMEM prog_char injector_code_0x0E[] PROGMEM = "BM";
PROGMEM prog_char injector_code_0x0F[] PROGMEM = "MB";
PROGMEM prog_char injector_code_0x10[] PROGMEM = "BE";
PROGMEM prog_char injector_code_0x11[] PROGMEM = "EB";
PROGMEM prog_char injector_code_0x12[] PROGMEM = "BD";
PROGMEM prog_char injector_code_0x13[] PROGMEM = "DB";
PROGMEM prog_char injector_code_0x14[] PROGMEM = "BC";
PROGMEM prog_char injector_code_0x15[] PROGMEM = "CB";
PROGMEM prog_char injector_code_0x16[] PROGMEM = "BG";
PROGMEM prog_char injector_code_0x17[] PROGMEM = "GB";
PROGMEM prog_char injector_code_0x18[] PROGMEM = "BL";
PROGMEM prog_char injector_code_0x19[] PROGMEM = "LB";
PROGMEM prog_char injector_code_0x1A[] PROGMEM = "BN";
PROGMEM prog_char injector_code_0x1B[] PROGMEM = "NB";
PROGMEM prog_char injector_code_0x1C[] PROGMEM = "BB";
PROGMEM prog_char injector_code_0x1D[] PROGMEM = "BB";
PROGMEM prog_char injector_code_0x1E[] PROGMEM = "BF";
PROGMEM prog_char injector_code_0x1F[] PROGMEM = "FB";
PROGMEM prog_char injector_code_0x20[] PROGMEM = "BH";
PROGMEM prog_char injector_code_0x21[] PROGMEM = "HF";
PROGMEM prog_char injector_code_0x22[] PROGMEM = "FM";
PROGMEM prog_char injector_code_0x23[] PROGMEM = "MF";
PROGMEM prog_char injector_code_0x24[] PROGMEM = "FE";
PROGMEM prog_char injector_code_0x25[] PROGMEM = "EF";
PROGMEM prog_char injector_code_0x26[] PROGMEM = "FD";
PROGMEM prog_char injector_code_0x27[] PROGMEM = "DF";
PROGMEM prog_char injector_code_0x28[] PROGMEM = "FC";
PROGMEM prog_char injector_code_0x29[] PROGMEM = "CF";
PROGMEM prog_char injector_code_0x2A[] PROGMEM = "FG";
PROGMEM prog_char injector_code_0x2B[] PROGMEM = "GF";
PROGMEM prog_char injector_code_0x2C[] PROGMEM = "FL";
PROGMEM prog_char injector_code_0x2D[] PROGMEM = "LF";
PROGMEM prog_char injector_code_0x2E[] PROGMEM = "FN";
PROGMEM prog_char injector_code_0x2F[] PROGMEM = "NF";
PROGMEM prog_char injector_code_0x30[] PROGMEM = "FB";
PROGMEM prog_char injector_code_0x31[] PROGMEM = "BF";
PROGMEM prog_char injector_code_0x32[] PROGMEM = "FF";
PROGMEM prog_char injector_code_0x33[] PROGMEM = "FF";
PROGMEM prog_char injector_code_0x34[] PROGMEM = "FH";
PROGMEM prog_char injector_code_0x35[] PROGMEM = "HH";
PROGMEM prog_char injector_code_0x36[] PROGMEM = "HM";
PROGMEM prog_char injector_code_0x37[] PROGMEM = "MH";
PROGMEM prog_char injector_code_0x38[] PROGMEM = "HE";
PROGMEM prog_char injector_code_0x39[] PROGMEM = "EH";
PROGMEM prog_char injector_code_0x3A[] PROGMEM = "HD";
PROGMEM prog_char injector_code_0x3B[] PROGMEM = "DH";
PROGMEM prog_char injector_code_0x3C[] PROGMEM = "HC";
PROGMEM prog_char injector_code_0x3D[] PROGMEM = "CH";
PROGMEM prog_char injector_code_0x3E[] PROGMEM = "HG";
PROGMEM prog_char injector_code_0x3F[] PROGMEM = "GH";
PROGMEM prog_char injector_code_0x40[] PROGMEM = "HL";
PROGMEM prog_char injector_code_0x41[] PROGMEM = "LH";
PROGMEM prog_char injector_code_0x42[] PROGMEM = "HN";
PROGMEM prog_char injector_code_0x43[] PROGMEM = "NH";
PROGMEM prog_char injector_code_0x44[] PROGMEM = "HB";
PROGMEM prog_char injector_code_0x45[] PROGMEM = "BH";
PROGMEM prog_char injector_code_0x46[] PROGMEM = "HF";
PROGMEM prog_char injector_code_0x47[] PROGMEM = "FH";
PROGMEM prog_char injector_code_0x48[] PROGMEM = "HH";
PROGMEM prog_char injector_code_0x49[] PROGMEM = "HA";
PROGMEM prog_char injector_code_0x4A[] PROGMEM = "AM";
PROGMEM prog_char injector_code_0x4B[] PROGMEM = "MA";
PROGMEM prog_char injector_code_0x4C[] PROGMEM = "AE";
PROGMEM prog_char injector_code_0x4D[] PROGMEM = "EA";
PROGMEM prog_char injector_code_0x4E[] PROGMEM = "AD";
PROGMEM prog_char injector_code_0x4F[] PROGMEM = "DA";
PROGMEM prog_char injector_code_0x50[] PROGMEM = "AC";
PROGMEM prog_char injector_code_0x51[] PROGMEM = "CA";
PROGMEM prog_char injector_code_0x52[] PROGMEM = "AG";
PROGMEM prog_char injector_code_0x53[] PROGMEM = "GA";
PROGMEM prog_char injector_code_0x54[] PROGMEM = "AL";
PROGMEM prog_char injector_code_0x55[] PROGMEM = "LA";
PROGMEM prog_char injector_code_0x56[] PROGMEM = "AN";
PROGMEM prog_char injector_code_0x57[] PROGMEM = "NA";
PROGMEM prog_char injector_code_0x58[] PROGMEM = "AB";
PROGMEM prog_char injector_code_0x59[] PROGMEM = "BA";
PROGMEM prog_char injector_code_0x5A[] PROGMEM = "AF";
PROGMEM prog_char injector_code_0x5B[] PROGMEM = "FA";
PROGMEM prog_char injector_code_0x5C[] PROGMEM = "AH";
PROGMEM prog_char injector_code_0x5D[] PROGMEM = "HK";
PROGMEM prog_char injector_code_0x5E[] PROGMEM = "KM";
PROGMEM prog_char injector_code_0x5F[] PROGMEM = "MK";
PROGMEM prog_char injector_code_0x60[] PROGMEM = "KE";
PROGMEM prog_char injector_code_0x61[] PROGMEM = "EK";
PROGMEM prog_char injector_code_0x62[] PROGMEM = "KD";
PROGMEM prog_char injector_code_0x63[] PROGMEM = "DK";
PROGMEM prog_char injector_code_0x64[] PROGMEM = "KC";
PROGMEM prog_char injector_code_0x65[] PROGMEM = "CK";
PROGMEM prog_char injector_code_0x66[] PROGMEM = "KG";
PROGMEM prog_char injector_code_0x67[] PROGMEM = "GK";
PROGMEM prog_char injector_code_0x68[] PROGMEM = "KL";
PROGMEM prog_char injector_code_0x69[] PROGMEM = "LK";
PROGMEM prog_char injector_code_0x6A[] PROGMEM = "KN";
PROGMEM prog_char injector_code_0x6B[] PROGMEM = "NK";
PROGMEM prog_char injector_code_0x6C[] PROGMEM = "KB";
PROGMEM prog_char injector_code_0x6D[] PROGMEM = "BK";
PROGMEM prog_char injector_code_0x6E[] PROGMEM = "KF";
PROGMEM prog_char injector_code_0x6F[] PROGMEM = "FK";
PROGMEM prog_char injector_code_0x70[] PROGMEM = "KH";
PROGMEM prog_char injector_code_0x71[] PROGMEM = "HJ";
PROGMEM prog_char injector_code_0x72[] PROGMEM = "JM";
PROGMEM prog_char injector_code_0x73[] PROGMEM = "MJ";
PROGMEM prog_char injector_code_0x74[] PROGMEM = "JE";
PROGMEM prog_char injector_code_0x75[] PROGMEM = "EJ";
PROGMEM prog_char injector_code_0x76[] PROGMEM = "JD";
PROGMEM prog_char injector_code_0x77[] PROGMEM = "DJ";
PROGMEM prog_char injector_code_0x78[] PROGMEM = "JC";
PROGMEM prog_char injector_code_0x79[] PROGMEM = "CJ";
PROGMEM prog_char injector_code_0x7A[] PROGMEM = "JG";
PROGMEM prog_char injector_code_0x7B[] PROGMEM = "GJ";
PROGMEM prog_char injector_code_0x7C[] PROGMEM = "JL";
PROGMEM prog_char injector_code_0x7D[] PROGMEM = "LJ";
PROGMEM prog_char injector_code_0x7E[] PROGMEM = "JN";
PROGMEM prog_char injector_code_0x7F[] PROGMEM = "N ";
PROGMEM const char *injector_codes[] = { 
  injector_code_0x00, injector_code_0x01, injector_code_0x02, injector_code_0x03, injector_code_0x04, injector_code_0x05, injector_code_0x06, injector_code_0x07,
  injector_code_0x08, injector_code_0x09, injector_code_0x0A, injector_code_0x0B, injector_code_0x0C, injector_code_0x0D, injector_code_0x0E, injector_code_0x0F,
  injector_code_0x10, injector_code_0x11, injector_code_0x12, injector_code_0x13, injector_code_0x14, injector_code_0x15, injector_code_0x16, injector_code_0x17,
  injector_code_0x18, injector_code_0x19, injector_code_0x1A, injector_code_0x1B, injector_code_0x1C, injector_code_0x1D, injector_code_0x1E, injector_code_0x1F,
  injector_code_0x20, injector_code_0x21, injector_code_0x22, injector_code_0x23, injector_code_0x24, injector_code_0x25, injector_code_0x26, injector_code_0x27,
  injector_code_0x28, injector_code_0x29, injector_code_0x2A, injector_code_0x2B, injector_code_0x2C, injector_code_0x2D, injector_code_0x2E, injector_code_0x2F,
  injector_code_0x30, injector_code_0x31, injector_code_0x32, injector_code_0x33, injector_code_0x34, injector_code_0x35, injector_code_0x36, injector_code_0x37,
  injector_code_0x38, injector_code_0x39, injector_code_0x3A, injector_code_0x3B, injector_code_0x3C, injector_code_0x3D, injector_code_0x3E, injector_code_0x3F,
  injector_code_0x40, injector_code_0x41, injector_code_0x42, injector_code_0x43, injector_code_0x44, injector_code_0x45, injector_code_0x46, injector_code_0x47,
  injector_code_0x48, injector_code_0x49, injector_code_0x4A, injector_code_0x4B, injector_code_0x4C, injector_code_0x4D, injector_code_0x4E, injector_code_0x4F,
  injector_code_0x50, injector_code_0x51, injector_code_0x52, injector_code_0x53, injector_code_0x54, injector_code_0x55, injector_code_0x56, injector_code_0x57,
  injector_code_0x58, injector_code_0x59, injector_code_0x5A, injector_code_0x5B, injector_code_0x5C, injector_code_0x5D, injector_code_0x5E, injector_code_0x5F,
  injector_code_0x60, injector_code_0x61, injector_code_0x62, injector_code_0x63, injector_code_0x64, injector_code_0x65, injector_code_0x66, injector_code_0x67,
  injector_code_0x68, injector_code_0x69, injector_code_0x6A, injector_code_0x6B, injector_code_0x6C, injector_code_0x6D, injector_code_0x6E, injector_code_0x6F,
  injector_code_0x70, injector_code_0x71, injector_code_0x72, injector_code_0x73, injector_code_0x74, injector_code_0x75, injector_code_0x76, injector_code_0x77,
  injector_code_0x78, injector_code_0x79, injector_code_0x7A, injector_code_0x7B, injector_code_0x7C, injector_code_0x7D, injector_code_0x7E, injector_code_0x7F };


// Fault codes texts
#ifdef _FAULT_CODES_STRINGS_
PROGMEM prog_char fault_code_void[]="Unknown";
PROGMEM prog_char fault_code_01_01[]="1-1 egr inlet throttle diagnostics (L)";
PROGMEM prog_char fault_code_01_02[]="1-2 turbocharger wastegate diagnostics (L)";
PROGMEM prog_char fault_code_01_03[]="1-3 egr vacuum diagnostics (L)";
PROGMEM prog_char fault_code_01_04[]="1-4 temperature gauge diagnostics (L)";
PROGMEM prog_char fault_code_01_05[]="1-5 driver demand problem 1 (L)";
PROGMEM prog_char fault_code_01_06[]="1-6 driver demand problem 2 (L)";
PROGMEM prog_char fault_code_01_07[]="1-7 air flow circuit (L)";
PROGMEM prog_char fault_code_01_08[]="1-8 manifold pressure circuit (L)";
PROGMEM prog_char fault_code_02_01[]="2-1 inlet air temp. circuit (L)";
PROGMEM prog_char fault_code_02_02[]="2-2 fuel temp. circuit (L)";
PROGMEM prog_char fault_code_02_03[]="2-3 coolant temp. circuit (L)";
PROGMEM prog_char fault_code_02_04[]="2-4 battery volts (L)";
PROGMEM prog_char fault_code_02_05[]="2-5 reference voltage (L)";
PROGMEM prog_char fault_code_02_06[]="2-6 ambient air temp. circuit (L)";
PROGMEM prog_char fault_code_02_07[]="2-7 driver demand supply problem (L)";
PROGMEM prog_char fault_code_02_08[]="2-8 ambient pressure circuit (L)";
PROGMEM prog_char fault_code_03_01[]="3-1 egr inlet throttle diagnostics (L)";
PROGMEM prog_char fault_code_03_02[]="3-2 turbocharger wastegate diagnostics (L)";
PROGMEM prog_char fault_code_03_03[]="3-3 egr vacuum diagnostics (L)";
PROGMEM prog_char fault_code_03_04[]="3-4 temperature gauge diagnostics (L)";
PROGMEM prog_char fault_code_03_05[]="3-5 driver demand problem 1 (L)";
PROGMEM prog_char fault_code_03_06[]="3-6 driver demand problem 2 (L)";
PROGMEM prog_char fault_code_03_07[]="3-7 air flow circuit (L)";
PROGMEM prog_char fault_code_03_08[]="3-8 manifold pressure circuit (L)";
PROGMEM prog_char fault_code_04_01[]="4-1 inlet air temp. circuit (L)";
PROGMEM prog_char fault_code_04_02[]="4-2 fuel temperature circuit (L)";
PROGMEM prog_char fault_code_04_03[]="4-3 coolant temp. circuit (L)";
PROGMEM prog_char fault_code_04_04[]="4-4 battery volts (L)";
PROGMEM prog_char fault_code_04_05[]="4-5 reference voltage (L)";
PROGMEM prog_char fault_code_04_06[]="4-6 ambient air temperature circuit (L)";
PROGMEM prog_char fault_code_04_07[]="4-7 driver demand supply problem (L)";
PROGMEM prog_char fault_code_04_08[]="4-8 ambient pressure circuit (L)";
PROGMEM prog_char fault_code_05_01[]="5-1 egr inlet throttle diagnostics (C)";
PROGMEM prog_char fault_code_05_02[]="5-2 turbocharger wastegate diagnostics (C)";
PROGMEM prog_char fault_code_05_03[]="5-3 egr vacuum diagnostics (C)";
PROGMEM prog_char fault_code_05_04[]="5-4 temperature gauge diagnostics (C)";
PROGMEM prog_char fault_code_05_05[]="5-5 driver demand problem 1 (C)";
PROGMEM prog_char fault_code_05_06[]="5-6 driver demand problem 2 (C)";
PROGMEM prog_char fault_code_05_07[]="5-7 air flow circuit (C)";
PROGMEM prog_char fault_code_05_08[]="5-8 manifold pressure circuit (C)";
PROGMEM prog_char fault_code_06_01[]="6-1 inlet air temp. circuit (C)";
PROGMEM prog_char fault_code_06_02[]="6-2 fuel temperature circuit (C)";
PROGMEM prog_char fault_code_06_03[]="6-3 coolant temp. circuit (C)";
PROGMEM prog_char fault_code_06_04[]="6-4 battery voltage problem (C)";
PROGMEM prog_char fault_code_06_05[]="6-5 reference voltage (C)";
PROGMEM prog_char fault_code_06_07[]="6-7 driver demand supply problem (C)";
PROGMEM prog_char fault_code_06_08[]="6-8 ambient pressure circuit (C)";
PROGMEM prog_char fault_code_07_01[]="7-1 cruise lamp drive over temp. (L)";
PROGMEM prog_char fault_code_07_02[]="7-2 fuel used output drive over temp. (L)";
PROGMEM prog_char fault_code_07_03[]="7-3 radiator fan drive over temp. (L)";
PROGMEM prog_char fault_code_07_04[]="7-4 active engine mounting over temp. (L)";
PROGMEM prog_char fault_code_07_05[]="7-5 turbocharger wastegate short circuit (L)";
PROGMEM prog_char fault_code_07_06[]="7-6 egr inlet throttle short circuit (L)";
PROGMEM prog_char fault_code_07_07[]="7-7 egr vacuum modulator short circuit (L)";
PROGMEM prog_char fault_code_07_08[]="7-8 temperature gauge short circuit (L)";
PROGMEM prog_char fault_code_08_01[]="8-1 air conditioning fan drive over temp. (L)";
PROGMEM prog_char fault_code_08_02[]="8-2 fuel pump drive over temp. (L)";
PROGMEM prog_char fault_code_08_03[]="8-3 tacho drive over temp. (L)";
PROGMEM prog_char fault_code_08_04[]="8-4 gearbox/abs drive over temp. (L)";
PROGMEM prog_char fault_code_08_05[]="8-5 air conditioning clutch over temp. (L)";
PROGMEM prog_char fault_code_08_06[]="8-6 mil lamp drive over temp. (L)";
PROGMEM prog_char fault_code_08_07[]="8-7 glow plug relay drive over temp. (L)";
PROGMEM prog_char fault_code_08_08[]="8-8 glowplug lamp drive over temperature (L)";
PROGMEM prog_char fault_code_09_01[]="9-1 fuel used output drive open load (L)";
PROGMEM prog_char fault_code_09_02[]="9-2 cruise lamp drive open load (L)";
PROGMEM prog_char fault_code_09_03[]="9-3 radiator fan drive open load (L)";
PROGMEM prog_char fault_code_09_04[]="9-4 active engine mounting open load (L)";
PROGMEM prog_char fault_code_09_05[]="9-5 turbocharger wastegate open load (L)";
PROGMEM prog_char fault_code_09_06[]="9-6 egr inlett throttle open load (L)";
PROGMEM prog_char fault_code_09_07[]="9-7 egr vacuum modulator open load (L)";
PROGMEM prog_char fault_code_09_08[]="9-8 temperature gauge open load (L)";
PROGMEM prog_char fault_code_10_01[]="10-1 air conditioning fan drive open load (L)";
PROGMEM prog_char fault_code_10_02[]="10-2 fuel pump drive open load (L)";
PROGMEM prog_char fault_code_10_03[]="10-3 tachometer open load (L)";
PROGMEM prog_char fault_code_10_04[]="10-4 gearbox/abs drive open load (L)";
PROGMEM prog_char fault_code_10_05[]="10-5 air conditioning clutch open load (L)";
PROGMEM prog_char fault_code_10_06[]="10-6 mil lamp drive open load (L)";
PROGMEM prog_char fault_code_10_07[]="10-7 glow plug lamp drive open load (L)";
PROGMEM prog_char fault_code_10_08[]="10-8 glow plug relay drive open load (L)";
PROGMEM prog_char fault_code_11_01[]="11-1 cruise control lamp drive over temperature (C)";
PROGMEM prog_char fault_code_11_02[]="11-2 fuel used output drive over temperature (C)";
PROGMEM prog_char fault_code_11_03[]="11-3 radiator fan drive over temperature (C)";
PROGMEM prog_char fault_code_11_04[]="11-4 active engine mounting over temperature (C)";
PROGMEM prog_char fault_code_11_05[]="11-5 turbocharger wastegate short circuit (C)";
PROGMEM prog_char fault_code_11_06[]="11-6 egr inlet throttle short circuit (C)";
PROGMEM prog_char fault_code_11_07[]="11-7 egr vacuum modulator short circuit (C)";
PROGMEM prog_char fault_code_11_08[]="11-8 temperature gauge short circuit (C)";
PROGMEM prog_char fault_code_12_01[]="12-1 air conditioning fan drive open load (C)";
PROGMEM prog_char fault_code_12_02[]="12-2 fuel pump drive open load (C)";
PROGMEM prog_char fault_code_12_03[]="12-3 tachometer open load (C)";
PROGMEM prog_char fault_code_12_04[]="12-4 gearbox/abs drive open load (C)";
PROGMEM prog_char fault_code_12_05[]="12-5 air conditioning clutch open load (C)";
PROGMEM prog_char fault_code_12_06[]="12-6 mil lamp drive open load (C)";
PROGMEM prog_char fault_code_12_07[]="12-7 glow plug relay drive open load (C)";
PROGMEM prog_char fault_code_12_08[]="12-8 glowplug relay drive open load (C)";
PROGMEM prog_char fault_code_13_01[]="13-1 cruise control lamp drive over temp. (C)";
PROGMEM prog_char fault_code_13_02[]="13-2 fuel used output drive over temp. (C)";
PROGMEM prog_char fault_code_13_03[]="13-3 radiator fan drive over temp. (C)";
PROGMEM prog_char fault_code_13_04[]="13-4 active engine mounting over temp. (C)";
PROGMEM prog_char fault_code_13_05[]="13-5 turbocharger wastegate short circuit (C)";
PROGMEM prog_char fault_code_13_06[]="13-6 egr inlet throttle short circuit (C)";
PROGMEM prog_char fault_code_13_07[]="13-7 egr vacuum modulator short circuit (C)";
PROGMEM prog_char fault_code_13_08[]="13-8 temperature gauge short circuit (C)";
PROGMEM prog_char fault_code_14_01[]="14-1 air conditioning fan drive open load (C)";
PROGMEM prog_char fault_code_14_02[]="14-2 fuel pump drive open load (C)";
PROGMEM prog_char fault_code_14_03[]="14-3 tachometer open load (C)";
PROGMEM prog_char fault_code_14_04[]="14-4 gearbox/abs drive open load (C)";
PROGMEM prog_char fault_code_14_05[]="14-5 air conditioning clutch open load (C)";
PROGMEM prog_char fault_code_14_06[]="14-6 mil lamp drive open load (C)";
PROGMEM prog_char fault_code_14_07[]="14-7 glow plug relay drive open load (C)";
PROGMEM prog_char fault_code_14_08[]="14-8 glowplug relay drive open load (C)";
PROGMEM prog_char fault_code_15_02[]="15-2 high speed crank (L)";
PROGMEM prog_char fault_code_16_02[]="16-2 high speed crank (L)";
PROGMEM prog_char fault_code_17_02[]="17-2 high speed crank (C)";
PROGMEM prog_char fault_code_19_02[]="19-2 can rx/tx error (L)";
PROGMEM prog_char fault_code_19_03[]="19-3 can tx/rx error (L)";
PROGMEM prog_char fault_code_19_06[]="19-6 noisy crank signal has been detected (L)";
PROGMEM prog_char fault_code_19_08[]="19-8 can has had reset failure (L)";
PROGMEM prog_char fault_code_20_01[]="20-1 turbocharger under boosting (L)";
PROGMEM prog_char fault_code_20_02[]="20-2 turbocharger over boosting (L)";
PROGMEM prog_char fault_code_20_04[]="20-4 egr valve stuck open (L)";
PROGMEM prog_char fault_code_20_05[]="20-5 egr valve stuck closed (L)";
PROGMEM prog_char fault_code_21_04[]="21-4 driver demand 1 out of range (L)";
PROGMEM prog_char fault_code_21_05[]="21-5 driver demand 2 out of range (L)";
PROGMEM prog_char fault_code_21_06[]="21-6 problem detected with driver demand (L)";
PROGMEM prog_char fault_code_21_07[]="21-7 inconsistencies found with driver demand (L)";
PROGMEM prog_char fault_code_21_08[]="21-8 injector trim data corrupted (L)";
PROGMEM prog_char fault_code_22_01[]="22-1 road speed missing (L)";
PROGMEM prog_char fault_code_22_03[]="22-3 vehicle accel. outside bounds of cruise control (L)";
PROGMEM prog_char fault_code_22_07[]="22-7 cruise control resume stuck closed (L)";
PROGMEM prog_char fault_code_22_08[]="22-8 cruise control set stuck closed (L)";
PROGMEM prog_char fault_code_23_01[]="23-1 excessive can bus off (C)";
PROGMEM prog_char fault_code_23_02[]="23-2 can rx/tx error (C)";
PROGMEM prog_char fault_code_23_03[]="23-3 can tx/rx error (C)";
PROGMEM prog_char fault_code_23_04[]="23-4 unable to detect remote can mode (C)";
PROGMEM prog_char fault_code_23_05[]="23-5 under boost has occurred on this trip (C)";
PROGMEM prog_char fault_code_23_06[]="23-6 noisy crack signal has been detected (C)";
PROGMEM prog_char fault_code_24_01[]="24-1 turbocharger under boosting (C)";
PROGMEM prog_char fault_code_24_02[]="24-2 turbocharger over boosting (C)";
PROGMEM prog_char fault_code_24_03[]="24-3 over boost has occurred this trip (C)";
PROGMEM prog_char fault_code_24_04[]="24-4 egr valve stuck open (C)";
PROGMEM prog_char fault_code_24_05[]="24-5 egr valve stuck closed (C)";
PROGMEM prog_char fault_code_24_07[]="24-7 problem detected with auto gear box (C)";
PROGMEM prog_char fault_code_25_04[]="25-4 driver demand 1 out of range (L)";
PROGMEM prog_char fault_code_25_05[]="25-5 driver demand 2 out of range (L)";
PROGMEM prog_char fault_code_25_06[]="25-6 problem detected with drive demand (C)";
PROGMEM prog_char fault_code_25_07[]="25-7 inconsistencies found with driver demand (C)";
PROGMEM prog_char fault_code_25_08[]="25-8 injector trim data corrupted (C)";
PROGMEM prog_char fault_code_26_01[]="26-1 road speed missing (C)";
PROGMEM prog_char fault_code_26_02[]="26-2 cruise control system problem (C)";
PROGMEM prog_char fault_code_26_03[]="26-3 vehicle accel. outside bounds for cruise control (C)";
PROGMEM prog_char fault_code_26_07[]="26-7 cruise control resume stuck closed (C)";
PROGMEM prog_char fault_code_26_08[]="26-8 cruise control set stuck closed (C)";
PROGMEM prog_char fault_code_27_01[]="27-1 inj. 1 peak charge long (L)";
PROGMEM prog_char fault_code_27_02[]="27-2 inj. 2 peck charge long (L)";
PROGMEM prog_char fault_code_27_03[]="27-3 inj. 3 peak charge long (L)";
PROGMEM prog_char fault_code_27_04[]="27-4 inj. 4 peck charge long (L)";
PROGMEM prog_char fault_code_27_05[]="27-5 inj. 5 peak charge long (L)";
PROGMEM prog_char fault_code_27_06[]="27-6 inj. 6 peck charge long (L)";
PROGMEM prog_char fault_code_27_07[]="27-7 topside switch failed post injection (L)";
PROGMEM prog_char fault_code_28_01[]="28-1 inj. 1 peak charge short (L)";
PROGMEM prog_char fault_code_28_02[]="28-2 inj. 2 peck charge short (L)";
PROGMEM prog_char fault_code_28_03[]="28-3 inj. 3 peak charge short (L)";
PROGMEM prog_char fault_code_28_04[]="28-4 inj. 4 peck charge short (L)";
PROGMEM prog_char fault_code_28_05[]="28-5 inj. 5 peak charge short (L)";
PROGMEM prog_char fault_code_28_06[]="28-6 inj. 6 peck charge short (L)";
PROGMEM prog_char fault_code_28_07[]="28-7 topside switch failed pre injection (L)";
PROGMEM prog_char fault_code_29_01[]="29-1 inj. 1 peak charge long (C)";
PROGMEM prog_char fault_code_29_02[]="29-2 inj. 2 peck charge long (C)";
PROGMEM prog_char fault_code_29_03[]="29-3 inj. 3 peak charge long (C)";
PROGMEM prog_char fault_code_29_04[]="29-4 inj. 4 peck charge long (C)";
PROGMEM prog_char fault_code_29_05[]="29-5 inj. 5 peak charge long (C)";
PROGMEM prog_char fault_code_29_06[]="29-6 inj. 6 peck charge long (C)";
PROGMEM prog_char fault_code_29_07[]="29-7 topside switch failed post injection (C)";
PROGMEM prog_char fault_code_30_01[]="30-1 inj. 1 peak charge short (C)";
PROGMEM prog_char fault_code_30_02[]="30-2 inj. 2 peck charge short (C)";
PROGMEM prog_char fault_code_30_03[]="30-3 inj. 3 peak charge short (C)";
PROGMEM prog_char fault_code_30_04[]="30-4 inj. 4 peck charge short (C)";
PROGMEM prog_char fault_code_30_05[]="30-5 inj. 5 peak charge short (C)";
PROGMEM prog_char fault_code_30_06[]="30-6 inj. 6 peck charge short (C)";
PROGMEM prog_char fault_code_30_07[]="30-7 topside switch failed pre injection (C)";
PROGMEM prog_char fault_code_31_01[]="31-1 inj. 1 open circuit (L)";
PROGMEM prog_char fault_code_31_02[]="31-2 inj. 2 open circuit (L)";
PROGMEM prog_char fault_code_31_03[]="31-3 inj. 3 open circuit (L)";
PROGMEM prog_char fault_code_31_04[]="31-4 inj. 4 open circuit (L)";
PROGMEM prog_char fault_code_31_05[]="31-5 inj. 5 open circuit (L)";
PROGMEM prog_char fault_code_31_06[]="31-6 inj. 6 open circuit (L)";
PROGMEM prog_char fault_code_32_01[]="32-1 inj. 1 short circuit (L)";
PROGMEM prog_char fault_code_32_02[]="32-2 inj. 2 short circuit (L)";
PROGMEM prog_char fault_code_32_03[]="";   // fake due to unknown downloading error
PROGMEM prog_char _fault_code_32_03[]="32-3 inj. 3 short circuit (L)";  // duplicated and renamed due to unknown downloading error
PROGMEM prog_char fault_code_32_04[]="32-4 inj. 4 short circuit (L)";
PROGMEM prog_char fault_code_32_05[]="32-5 inj. 5 short circuit (L)";
PROGMEM prog_char fault_code_32_06[]="32-6 inj. 6 short circuit (L)";
PROGMEM prog_char fault_code_33_01[]="33-1 inj. 1 open circuit (C)";
PROGMEM prog_char fault_code_33_02[]="33-2 inj. 2 open circuit (C)";
PROGMEM prog_char fault_code_33_03[]="33-3 inj. 3 open circuit (C)";
PROGMEM prog_char fault_code_33_04[]="33-4 inj. 4 open circuit (C)";
PROGMEM prog_char fault_code_33_05[]="33-5 inj. 5 open circuit (C)";
PROGMEM prog_char fault_code_33_06[]="33-6 inj. 6 open circuit (C)";
PROGMEM prog_char fault_code_34_01[]="34-1 inj. 1 short circuit (C)";
PROGMEM prog_char fault_code_34_02[]="34-2 inj. 2 short circuit (C)";
PROGMEM prog_char fault_code_34_03[]="34-3 inj. 3 short circuit (C)";
PROGMEM prog_char fault_code_34_04[]="34-4 inj. 4 short circuit (C)";
PROGMEM prog_char fault_code_34_05[]="34-5 inj. 5 short circuit (C)";
PROGMEM prog_char fault_code_34_06[]="34-6 inj. 6 short circuit (C)";
PROGMEM prog_char fault_code_35_01[]="35-1 inj. 1 partial short circuit (L)";
PROGMEM prog_char fault_code_35_02[]="35-2 inj. 2 partial short circuit (L)";
PROGMEM prog_char fault_code_35_03[]="35-3 inj. 3 partial short circuit (L)";
PROGMEM prog_char fault_code_35_04[]="35-4 inj. 4 partial short circuit (L)";
PROGMEM prog_char fault_code_35_05[]="35-5 inj. 5 partial short circuit (L)";
PROGMEM prog_char fault_code_35_06[]="35-6 inj. 6 partial short circuit (L)";
PROGMEM const char *fault_code[] = {
  fault_code_01_01, fault_code_01_02, fault_code_01_03, fault_code_01_04, fault_code_01_05, fault_code_01_06, fault_code_01_07, fault_code_01_08,
  fault_code_02_01, fault_code_02_02, fault_code_02_03, fault_code_02_04, fault_code_02_05, fault_code_02_06, fault_code_02_07, fault_code_02_08,
  fault_code_03_01, fault_code_03_02, fault_code_03_03, fault_code_03_04, fault_code_03_05, fault_code_03_06, fault_code_03_07, fault_code_03_08,
  fault_code_04_01, fault_code_04_02, fault_code_04_03, fault_code_04_04, fault_code_04_05, fault_code_04_06, fault_code_04_07, fault_code_04_08,
  fault_code_05_01, fault_code_05_02, fault_code_05_03, fault_code_05_04, fault_code_05_05, fault_code_05_06, fault_code_05_07, fault_code_05_08,
  fault_code_06_01, fault_code_06_02, fault_code_06_03, fault_code_06_04, fault_code_06_05, fault_code_void,  fault_code_06_07, fault_code_06_08,
  fault_code_07_01, fault_code_07_02, fault_code_07_03, fault_code_07_04, fault_code_07_05, fault_code_07_06, fault_code_07_07, fault_code_07_08,
  fault_code_08_01, fault_code_08_02, fault_code_08_03, fault_code_08_04, fault_code_08_05, fault_code_08_06, fault_code_08_07, fault_code_08_08,
  fault_code_09_01, fault_code_09_02, fault_code_09_03, fault_code_09_04, fault_code_09_05, fault_code_09_06, fault_code_09_07, fault_code_09_08,
  fault_code_10_01, fault_code_10_02, fault_code_10_03, fault_code_10_04, fault_code_10_05, fault_code_10_06, fault_code_10_07, fault_code_10_08,
  fault_code_11_01, fault_code_11_02, fault_code_11_03, fault_code_11_04, fault_code_11_05, fault_code_11_06, fault_code_11_07, fault_code_11_08,
  fault_code_12_01, fault_code_12_02, fault_code_12_03, fault_code_12_04, fault_code_12_05, fault_code_12_06, fault_code_12_07, fault_code_12_08,
  fault_code_13_01, fault_code_13_02, fault_code_13_03, fault_code_13_04, fault_code_13_05, fault_code_13_06, fault_code_13_07, fault_code_13_08,
  fault_code_14_01, fault_code_14_02, fault_code_14_03, fault_code_14_04, fault_code_14_05, fault_code_14_06, fault_code_14_07, fault_code_14_08,
  fault_code_void,  fault_code_15_02, fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,
  fault_code_void,  fault_code_16_02, fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,
  fault_code_void,  fault_code_17_02, fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,
  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_void,
  fault_code_void,  fault_code_19_02, fault_code_19_03, fault_code_void,  fault_code_void,  fault_code_19_06, fault_code_void,  fault_code_19_08,    
  fault_code_20_01, fault_code_20_02, fault_code_void,  fault_code_20_04, fault_code_20_05, fault_code_void,  fault_code_void,  fault_code_void,
  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_21_04, fault_code_21_05, fault_code_21_06, fault_code_21_07, fault_code_void,
  fault_code_22_01, fault_code_void,  fault_code_22_03, fault_code_void,  fault_code_void,  fault_code_void,  fault_code_22_07, fault_code_22_08,
  fault_code_23_01, fault_code_23_02, fault_code_23_03, fault_code_23_04, fault_code_23_05, fault_code_23_06, fault_code_void,  fault_code_void,
  fault_code_24_01, fault_code_24_02, fault_code_24_03, fault_code_24_04, fault_code_24_05, fault_code_void,  fault_code_24_07, fault_code_void,
  fault_code_void,  fault_code_void,  fault_code_void,  fault_code_25_04, fault_code_25_05, fault_code_25_06, fault_code_25_07, fault_code_25_08,
  fault_code_26_01, fault_code_26_02, fault_code_26_03, fault_code_void,  fault_code_void,  fault_code_void,  fault_code_26_07, fault_code_26_08,
  fault_code_27_01, fault_code_27_02, fault_code_27_03, fault_code_27_04, fault_code_27_05, fault_code_27_06, fault_code_27_07, fault_code_void,
  fault_code_28_01, fault_code_28_02, fault_code_28_03, fault_code_28_04, fault_code_28_05, fault_code_28_06, fault_code_28_07, fault_code_void,
  fault_code_29_01, fault_code_29_02, fault_code_29_03, fault_code_29_04, fault_code_29_05, fault_code_29_06, fault_code_29_07, fault_code_void,
  fault_code_30_01, fault_code_30_02, fault_code_30_03, fault_code_30_04, fault_code_30_05, fault_code_30_06, fault_code_30_07, fault_code_void,
  fault_code_31_01, fault_code_31_02, fault_code_31_03, fault_code_31_04, fault_code_31_05, fault_code_31_06, fault_code_void,  fault_code_void,
  fault_code_32_01, fault_code_32_02, _fault_code_32_03, fault_code_32_04, fault_code_32_05, fault_code_32_06, fault_code_void,  fault_code_void,
  fault_code_33_01, fault_code_33_02, fault_code_33_03, fault_code_33_04, fault_code_33_05, fault_code_33_06, fault_code_void,  fault_code_void,
  fault_code_34_01, fault_code_34_02, fault_code_34_03, fault_code_34_04, fault_code_34_05, fault_code_34_06, fault_code_void,  fault_code_void,
  fault_code_35_01, fault_code_35_02, fault_code_35_03, fault_code_35_04, fault_code_35_05, fault_code_35_06, fault_code_void,  fault_code_void };
#endif
