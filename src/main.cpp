#include <Arduino.h>
#include <Wire.h>

#include "Portexpander.h"
#include "Touchpanel.h"

PortExpander *portExpander;
Touchpanel *touchpanel;

volatile bool change = false;

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

  touchpanel->attachChangeCallback([]() {
    change = true;
  });
}

void loop() {
  if(change) {
    change = false;
    if (touchpanel->isKeyPressed(TouchpanelKey::kKeyPower)) {
      Serial.println("Power");
    } else if(touchpanel->isKeyPressed(TouchpanelKey::kKeyAnalogExt)) {
      Serial.println("Analog Ext");
      portExpander->setPortPin(PortExpanderPin::kPinSelectAnalog, HIGH);
    } else if(touchpanel->isKeyPressed(TouchpanelKey::kKeyAnalogInt)) {
      Serial.println("Analog Int");
      portExpander->setPortPin(PortExpanderPin::kPinLedAnalogInt, HIGH);
    } else if(touchpanel->isKeyPressed(TouchpanelKey::kKeyBluetooth)) {
      Serial.println("Bluetooth");
      portExpander->setPortPin(PortExpanderPin::kPinSelectBt, HIGH);
    } else {
      portExpander->setPortPin(PortExpanderPin::kPinLedAnalogExt, LOW);
      portExpander->setPortPin(PortExpanderPin::kPinSelectBt, LOW);
    }
  }
}