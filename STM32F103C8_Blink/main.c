// Filename: main.c
//Beispiel ohne Anwendung einer zusätzlichen Library
//nur CMSIS

#include <stdint.h>
#include "stm32f10x.h"
#include <semihosting.h>

// delay loop for 8 MHz CPU clock with optimizer enabled
void delay(uint32_t msec)
{
    for (uint32_t j=0; j < 2000UL * msec; j++)
    {
        __NOP();
    }
}

// Output a trace message
void ITM_SendString(char *ptr)
{
    while (*ptr)
    {
        ITM_SendChar(*ptr);
        ptr++;
    }
}

int main(void)
{
    // Enable Port A, C and alternate functions
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_IOPAEN + RCC_APB2ENR_IOPCEN);

    // PA5 and PC13 = Output for LEDs
    MODIFY_REG(GPIOA->CRL, GPIO_CRL_CNF5  + GPIO_CRL_MODE5,  GPIO_CRL_MODE5_0);
    MODIFY_REG(GPIOC->CRH, GPIO_CRH_CNF13 + GPIO_CRH_MODE13, GPIO_CRH_MODE13_0);

    while(1)
    {
        // LED Pin -> High
        WRITE_REG(GPIOA->BSRR, GPIO_BSRR_BS5);
        WRITE_REG(GPIOC->BSRR, GPIO_BSRR_BS13);
        ITM_SendString("Pin High\n"); //funktioniert noch nicht in CooCox
        printf("Pin High\r\n");
        delay(500);


        // LED Pin -> Low
        WRITE_REG(GPIOA->BSRR, GPIO_BSRR_BR5);
        WRITE_REG(GPIOC->BSRR, GPIO_BSRR_BR13);
        ITM_SendString("Pin Low\n"); //funktioniert noch nicht in CooCox
        printf("Pin Low\r\n");
        delay(500);

    }
}
