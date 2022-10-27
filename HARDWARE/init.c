#include "include.h"
#include "core_cm0.h"
// 
// #ifdef __GNUC__
//  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
//     set to 'Yes') calls __io_putchar() */
//  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
//#else
//  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
//#endif /* __GNUC__ */
//  
//  
void  _sys_exit(int x)
{
 x=x;
}
//int fputc(int ch,FILE *f)
//{
//  while((USART1->STS&(0x40))==0);
//  USART1->DAT =(u8)ch;
//	return ch;
//}

 void GPIOInit()
 {
	/* GPIOC Periph clock enable */	 
	  RCC ->APB2PCLKEN |= 1<<2;  //ʹ�� GPIOA  ʱ��
	  RCC ->APB2PCLKEN |= 1<<3;  //ʹ�� GPIOB  ʱ��
    RCC ->APB2PCLKEN |= 1<<0;  //ʹ��(AFIO)����ʱ��
	  // PA 0 4 9 10	 
	  GPIOA->PMODE  &= ~(3<<18);   //PA9
    GPIOA->PMODE  &= ~(3<<0);  
    GPIOA->PMODE  &= ~(3<<8); 
    GPIOA->PMODE  &= ~(3<<20); 
	  
	  GPIOA->PMODE  |= 1<<18;   //PA9
    GPIOA->PMODE  |= 1<<0; 
    GPIOA->PMODE  |= 1<<8; 
    GPIOA->PMODE  |= 1<<20; 	 	 
//	  GPIOA->PMODE   &= 0XFFC3FCFC;
//	  GPIOA->PMODE   |= 0X00140101;   //���ģʽ
	 
	  GPIOA->POTYPE &= ~(1<<18);
	  GPIOA->POTYPE &= ~(1<<0); 
	  GPIOA->POTYPE &= ~(1<<8); 
	  GPIOA->POTYPE &= ~(1<<20);
    		
//	  GPIOA->POTYPE  &= 0XFFFFF9EE;   //����ģʽ

    
   GPIOA->PUPD  &= ~(3<<18);    //
   GPIOA->PUPD  &= ~(3<<0);
   GPIOA->PUPD  &= ~(3<<8);
   GPIOA->PUPD  &= ~(3<<20);	 
	   
	  GPIOA->PUPD    |= 0X00000200;   //PA4 ����
	 
	  GPIOA->SR      &= 0XFFFFF9EE;   //����GPIO
	 
	  //PA4***************************
	 
    //	PA 1 7   OLED
	  GPIOA->PMODE   &= 0XFFFF3FF3;
	  GPIOA->PMODE   |= 0X00004004;   //���ģʽ	

//	  GPIOA->POTYPE |= 1<<1;     //��©ģʽ
//	  GPIOA->POTYPE |= 1<<7;   
	  GPIOA->POTYPE &= ~(1<<1);   
    GPIOA->POTYPE &= ~(1<<7);
		
	  GPIOA->PUPD    &= 0XFFFF3FF3;
	 	GPIOA->PUPD    |= 0X00004004;   //����
		
	  GPIOA->SR      &= 0XFFFFFF5D;   //����GPIO

	  //	PA 5 6    IIC
		GPIOA->PMODE   &= 0XFFFFC3FF;
	  GPIOA->PMODE   |= 0X00001400;   //���ģʽ
		
		GPIOA->POTYPE  &= ~(1<<5);    //����ģʽ
	  GPIOA->POTYPE  &= ~(1<<6);
		
    GPIOA->PUPD    &= 0XFFFFCFFF;
	 	GPIOA->PUPD    |= 0X00001000;   //����
	 
    GPIOA->SR      &= 0XFFFFFFBF;		//����GPIO
 }
 
 
 
void TIM1_Conf(u16 pre,u16 per)
 {
  /* Time base configuration */ 
	 RCC->APB2PCLKEN  |= 1<<12;    //ʹ��TIM1ʱ��
	 TIM1->PSC = per;              //Ԥ��Ƶֵ
   TIM1->AR  = pre;              //�Զ���װ��ֵ
	 TIM1->CTRL1 &= 0xFFFFFC8F;    // 0��Ƶ  ���ض���  ���ϼ���
	 TIM1->CTRL1 |= 0x00000081;    // �����Զ���װ��   ʹ�ܼ����� 
	 TIM1->DINTEN |= 1<<0;         //  ��������жϣ�TIM_IT_Update��
	 
	 
	NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,0x02); 
	NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
 	 
 }
 
 


 void TIM3_Conf(u16 pre,u16 per)
 {
  /* Time base configuration */
	 RCC->APB1PCLKEN |= 1<<1;  //ʹ��TIM3ʱ��
	 
	 TIM3->PSC = per;             //Ԥ��Ƶֵ
   TIM3->AR  = pre;             //�Զ���װ��ֵ

	 TIM3->CTRL1  |= (1<<2);	 
	 TIM3->CTRL1 &= 0xFFFFFC8F;    // 0��Ƶ  ���ض���  ���ϼ���
	 TIM3->CTRL1 |= 0x00000081;    // �����Զ���װ��   ʹ�ܼ�����

	
	 TIM3->DINTEN |= 1<<0;         //  ��ֹ�����жϣ�TIM_IT_Update��

	 NVIC_SetPriority(TIM3_IRQn,0x01);	 	
	 NVIC_EnableIRQ(TIM3_IRQn);
	 
 } 
 
 
 
 
void TIM6_Conf(u16 pre,u16 per)
 {
	 
   RCC->APB1PCLKEN  |= 1<<4;  //ʹ��TIM6ʱ��
	  TIM6->AR = pre;             //�Զ���װ��ֵ
	  TIM6->PSC= per;             //Ԥ��Ƶֵ
    TIM6->CTRL1 =0X0081;        //	 
	  TIM6->STS = 0;            //��������жϱ�־ 
	                            // tim6������ ��Ƶϵ��  ���ϼ����Ĵ���
	  TIM6->DINTEN |= 1<<0;     //����ʱ�������ж� 
	 
	  NVIC_SetPriority(LPTIM_TIM6_IRQn,0x03);		 
	 	NVIC_EnableIRQ(LPTIM_TIM6_IRQn);
 
 }
 
 void USART1_Config(void)
{ 
	  u8 EVENODD=2;
	  float temp;
	  u16 mantissa;
	  u16 fraction;	   
    u32 bound;
	
	  RCC ->APB2PCLKEN |= 1<<2;  //ʹ�� GPIOA  ʱ��
	  RCC ->APB2PCLKEN |= 1<<14; //ʹ�� USART1 ʱ��
//	/* ����PA2 ,PA3*/
	  GPIOA->PMODE     &= 0XFFFFFF0F;   //�Ƚ�PA 2 3 ����λ����
	  GPIOA->PMODE     |= 0X000000A0;   //PA2 3 �˿ڸ���
	
		GPIOA->POTYPE    &= 0XFFFFFFF3;   //�������
		
		GPIOA->PUPD      &= 0xFFFFFF0F;
		GPIOA->PUPD      |= 0X00000050;   //����
		
		GPIOA->SR        &= 0XFFFFFFF3;   //����ģʽ

	  GPIOA->AFL       &= 0XFFFF00FF;  //�Ȱѽ�Ҫ�ĵ�λ����
	  GPIOA->AFL       |= 0X00000100;  // PIN2 ->  AF_1
	  GPIOA->AFL       |= 0X00001000;  // PIN3  -> AF_1		


	if(ModelBaud==1)
     bound = 4800;
	else if (ModelBaud==2)
		 bound = 9600;
	else if (ModelBaud==3)
		 bound =19200;
	else if (ModelBaud==4)
		 bound =38400;
	else if (ModelBaud==5)
		 bound =57600;
	else if (ModelBaud==6)
		 bound =115200;
	else 
		 bound =2400;
	
	temp=(float)(48*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				              //�õ���������
	fraction=(temp-mantissa)*16;        //�õ�С������
  mantissa<<=4;
	mantissa+=fraction;
	
	USART1->BRCF = mantissa;
	
	if(EVENODD==0||EVENODD==1)
	  USART1->CTRL1 |= 1<<12;      // USART_WordLength_9b
	else
		USART1->CTRL1 &= 0XFFFFEF;   //  USART_WordLength_8b
	
	  USART1->CTRL2 &= 0XFFFFCFFF; // USART_StopBits_1
	
	if(EVENODD==0)
	{
		 USART1->CTRL1   |=1<<10 ;   //ʹ��У��
		 USART1->CTRL1   &=0XFFFFFDFF;//żУ��
	}
	else if(EVENODD==1)
	{
		  USART1->CTRL1   |=1<<10 ;   //ʹ��У��
		  USART1->CTRL1   |=1<<9;   //��У��		
	}
	else
	{
	  USART1->CTRL1   &=0xFFFFFBFF;   //У�����
	}
 
	  USART1->CTRL3 &= 0xFFFFF8FF; //  USART_HardwareFlowControl_None
	
	USART1->CTRL1 |= 1<<3;   //������ʹ��
	USART1->CTRL1 |= 1<<2;   //������ʹ��

  USART1->CTRL1 |= 1<<5;  //�����ж�ʹ�� 

 	NVIC_SetPriority(USART1_IRQn,0x00);	
	NVIC_EnableIRQ(USART1_IRQn);
	
  
 
	USART1->CTRL1 |= 1<<13;     //����ʹ��
}

void USART1_Modelbaud_Set(void)
{
  float temp;
	u16 mantissa;
	u16 fraction;	   
  u32 bound;
	if(ModelBaud==1)
     bound = 4800;
	else if (ModelBaud==2)
		 bound = 9600;
	else if (ModelBaud==3)
		 bound =19200;
	else if (ModelBaud==4)
		 bound =38400;
	else if (ModelBaud==5)
		 bound =57600;
	else if (ModelBaud==6)
		 bound =115200;
	else 
		 bound =2400;
	temp=(float)(48*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				              //�õ���������
	fraction=(temp-mantissa)*16;        //�õ�С������
  mantissa<<=4;
	mantissa+=fraction;
	
	USART1->BRCF = mantissa;
}

void InitALL()
{
	GPIOInit();
	USART1_Config();			//���ڳ�ʼ��
	
	TIM6_Conf(48-1,106-1);   //ģ�⴮���ö�ʱ��
}

