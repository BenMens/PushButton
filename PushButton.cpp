#include <arduino.h>

#include "PushButton.h"

int PushButton::numButtons=0;
PushButton *PushButton::buttonState[PUSH_BUTTON_MAX_BUTTON_COUNT];

PushButton::PushButton(byte pin) {
    pinMode( pin,INPUT_PULLUP);

    this->pin = pin;

    buttonState[numButtons++] = this;

    // if (useInterrupt) {
    //   pciSetup(pin);
    // }

    this->state = digitalRead(this->pin);
    this->changeTime = millis();
}

void PushButton::checkAll() {
    if (numButtons < PUSH_BUTTON_MAX_BUTTON_COUNT) {
        for (int i=0; i<numButtons; i++) {
            buttonState[i]->check();
        }
    }
}


ButtonPressType PushButton::read() {
    if ((millis() > this->changeTime)) {

        if (!this->state) {
            if (this->lastMessage == repeatedPress || this->lastMessage == firstPress) {
                this->changeTime = millis() + PUSH_BUTTON_REPEAT_INTERVAL;
                this->lastMessage = ButtonPressType::repeatedPress;
            } else {
                this->changeTime = millis() + PUSH_BUTTON_TIME_TO_REPEAT;
                this->lastMessage = ButtonPressType::firstPress;
            }
        } else {
          if (this->lastMessage == repeatedPress || this->lastMessage == firstPress) {
            this->lastMessage = ButtonPressType::release;
          }
          else {
            this->lastMessage = ButtonPressType::noPress;
          }
        }

        return this->lastMessage;
    }

    return ButtonPressType::noPress;
}

void PushButton::check() {
    if (this->state != digitalRead(this->pin)) {
        this->state = !this->state;
        this->changeTime = millis()+PUSH_BUTTON_STABLE_TIME;
    }
}
