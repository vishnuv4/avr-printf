#ifndef UART_H
#define UART_H

#include <stdio.h>

#ifndef MAX_STRING_LENGTH
    #define MAX_STRING_LENGTH 100
#endif

void UART_init(int prescale);

int UART_send(char data, FILE* stream);

int UART_receive(FILE* stream);

void UART_receive_string(char* buffer);

void UART_scanf(const char* format, ...);

#endif 