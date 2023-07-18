#ifndef TOUCHPANEL_H
#define TOUCHPANEL_H

#include <AT42QT2120.h>
#include <Arduino.h>
#include <Wire.h>

enum class TouchpanelKey : uint8_t {
    kKeyPower = 0u,
    kKeyAnalogExt = 1u,
    kKeyAnalogInt = 2u,
    kKeyBluetooth = 3u,
};

class Touchpanel {

    private:
    const uint8_t kTouchpanelAdress = 0x1C;
    const uint8_t kTouchpanelChangePin = 18u;

    const uint resetDelay = 2000u;
    const uint calibrationLoopDelay = 50u;

    AT42QT2120 *touch_sensor;

    void (*pinCallback_[4])(uint8_t) = {nullptr, nullptr, nullptr, nullptr};


    public:
    Touchpanel(TwoWire *pWire);
    ~Touchpanel();
    
    bool isKeyPressed(TouchpanelKey key);
    void attachChangeCallback(const AT42QT2120::Callback callback) {
        touch_sensor->attachChangeCallback(callback);
    }
};


#endif