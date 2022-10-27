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
	  RCC ->APB2PCLKEN |= 1<<2;  //使能 GPIOA  时钟
	  RCC ->APB2PCLKEN |= 1<<3;  //使能 GPIOB  时钟
    RCC ->APB2PCLKEN |= 1<<0;  //使能(AFIO)复用时钟
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
//	  GPIOA->PMODE   |= 0X00140101;   //输出模式
	 
	  GPIOA->POTYPE &= ~(1<<18);
	  GPIOA->POTYPE &= ~(1<<0); 
	  GPIOA->POTYPE &= ~(1<<8); 
	  GPIOA->POTYPE &= ~(1<<20);
    		
//	  GPIOA->POTYPE  &= 0XFFFFF9EE;   //推挽模式

    
   GPIOA->PUPD  &= ~(3<<18);    //
   GPIOA->PUPD  &= ~(3<<0);
   GPIOA->PUPD  &= ~(3<<8);
   GPIOA->PUPD  &= ~(3<<20);	 
	   
	  GPIOA->PUPD    |= 0X00000200;   //PA4 下拉
	 
	  GPIOA->SR      &= 0XFFFFF9EE;   //高速GPIO
	 
	  //PA4***************************
	 
    //	PA 1 7   OLED
	  GPIOA->PMODE   &= 0XFFFF3FF3;
	  GPIOA->PMODE   |= 0X00004004;   //输出模式	

//	  GPIOA->POTYPE |= 1<<1;     //开漏模式
//	  GPIOA->POTYPE |= 1<<7;   
	  GPIOA->POTYPE &= ~(1<<1);   
    GPIOA->POTYPE &= ~(1<<7);
		
	  GPIOA->PUPD    &= 0XFFFF3FF3;
	 	GPIOA->PUPD    |= 0X00004004;   //上拉
		
	  GPIOA->SR      &= 0XFFFFFF5D;   //高速GPIO

	  //	PA 5 6    IIC
		GPIOA->PMODE   &= 0XFFFFC3FF;
	  GPIOA->PMODE   |= 0X00001400;   //输出模式
		
		GPIOA->POTYPE  &= ~(1<<5);    //推挽模式
	  GPIOA->POTYPE  &= ~(1<<6);
		
    GPIOA->PUPD    &= 0XFFFFCFFF;
	 	GPIOA->PUPD    |= 0X00001000;   //上拉
	 
    GPIOA->SR      &= 0XFFFFFFBF;		//高速GPIO
 }
 
 
 
void TIM1_Conf(u16 pre,u16 per)
 {
  /* Time base configuration */ 
	 RCC->APB2PCLKEN  |= 1<<12;    //使能TIM1时钟
	 TIM1->PSC = per;              //预分频值
   TIM1->AR  = pre;              //自动重装载值
	 TIM1->CTRL1 &= 0xFFFFFC8F;    // 0分频  边沿对齐  向上计数
	 TIM1->CTRL1 |= 0x00000081;    // 允许自动重装载   使能计数器 
	 TIM1->DINTEN |= 1<<0;         //  允许更新中断（TIM_IT_Update）
	 
	 
	NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn,0x02); 
	NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
 	 
 }
 
 


 void TIM3_Conf(u16 pre,u16 per)
 {
  /* Time base configuration */
	 RCC->APB1PCLKEN |= 1<<1;  //使能TIM3时钟
	 
	 TIM3->PSC = per;             //预分频值
   TIM3->AR  = pre;             //自动重装载值

	 TIM3->CTRL1  |= (1<<2);	 
	 TIM3->CTRL1 &= 0xFFFFFC8F;    // 0分频  边沿对齐  向上计数
	 TIM3->CTRL1 |= 0x00000081;    // 允许自动重装载   使能计数器

	
	 TIM3->DINTEN |= 1<<0;         //  禁止更新中断（TIM_IT_Update）

	 NVIC_SetPriority(TIM3_IRQn,0x01);	 	
	 NVIC_EnableIRQ(TIM3_IRQn);
	 
 } 
 
 
 
 
void TIM6_Conf(u16 pre,u16 per)
 {
	 
   RCC->APB1PCLKEN  |= 1<<4;  //使能TIM6时钟
	  TIM6->AR = pre;             //自动重装载值
	  TIM6->PSC= per;             //预分频值
    TIM6->CTRL1 =0X0081;        //	 
	  TIM6->STS = 0;            //清除更新中断标志 
	                            // tim6无设置 分频系数  向上计数寄存器
	  TIM6->DINTEN |= 1<<0;     //允许定时器更新中断 
	 
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
	
	  RCC ->APB2PCLKEN |= 1<<2;  //使能 GPIOA  时钟
	  RCC ->APB2PCLKEN |= 1<<14; //使能 USART1 时钟
//	/* 配置PA2 ,PA3*/
	  GPIOA->PMODE     &= 0XFFFFFF0F;   //先将PA 2 3 所在位清零
	  GPIOA->PMODE     |= 0X000000A0;   //PA2 3 端口复用
	
		GPIOA->POTYPE    &= 0XFFFFFFF3;   //推挽输出
		
		GPIOA->PUPD      &= 0xFFFFFF0F;
		GPIOA->PUPD      |= 0X00000050;   //上拉
		
		GPIOA->SR        &= 0XFFFFFFF3;   //快速模式

	  GPIOA->AFL       &= 0XFFFF00FF;  //先把将要改的位清零
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
	
	temp=(float)(48*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				              //得到整数部分
	fraction=(temp-mantissa)*16;        //得到小数部分
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
		 USART1->CTRL1   |=1<<10 ;   //使能校验
		 USART1->CTRL1   &=0XFFFFFDFF;//偶校验
	}
	else if(EVENODD==1)
	{
		  USART1->CTRL1   |=1<<10 ;   //使能校验
		  USART1->CTRL1   |=1<<9;   //奇校验		
	}
	else
	{
	  USART1->CTRL1   &=0xFFFFFBFF;   //校验禁用
	}
 
	  USART1->CTRL3 &= 0xFFFFF8FF; //  USART_HardwareFlowControl_None
	
	USART1->CTRL1 |= 1<<3;   //发送器使能
	USART1->CTRL1 |= 1<<2;   //接收器使能

  USART1->CTRL1 |= 1<<5;  //接收中断使能 

 	NVIC_SetPriority(USART1_IRQn,0x00);	
	NVIC_EnableIRQ(USART1_IRQn);
	
  
 
	USART1->CTRL1 |= 1<<13;     //串口使能
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
	temp=(float)(48*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				              //得到整数部分
	fraction=(temp-mantissa)*16;        //得到小数部分
  mantissa<<=4;
	mantissa+=fraction;
	
	USART1->BRCF = mantissa;
}

void InitALL()
{
	GPIOInit();
	USART1_Config();			//串口初始化
	
	TIM6_Conf(48-1,106-1);   //模拟串口用定时器
}

