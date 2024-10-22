# Printf and Scanf for the ATMega328PB (MPLAB X IDE) 

## Usage notes

In uart.h, there are two macros at the top that you **must configure** for this library to work.

The instructions on how to configure that can be found in the uart.h file, in the "USER CONFIG" section.

## APIs

- ```printf("<format string>", arg1, arg2, ...)```: works just like the native ```printf()```
- ```UART_scanf("<format string>", &arg1, &arg2, ...)```: works just like the native ```scanf()```

For ```UART_scanf()```, only three format specifiers have been implemented:
- ```%d```: integer
- ```%s```: string
- ```%c```: character

You might ask why we can use the standard printf, but not the standard scanf. Well, the native printf works just fine by piping stdout to the UART interface. The native scanf also technically can work the same way - however, that has double buffering issues with UART, and apparently you can't disable those on the XC8 compiler (if you're curious about what that means, change UART_scanf to scanf in one of the examples in newmain.c). So I implemented my own version and called it UART_scanf.

## Examples

The newmain.c file has some example code that you can selectively enable or disable at the top of that file.
