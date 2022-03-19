# Seeed grove w600 UART wifi[![Build Status](https://travis-ci.com/Seeed-Studio/Grove_w600.svg?branch=master)](https://travis-ci.com/Seeed-Studio/Grove_w600)

## Introduction
This library is intended to control the w600 wifi module from Arduino via AT commands. I have substantially re-written the original grove code to reduce dynamic memory allocation (particularly the use of String objects). 

#### Core functionality:
   - genderic function to send AT commands (sendAT)
   - helper functions built on top of this to enable connecting the module to a wifi access point and posing data via http. 

The Air602 is a 2.4G Wi-Fi module based on the embedded Wi-Fi SoC chip (W600) with a  12-pin Stamp Hole Expansion Interface. 

The air602 UART wifi module receive AT command,So arduino board can control it via UART port.  

## Notice
* Since atmega328(like arduino UNO) has only one serial port,The library use hardware serial port to output log info,and control the Air602 via softserial(2,3)，So the grove cable should attach to (D2,D3) port.  

* When using the samd board(like arduino zero,seeeduino cortex M0+),the SerialUSB for printing log info.The Serial(defined in library)for send AT command.  

* By default, The arduino board outputs the instruction info while sending AT command to air602 wifi module,user can close it in file:ATSerial.h,change the DEBUG_EN from 1 to 0.


* The sta_http_get_lcd_display example does not support arduino UNO(Actually all boards which based on atmega328) since it only  has a small serial buffer.

***
This software is written by downey  for seeed studio<br>
Email:dao.huang@seeed.cc
and modified by finn lattimore
and is licensed under [The MIT License](http://opensource.org/licenses/mit-license.php). Check License.txt for more information.<br>



Contributing to this software is warmly welcomed. You can do this basically by<br>
[forking](https://help.github.com/articles/fork-a-repo), committing modifications and then [pulling requests](https://help.github.com/articles/using-pull-requests) (follow the links above<br>
for operating guide). Adding change log and your contact into file header is encouraged.<br>
Thanks for your contribution.

Seeed Studio is an open hardware facilitation company based in Shenzhen, China. <br>
Benefiting from local manufacture power and convenient global logistic system, <br>
we integrate resources to serve new era of innovation. Seeed also works with <br>
global distributors and partners to push open hardware movement.<br>



