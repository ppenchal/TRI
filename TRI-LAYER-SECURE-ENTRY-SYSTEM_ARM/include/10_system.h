
//system.h
#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"

void System_Init(void);
void RFID_ReadTag(u8 *tag);
u8 Check(u8 *tag);
u8 VerifyPassword(void);
u8 VerifyOTP(void);
void GrantAccess(void);
void ShowInvalidCard(u8 *tag);
void LED_ON(void);

void UART0_Init(void);
void UART0_TxString(char *s);
void UART0_TxChar(unsigned char c);

void Generate_OTP(u8 *otp);
void Send_OTP_SMS(u8 *otp);

u8 Get_OTP_WithTimeout(u8 *buf, u16 timeout);

#endif
