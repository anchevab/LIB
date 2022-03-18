
#ifndef __REMOTE_CODES__
#define __REMOTE_CODES__

#include "Arduino.h"

int getButtonCode(unsigned long irCode);

// constants for buttons
#define BUTTON_ON_OFF 0
#define BUTTON_AV     1
#define BUTTON_GUIDE  2
#define BUTTON_MENU   3
#define BUTTON_INFO   4
#define BUTTON_EXIT   5
#define BUTTON_UP     6
#define BUTTON_DOWN   7
#define BUTTON_LEFT   8
#define BUTTON_RIGHT  9
#define BUTTON_OK    10
#define BUTTON_RED   11
#define BUTTON_GREEN  12
#define BUTTON_YELLOW  13
#define BUTTON_BLUE  14
#define BUTTON_VOLUME_UP  15
#define BUTTON_VOLUME_DOWN  16
#define BUTTON_MUTE  17
#define BUTTON_RETURN  18
#define BUTTON_CHANEL_UP  19
#define BUTTON_CHANNEL_DOWN  20
#define BUTTON_PROGRANM_DOWN  21
#define BUTTON_PROGRAM_UP  22
#define BUTTON_FAST_REWARD  23
#define BUTTON_FAST_FORWARD  24
#define BUTTON_STOP  25
#define BUTTON_RECORD  26
#define BUTTON_PLAY  27
#define BUTTON_PAUSE  28
#define BUTTON_1  29
#define BUTTON_2  30
#define BUTTON_3  31
#define BUTTON_4  32
#define BUTTON_5  33
#define BUTTON_6  34
#define BUTTON_7  35
#define BUTTON_8  36
#define BUTTON_9  37
#define BUTTON_0  38
#define BUTTON_TXT  39
#define BUTTON_HELP  40
//
#define NUM_BUTTONS (BUTTON_HELP - BUTTON_ON_OFF + 1)

extern const char* BUTTON_NAMES[];

extern const unsigned long IR_CODES[];



#endif
