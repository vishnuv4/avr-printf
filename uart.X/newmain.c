#define F_CPU               16000000UL
#define UART_BAUD_RATE      9600
#define UART_BAUD_PRESCALER (((F_CPU / (UART_BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "uart.h"

#define LED_PIN PB5

#define PRINTF_HELLOWORLD   0
#define RECEIVE_STRING      0
#define SCANFTEST_NUM       1
#define SCANFTEST_STR       0
#define SCANFTEST_CHAR      0

#if defined(SCANFTEST_STR) || defined(RECEIVE_STRING)
char rcbuf[MAX_STRING_LENGTH];
#endif

int main()
{
    UART_init(UART_BAUD_PRESCALER);
    DDRB |= (1 << LED_PIN);
    
#if SCANFTEST_CHAR
    char ch;
#endif
    
#if SCANFTEST_NUM
    int num;
#endif
    
    while(1)
    {
        
#if PRINTF_HELLOWORLD
        printf("Hello World!\r\n");
        _delay_ms(500);
#endif
        
        
#if RECEIVE_STRING
        printf("Enter a string: ");
        UART_receive_string(rcbuf);
        printf("The string you entered is: %s\r\n", rcbuf);
#endif
        
        
#if SCANFTEST_CHAR
        printf("Enter a character: ");
        UART_scanf("%c\n",&ch);
        printf("----The character is: %c\r\n", ch);
#endif
        
        
#if SCANFTEST_NUM
        printf("Enter a number: ");
        UART_scanf("%d\r\n", &num);
        if (num == 0)
        {
            printf("OFF -- The number is %d\r\n", num);
            PORTB &= ~(1 << LED_PIN);
        }
        else
        {
            printf("ON -- The number is %d\r\n", num);
            PORTB |= (1 << LED_PIN);
        }
#endif
        
        
#if SCANFTEST_STR
        printf("Enter a string: ");
        UART_scanf("%s", rcbuf);
        printf("The string you entered is: %s\r\n", rcbuf);
#endif
    }
    return 0;
}
