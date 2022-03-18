// OLED_StatusIcons_16x16_Icons_Demo
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my OLED_StatusIcons library.
//
// This program requires OLED_StatusIcons as well as my OLED_I2C.
//
// Please refer to the OLED_I2C library documentation and examples for 
// information on connecting the OLED display.
//

#include <OLED_I2C.h>
#include <OLED_StatusIcons.h>

OLED              myOLED(SDA, SCL, 8);
OLED_StatusIcons  myIcons(&myOLED, ICONSIZE_16X16, ICONPOSITION_TOP_RIGHT);

extern uint8_t batteryh0_16[];
extern uint8_t batteryh1_16[];
extern uint8_t batteryh2_16[];
extern uint8_t batteryh3_16[];
extern uint8_t batteryh4_16[];
extern uint8_t batteryhc_16[];
extern uint8_t ethernet_16[];
extern uint8_t fan_16[];
extern uint8_t mail_16[];
extern uint8_t power_16[];
extern uint8_t wireless0_16[];
extern uint8_t wireless1_16[];
extern uint8_t wireless2_16[];
extern uint8_t wireless3_16[];

// Declaring a few constants makes it easier to remember which position
// we would like to put the various icons in.
const byte icon_position_power    = 0;
const byte icon_position_battery  = 1;
const byte icon_position_mail     = 2;
const byte icon_position_wireless = 3;
const byte icon_position_ethernet = 4;
const byte icon_position_fan      = 5;

void setup()
{
  // Initialize our objects
  myOLED.begin();
  myIcons.begin();
  // Set the StatusIcons bar to update every 100ms instead of the default 1000ms
  myIcons.updateSpeed(100);
  // Create some icons for the status bar
  myIcons.createIcon(icon_position_power, power_16, true);  
  myIcons.createIcon(icon_position_battery, batteryh4_16, true);  
  myIcons.createIcon(icon_position_mail, mail_16);  
  myIcons.createIcon(icon_position_wireless, wireless3_16, true);  
  myIcons.createIcon(icon_position_ethernet, ethernet_16);  
  myIcons.createIcon(icon_position_fan, fan_16);  
  // Enable the display of the status bar
  myIcons.enableStatusbar();
}

void loop()
{
  // Draw a vertical bar moving across the screen
  for (int xpos = 0; xpos < 128; xpos++)
  {
    myOLED.drawLine(xpos, 16, xpos, 48);
    if (xpos == 0)
      myOLED.clrLine(127, 16, 127, 48);
    else
      myOLED.clrLine(xpos - 1, 16, xpos - 1, 48);
    switch (xpos)                                                    // When the bar is in these positions we make some changes to the icons (The actual change in the icons may be slightly out of sync as they are refreshed periodically)
    {
      case 16:                                                       // Line position 16: Enable the "mail" icon and lower the "battery voltage"
          myIcons.enableIcon(icon_position_mail);
          myIcons.changeIcon(icon_position_battery, batteryh3_16);
          break;
      case 32:                                                       // Line position 32: Disable the "mail" icon again, enable the "fan" icon and lower the "battery voltage" further
          myIcons.disableIcon(icon_position_mail);
          myIcons.enableIcon(icon_position_fan);
          myIcons.changeIcon(icon_position_battery, batteryh2_16);
          break;
      case 48:                                                       // Line position 48: Then we disable the "fan" icon again and lower the "battery voltage" even further
          myIcons.disableIcon(icon_position_fan);
          myIcons.changeIcon(icon_position_battery, batteryh1_16);
          break;
      case 64:                                                       // Line position 64: Change the "wireless" icon to indicate "No reception", enable the "ethernet" icon and lower the "battery voltage" to empty
          myIcons.changeIcon(icon_position_wireless, wireless0_16);    
          myIcons.enableIcon(icon_position_ethernet);
          myIcons.changeIcon(icon_position_battery, batteryh0_16);
         break;
      case 80:                                                       // Line position 80: Change the "wireless" icon to indicate "Low reception" and "start charging the battery"
          myIcons.changeIcon(icon_position_wireless, wireless1_16);    
          myIcons.changeIcon(icon_position_battery, batteryhc_16);
          break;
      case 96:                                                       // Line position 96: Change the "wireless" icon to indicate "Medium reception"
          myIcons.changeIcon(icon_position_wireless, wireless2_16);    
          break;
      case 112:                                                      // Line position 112: Change the "wireless" icon to indicate "Full reception" again and "stop charging the battery" and display the "full battery" icon
          myIcons.changeIcon(icon_position_wireless, wireless3_16);   
          myIcons.changeIcon(icon_position_battery, batteryh4_16);
          break; 
      case 127:                                                      // Line position 127: Disable the "ethernet" icon again (since we have full wireless reception again :) )
          myIcons.disableIcon(icon_position_ethernet);
          break;
    }
    myOLED.update();
    delay(25);
  }
}

