#include <Arduino.h>

#define GPIO_15 15
#define GPIO_16 16
#define GPIO_17 16
#define RGB_PIN 48

const uint8_t RAINBOW[][3] = {
    {255, 0, 0},
    {255, 60, 0},
    {255, 150, 0},
    {0, 255, 0},
    {0, 150, 255},
    {0, 0, 255},
    {120, 0, 255},
};
const size_t RAINBOW_COUNT = sizeof(RAINBOW) / sizeof(RAINBOW[0]);
#define BRIGHTNESS 64 

void setup()
{
    pinMode(GPIO_15, OUTPUT);
    pinMode(GPIO_16, OUTPUT);
    pinMode(GPIO_17, OUTPUT);
    Serial.begin(115200);
}

void police()
{
    digitalWrite(GPIO_15, HIGH);
    digitalWrite(GPIO_16, LOW);
    delay(1000);

    digitalWrite(GPIO_15, LOW);
    digitalWrite(GPIO_16, HIGH);
    delay(1000);
}

void police_complex()
{
    digitalWrite(GPIO_15, LOW);
    digitalWrite(GPIO_16, HIGH);
    delay(200);
    digitalWrite(GPIO_16, LOW);
    delay(200);
    digitalWrite(GPIO_16, HIGH);
    delay(200);
    digitalWrite(GPIO_16, LOW);
    digitalWrite(GPIO_15, HIGH);
    delay(200);
}

void three_diods()
{
    const uint8_t LED_PINS[] = {GPIO_15, GPIO_16, GPIO_17};
    for (size_t active = 0; active < 3; active++)
    {
        for (size_t i = 0; i < 3; i++)
        {
            digitalWrite(LED_PINS[i], i == active ? HIGH : LOW);
        }
        delay(1000);
    }
}

void speed_changes(uint16_t interval)
{
    digitalWrite(GPIO_15, HIGH);
    digitalWrite(GPIO_16, LOW);
    delay(interval);

    digitalWrite(GPIO_15, LOW);
    digitalWrite(GPIO_16, HIGH);
    delay(interval);
}

void speed_change_loop()
{
    static uint16_t interval = 1000;
    static uint16_t step = -100;
    interval += step;
    if (interval <= 100 || interval >= 1000)
    {
        step = -step;
    }
    speed_changes(interval);
}

void one_gpio_two_blink()
{
    /*
    3V3 ──[220Ω]──|>|── GPIO_15 ──|>|──[220Ω]── GND
                  LED2              LED1
    */

    digitalWrite(GPIO_15, HIGH);
    delay(1000);

    digitalWrite(GPIO_15, LOW);
    delay(1000);
}

void rgb()
{
    for (size_t i = 0; i < RAINBOW_COUNT; i++)
    {
        neopixelWrite(RGB_PIN,
                      RAINBOW[i][0] * BRIGHTNESS / 0xFF,
                      RAINBOW[i][1] * BRIGHTNESS / 0xFF,
                      RAINBOW[i][2] * BRIGHTNESS / 0xFF);
        delay(500);
    }
}

void loop()
{
    // police();
    // police_complex();
    // three_diods();
    // speed_change_loop();
    // one_gpio_two_blink();
    rgb();
}
