#include <Arduino.h>

#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

/*
Napisz program, który będzie migał trzema kolorami diody RGB.

Każdy kolor diody ma mieć zmienny czas migania wyrażony w milisekundach.
Program startuje z czasami R-0,9s, G-1,0s, B-1,1s.
Proszę wykorzystać przyciski do zmiany wartości czasów migania. Można przyjąć, że przycisk czerwony wybiera aktualną diodę do zmiany wartości, a zielony zmienia wartość migania cyklicznie w przedziale 0,5s - 2,0s z krokiem co 0,1s.
Aktualna nastawa czasu jest wyświetlana na wyświetlaczu LCD.
Program przygotować tak, aby nie blokować przełączania diod wzajemnie, nie blokować wykonania programu.
*/

int led[] = {LED_RED, LED_GREEN, LED_BLUE};

void initRGB()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    pinMode(LED_RED, OUTPUT);
    digitalWrite(LED_RED, HIGH);

    pinMode(LED_GREEN, OUTPUT);
    digitalWrite(LED_GREEN, LOW);

    pinMode(LED_BLUE, OUTPUT);
    digitalWrite(LED_BLUE, LOW);
}

void initButtons()
{
    pinMode(RED_BUTTON, INPUT_PULLUP);
    pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

bool isGreenButtonPressed()
{
    static int debounced_button_state = HIGH;
    static int previous_reading = HIGH;
    static int blocker = 0;
    bool isPressed = false;

    int current_reading = digitalRead(GREEN_BUTTON);

    if (previous_reading != current_reading)
    {
        blocker = 1000;
    }

    if (blocker == 0)
    {
        if(current_reading != debounced_button_state)
        {
            if (debounced_button_state == HIGH && current_reading == LOW)
            {
                isPressed = true;
            }
            debounced_button_state = current_reading;
        }
    }
    else
    {
        --blocker;
    }

    previous_reading = current_reading;

    return isPressed;
}

void setup()
{
    initRGB();
    initButtons();
}

int led_index = 0;
void loop()
{
    if (isGreenButtonPressed())
    {
        digitalWrite(led[led_index], LOW);
        led_index = ++led_index % 3;
        digitalWrite(led[led_index], HIGH);
    }
}
