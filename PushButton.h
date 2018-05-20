#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#define PUSH_BUTTON_MAX_BUTTON_COUNT        8
#define PUSH_BUTTON_STABLE_TIME            10
#define PUSH_BUTTON_TIME_TO_REPEAT       1000
#define PUSH_BUTTON_REPEAT_INTERVAL       200

typedef enum {
  noPress,
  firstPress,
  repeatedPress,
  release
} ButtonPressType;

class PushButton {

  private:

    static int numButtons;
    static PushButton *buttonState[PUSH_BUTTON_MAX_BUTTON_COUNT];
    static void pciSetup(byte pin);

  public:

    static void checkAll();

    byte pin;
    bool state;
    unsigned long changeTime;
    ButtonPressType lastMessage;

    PushButton(byte pin);

    void check();
    ButtonPressType read();
};

#endif
