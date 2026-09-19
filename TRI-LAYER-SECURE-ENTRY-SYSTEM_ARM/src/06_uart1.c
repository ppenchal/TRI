//uart1.c
#include <LPC214x.h>
#include "uart1.h"

// UART1 Configuration
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define BAUD 9600
#define DIVISOR (PCLK/(16*BAUD))

#define RDR_BIT 0
#define THRE_BIT 5
#define TEMT_BIT 6

void UART1_Init(void)
{

    PINSEL0 |= (1<<16) | (1<<18);

    U1LCR = 0x83;      // 8-bit, enable DLAB
    U1DLL = DIVISOR;
    U1DLM = DIVISOR >> 8;
    U1LCR = 0x03;      // Disable DLAB
}

void UART1_TxChar(unsigned char ch)
{
    U1THR = ch;
    while(((U1LSR >> TEMT_BIT) & 1) == 0);
}

unsigned char UART1_RxChar(void)
{
    while(((U1LSR >> RDR_BIT) & 1) == 0);
    return U1RBR;
}

void UART1_TxString(unsigned char *str)
{
    while(*str)
        UART1_TxChar(*str++);
}

void UART1_RxString(unsigned char *str, unsigned int maxlen)
{
    unsigned int i=0;
    unsigned char ch;

    while(1)
    {
        ch = UART1_RxChar();

        if(ch=='\r' || ch=='\n')
        {
            str[i] = '\0';
            break;
        }
        else if(i >= maxlen-1)
        {
            str[i] = '\0';
            break;
        }
        else
        {
            str[i++] = ch;
        }
    }
}
