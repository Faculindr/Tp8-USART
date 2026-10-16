#include "clk_maximizer.h"

void clock_72MHz(void)
{
    // Habilito HSE cristal externo de 8 MHz
    RCC->CR |= RCC_CR_HSEON;

    // Espero a HSE
    while(!(RCC->CR & RCC_CR_HSERDY));

    // Configuración de Flash para 72 MHz
    FLASH->ACR |= FLASH_ACR_PRFTBE;
    FLASH->ACR &= ~FLASH_ACR_LATENCY;
    FLASH->ACR |= FLASH_ACR_LATENCY_2;

    // AHB = 72 MHz
    RCC->CFGR &= ~RCC_CFGR_HPRE;

    // APB2 = 72 MHz
    RCC->CFGR &= ~RCC_CFGR_PPRE2;

    // APB1 = 36 MHz
    RCC->CFGR &= ~RCC_CFGR_PPRE1;
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

    // Fuente del PLL = HSE
    RCC->CFGR |= RCC_CFGR_PLLSRC;

    // HSE sin dividir
    RCC->CFGR &= ~RCC_CFGR_PLLXTPRE;

    // PLL x9
    RCC->CFGR &= ~RCC_CFGR_PLLMULL;
    RCC->CFGR |= RCC_CFGR_PLLMULL9;

    // Habilito PLL
    RCC->CR |= RCC_CR_PLLON;

    // Espero a PLL
    while(!(RCC->CR & RCC_CR_PLLRDY));

    // Selecciono PLL como clock del sistema
    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    // Espero hasta que PLL sea SYSCLK
    while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}