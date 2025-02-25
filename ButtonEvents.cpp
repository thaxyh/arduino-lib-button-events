#include "ButtonEvents.h"
#include "Timers.h"

ButtonEvents::ButtonEvents()
{
    _onButtonClick = nullptr;
    _onButtonHoldInit = nullptr;
    _onButtonHold = nullptr;
    _onButtonHoldRelease = nullptr;
}

void ButtonEvents::attachOnButtonClick(void (*func)(void))
{
    _onButtonClick = func;
}

void ButtonEvents::attachOnButtonHoldInit(void (*func)(void))
{
    _onButtonHoldInit = func;
}

void ButtonEvents::attachOnButtonHold(void (*func)(void))
{
    _onButtonHold = func;
}

void ButtonEvents::attachOnButtonHoldRelease(void (*func)(void))
{
    _onButtonHoldRelease = func;
}

void ButtonEvents::buttonPressed()
{
    if (_debounceTimer.available() && _previousClickState != 1)
    {
        _debounceTimer.restart();

        buttonDetectHoldTimer.begin(400);

        _previousClickState = 1;
    }
}

void ButtonEvents::buttonReleased()
{
    if (_debounceTimer.available() && _previousClickState != 0)
    {
        _debounceTimer.restart();

        buttonDetectHoldTimer.begin(0);  // stop
        buttonHoldTickInterval.begin(0); // stop

        if (isButtonHeld)
        {
            isButtonHeld = false;

            if (_onButtonHoldRelease != nullptr)
            {
                _onButtonHoldRelease();
            }
        }
        else
        {
            if (_onButtonClick != nullptr)
            {
                _onButtonClick();
            }
        }

        _previousClickState = 0;
    }
}

void ButtonEvents::update()
{
    if (buttonDetectHoldTimer.available())
    {
        if (_onButtonHoldInit != nullptr)
        {
            _onButtonHoldInit();
        }

        if (_onButtonHold != nullptr)
        {
            _onButtonHold();
        }

        isButtonHeld = true;

        buttonDetectHoldTimer.begin(0); // stop
        buttonHoldTickInterval.begin(200);
    }

    if (buttonHoldTickInterval.available())
    {
        if (_onButtonHold != nullptr)
        {
            _onButtonHold();
        }

        buttonHoldTickInterval.restart();
    }
}

void ButtonEvents::begin()
{
    _debounceTimer.begin(20);
}
