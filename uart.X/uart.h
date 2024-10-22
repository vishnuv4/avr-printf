#ifndef UART_H
#define UART_H

#include <stdio.h>

/***************************************/
/* USER CONFIG */
/***************************************/

/**
 * Line termination type that your terminal emulator follows
 *      \r  :   #define CR
 *      \n  :   #define LF
 *      \r\n:   #define CRLF
 * For example, PuTTY and MobaXTerm end a line with only \r (CR)
 * Arduino IDE supports termination with \r\n (CRLF)
 * VSCode serial monitor extension supports all three.
 * 
 * Call determine_line_ending() in your code to see which one your terminal supports.
 */
#define CRLF

/**
 * Maximum length of input string to support
 */
#define MAX_STRING_LENGTH   100


/***************************************/
/* MACROS AND FUNCTION DECLARATIONS */
/***************************************/

void UART_init(int prescale);

int UART_send(char data, FILE* stream);

int UART_receive(FILE* stream);

void UART_scanf(const char* format, ...);

void determine_line_ending(void);

#endif // UART_H