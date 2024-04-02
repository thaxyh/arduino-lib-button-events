#include "Timers.h"

#ifndef __BUTTON_EVENTS_H
#define __BUTTON_EVENTS_H

class ButtonEvents
{
private:
    void (*_onButtonClick)(void);
    // void (*_onButtonDoubleClick)(void);
    void (*_onButtonHoldInit)(void);
    void (*_onButtonHold)(void);
    void (*_onButtonHoldRelease)(void);
    Timer buttonDetectHoldTimer;
    Timer buttonHoldTickInterval;

    bool isButtonHeld = false;

public:
    ButtonEvents();
    void attachOnButtonClick(void (*func)(void));
    // void attachOnButtonDoubleClick(void (*func)(void));
    void attachOnButtonHoldInit(void (*func)(void));
    void attachOnButtonHold(void (*func)(void));
    void attachOnButtonHoldRelease(void (*func)(void));
    void buttonPressed();
    void buttonReleased();
    void update();
};

#endif
