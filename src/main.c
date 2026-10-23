#include "usart.h"

int main(){
    usart_init(USART1,9600);
    usart_send_char(USART1,'m');
}