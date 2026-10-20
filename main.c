#include "servo.h"
#include "UART.h"
#include "ADC.h"

#define ADC_DEADBAND 10

int main(void) {
    ServoInit();
    UART_Init();
    ADC_Init();

    uint32_t last_pot = 0;
    uint32_t pot;
    while (1) {
        pot = ADC_Read();
        if (abs(pot - last_pot) > ADC_DEADBAND) {
            ServoSetAngle(map(last_pot, 0, 4095, 0, 180));
            last_pot = pot;
        }
    }
    return 0;
}