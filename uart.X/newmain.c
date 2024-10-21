/***************************************/
/* ENABLES FOR EXAMPLES */
/***************************************/

#define PRINTF_HELLOWORLD   1cp 
#define RECEIVE_STRING      0
#define SCANFTEST_NUM       0
#define SCANFTEST_STR       0
#define SCANFTEST_CHAR      0

/***************************************/
/* INCLUDES AND DEFINES */
/***************************************/

#define F_CPU               16000000UL
#define UART_BAUD_RATE      9600
#define UART_BAUD_PRESCALER (((F_CPU / (UART_BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "uart.h"

#define LED_PIN PB5

/***************************************/
/* FORWARD DECLARATIONS */
/***************************************/

void printf_helloworld(void);
void receive_string(void);
void scanftest_char(void);
void scanftest_num(void);
void scanftest_str(void);

/***************************************/
/* MAIN */
/***************************************/

int main()
{
    UART_init(UART_BAUD_PRESCALER);
    DDRB |= (1 << LED_PIN);
    
    while(1)
    {
        
#if PRINTF_HELLOWORLD
    printf_helloworld();
#endif
        
        
#if RECEIVE_STRING
    receive_string();
#endif
        
        
#if SCANFTEST_CHAR
    scanftest_char();
#endif
        
        
#if SCANFTEST_NUM
    scanftest_num();
#endif
        
        
#if SCANFTEST_STR
    scanftest_str();
#endif
    }
    return 0;
}

/***************************************/
/* EXAMPLES */
/***************************************/

#if PRINTF_HELLOWORLD
void printf_helloworld(void)
{
    printf("Hello World!\r\n");
    _delay_ms(500);
}
#endif

#if RECEIVE_STRING
void receive_string(void)
{
    char rcbuf[MAX_STRING_LENGTH];
    printf("Enter a string: ");
    UART_receive_string(rcbuf);
    printf("The string you entered is: %s\r\n", rcbuf);
}
#endif

#if SCANFTEST_CHAR
void scanftest_char(void)
{
    char ch;
    printf("Enter a character: ");
    UART_scanf("%c\r\n",&ch);
    printf("----The character is: %c\r\n", ch);
}
#endif

#if SCANFTEST_NUM
void scanftest_num(void)
{
    int num;
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
}
#endif

#if SCANFTEST_STR
void scanftest_str(void)
{
    char rcbuf[MAX_STRING_LENGTH];
    printf("Enter a string: ");
    UART_scanf("%s", rcbuf);
    printf("The string you entered is: %s\r\n", rcbuf);
}
#endif