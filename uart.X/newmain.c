/***************************************/
/* EXAMPLES CONFIG */
/***************************************/

// Set these to 0 or 1 to enable or disable the example

#define PRINTF_HELLOWORLD   0       // Prints Hello World and a counter
#define LINE_ENDING         0       // Shows you the line termination style of your terminal emulator
#define SCANFTEST_NUM       0       // Scan a number, turn onboard LED off for 0 and on for anything else
#define SCANFTEST_STR       0       // Echoes the entered string
#define SCANFTEST_CHAR      1       // Echoes the entered character

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
        
    #if SCANFTEST_CHAR
    scanftest_char();
    #endif
        
    #if SCANFTEST_NUM
    scanftest_num();
    #endif
        
    #if SCANFTEST_STR
    scanftest_str();
    #endif

    #if LINE_ENDING
    determine_line_ending();
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
    static unsigned int ctr = 0;
    printf("Hello World! Counter: %d\r\n", ctr);
    ++ctr;
    _delay_ms(500);
}
#endif

#if SCANFTEST_CHAR
void scanftest_char(void)
{
    char ch;
    printf("SCANFTEST_CHAR :: Enter a character: ");
    UART_scanf("%c\r\n",&ch);
    printf("----The character is: %c\r\n\n", ch);
}
#endif

#if SCANFTEST_NUM
void scanftest_num(void)
{
    int num;
    printf("SCANFTEST_NUM :: Enter a number:\r\n");
    UART_scanf("%d", &num);
    if (num == 0)
    {
        printf("OFF -- The number is %d\r\n\n", num);
        PORTB &= ~(1 << LED_PIN);
    }
    else
    {
        printf("ON -- The number is %d\r\n\n", num);
        PORTB |= (1 << LED_PIN);
    }
}
#endif

#if SCANFTEST_STR
void scanftest_str(void)
{
    char rcbuf[MAX_STRING_LENGTH];
    printf("SCANFTEST_STR :: Enter a string: ");
    UART_scanf("%s\r\n", rcbuf);
    printf("The string you entered is: %s\r\n\n", rcbuf);
}
#endif
