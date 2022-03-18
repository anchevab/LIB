// IR Receiver Module
// Runs on Arduino Pro Mini


#include "Arduino.h"
#include <IRremote.h>
#include "RemoteCodes.h"

int RECV_PIN = 11;
decode_results results;
IRrecv irrecv(RECV_PIN);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) {
    // decode results.value to button code
    int buttonCode = getButtonCode(results.value);
    // send code trough Serial
    Serial.println(buttonCode, DEC);
    // Receive the next value
    irrecv.resume(); 
    }

}
