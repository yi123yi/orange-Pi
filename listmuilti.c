#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

// Define PCA9685 constants
#define PCA9685_ADDRESS   0x40
#define MODE1             0x00
#define MODE2             0x01
#define PRE_SCALE         0xFE
#define LED0_ON_L         0x06
#define LED0_ON_H         0x07
#define LED0_OFF_L        0x08
#define LED0_OFF_H        0x09

// Define GPIO pin numbers
#define SWITCH_LIFT_UP    21
#define SWITCH_LEVEL_DOWN 23

// Function to initialize PCA9685
int pca9685Setup(const int i2cAddress, const int i2cBus);

int main() {
    // Initialize WiringPi and PCA9685
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "Failed to initialize WiringPi\n");
        return 1;
    }

    int pca9685 = pca9685Setup(PCA9685_ADDRESS, 1);

    if (pca9685 < 0) {
        fprintf(stderr, "Error initializing PCA9685\n");
        return 1;
    }

    // Set PCA9685 frequency (e.g., 60Hz)
    int frequency = 1000;
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(3840);
    pwmSetRange(PCA9685_ADDRESS, frequency);

    // Initialize GPIO pins
    pinMode(SWITCH_LIFT_UP, INPUT);
    pinMode(SWITCH_LEVEL_DOWN, INPUT);
    pullUpDnControl(SWITCH_LIFT_UP, PUD_UP);
    pullUpDnControl(SWITCH_LEVEL_DOWN, PUD_UP);

    while (1) {
        // Check GPIO input state
        int liftUpState = digitalRead(SWITCH_LIFT_UP);
        int levelDownState = digitalRead(SWITCH_LEVEL_DOWN);

        // Check and handle lift up and level down conditions
        if (liftUpState == LOW) {
            // Lift: Moving Up
            pwmWrite(PCA9685_ADDRESS, LED0_ON_L, 0);
            pwmWrite(PCA9685_ADDRESS, LED0_OFF_L, 4095);
        } else {
            // Lift: Stop
            pwmWrite(PCA9685_ADDRESS, LED0_ON_L, 0);
            pwmWrite(PCA9685_ADDRESS, LED0_OFF_L, 0);
        }

        if (levelDownState == LOW) {
            // Level: Moving Down
            pwmWrite(PCA9685_ADDRESS, LED0_ON_H, 0);
            pwmWrite(PCA9685_ADDRESS, LED0_OFF_H, 4095);
        } else {
            // Level: Stop
            pwmWrite(PCA9685_ADDRESS, LED0_ON_H, 0);
            pwmWrite(PCA9685_ADDRESS, LED0_OFF_H, 0);
        }

        delay(100);  // Adjust delay as needed
    }

    return 0;
}
