/*
Td5Comm.cpp -
 
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
#include <Wire.h>
#include <E24C1024.h>
#include "td5comm.h"
#include "td5strings.h"
#include "td5hmi.h"
#include "td5remote.h"

static float ambientPressure = 100.0;

extern SoftwareSerialEx obdSerial;
extern Td5Remote remote;

prog_uchar pid_0x00[] PROGMEM = { 0x81, 0x13, 0xF7, 0x81, 0x0C };        // INIT_FRAME
prog_uchar pid_0x01[] PROGMEM = { 0x02, 0x10, 0xA0, 0x00 };              // START_DIAG
prog_uchar pid_0x02[] PROGMEM = { 0x02, 0x27, 0x01, 0x00 };              // REQ_SEED
prog_uchar pid_0x03[] PROGMEM = { 0x04, 0x27, 0x02, 0x00, 0x00, 0x00 };  // SEND_KEY
prog_uchar pid_0x04[] PROGMEM = { 0x02, 0x21, 0x20, 0x00 };              // START_FUELLING
prog_uchar pid_0x05[] PROGMEM = { 0x02, 0x21, 0x09, 0x00 };              // ENGINE_RPM
prog_uchar pid_0x06[] PROGMEM = { 0x02, 0x21, 0x1A, 0x00 };              // TEMPERATURES
prog_uchar pid_0x07[] PROGMEM = { 0x02, 0x21, 0x1C, 0x00 };              // INLET_PRES_MAF
prog_uchar pid_0x08[] PROGMEM = { 0x02, 0x21, 0x10, 0x00 };              // BATTERY_VOLT
prog_uchar pid_0x09[] PROGMEM = { 0x02, 0x21, 0x23, 0x00 };              // AMBIENT_PRES
prog_uchar pid_0x0A[] PROGMEM = { 0x02, 0x21, 0x0D, 0x00 };              // VEHICLE_SPEED
prog_uchar pid_0x0B[] PROGMEM = { 0x02, 0x21, 0x1B, 0x00 };              // THROTTLE_POS
prog_uchar pid_0x0C[] PROGMEM = { 0x03, 0x30, 0xC0, 0xF0, 0x00 };        // IO_CONTROL
prog_uchar pid_0x0D[] PROGMEM = { 0x02, 0x21, 0x40, 0x00 };              // INJ_BALANCE
prog_uchar pid_0x0E[] PROGMEM = { 0x02, 0x21, 0x21, 0x00 };              // RPM_ERROR
prog_uchar pid_0x0F[] PROGMEM = { 0x02, 0x21, 0x37, 0x00 };              // EGR_MOD
prog_uchar pid_0x10[] PROGMEM = { 0x02, 0x21, 0x38, 0x00 };              // ILT_MOD
prog_uchar pid_0x11[] PROGMEM = { 0x02, 0x21, 0x38, 0x00 };              // TWG_MOD   0x38 no good: TODO find good one...
prog_uchar pid_0x12[] PROGMEM = { 0x02, 0x3E, 0x01, 0x00 };              // KEEP_ALIVE
prog_uchar pid_0x13[] PROGMEM = { 0x02, 0x21, 0x3B, 0x00 };              // FAULT_CODES
prog_uchar pid_0x14[] PROGMEM = { 0x14, 0x31, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };              // CLEAR_FAULTS


PROGMEM const byte *td5_pids[] = 
{ 
  pid_0x00, pid_0x01, pid_0x02, pid_0x03, pid_0x04, pid_0x05, pid_0x06, pid_0x07,
  pid_0x08, pid_0x09, pid_0x0A, pid_0x0B, pid_0x0C, pid_0x0D, pid_0x0E, pid_0x0F,
  pid_0x10, pid_0x11, pid_0x12, pid_0x13, pid_0x14
};

Td5Pid pidInitFrame(INIT_FRAME, 5, 5);
Td5Pid pidStartDiag(START_DIAG, 4, 3);
Td5Pid pidRequestSeed(REQ_SEED, 4, 6);
Td5Pid pidSendKey(SEND_KEY, 6, 4);
Td5Pid pidRPM(ENGINE_RPM, 4, 6, 250);
Td5Pid pidTurboPressureMaf(INLET_PRES_MAF, 4, 12, 300);
Td5Pid pidTemperatures(TEMPERATURES, 4, 20, 1000);
Td5Pid pidBatteryVoltage(BATTERY_VOLT, 4, 8, 1500);
Td5Pid pidAmbientPressure(AMBIENT_PRES, 4, 8, 2000);
Td5Pid pidStartFuelling(START_FUELLING, 4, 8);
Td5Pid pidKeepAlive(KEEP_ALIVE, 4, 3, KEEP_ALIVE_TIME);
Td5Pid pidFaultCodes(FAULT_CODES, 4, 39);
Td5Pid pidResetFaults(CLEAR_FAULTS, 22, 4);
Td5Pid pidInjectorsBalance(INJ_BALANCE, 4, 14, 500);
Td5Pid pidVehicleSpeed(VEHICLE_SPEED, 4, 5, 1000);
Td5Pid pidThrottlePosition(THROTTLE_POS, 4, 14, 500);
Td5Pid pidRPMError(RPM_ERROR, 4, 6, 1000);
Td5Pid pidEGR(EGR_MOD, 4, 6, 1000);
Td5Pid pidILT(ILT_MOD, 4, 6, 1000);
Td5Pid pidTWG(TWG_MOD, 4, 6, 1000);

///////////////////////////////////////////////////
//              Generic functions                //
///////////////////////////////////////////////////
void debug_log_byte(byte b)
{
  // say what you got:
  if (b < 16) 
  {
    Serial.print('0'); 
  }        
  Serial.print(b, HEX); 
  Serial.print(' '); 
}

void debug_log_frame(byte *datasent, byte sentlen, byte *datarecv, byte recvlen)
{
  byte i;

  for(i=0; i<sentlen; i++)
    debug_log_byte(datasent[i]);

  Serial.print(' ');  

  for(i=0; i<recvlen; i++)
    debug_log_byte(datarecv[i]);

  Serial.println();  
}

void retrieve_keys_from_eeprom(uint8_t *seed, uint8_t *key)
{
  unsigned long address;

  address = (seed[1] + (seed[0] * 256L)) * 2L;
  key[0] = EEPROM1024.read(address);
  key[1] = EEPROM1024.read(address+1);
}

///////////////////////////////////////////////////
//                 Class Td5Comm                 //
///////////////////////////////////////////////////
Td5Comm::Td5Comm()
{
  lastReceivedPidTime = 0;
  initStep = 0;
  lostFrames = 0;
  consLostFrames = 0;
  initTime = 0;
  ecuConnection = false;
  newDataAvailable = false;
}

void Td5Comm::init()
{
  // init pinouts
  pinMode(ledPin, OUTPUT);
  pinMode(K_OUT, OUTPUT);
  pinMode(K_IN, INPUT);
}

boolean Td5Comm::read_byte(byte * b)
{
  int readData;
  boolean success = true;
  byte t=0;

  //digitalWrite(ledPin, HIGH);
  while(t != READ_ATTEMPTS  && (readData=obdSerial.read())==-1) 
  {
    delay(1);
    t++;
  }
  //digitalWrite(ledPin, LOW);

  if (t >= READ_ATTEMPTS) 
  {
    success = false;
  }

  if (success)
  {
    *b = (byte) readData;
  }

  return success;
}

void Td5Comm::write_byte(byte b)
{
  //digitalWrite(ledPin, HIGH);
  obdSerial.write(b);
  delay(Td5RequestByteDelay);  // ISO requires 5-20 ms delay between bytes.
  //digitalWrite(ledPin, LOW);
}

int8_t Td5Comm::getPid(Td5Pid* pid)
{
  boolean gotData = false;
  byte responseIndex = 0;
  byte dataCaught = '\0';  
  byte dataLen = 0;
  
  if (pid->id != INIT_FRAME)
    dataLen = pid->requestFrame[0] + 2;
  else
    dataLen = 5;

  long currentTime = millis();

  if ((currentTime >= (lastReceivedPidTime + Td5RequestDelay)) && (currentTime >= (pid->lastSeenTime + pid->cycleTime)))
  {
    // Send the message
    pid->requestFrame[dataLen-1] = checksum(pid->requestFrame, dataLen-1);

    for (byte i = 0; i < dataLen; i++)
    {
      write_byte(pid->requestFrame[i]);
    }
    
    // Wait for response for 300 ms
    long waitResponseTime = currentTime + 300;
    do
    {
      // If we find any data, keep catching it until it ends
      while(read_byte(&dataCaught) && (responseIndex < pid->responseLength))
      {
        gotData = true;
        pid->responseFrame[responseIndex] = dataCaught;
        responseIndex++;
      }
    } 
    while (millis() <= waitResponseTime && !gotData);

    if (gotData && (responseIndex > 1))
    {
      lastReceivedPidTime = millis();
      pid->lastSeenTime = lastReceivedPidTime;
      consLostFrames = 0;
      #ifdef _DEBUG_        
      debug_log_frame(pid->requestFrame, dataLen, pid->responseFrame, responseIndex);
      #endif
      if(checksum(pid->responseFrame, responseIndex-1) == pid->responseFrame[responseIndex-1])      
      {
        if(pid->responseFrame[1] != 0x7F) 
        {
          return responseIndex;
        }
        else
        {
          return PID_NEGATIVE_ANSWER; // negative response
        }
      }
    }
  }
  else 
  {
    return PID_NOT_READY;
  }

  #ifdef _DEBUG_
  Serial.println(P("Lost frame detected"));
  #endif
  lostFrames += 1;
  consLostFrames += 1;
  return PID_LOST_FRAME;      
}

boolean Td5Comm::ecuIsConnected()
{
  return ecuConnection; 
}

boolean Td5Comm::newDataIsAvailable()
{
  if(newDataAvailable)
  {
    newDataAvailable = false;
    return true;
  }
  else
    return false;
}

unsigned long Td5Comm::getLastReceivedPidTime()
{
  return lastReceivedPidTime;
}

unsigned long Td5Comm::getLastReceivedPidElapsedTime()
{
  return (millis() - lastReceivedPidTime);
}

int Td5Comm::getLostFrames()
{
  return lostFrames;
};

int Td5Comm::getConsecutiveLostFrames()
{
  return consLostFrames;
};

byte Td5Comm::checksum(byte *data, byte len)
{
  byte crc=0;
  for(byte i=0; i<len; i++)
    crc=crc+data[i];
  return crc;
}

void Td5Comm::setInitStep(byte init_step)
{
  initStep = init_step;  
}

byte Td5Comm::getInitStep()
{
  return initStep;  
}

void Td5Comm::initComm()
{
  unsigned long currentTime = millis();
  
  switch (initStep)
  {
  case 0:
    // setup
    ecuConnection = false;
    initTime = currentTime + 300;
    initStep++;
    break;
  case 1:
    if (currentTime >= initTime)
    {
      // drive K line high for 300ms
      digitalWrite(K_OUT, HIGH);
      digitalWrite(ledPin, HIGH);
      initTime = currentTime + 300;
      initStep++;
    }
    break;
  case 2:
  case 3:
    if (currentTime >= initTime)
    {
      // start or stop bit
      digitalWrite(K_OUT, (initStep == 2 ? LOW : HIGH));
      digitalWrite(ledPin, (initStep == 2 ? LOW : HIGH));
      initTime = currentTime + (initStep == 2 ? 25 : 25);
      initStep++;
    }
    break;
  case 4:
    if (currentTime >= initTime)
    {
      // switch now to 10400 bauds
      obdSerial.begin(10400);

      // bit banging done, now verify connection at 10400 baud
      if (getPid(&pidInitFrame) <= 0)
      {
        digitalWrite(ledPin, LOW);
        initStep = 0;
        break;
      }

      lastReceivedPidTime = currentTime;
      initTime = currentTime + Td5RequestDelay;
      initStep++;       
    }
    break;
  case 5:
    if (currentTime >= initTime)
    {
      if (getPid(&pidStartDiag) <= 0)
      {
        initStep = 0;
        break;
      }

      lastReceivedPidTime = currentTime;
      initTime = currentTime + Td5RequestDelay;
      initStep++;       
    }
    break;
  case 6:
    if (currentTime >= initTime)
    {
      if (getPid(&pidRequestSeed) <= 0)
      {
        initStep = 0;
        break;
      }
      
      lastReceivedPidTime = currentTime;
      initTime = currentTime + Td5RequestDelay;
      initStep++;       
    }
    break;
  case 7:
    if (currentTime >= initTime)
    {
      uint8_t seed[2], key[2];
      seed[0] = pidRequestSeed.getResponseByte(3);
      seed[1] = pidRequestSeed.getResponseByte(4);
      retrieve_keys_from_eeprom(seed, key);
      pidSendKey.setRequestByte(key[0], 3);
      pidSendKey.setRequestByte(key[1], 4);
      
      if (getPid(&pidSendKey) <= 0)
      {
        initStep = 0;
        break;
      }

      lastReceivedPidTime = currentTime;
      initTime = currentTime + Td5RequestDelay;

      delay(55);
      ecuConnection = true;
      digitalWrite(ledPin, HIGH);
      initStep = 0;       
    }
    break;
  }
}

boolean Td5Comm::connectToEcu(boolean showBar)
{
  ProgBar bar(0, 3, 20, 0, 7);
  if(showBar)
  { 
    bar.show();
  }
  initStep = 0;
  do
  {
    initComm();

    if(showBar)
    { 
      bar.update(initStep);
    }
  }
  while (initStep != 0);
  
  initTime = 0;
  return ecuConnection;
}

void Td5Comm::disconnectFromEcu()
{
  obdSerial.end();
  lostFrames = 0;
  digitalWrite(ledPin, LOW);
  ecuConnection = false; 
}

void Td5Comm::fuellingCycle()
{
  if(getPid(&pidRPM) > 0)
  {
    dtostrf(pidRPM.getlValue(), 5, 0, fuelling_values[1]);
    newDataAvailable = true;
    return;
  }

  if(getPid(&pidInjectorsBalance) > 0)
  {
    sprintf(fuelling_values[17], P("%5d"), pidInjectorsBalance.getulValue(0));
    sprintf(fuelling_values[18], P("%5d"), pidInjectorsBalance.getulValue(1));
    sprintf(fuelling_values[19], P("%5d"), pidInjectorsBalance.getulValue(2));
    sprintf(fuelling_values[20], P("%5d"), pidInjectorsBalance.getulValue(3));
    sprintf(fuelling_values[21], P("%5d"), pidInjectorsBalance.getulValue(4)); 
    return;
  }

  if(getPid(&pidTurboPressureMaf) > 0)
  {
    dtostrf((pidTurboPressureMaf.getfValue(0) - ambientPressure), 5, 2, fuelling_values[3]);
    dtostrf(pidTurboPressureMaf.getfValue(2), 5, 1, fuelling_values[5]);
    return;
  }

  if(getPid(&pidTemperatures) > 0)
  {
    dtostrf(pidTemperatures.getfValue(0), 5, 1, fuelling_values[14]);
    dtostrf(pidTemperatures.getfValue(1), 5, 1, fuelling_values[15]);
    dtostrf(pidTemperatures.getfValue(3), 5, 1, fuelling_values[16]);    
    return;
  }

  if(getPid(&pidThrottlePosition) > 0)
  {
    dtostrf(pidThrottlePosition.getfValue(0), 5, 3, fuelling_values[6]);
    dtostrf(pidThrottlePosition.getfValue(1), 5, 3, fuelling_values[7]);
    dtostrf(pidThrottlePosition.getfValue(2), 5, 3, fuelling_values[8]);
    dtostrf(pidThrottlePosition.getfValue(4), 5, 3, fuelling_values[9]);
    return;
  }

  if(getPid(&pidVehicleSpeed) > 0)
  {
    sprintf(fuelling_values[0], P("%5d"), pidVehicleSpeed.getbValue(0));
    return;
  }

  if(getPid(&pidBatteryVoltage) > 0)
  {
    dtostrf(pidBatteryVoltage.getfValue(), 5, 1, fuelling_values[2]);
    return;
  }
  
  if(getPid(&pidRPMError) > 0)
  {
    sprintf(fuelling_values[13], P("%5d"), pidRPMError.getulValue());
    return;
  }  

  if(getPid(&pidAmbientPressure) > 0)
  {
    ambientPressure = pidAmbientPressure.getfValue(1);
    dtostrf(pidAmbientPressure.getfValue(1), 5, 2, fuelling_values[4]);
    return;
  }  

  if(getPid(&pidEGR) > 0)
  {
    dtostrf(pidEGR.getfValue(), 5, 1, fuelling_values[10]);
    return;
  }

  if(getPid(&pidILT) > 0)
  {
    dtostrf(pidILT.getfValue(), 5, 1, fuelling_values[11]);
    return;
  }

/*
  if(getPid(&pidTWG) > 0)
  {
    dtostrf(pidTWG.getfValue(), 5, 1, fuelling_values[12]);
    return;
  }
*/
}


void Td5Comm::instrumentCycle()
{
  if(getPid(&pidRPM) > 0)
  {
    print_pid(0, 0, P("RPM"), pidRPM.getlValue(), 0);
    return;
  }

  if(getPid(&pidTurboPressureMaf) > 0)
  {
    print_pid(0, 1, P("TbP"), ((pidTurboPressureMaf.getfValue(0) - ambientPressure) > 0 ? (pidTurboPressureMaf.getfValue(0) - ambientPressure) : 0.0), 2);
    print_pid(10, 2, P("MAF"), pidTurboPressureMaf.getfValue(2), 1);
    return;
  }

  if(getPid(&pidTemperatures) > 0)
  {
    print_pid(10, 0, P("CoT"), pidTemperatures.getfValue(0), 1);
    print_pid(0, 3, P("InT"), pidTemperatures.getfValue(1), 1);
    print_pid(10, 3, P("FlT"), pidTemperatures.getfValue(3), 1);
    return;
  }

  if(getPid(&pidBatteryVoltage) > 0)
  {
    print_pid(10, 1, P("BtV"), pidBatteryVoltage.getfValue(), 1);
    return;
  }

  if(getPid(&pidAmbientPressure) > 0)
  {
    ambientPressure = pidAmbientPressure.getfValue(1);
    print_pid(0, 2, P("InP"), ambientPressure, 2);
    return;
  }
}


int Td5Comm::getFaultCodes()
{
  faultCodesCount = 0;
 
  if(getPid(&pidFaultCodes) > 0)
  {
    for(int i=0;i<35;i++)
    {
      byte fault_code_byte = 0;
      fault_code_byte = pidFaultCodes.getResponseByte(i+3);
      for(int j=0;j<=7;j++)
      {
        if(bitRead(fault_code_byte,j))
        {
          faultCodesCount += 1;
        }        
      }
    }
    return faultCodesCount;
  }
  return -1;
}

int Td5Comm::getFaultCode(int index)
{
  int fault_codes_cnt = 0;
  byte fault_code_byte = 0;

  if(index < MAX_FAULT_CODE)
  {
    for(int i=0;i<35;i++)
    {
      fault_code_byte = pidFaultCodes.getResponseByte(i+3);
      for(int j=0;j<=7;j++)
      {
        if(bitRead(fault_code_byte,j))
        {
          if(fault_codes_cnt == index)
          {
            return ((i*8)+j);   
          }
          else
          {
            fault_codes_cnt += 1;
          }
        }        
      }
    }
  }
  return -1;  
}

int8_t Td5Comm::resetFaults()
{
  return getPid(&pidResetFaults);
}


///////////////////////////////////////////////////
//                 Class Td5Pid                  //
///////////////////////////////////////////////////
Td5Pid::Td5Pid(byte ID, byte reqlen, byte resplen, long cycletime)
{
  id = ID;
  cycleTime = cycletime;
  lastSeenTime = 0;
  
  responseLength = resplen;  

  requestFrame= (byte *)malloc(sizeof(byte) * reqlen);
  memcpy_P(requestFrame, (byte*)pgm_read_word(&(td5_pids[id])),reqlen);
  responseFrame = (byte *)malloc(sizeof(byte) * resplen);
}

boolean Td5Pid::getValue(float *fvalue, byte index)
{
  boolean dataValid = false;
  uint16_t value;
  
  switch(id)
  {
    case AMBIENT_PRES:
      value = (uint16_t)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      *fvalue = (float) value / 10000.0;
      dataValid = true;
      break;
    case TEMPERATURES:     // 1/10 Celsius degrees
      value = (uint16_t)(((responseFrame[3 + (index * 4)] * 256L) + responseFrame[4 + (index * 4)]) - 2732L);
      *fvalue = (float) value / 10.0;
      dataValid = true;
      break;
    case INLET_PRES_MAF:   // 1/10000 bar
      value = (uint16_t)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      switch(index)
      {
        case 0:
        case 1:
          *fvalue = (float) value / 10000.0;    
          break;
        case 2:
        case 3:
          *fvalue = (float) value / 10.0;    
          break;
      }
      dataValid = true;
      break;
    case BATTERY_VOLT:     // 1/1000 Volt
      value = (uint16_t)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      *fvalue = (float) value / 1000.0;
      dataValid = true;
      break;
    case THROTTLE_POS:     // 1/1000 Volt   
      value = (uint16_t)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      *fvalue = (float) value / 1000.0;
      dataValid = true;
      break;
    case EGR_MOD:         // %   
    case ILT_MOD:         // %   
    case TWG_MOD:         // %   
      value = (uint16_t)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      *fvalue = (float) value / 10.0;
      dataValid = true;
      break;

    default: // return value incompatible with this pid
      *fvalue = 0.0;
      dataValid = false;
      break;
  }

  return dataValid;
}

float Td5Pid::getfValue(byte index)
{
  uint16_t value;
  
  switch(id)
  {
    case AMBIENT_PRES:
      value = (uint16_t)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      return ((float) value / 10000.0);
    case TEMPERATURES:     // 1/10 Celsius degrees
      value = (uint16_t)(((responseFrame[3 + (index * 4)] * 256L) + responseFrame[4 + (index * 4)]) - 2732L);
      return ((float) value / 10.0);
    case INLET_PRES_MAF:   // 1/10000 bar
      value = (uint16_t)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      switch(index)
      {
        case 0:
        case 1:
          return ((float) value / 10000.0);    
        case 2:
        case 3:
          return ((float) value / 10.0);    
      }
    case BATTERY_VOLT:     // 1/1000 Volt
      value = (uint16_t)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      return ((float) value / 1000.0);
    case THROTTLE_POS:     // 1/1000 Volt   
      value = (uint16_t)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      return ((float) value / 1000.0);
    case EGR_MOD:         // %   
    case ILT_MOD:         // %   
    case TWG_MOD:         // %       
      value = (uint16_t)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      return ((float) value / 1000.0);

    default: // return value incompatible with this pid
      return 0.0;
  }
}


boolean Td5Pid::getValue(uint16_t *value, byte index)
{
  boolean dataValid = false;
  
  switch(id)
  {
    case ENGINE_RPM:       // rpm
      *value = (uint16_t)((responseFrame[3] * 256L) + responseFrame[4]);
      dataValid = true;
      break;
    case RPM_ERROR:       // rpm
      *value = (uint16_t)((responseFrame[3] * 256L) + responseFrame[4]);
      dataValid = true;
      break;

    default: // return value incompatible with this pid
      *value = 0L;
      dataValid = false;
      break;
  }

  return dataValid;
}


boolean Td5Pid::getValue(int *value, byte index)
{
  boolean dataValid = false;
  
  switch(id)
  {
    case INJ_BALANCE:       // injectors balance
      *value = (int)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      dataValid = true;
      break;

    default: // return value incompatible with this pid
      *value = 0;
      dataValid = false;
      break;
  }

  return dataValid;
}


uint16_t Td5Pid::getulValue(byte index)
{
  switch(id)
  {
    case ENGINE_RPM:       // rpm
      return((uint16_t)((responseFrame[3] * 256L) + responseFrame[4]));
      break;
    case RPM_ERROR:       // rpm
      return((uint16_t)((responseFrame[3] * 256L) + responseFrame[4]));
      break;
    case INJ_BALANCE:       // injectors balance
      return(int)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      break;      

    default: // return value incompatible with this pid
      return 0L;
  }
}

int16_t Td5Pid::getlValue(byte index)
{
  switch(id)
  {
    case ENGINE_RPM:       // rpm
      return(int16_t)((responseFrame[3] * 256L) + responseFrame[4]);
      break;
    case RPM_ERROR:       // rpm
      return(int16_t)((responseFrame[3] * 256L) + responseFrame[4]);
      break;
    case INJ_BALANCE:       // injectors balance
      return(int16_t)((responseFrame[3 + (index * 2)] * 256L) + responseFrame[4 + (index * 2)]);
      break;      

    default: // return value incompatible with this pid
      return 0L;
  }
}

byte Td5Pid::getbValue(byte index)
{
  switch(id)
  {
    case VEHICLE_SPEED:       // vehicle speed
      return((byte)(responseFrame[3]));

    default: // return value incompatible with this pid
      return 0;
  }
}

void Td5Pid::setRequestByte(byte value, byte pos)
{
  requestFrame[pos] = value;    
}

byte Td5Pid::getResponseByte(byte pos)
{
  return responseFrame[pos];    
}



