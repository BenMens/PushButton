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
} ButtonPressType;

class PushButton {

  private:

    static int numButtons;
    static PushButton *buttons[PUSH_BUTTON_MAX_BUTTON_COUNT];

    byte pin;
    bool state;
    unsigned long nextEvalTime;
    ButtonPressType lastMessage;

  public:

    static void loop();
    static char* buttonPressTypeToString(ButtonPressType msg);

    PushButton(byte pin);

    ButtonPressType read();
};

#endif
