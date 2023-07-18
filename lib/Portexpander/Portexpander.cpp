#include "Portexpander.h"

PortExpander::PortExpander(TwoWire *pWire) {
  portExpander1_ = new PCF8574(pWire, kPort1Adress);
  portExpander2_ = new PCF8574(pWire, kPort2Adress);

  portExpander1_->pinMode(0, OUTPUT, LOW);
  portExpander1_->pinMode(1, OUTPUT, LOW);
  portExpander1_->pinMode(2, OUTPUT, LOW);
  portExpander1_->pinMode(3, OUTPUT, LOW);
  portExpander1_->pinMode(4, OUTPUT, LOW);
  portExpander1_->pinMode(5, OUTPUT, LOW);
  portExpander1_->pinMode(6, OUTPUT, LOW);
  portExpander1_->pinMode(7, OUTPUT, LOW);

  portExpander2_->pinMode(0, OUTPUT, LOW);
  portExpander2_->pinMode(1, OUTPUT, LOW);
  portExpander2_->pinMode(2, OUTPUT, LOW);
  portExpander2_->pinMode(3, OUTPUT, LOW);
  portExpander2_->pinMode(4, OUTPUT, LOW);
  portExpander2_->pinMode(5, OUTPUT, LOW);
  portExpander2_->pinMode(6, OUTPUT, LOW);
  portExpander2_->pinMode(7, OUTPUT, LOW);

  initPortPins();
}

void PortExpander::initPortPins(void) {
  portExpander2_->digitalWrite(5, HIGH);
  portExpander2_->digitalWrite(6, HIGH);
  portExpander2_->digitalWrite(7, HIGH);

  portExpander1_->digitalWrite(0, HIGH);
  portExpander1_->digitalWrite(0, HIGH);
}

void PortExpander::setPortPin(PortExpanderPin pin, uint8_t value) {
  uint8_t portPin = static_cast<uint8_t>(pin);

  switch (pin) {
    case PortExpanderPin::kPinAmpShutdown:
    case PortExpanderPin::kPinPinNotAmpMute:
    case PortExpanderPin::kPinAmpGain0:
    case PortExpanderPin::kPinAmpGain1:
    case PortExpanderPin::kPinSelectAnalog:
    case PortExpanderPin::kPinSelectBt:
      portExpander1_->digitalWrite(portPin, value);
      break;

    case PortExpanderPin::kPinBtPause:
    case PortExpanderPin::kPinBtNext:
    case PortExpanderPin::kPinBtPrev:
    case PortExpanderPin::kPinBtOnOff:
    case PortExpanderPin::kPinBtMute:
    case PortExpanderPin::kPinLedAnalogInt:
    case PortExpanderPin::kPinLedAnalogExt:
    case PortExpanderPin::kPinLedBt:
      portPin = portPin - 10;
      portExpander2_->digitalWrite(portPin, value);
      break;

    default:
      break;
  }
}

uint8_t PortExpander::readPortPin(PortExpanderPin pin) {
  uint8_t portPin = static_cast<uint8_t>(pin);
  uint8_t returnValue = 0;

  switch (pin) {
    case PortExpanderPin::kPinAmpShutdown:
    case PortExpanderPin::kPinPinNotAmpMute:
    case PortExpanderPin::kPinAmpGain0:
    case PortExpanderPin::kPinAmpGain1:
    case PortExpanderPin::kPinSelectAnalog:
    case PortExpanderPin::kPinSelectBt:
      returnValue = portExpander1_->digitalRead(portPin);
      break;

    case PortExpanderPin::kPinBtPause:
    case PortExpanderPin::kPinBtNext:
    case PortExpanderPin::kPinBtPrev:
    case PortExpanderPin::kPinBtOnOff:
    case PortExpanderPin::kPinBtMute:
    case PortExpanderPin::kPinLedAnalogInt:
    case PortExpanderPin::kPinLedAnalogExt:
    case PortExpanderPin::kPinLedBt:
      portPin = portPin - 10;
      returnValue = portExpander2_->digitalRead(portPin);
      break;

    default:
      break;
  }

  return returnValue;
}
