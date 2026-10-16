#include "usart.h"
#include "stm32f103xb.h"


void usart_init(USART_TypeDef * USARTx, uint32_t baudrate){//funcion de inicio
    if(USARTx==USART1 ){//si se quiere usar el usart 1
        RCC->APB2ENR|=RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;
        int tx=9;
        int rx=10;
        GPIOA->CRH&=~(0xF<<(tx%8)*4);//configuracion de pines tx y rx
        GPIOA->CRH|=(0xb<<(tx%8)*4);
        GPIOA->CRH&=~(0xF<<(rx%8)*4);
        GPIOA->CRH|=(0x4<<(rx%8)*4);

        clock_72Mhz();//configuramos el clock a 72Mhz

        float div=72000000/(16*baudrate);
        int mattissa=div;
        int fraction=(div-mattissa)*100;
        USART1->BRR=(fraction&0xf)|(mattissa<<4);

    }
    if(USARTx==USART2){
        RCC->APB1ENR|=RCC_APB1ENR_USART2EN;
        RCC->APB2ENR|=RCC_APB2ENR_IOPAEN;
        int tx=2;
        int rx=3;
        GPIOA->CRL&=~(0xF<<tx*4);//configuracion de pines tx y rx
        GPIOA->CRL|=(0xb<<tx*4);
        GPIOA->CRL&=~(0xF<<rx*4);
        GPIOA->CRL|=(0x4<<rx*4);

        float div=(16*baudrate)/36000000;
        int mattissa=div;
        int fraction=(div-mattissa)*100;
        USART2->BRR=(fraction&0xf)|(mattissa<<4);

    }
    if(USARTx==USART3){
        RCC->APB1ENR|=RCC_APB1ENR_USART3EN;
        RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
        int tx=10;
        int rx=11;
        GPIOB->CRH&=~(0xF<<(tx%8)*4);//configuracion de pines tx y rx
        GPIOB->CRH|=(0xb<<(tx%8)*4);
        GPIOB->CRH&=~(0xF<<(rx%8)*4);
        GPIOB->CRH|=(0x4<<(rx%8)*4);

        float div=36000000/(16*baudrate);//formula para la velocidad de comunicacion
        int mattissa=div;//lo pasamos a entero
        int fraction=(div-mattissa)*100;//nos quedamos con la parte fraccional
        USART3->BRR=(fraction&0xf)|(mattissa<<4);//le pasamos al registro la parte de la fraccion(los primeros 4 bits) y la parte entera desplazada 4 bits(los otros 12)
    }
    USARTx->CR1|=USART_CR1_UE;//iniciamos el usart
    USARTx->CR1&=~USART_CR1_M;//configuramos 8 bits de datos
    USARTx->CR1&=~USART_CR1_PCE;//desactivamos el bit de paridad
    USARTx->CR1|=USART_CR1_TE;//habilita el transmisor
    USARTx->CR1|=USART_CR1_RE;//habilita el receptor
}

void usart_send_char(USART_TypeDef * USARTx, uint8_t data){
    while(!(USARTx->SR&USART_SR_TXE));//esperamos a que el registro este disponible
    USARTx->DR=data;//cuando este en 1 enviamos el caracter
    
}

void usart_send_string(USART_TypeDef*USARTx, char*txt){
    while(*txt){//accedemos al txt con un puntero
        usart_send_char(USARTx, *txt);//le pasamos cada caracter individualmente
        txt++;//pasamos a la siguiente posicion (siguiente caracter)
    }
}

uint8_t usart_receive_char(USART_TypeDef * USARTx){
    while(!(USARTx->SR&USART_SR_RXNE));//esperamos a que reciba el caracter
    return USARTx->DR;//cuando este en 1 devolvemos el caracter recibido
    
}
