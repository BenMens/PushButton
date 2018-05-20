#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#define PUSH_BUTTON_MAX_BUTTON_COUNT        8
#define PUSH_BUTTON_STABLE_TIME            10
#define PUSH_BUTTON_TIME_TO_REPEAT       1000
#define PUSH_BUTTON_REPEAT_INTERVAL       200

typedef enum {
  none,
  firstPress,
  repeatedPress,
  release
} ButtonEvent;

class PushButton {

  private:

    static int numButtons;
    static PushButton *buttons[PUSH_BUTTON_MAX_BUTTON_COUNT];

    byte pin;
    bool state;
    unsigned long nextEvalTime;
    ButtonEvent lastEvent;

  public:

    static void loop();
    static char* eventToString(ButtonEvent event);

    PushButton(byte pin);

    ButtonEvent read();
};

#endif
