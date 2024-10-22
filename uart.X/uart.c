#include <stdio.h>
#include "uart.h"
#include <avr/io.h>
#include <stdarg.h>
#include <string.h>

void UART_init(int BAUD_PRESCALER)
{

    /*Set baud rate */
    UBRR0H = (unsigned char)(BAUD_PRESCALER>>8);
    UBRR0L = (unsigned char)BAUD_PRESCALER;
    //Enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* Set frame format: 2 stop bits, 8 data bits */
    UCSR0C = (1<<UCSZ01) | (1<<UCSZ00); // 8 data bits
    UCSR0C |= (1<<USBS0); // 2 stop bits
    
    __init_stdout(UART_send);
    __init_stdin(UART_receive);
}

int UART_send(char data, FILE* stream)
{
    // Wait for empty transmit buffer
    while(!(UCSR0A & (1<<UDRE0)));
    // Put data into buffer and send data
    UDR0 = data;
    return 0;
}

int UART_receive(FILE* stream)
{
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void determine_line_ending() {
    char c;
    printf("Press Enter to detect the line ending style...\n");

    while(1)
    {
        c = UART_receive(NULL);
        if (c == '\r') {
            printf("\\r (CR) detected.\n");
        } else if (c == '\n') {
            printf("\\n (LF) detected.\n");
        } else {
            printf("Unknown line ending.\n");
        }
    }
}

// Only integer (%d), char (%c), and string (%s) format specifiers have been implemented
#if !defined(CR) && !defined(LF) && !defined(CRLF)
#error "No line termination defined! #define one out of CR, LF, or CRLF"
#else
#ifdef MAX_STRING_LENGTH
void UART_scanf(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    const char* p = format;
    char buffer[MAX_STRING_LENGTH];
    int i = 0, num = 0;
    char c;

    while (*p) {
        if (*p == '%') 
        {
            p++;
            switch (*p) 
            {
                case 'd':
                {
                    num = 0;
                    while(1) {
                        c = UART_receive(NULL);
                        if(c >= '0' && c <= '9') 
                        {
                            num = num * 10 + (c - '0');
                        }
                        #if defined(CR) || defined(CRLF)
                        else if(c == '\r')
                        {
                            #ifdef CRLF
                            UART_receive(NULL);
                            #endif
                            break;
                        }
                        #endif
                        #ifdef LF
                        else if(c == '\n')
                        {
                            break;
                        }
                        #endif
                    }
                    int *int_ptr = va_arg(args, int*);
                    *int_ptr = num;
                    break;
                }
                case 's':
                {
                    i = 0;
                    while(1) 
                    {
                        c = UART_receive(NULL);

                        #if defined(CR) || defined(CRLF) 
                        if(c == '\r')
                        {
                            #ifdef CRLF
                            UART_receive(NULL);
                            #endif
                            buffer[i] = '\0';
                            break;
                        }
                        #endif
                        #ifdef LF
                        if(c == '\n')
                        {
                            buffer[i] = '\0';
                            break;
                        }
                        #endif

                        if(i < MAX_STRING_LENGTH - 1 && c != '\r' && c != '\n') 
                        {
                            buffer[i++] = c;
                        }
                    }
                    buffer[i] = '\0';
                    char *str_ptr = va_arg(args, char*);
                    strcpy(str_ptr, buffer);
                    break;
                }
                case 'c':
                {
                    while(1)
                    {
                        c = UART_receive(NULL);
                        #if defined(CR) || defined(CRLF)
                        if(c == '\r') 
                        {
                            #ifdef CRLF
                            c = UART_receive(NULL);
                            #endif
                            break;
                        }
                        #endif
                        #ifdef LF
                        if(c == '\n') 
                        {
                            break;
                        }
                        #endif
                        char *char_ptr = va_arg(args, char*);
                        *char_ptr = c;
                    }
                }
            }
        }
        p++;
    }
    va_end(args);
}
#else
#error "MAX_STRING_LENGTH undefined"
#endif
#endif