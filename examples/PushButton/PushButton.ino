#include <PushButton.h>

#define BUTTON1_PIN 6
#define BUTTON2_PIN 2
#define BUTTON3_PIN 3

PushButton buttons[] = {
  PushButton(BUTTON1_PIN),
  PushButton(BUTTON2_PIN),
  PushButton(BUTTON3_PIN)
};

#define NUM_BUTTONS (sizeof(buttons)/sizeof(PushButton))

void setup() {
  Serial.begin(115200);
  Serial.println("Started");
}

void loop() {

  PushButton::loop();

  for (uint8_t buttonIndex = 0; buttonIndex < NUM_BUTTONS; buttonIndex++) {

    char buffer[64];

    ButtonEvent event = buttons[buttonIndex].read();

    if (event != ButtonEvent::none) {
      sprintf(buffer, "button #%u %s",buttonIndex, PushButton::eventToString(event));
      Serial.println(buffer);
    }

  }

}
