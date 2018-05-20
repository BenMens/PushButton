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

char* PushButton::eventToString(ButtonEvent event) {
  switch(event) {
    case ButtonEvent::firstPress:
      return "firstPress";
      break;
    case ButtonEvent::repeatedPress:
      return "repeatedPress";
      break;
    case ButtonEvent::release:
      return "release";
      break;
    case ButtonEvent::none:
      return "none";
      break;
    default:
    return "unknown";
    break;
  }
}



ButtonEvent PushButton::read() {
  if ((millis() > this->nextEvalTime)) {

    if (!this->state) {

      if (this->lastEvent == repeatedPress || this->lastEvent == firstPress) {
          this->nextEvalTime = millis() + PUSH_BUTTON_REPEAT_INTERVAL;
          this->lastEvent = ButtonEvent::repeatedPress;
      } else {
          this->nextEvalTime = millis() + PUSH_BUTTON_TIME_TO_REPEAT;
          this->lastEvent = ButtonEvent::firstPress;
      }

    } else {

      if (this->lastEvent == repeatedPress || this->lastEvent == firstPress) {
        this->lastEvent = ButtonEvent::release;
      } else {
        this->lastEvent = ButtonEvent::none;
      }

    }

    return this->lastEvent;
  }

  return ButtonEvent::none;
}
