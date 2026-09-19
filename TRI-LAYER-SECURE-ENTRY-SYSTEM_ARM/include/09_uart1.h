//uart1.h
#ifndef UART1_H
#define UART1_H

#include <LPC214x.h>

void UART1_Init(void);
void UART1_TxChar(unsigned char ch);
unsigned char UART1_RxChar(void);
void UART1_TxString(unsigned char *str);
void UART1_RxString(unsigned char *str, unsigned int maxlen);

#endif
