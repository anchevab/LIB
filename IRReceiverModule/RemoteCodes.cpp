#include "Arduino.h"
#include "RemoteCodes.h"

 const char* BUTTON_NAMES[] = {
"ON_OFF",
"AV",
"GUIDE",
"MENU",
"INFO",
"EXIT",
"UP",
"DOWN",
"LEFT",
"RIGHT",
"OK",
"RED",
"GREEN",
"YELLOW",
"BLUE",
"VOLUME_UP",
"VOLUME_DOWN",
"MUTE",
"RETURN",
"CHANEL_UP",
"CHANNEL_DOWN",
"PROGRANM_DOWN",
"PROGRAM_UP",
"FAST_REWARD",
"FAST_FORWARD",
"STOP",
"RECORD",
"PLAY",
"PAUSE",
"1",
"2",
"3",
"4",
"5",
"6",
"7",
"8",
"9",
"0",
"TXT",
"HELP"
};

const unsigned long IR_CODES[] = {
  0xC,
  0x80C,
  0x38,
  0x838,
  0x55838E0F,
  0x8B3A8D5E,
  0xBFB8F2FE,
  0xD9F9700B,
  0xE0C77F29,
  0x59C5D2A8,
  0x3AA23BC4,
  0x56C2C349,
  0xAC516266,
  0xE5139CA7,
  0xAD5163FB,
  0xE4139B12,
  0xDB9D3097,
  0xBE15326E,
  0x9FA96F,
  0x9912B99A,
  0xB411F6DE,
  0xDD53082F,
  0x1C102884,
  0x4B995E59,
  0xE050BDE6,
  0xEF4EDF53,
  0xDF50BC53,
  0xF04EE0E6,
  0x8533B77,
  0x5F564B6A,
  0x810,
  0x10,
  0x811,
  0x11,
  0x80D,
  0xD,
  0x822,
  0x22,
  0x820,
  0x20,
  0x821,
  0x21,
  0x83C,
  0x3C,
  0x80F,
  0xF,
  0x829,
  0x29,
  0x82B,
  0x2B,
  0x7143776E,
  0xC949DA63,
  0x4DA81859,
  0xCAA85220,
  0x82D56E6A,
  0x4C73404F,
  0x29616B83,
  0x35FAB762,
  0x801,
  0x1,
  0x802,
  0x2,
  0x803,
  0x3,
  0x804,
  0x4,
  0x805,
  0x5,
  0x806,
  0x6,
  0x807,
  0x7,
  0x8,
  0x808,
  0x809,
  0x9,
  0x0,
  0x800,
  0xF280BC5B,
  0xAD8C62D2,
  0xA,
  0x80A,
};

int getButtonCode(unsigned long irCode) {
  int i;
  for (i = 0; i < NUM_BUTTONS * 2; i++) {
    if (IR_CODES[i] == irCode) {
      return i >> 1;
    }
  }
  return -1;
};

