#include "Touchpanel.h"
#include <functional>

Touchpanel::Touchpanel(TwoWire *pWire) {
    touch_sensor = new AT42QT2120(*pWire, kTouchpanelChangePin);
    touch_sensor->begin();
    
    //resetting the device
    touch_sensor->reset();
    delay(resetDelay);

    //triggering calibration
    touch_sensor->triggerCalibration();
    delay(calibrationLoopDelay);
    while (touch_sensor->calibrating())
    {
        delay(calibrationLoopDelay);
    }
}

Touchpanel::~Touchpanel() {
    delete touch_sensor;
}

bool Touchpanel::isKeyPressed(TouchpanelKey key) {
    AT42QT2120::Status status = touch_sensor->getStatus();
    return touch_sensor->touched(status, (uint8_t)key);
}