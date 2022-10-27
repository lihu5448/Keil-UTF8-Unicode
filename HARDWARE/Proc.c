#include "include.h"
 
 //2KB
#define FLASH_USER_START_ADDR    ((uint32_t)0x08007000)  /* Start @ of user Flash area */

 u8 CpuID[12];
 u16 cpuID[6];
 u16 DQSelect,DACSelect,cof_DACcheng,cof_DACchu,cof_5vcheng,cof_5vchu,DAC2_Style,cof_yurevalue;
 s16 cof_DACb;
 u32 cof_DACmax;
 u16 Flash_Check;
 u8 EVENODD;

uint32_t EraseCounter = 0x00, Address = 0x00;
uint32_t Data = 0x3210ABCD;
uint32_t NbrOfPage = 0x00;
__IO FLASH_STS FLASHStatus ;

void GetLockCode(void)
{
 u32 CpuID[3];
 //获取CPU唯一ID
 CpuID[0]=*(vu32*)(0x1ffff4fc);
 CpuID[1]=*(vu32*)(0x1ffff500);
 CpuID[2]=*(vu32*)(0x1ffff504);
 cpuID[0]=CpuID[0]>>16;
 cpuID[1]=CpuID[0];
 cpuID[2]=CpuID[1]>>16;
 cpuID[3]=CpuID[1];
 cpuID[4]=CpuID[2]>>16;
 cpuID[5]=CpuID[2];
 //加密算法,很简单的加密算法
}

void ResetInf()
{
	  /* Unlock the Flash to enable the flash control register access *************/ 
  FLASH_Unlock();
    
  /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR); 
  /* Erase the FLASH pages */

  if (FLASH_EraseOnePage(FLASH_USER_START_ADDR )!= FLASH_COMPL)
		{
      while (1)
      {
      }
		}
		
  Address = FLASH_USER_START_ADDR;

  while(FLASH_ProgramWord(FLASH_USER_START_ADDR, 0x12345678) != FLASH_COMPL);
  while(FLASH_ProgramWord(FLASH_USER_START_ADDR+4, 0x1) != FLASH_COMPL);
  Address = Address + 4;
   while(FLASH_ProgramWord(FLASH_USER_START_ADDR+8, 0x2) != FLASH_COMPL);		//0 2400， 1 4800 2 9600
  Address = Address + 4;
  while(FLASH_ProgramWord(FLASH_USER_START_ADDR+12, 0xffffffff) != FLASH_COMPL);
  Address = Address + 4;
  while(FLASH_ProgramWord(FLASH_USER_START_ADDR+16, 0) != FLASH_COMPL);
  while(FLASH_ProgramWord(FLASH_USER_START_ADDR+20, 0) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+92, 1100) != FLASH_COMPL);
  while(FLASH_ProgramWord(FLASH_USER_START_ADDR+96, 148) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+100, 1085) != FLASH_COMPL);
  while(FLASH_ProgramWord(FLASH_USER_START_ADDR+104, 532) != FLASH_COMPL);
//	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+72, 0xffffffff) != FLASH_COMPL);	  
}
void WriteInf()
{
	 FLASH_Unlock();  
  /* Erase the user Flash area
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/
  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR); 
  /* Erase the FLASH pages */
    if (FLASH_EraseOnePage(FLASH_USER_START_ADDR)!= FLASH_COMPL)
      while (1)
      {
		  
      }
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR, 0x12345678) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+4, ModelID) != FLASH_COMPL);    //  ModelID
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+8, ModelBaud) != FLASH_COMPL);  //ModelBaud
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+12, 0xffffffff) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+16, TemOff) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+20, HumOff) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+24, DAC2_Style) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+28, cof_showstyle) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+32, DQSelect) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+36, TemSelect) != FLASH_COMPL);    
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+40, LuxSelect) != FLASH_COMPL);           
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+44, cof_DACmax) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+48, cof_DACcheng) != FLASH_COMPL);                                                                                                                
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+60, cof_5vcheng) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+64, cof_5vchu) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+68, DACSelect) != FLASH_COMPL);	  
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+72, EVENODD) != FLASH_COMPL);	  
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+76, CO2Off) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+80, ischange) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+84, LuxMult) != FLASH_COMPL);           
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+88, LuxOff) != FLASH_COMPL);
	
	
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+92, Tem_K[0]) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+96, Tem_K[1]) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+100, Hum_K[0]) != FLASH_COMPL);
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+104, Hum_K[1]) != FLASH_COMPL);	
	while(FLASH_ProgramWord(FLASH_USER_START_ADDR+108, pressure_off) != FLASH_COMPL);		
	
  FLASH_Lock();
}



void FlashCheck()
{
	u16 i =0;
	Flash_Check=0;
	for(i=0;i<256;i++)
	Flash_Check+=*(__IO uint32_t*)(0x8000000+i*4);
	for(i=0;i<256;i++)
	Flash_Check+=*(__IO uint32_t*)(0x8001000+i*4);
	for(i=0;i<256;i++)
	Flash_Check+=*(__IO uint32_t*)(0x8002000+i*4);
	for(i=0;i<256;i++)
	Flash_Check+=*(__IO uint32_t*)(0x8003000+i*4);
}
void ReadInf()
{
  u32 dateread[4];		//4个字节的存储信息
  Address = FLASH_USER_START_ADDR;

	dateread[0] = *(__IO uint32_t *)(FLASH_USER_START_ADDR);     //  确认是否是所要用的地址
	dateread[1] = *(__IO uint32_t *)(FLASH_USER_START_ADDR+4);   //  ModelID
	dateread[2] = *(__IO uint32_t *)(FLASH_USER_START_ADDR+8);   //  ModelBaud
	dateread[3] = *(__IO uint32_t *)(FLASH_USER_START_ADDR+12);
	TemOff = *(__IO uint32_t *)(FLASH_USER_START_ADDR+16);
	HumOff = *(__IO uint32_t *)(FLASH_USER_START_ADDR+20);
	DAC2_Style= *(__IO uint32_t *)(FLASH_USER_START_ADDR+24);
	cof_showstyle= *(__IO uint32_t *)(FLASH_USER_START_ADDR+28);
	DQSelect= *(__IO uint32_t *)(FLASH_USER_START_ADDR+32);
	TemSelect= *(__IO uint32_t *)(FLASH_USER_START_ADDR+36);
	LuxSelect= *(__IO uint32_t *)(FLASH_USER_START_ADDR+40);
	cof_DACmax= *(__IO uint32_t *)(FLASH_USER_START_ADDR+44);
	cof_DACcheng= *(__IO uint32_t *)(FLASH_USER_START_ADDR+48);
	cof_DACchu= *(__IO uint32_t *)(FLASH_USER_START_ADDR+52);
	cof_DACb = *(__IO uint32_t *)(FLASH_USER_START_ADDR+56);
	cof_5vcheng = *(__IO uint32_t *)(FLASH_USER_START_ADDR+60);
	cof_5vchu = *(__IO uint32_t *)(FLASH_USER_START_ADDR+64);
	DACSelect = *(__IO uint32_t *)(FLASH_USER_START_ADDR+68);
	EVENODD = *(__IO uint32_t *)(FLASH_USER_START_ADDR+72);
	CO2Off=*(__IO uint32_t *)(FLASH_USER_START_ADDR+76);
	ischange=*(__IO uint32_t *)(FLASH_USER_START_ADDR+80);
	LuxMult=*(__IO uint32_t *)(FLASH_USER_START_ADDR+84);	
	LuxOff=*(__IO uint32_t *)(FLASH_USER_START_ADDR+88);


  Tem_K[0]=*(__IO uint32_t *)(FLASH_USER_START_ADDR+92);
  Tem_K[1]=*(__IO uint32_t *)(FLASH_USER_START_ADDR+96);
	Hum_K[0]=*(__IO uint32_t *)(FLASH_USER_START_ADDR+100);	
	Hum_K[1]=*(__IO uint32_t *)(FLASH_USER_START_ADDR+104);
	pressure_off = *(__IO uint32_t *)(FLASH_USER_START_ADDR+108);
	
	ModelID=dateread[1];
	if(ModelID>253)
		ModelID=253;
	ModelBaud=dateread[2];
	if(ModelBaud>6)				//0 1 2 3 4 5 6 - 2400 4800 9600 19200 38400 57600 115200
		ModelBaud=2;
	
	if(LuxMult>60000&&LuxOff==-1)//光照倍数初始化为1.00,光照修正初始化为0
	 {LuxMult=100;LuxOff=0;}
	 
	if(cof_DACmax>60000)
	cof_DACmax=5000;
 // printf("ModelID:%d,Baud:%d\r\n",ModelID,ModelBaud);
  if(dateread[0]!=0x12345678)	//如果是新的内存块
  {
	 ResetInf();
	 ReadInf(); 
  }
//	printf("ReadInf OK\r\n");
	  FLASH_Lock();
}


void RS485_SendBuf(u8 *data,u16 len)
{
	u16  i;
	GPIOA->POD |= 1<<4;   //485使能端(PA4)置高
	
	for(i=0;i<len;i++)
	{
		USART1->DAT = (uint8_t)data[i];
		  /* Loop until transmit data register is empty */
		while((USART1->STS & (1<<7))==RESET); //判断发送数据缓冲区是否为空
//		  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);	  
	}
	  while((USART1->STS & (1<<6))==RESET);  //判断是否完成
//	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET); 
	
	GPIOA->POD &= ~(1<<4);   //485使能端(PA4)置低
	
}



void SetSDAPP()
{
   RCC->APB2PCLKEN |= 1<<2; //使能GPIOA时钟
	 //PA5
	 GPIOA->PMODE  &= 0XFFFFF3FF;
	 GPIOA->PMODE  |= 0X00000400;  //PA5 输出
   
	 GPIOA->POTYPE &= ~(1<<5);     //推挽输出

	 GPIOA->PUPD   &= 0XFFFFF3FF;
	 GPIOA->PUPD   |= 0X00000400;  //上拉
	
	 GPIOA->SR     &= ~(1<<5);     //高速
	
	 GPIOA->POD    |= 1<<5;   //输出高
}
void SetSDAOD()
{
	 RCC->APB2PCLKEN |= 1<<2; //使能GPIOA时钟
	 //PA5
	 GPIOA->PMODE  &= 0XFFFFF3FF;  //PA5 输入
	 GPIOA->POTYPE |= 1<<5;        //开漏模式

	 GPIOA->PUPD   &= 0XFFFFF3FF;
	 GPIOA->PUPD   |= 0X00000400;  //上拉
	
	 GPIOA->SR     &= ~(1<<5);     //高速	
}


//#define IO_SCLK GPIO_PIN_1
//#define IO_CS   GPIO_PIN_5
//#define IO_CS2  GPIO_PIN_9
//#define IO_DIN  GPIO_PIN_7

void DAC7512(u16 DAData)			//满电压是5000mV  4096分度值
{
	u8 i;
	u32 temp=DAData;
	SetSDAPP();
	
	GPIOA->POD &= ~(1<<1);  //IO_SCLK(PA1)
	GPIOA->POD &= ~(1<<5);  //IO_CS(PA5)
	GPIOA->POD |=   1<<1;   //IO_SCLK(PA1)
	temp=temp*cof_5vcheng/cof_5vchu;//    /5000*4096
//	if(temp>4095)
//		temp=4095;
	if(temp>4295)
		temp=4295;
	DAData=temp;
	for(i=0;i<16;i++)//AD7888写入命令与获取数值一次。
	{  
		if((DAData&(0x8000>>i))>>(15-i))
			GPIOA->POD  |= 1<<7 ; //PA7置高
		else
		GPIOA->POD    &= ~(1<<7) ; //PA7置低

		GPIOA->POD    &= ~(1<<1);//PA1//下降写入
		GPIOA->POD    &= ~(1<<7);//PA7 启动转换;//每次数据移入后，DIN还需要置0真变态
    GPIOA->POD    |=  1<<1; 
	}
	GPIOA->POD &= ~(1<<1);  // 这里还需要SCLK置0，更变态,datasheet上却没提
	GPIOA->POD |=   1<<5;
	
	SetSDAOD();
}
void DAC7512_2(u16 DAData)			//满电压是5000mV  4096分度值
{
	u8 i;
	u32 temp=DAData;
	//SetSDAPP();	
	
	GPIOA->POD &= ~(1<<1);  //IO_SCLK(PA1)
	GPIOA->POD &= ~(1<<9);  //IO_CS2(PA9)
	GPIOA->POD |=   1<<1;   //IO_SCLK(PA1)
	temp=temp*cof_5vcheng/cof_5vchu;//    /5000*4096
	if(temp>4095)
		temp=4095;
	//temp=4095;
	DAData=temp;
	for(i=0;i<16;i++)//AD7888写入命令与获取数值一次。
	{  
		if((DAData&(0x8000>>i))>>(15-i))
		GPIOA->POD  |= 1<<7 ; //PA7置高
		else
		GPIOA->POD    &= ~(1<<7) ; //PA7置低			
		
		GPIOA->POD    &= ~(1<<1);//PA1//下降写入
		GPIOA->POD    &= ~(1<<7);//PA7 启动转换;//每次数据移入后，DIN还需要置0真变态
    GPIOA->POD    |=  1<<1; 		
		
	}
	
	GPIOA->POD &= ~(1<<1);  // 这里还需要SCLK置0，更变态,datasheet上却没提
	GPIOA->POD |=   1<<9;
	//SetSDAOD();
}







