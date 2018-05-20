#include <arduino.h>

#include "PushButton.h"

int PushButton::numButtons = 0;
PushButton *PushButton::buttons[PUSH_BUTTON_MAX_BUTTON_COUNT];


PushButton::PushButton(byte pin) {
  pinMode(pin, INPUT_PULLUP);

  this->pin = pin;
  this->state = digitalRead(this->pin);
  this->nextEvalTime = millis();

  buttons[numButtons++] = this;
}


void PushButton::loop() {
  if (numButtons < PUSH_BUTTON_MAX_BUTTON_COUNT) {
    for (int i = 0; i < numButtons; i++) {

      PushButton *b = buttons[i];

      if (b->state != digitalRead(b->pin)) {
          b->state = !b->state;
          b->nextEvalTime = millis() + PUSH_BUTTON_STABLE_TIME;
      }
    }
  }
}

char* PushButton::buttonPressTypeToString(ButtonPressType msg) {
  switch(msg) {
    case ButtonPressType::firstPress:
      return "firstPress";
      break;
    case ButtonPressType::repeatedPress:
      return "repeatedPress";
      break;
    case ButtonPressType::release:
      return "release";
      break;
    case ButtonPressType::none:
      return "none";
      break;
    default:
    return "unknown";
    break;
  }
}



ButtonPressType PushButton::read() {
  if ((millis() > this->nextEvalTime)) {

    if (!this->state) {

      if (this->lastMessage == repeatedPress || this->lastMessage == firstPress) {
          this->nextEvalTime = millis() + PUSH_BUTTON_REPEAT_INTERVAL;
          this->lastMessage = ButtonPressType::repeatedPress;
      } else {
          this->nextEvalTime = millis() + PUSH_BUTTON_TIME_TO_REPEAT;
          this->lastMessage = ButtonPressType::firstPress;
      }

    } else {

      if (this->lastMessage == repeatedPress || this->lastMessage == firstPress) {
        this->lastMessage = ButtonPressType::release;
      } else {
        this->lastMessage = ButtonPressType::none;
      }

    }

    return this->lastMessage;
  }

  return ButtonPressType::none;
}
