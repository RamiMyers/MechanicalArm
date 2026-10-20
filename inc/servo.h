#ifndef SERVO_H
#define SERVO_H

#include "PWM.h"

// PWM Frequency = 50 Hz = 20 ms
// 0.5 ms = 0 degrees = 2.5% duty cycle
// 2.4 ms = 180 degrees = 12% duty cycle

static inline long map(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Initializes PWM with a frequency of 50 Hz
static inline void ServoInit(void) {
    PWM_Init(50);
}

// Maps an angle between 0 - 180 degrees to a duty cycle of 2.5% - 12%
static inline void ServoSetAngle(unsigned angle) {
    PWM_Set(map(angle, 0, 180, 25, 120));
}

#endif