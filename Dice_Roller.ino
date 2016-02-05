/*
  COMP-50 Wearables Dice Roller
  This sketch uses a button between pin 4 and
  ground to toggle an LED connected between pin 5 and
  a resistor (which is tied to ground).
*/
#include <PinChangeInt.h>

#define BUTTON A0
#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3
#define LED5 4
#define LED6 5

bool button_pushed = false;
int light_status = HIGH;

void setup() {
        pinMode(LED1, OUTPUT);          // LED
        pinMode(LED2, OUTPUT);          // LED
        pinMode(LED3, OUTPUT);          // LED
        pinMode(LED4, OUTPUT);          // LED
        pinMode(LED5, OUTPUT);          // LED
        pinMode(LED6, OUTPUT);          // LED
        pinMode(BUTTON, INPUT_PULLUP); // button
        attachPinChangeInterrupt(BUTTON, button, FALLING);
        Serial.begin(57600);
        Serial.setTimeout(25);
        digitalWrite(LED1, light_status);
        digitalWrite(LED2, light_status);
        digitalWrite(LED3, light_status);
        digitalWrite(LED4, light_status);
        digitalWrite(LED5, light_status);
        digitalWrite(LED6, light_status);
}

void loop() {
        if (button_pushed) {
                // send a "b" via the serial connection for debugging
                Serial.write((const uint8_t *)"b", 1);
                
                int num_leds = random(0, 7); 
                /* Turn on correct LEDs  */
                for(int i = 0; i <= num_leds; i++) {
                    digitalWrite(i, HIGH);
                }
                /* Turn off remaining LEDs*/
                for(int i = 5; i > num_leds; i--) {
                    digitalWrite(i, LOW);
                }
                button_pushed = false;
        }
        delay(10);
}

void button() { // will be called via interrupt when button is pressed
        static unsigned long last_interrupt_time = 0;
        unsigned long interrupt_time = millis();
        // If interrupts come faster than 200ms, assume it's a bounce and ignore
        if ((interrupt_time - last_interrupt_time > 200) and !button_pushed) {
                // button pressed
                if (!button_pushed)
                        button_pushed = true;
        }
        last_interrupt_time = interrupt_time;
}
