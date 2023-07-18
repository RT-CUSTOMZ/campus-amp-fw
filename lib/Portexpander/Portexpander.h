#ifndef PORTEXPANDER_H
#define PORTEXPANDER_H

#include <Arduino.h>
#include <PCF8574.h>
#include <Wire.h>

enum class PortExpanderPin {
  kPinAmpShutdown = 0u,
  kPinPinNotAmpMute = 1u,
  kPinAmpGain0 = 2u,
  kPinAmpGain1 = 3u,
  kPinSelectAnalog = 4u,
  kPinSelectBt = 5u,
  kPinBtPause = 10u,
  kPinBtNext = 11u,
  kPinBtPrev = 12u,
  kPinBtOnOff = 13u,
  kPinBtMute = 14u,
  kPinLedAnalogInt = 15u,
  kPinLedAnalogExt = 16u,
  kPinLedBt = 17u,
  kEndMarker = 18u
};

class PortExpander {
 private:
  const uint8_t kPort1Adress = 0x20;
  const uint8_t kPort2Adress = 0x21;

  PCF8574 *portExpander1_;
  PCF8574 *portExpander2_;

  void initPortPins(void);

 public:
  PortExpander(TwoWire *pWire);

  void setPortPin(PortExpanderPin pin, uint8_t value);

  uint8_t readPortPin(PortExpanderPin pin);
};

#endif
