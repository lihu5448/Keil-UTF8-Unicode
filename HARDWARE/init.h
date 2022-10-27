#ifndef _init_h
#define _init_h

#include "n32g031.h"


void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group)	;
void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 ;
void InitALL(void);
void TIM1_Conf(u16 pre,u16 per);
void TIM3_Conf(u16 pre,u16 per);
void TIM6_Conf(u16 pre,u16 per);
void USART1_Config(void);
void USART1_Modelbaud_Set(void);
#endif

