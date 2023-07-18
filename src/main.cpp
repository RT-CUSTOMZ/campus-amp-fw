#include <Arduino.h>
#include <Wire.h>

#include "Portexpander.h"

PortExpander portExpander(&Wire);

void setup() {
  uint8_t state = LOW;

  Serial.begin(115200);

  delay(1000);
  Serial.println("INIT");

  Wire.setPins(5, 4);
  Wire.setClock(10000);
  Wire.begin();

  portExpander.setPortPin(PortExpanderPin::kPinSelectBt, LOW);
  portExpander.setPortPin(PortExpanderPin::kPinSelectAnalog, LOW);
  portExpander.setPortPin(PortExpanderPin::kPinAmpShutdown, LOW);
  portExpander.setPortPin(PortExpanderPin::kPinPinNotAmpMute, HIGH);

  portExpander.setPortPin(PortExpanderPin::kPinAmpGain0, LOW);
  portExpander.setPortPin(PortExpanderPin::kPinAmpGain1, LOW);

  portExpander.setPortPin(PortExpanderPin::kPinBtMute, HIGH);
  portExpander.setPortPin(PortExpanderPin::kPinBtNext, HIGH);
  portExpander.setPortPin(PortExpanderPin::kPinBtOnOff, HIGH);
  portExpander.setPortPin(PortExpanderPin::kPinBtPause, HIGH);
  portExpander.setPortPin(PortExpanderPin::kPinBtPrev, HIGH);

  portExpander.setPortPin(PortExpanderPin::kPinSelectBt, HIGH);

  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, LOW);
}

void loop() {
  // static uint8_t state = LOW;
  // static PortExpanderPin pin = PortExpanderPin::kPinLedAnalogInt;

  // portExpander.setPortPin(PortExpanderPin::kPinLedBt, HIGH);
  // portExpander.setPortPin(PortExpanderPin::kPinLedAnalogInt, HIGH);
  // portExpander.setPortPin(PortExpanderPin::kPinLedAnalogExt, HIGH);

  // portExpander.setPortPin(pin, state);

  // if (state == LOW) {
  //   state == HIGH;
  //   portExpander.setPortPin(PortExpanderPin::kPinAmpShutdown, HIGH);
  // } else {
  //   state == LOW;
  //   portExpander.setPortPin(PortExpanderPin::kPinAmpShutdown, LOW);
  // }

  // pin = (PortExpanderPin)(((uint8_t)pin) + 1);

  // if (PortExpanderPin::kEndMarker == pin) {
  //   pin = PortExpanderPin::kPinLedAnalogInt;
  // }

  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, HIGH);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, LOW);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, HIGH);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, LOW);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, HIGH);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, LOW);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, HIGH);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, LOW);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, HIGH);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, LOW);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, HIGH);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, LOW);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, HIGH);
  // delay(100);
  // portExpander.setPortPin(PortExpanderPin::kPinBtPause, LOW);
  // delay(100);

  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 80; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    } else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
    break;
  }

  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);  // wait 5 seconds for next scan
}