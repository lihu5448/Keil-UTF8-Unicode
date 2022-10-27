#include "include.h"
void LED_Init(void)
{
   RCC ->APB2PCLKEN |= 1<<2;  //ʹ�� GPIOA  ʱ��
   
	//PA10
	 GPIOA->PMODE  &= 0XFFDFFFFF;  //���ģʽ
	 GPIOA->POTYPE &= 0XFFFFFBFF;  //����ģʽ
	 GPIOA->PUPD   |= 0x00C00000;  //nopull
   GPIOA->SR     &= 0XFFFFFBFF;  //  ����

}

void SetLed(u8 onoff)
{
    //PA10
	
		if(onoff)
			GPIOA->POD |= 1<<10;   //PA10�����
		else
			GPIOA->POD &= 0XFFFFFBFF;   //PA10�����		

}

