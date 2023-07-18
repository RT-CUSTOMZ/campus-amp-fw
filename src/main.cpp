#include <Arduino.h>
#include <Wire.h>

#include "Portexpander.h"
#include "Touchpanel.h"

PortExpander *portExpander;
Touchpanel *touchpanel;

void setup() {
  uint8_t state = LOW;

  Serial.begin(115200);

  delay(1000);
  Serial.println("INIT");

  Wire.setPins(5, 4);
  Wire.begin();

  
  Serial.println("Setup Peripherals");

  portExpander = new PortExpander(&Wire);
  touchpanel = new Touchpanel(&Wire);

  Serial.println("Setup Peripherals done");

  portExpander->setPortPin(PortExpanderPin::kPinBtPause, LOW);
}

void loop() {
  static uint8_t state = LOW;
  static PortExpanderPin pin = PortExpanderPin::kPinLedAnalogInt;

  if (touchpanel->isKeyPressed(TouchpanelKey::kKeyPower)) {
    Serial.println("Power");
  } else if(touchpanel->isKeyPressed(TouchpanelKey::kKeyAnalogExt)) {
    Serial.println("Analog Ext");
  } else if(touchpanel->isKeyPressed(TouchpanelKey::kKeyAnalogInt)) {
    Serial.println("Analog Int");
  } else if(touchpanel->isKeyPressed(TouchpanelKey::kKeyBluetooth)) {
    Serial.println("Bluetooth");
  }
  delay(100);
}