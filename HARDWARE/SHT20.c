#include "include.h"


u8 TemSelect=1,cof_showstyle=0,cof_showstyle_last=0;
u8 hour,minutes,seconds;
s16 Tem,Hum,Tem_last,Hum_last,Tem_count=0,Hum_count=0;
u16 ModelBaud,CO2,tvoc,NH3[4],LuxMult;
u32 DQQY,Lux;
s16 LuxOff;
u32 biaozhiwei;
int16_t Tem_K[2],TemOff,HumOff,Hum_K[2];
u8 ModelID,LuxSelect;			//ModelID

/*================================================================
                           IIC address
================================================================*/
#define SHT20ADDR      0x80
#define SHT31ADDR      0x88
/*================================================================
                 ACK  and  NACK  defination
================================================================*/
#define ACK            1
#define NACK           0

/*================================================================
                       HTU20D Command Code
================================================================*/
/*
  Command                         Code              Comment
  Trigger Temperature Measurement 0xe3              Hold master
  Trigger Humidity Measurement    0xe5              Hold master
  Trigger Temperature Measuremeng 0xf3              No Hold master
  Trigger Humidity Measurement    0xf5              No Hold master
  Write user register             0xe6
  Read user register              0xe7
  Soft Reset                      0xfe
*/
#define SOFT_RESET      0xfe
#define READ_REGISTER   0xe7
#define WRITE_REGISTER  0xe6
#define TRIGGER_TEMP    0xf3
#define TRIGGER_HUMI    0xf5

/*================================================================
                    HTU20 operate interface
================================================================*/
#define HTU20_SDA         ((GPIOA->PID)&0X00000020)              //GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_5)
#define HTU20_SCL         ((GPIOA->PID)&0X00000040)              //GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_6)


#define ADDR_24CXX       0xA0
#define SCLH        scl3_h()
#define SCLL        scl3_l()
   
#define SDAH        sda3_h()
#define SDAL        sda3_l()
#define SDA_O       sda_out()
#define SDA_I       sda_in()
#define SCLread     ((GPIOA->PID)&0X00000040)                     //GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_6)
#define SDAread     ((GPIOA->PID)&0X00000020)                     //GPIO_ReadInputDataBit(GPIOA,GPIO_PIN_5)

#define  MS561101BA_SlaveAddress 0xee  //����������IIC�����еĴӵ�ַ

#define  MS561101BA_D1 0x40 
#define  MS561101BA_D2 0x50 
#define  MS561101BA_RST 0x1E 

//#define  MS561101BA_D1_OSR_256 0x40 
//#define  MS561101BA_D1_OSR_512 0x42 
//#define  MS561101BA_D1_OSR_1024 0x44 
//#define  MS561101BA_D1_OSR_2048 0x46 
#define  MS561101BA_D1_OSR_4096 0x48 

//#define  MS561101BA_D2_OSR_256 0x50 
//#define  MS561101BA_D2_OSR_512 0x52 
//#define  MS561101BA_D2_OSR_1024 0x54 
//#define  MS561101BA_D2_OSR_2048 0x56 
#define  MS561101BA_D2_OSR_4096 0x58 

#define  MS561101BA_ADC_RD 0x00 
#define  MS561101BA_PROM_RD 0xA0 
#define  MS561101BA_PROM_CRC 0xAE 
u16 Cal_C[7];  //���ڴ��PROM�е�8������

void scl3_h(void)
{	
    GPIOA->POD |=0X00000040;    //GPIO_SetBits(GPIOA,GPIO_PIN_6);	
}
void scl3_l(void)
{ 
    GPIOA->POD  &=0XFFFFFFBF;    //GPIO_ResetBits(GPIOA,GPIO_PIN_6);	
}

void sda_out(void)
{
	//PA5
	GPIOA->PMODE  &= 0XFFFFF3FF;
	GPIOA->PMODE  |= 0X00000400;   //���
	
//	GPIOA->POTYPE |= 1<<5;   //��©
	GPIOA->POTYPE   &= ~(1<<5);   //����
  
	GPIOA->PUPD   &= 0XFFFFF3FF;    //��λ ����
	GPIOA->PUPD   |= 0X00000400;    //����
	
//	  GPIOA->PUPD   &= 0XFFFFF3FF;   //�������� 
	
	GPIOA->SR     &= 0xFFFFFFBF;   //����ģʽ

}

void sda_in(void)
{
	//PA5
  GPIOA->PMODE  &= 0XFFFFF3FF;   //����ģʽ
	
//	GPIOA->POTYPE |= 1<<5;        //��©
	
	GPIOA->POTYPE   &= ~(1<<5);   //����
	
	GPIOA->PUPD   &= 0XFFFFF3FF;    //��λ ����
	GPIOA->PUPD   |= 0X00000400;    //����
//	  GPIOA->PUPD   &= 0XFFFFF3FF;   //�������� 
	
	GPIOA->SR     &= 0XFFFFFFDF;    //����ģʽ
}
void sda3_h(void)
{ 
  GPIOA->POD  |= 1<<5; 	
}
void sda3_l(void)
{
	//PA5
 GPIOA->POD &= ~(1<<5);
}
void I2C3_delay(void)
{ 
   int i=6; //��������Ż��ٶ� ����������͵�5����д��
   while(i--) 
   { 
  __nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();	   
   } 
}
u8 I2C3_Start(void)
{    
	   SDA_O;
     SCLH;
     delay_us(4);	
	   SDAH;
     delay_us(4);
     if(!SDAread)
			 return 0; //SDA��Ϊ�͵�ƽ������æ,�˳�
     SDAL;
     delay_us(4);
     if(SDAread) 
			 return 0; //SDA��Ϊ�ߵ�ƽ�����߳���,�˳�
     SCLL;
     delay_us(4);
     return 1;
}
void I2C3_Stop(void)
{
 SDA_O;
 SDAL;
 delay_us(4);
 SCLH;
 delay_us(4);
 SDAH;
 delay_us(4);
}

void I2C3_Ack(void)
{
 SDA_O;
 SDAL;
 delay_us(4);
 SCLH;
 delay_us(4);
 SCLL;
 delay_us(4);
 SDAH;
 delay_us(4);
}

void I2C3_NoAck(void)
{
 SDA_O; 	
 SDAH;
 delay_us(4);
 SCLH;
 delay_us(4);
 SCLL;
 delay_us(4);
}

u8 I2C3_WaitAck(void)  //����Ϊ:=1��ACK,=0��ACK
{
 SDA_I;
 SCLL;
 delay_us(4);
 SDAH;   
 delay_us(4);
 SCLH;
 delay_us(4);
 if(SDAread)
 {
     SCLL;
   return 0;
 }
 SCLL;
   return 1;
}

#define REPEAT_CHK_ACK_NUM		8

u8 I2C3_Check(void)
{
  u8 ack,i;
	SDA_I;	
	SCLH;
	for (i=0; i<REPEAT_CHK_ACK_NUM ; i++)
	 {
		if(SDAread==0)
	   {
		  ack = 0;
		  break;
		 }
		else
		 {
			ack = 1;
		 }
	  }	
   delay_us(5);
	 SCLL;
	 delay_us(5);
	 SDA_O;
	return ack;
}


void I2C3_SendByte(u8 SendByte) //���ݴӸ�λ����λ//
{
    u8 i=8;
	  SDA_O;
    while(i--)
    {
       if(SendByte&0x80)
         SDAH;  
       else 
         SDAL;   
       SendByte<<=1;
			 
       delay_us(4);
			 SCLH;
       delay_us(4);
       SCLL;
       delay_us(4);
    }
}
u8 I2C3_ReceiveByte(void) //���ݴӸ�λ����λ//
{ 
   u8 i=8;
   u8 ReceiveByte=0;
	 SDA_I;
   SDAH;    
    while(i--)
    {
			
      ReceiveByte<<=1;  
			delay_us(4);
      SCLH;    
      delay_us(4); 			
      if(SDAread)
      {
       ReceiveByte|=0x01;
      }
		  delay_us(4); 			
      SCLL;
    }
    return ReceiveByte;
}
/**
  * @brief  soft reset by transmit reset command
  * @retval None
  */
void I2cI2cI2cSoftReset(void)
{
  I2C3_Start();
  I2C3_SendByte(SHT20ADDR & 0xfe);  //I2C address + write
  I2C3_WaitAck();
  I2C3_SendByte(SOFT_RESET);        //soft reset
  I2C3_WaitAck(); 
  I2C3_Stop();
} 
/**
  * @brief  SET HTU20D resolution by write register
  * @retval None
  */
void SET_Resolution(void)
{
  I2C3_Start();      
  I2C3_SendByte(SHT20ADDR & 0xfe);
  if(I2C3_WaitAck() == ACK) //I2C address + write + ACK
  {
      I2C3_SendByte(WRITE_REGISTER);
    if(I2C3_WaitAck() == ACK)
    {
        I2C3_SendByte(0x83);
      if(I2C3_WaitAck() == ACK) ;       //���÷ֱ���   11bit RH% ����ʱ�䣺12ms(typ.)
    }                                   //             11bit T�� ����ʱ�䣺9ms(typ.)
  }
  I2C3_Stop();
}

/**
  * @brief  read sht20's converted result
  * @param  TempOrHumiCMD: operation command for temperature or humidity
  * @retval None
  */
u16 ReadSht20(char TempOrHumiCMD)
{
  u16 temp;
  u8 MSB,LSB;
  u16 Humidity,Temperature;
  u8 outtime=0;
  SET_Resolution();  //���÷ֱ���
  I2C3_Start();
  I2C3_SendByte(0x80) ;  //�������豸��ַ
  if(I2C3_WaitAck() != ACK)   
		   return 0;   //I2C address + write + ACK
  I2C3_SendByte(TempOrHumiCMD) ;  
  if(I2C3_WaitAck() != ACK)  
   		 return 0;           
	do
	{
		if(outtime++>200)     
			return 0xffff;
		I2C3_Start();
		I2C3_SendByte(0x81) ;
		delay_ms(6);          //��ʱ6ms
	} while(I2C3_WaitAck()== NACK); //I2C address + read + NACK

	MSB = I2C3_ReceiveByte(); 
  I2C3_Ack();
	LSB = I2C3_ReceiveByte(); 
  I2C3_Ack();
	I2C3_ReceiveByte();
  I2C3_NoAck();
    
	I2C3_Stop();                                //Checksum  + NACK      I2CStop();
  LSB &= 0xfc;                                //Data (LSB) �ĺ���λ�ڽ����������ǰǰ����0
  temp = (MSB << 8) + LSB;

      if (TempOrHumiCMD == ((char)TRIGGER_HUMI))
      {
        /*-- calculate relative humidity [%RH] --*/
        //equation: RH% = -6 + 125 * SRH/2^16         
        Humidity = (temp * 1250) / 65536 ;
         // printf("H:%d\r\n",Humidity);
        return Humidity;
      }
      else
      {
        /*-- calculate temperature [��C] --*/
        //equation:T = -46.85 + 175.72 * ST/2^16
        Temperature = ((temp * 17572) / 65536 - 4685)/10;
		//  printf("T:%d\r\n",Temperature);
        return Temperature;
      }
}
/**
  * @brief  read sht20's converted result
  * @param  TempOrHumiCMD: operation command for temperature or humidity
  * @retval None
  */
void ReadSht20Pro()          ////////////////////////////////////////////////////////////////////////////////////////////////sht20//////////////////////////////////////////////////////////////////
{
	Tem = ReadSht20(TRIGGER_TEMP);
	
	if(Tem==0xffff)
	{		
		SetLed(0);		//Ϩ��led
		return ;	
	}
	else
	{		
		SetLed(1);		
	}
	Hum=ReadSht20(TRIGGER_HUMI);
	if(Hum==0xffff)
	{
		SetLed(0);		
	}
	else
	{
		SetLed(1);		
	}
	
	Tem+= TemOff;
	Hum+= HumOff;

  if(Tem<-400)
	{
		Tem_count++;
		if(Tem_count>=10)
		{
			Tem_count = 0 ; 
			Tem =-400;
		}
		else
		  Tem = Tem_last; 
	}
  if(Tem>800)
	{
		Tem_count++;
		if(Tem_count>=10)
		{
			Tem_count = 0 ; 
			Tem = 800;
		}
		else
		  Tem = Tem_last; 
	}
	
  if(Hum<0)
	{
		Hum_count++;
		if(Hum_count>=10)
		{
			Hum_count = 0 ; 
			Hum =0;
		}
		else
		  Hum = Hum_last;
  }
	if(Hum>=1000)
	{
		Hum_count++;
		if(Hum_count>=10)
		{
			Hum_count = 0 ; 
			Hum =999;
		}
		else
		  Hum = Hum_last;
	}
	Tem_last = Tem;
	Hum_last = Hum;
}
u8 sht31first=0;

u16 ReadSht31()  /////////////////////////////////////////////////////////////////////////////////////////////////////////////sht31///////////////////////////////////////////////////////////////////
{
	u32 temp;
	u8 MSB,LSB;
	//u16 Humidity,Temperature;
  //	u8 outtime=0;
 if(sht31first==0)
	{
		I2C3_Start();
		I2C3_SendByte(SHT31ADDR & 0xfe);  //I2C address + write
		if(I2C3_WaitAck() != ACK)   return 0;   //I2C address + write + ACK
		I2C3_SendByte(0x2C) ;  
		if(I2C3_WaitAck() != ACK)   return 0;   
		I2C3_SendByte(0x06) ;  
		if(I2C3_WaitAck() != ACK)   return 0;       
		I2C3_Stop(); 
		sht31first=1;
	}
 else
	{
		I2C3_Start();
		I2C3_SendByte((SHT31ADDR & 0xfe)+1);    //I2C address + write
		if(I2C3_WaitAck() != ACK)   return 0;   //I2C address + write + ACK	
		MSB = I2C3_ReceiveByte(); 
		I2C3_Ack();
		LSB =I2C3_ReceiveByte (); 
		I2C3_Ack();
		I2C3_ReceiveByte();
		I2C3_Ack();
		//LSB &= 0xfc;                                
		temp = (MSB << 8) + LSB;
		Tem=(1750*(temp)/65535-480);

		MSB = I2C3_ReceiveByte(); 
		I2C3_Ack();
		LSB = I2C3_ReceiveByte(); 
		I2C3_Ack();
		I2C3_ReceiveByte();
		I2C3_NoAck();
		I2C3_Stop();                       //Checksum  + NACK      I2CStop();	
		//LSB &= 0xfc;                                //Data (LSB) �ĺ���λ�ڽ����������ǰǰ����0
		temp = (MSB << 8) + LSB;
	 Hum=1000*(temp)/65535;	
	 sht31first=0;	
	 Hum+=HumOff;
	 Tem+=TemOff;
   if(Tem<-400)Tem=-400;
   if(Tem>800)Tem=800;
   if(Hum<0)Hum=0;
   if(Hum>1000)Hum=1000;	
	}
	return 0;
}
//�����ǹ��նȶ�ȡ����
u8 BUF[8];
void Single_Write_BH1750(u8 REG_Address)
{
	I2C3_Start();
	I2C3_SendByte(0x46);   //�����豸��ַ+д�ź�
	I2C3_WaitAck();   //I2C address + write + ACK
	I2C3_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ 
	I2C3_WaitAck();   //I2C address + write + ACK
	I2C3_Stop();                   //����ֹͣ�ź�
}
u8 hilux=0;
void Set20Wlux()
{
 	Single_Write_BH1750(0x41);   // ͸����	 01000_xxx				����Ϊ3��			60%
	Single_Write_BH1750(0x7c);   // ͸����	 011_XXXXX
	hilux=1;
}
void Set6WLux()
{
	Single_Write_BH1750(0x45);   // ͸����			����λ3��			182%
	Single_Write_BH1750(0x96);   // ͸����
	hilux=0;
}

//*********************************************************//
//                                                         //
//��������BH1750�ڲ�����                                   //
//                                                         //
//*********************************************************//
void Multiple_read_BH1750(void)
{  
   	u8 i;	
    I2C3_Start();                          //��ʼ�ź�
    I2C3_SendByte(0x46+1);         //�����豸��ַ+���ź�
	I2C3_WaitAck();	
	 for (i=0; i<3; i++)                      //������ ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = I2C3_ReceiveByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 2)
        {
           I2C3_NoAck();				
        }
        else
        {						
           I2C3_Ack();					
       }
   }    
	I2C3_Stop();                          //ֹͣ�ź�
	delay_ms(5);                          
   
  Lux=BUF[0]*256+BUF[1];

  if(LuxSelect>1)				
	 {
	  if(hilux) 
		 Lux*=3;
	  if(Lux<30000&&hilux)		//С��30000���õ;���
		 {
		  Set6WLux();
		 //Multiple_read_BH1750();
		 }
	  if(Lux>40000&&!hilux)		//С��30000���õ;���
		 {
		  Set20Wlux();
		 // Multiple_read_BH1750();
		 }	
	 }
  else
	 Set6WLux();
	Lux=(Lux*LuxMult)/100;
  Lux+=LuxOff;

	if(LuxSelect==1)
	 {
		if(Lux>65535)Lux=65535; 
		if(Lux<0)
			    Lux=0; 
	 }
	else if(LuxSelect==2)
	 {
	  if(Lux>200000)Lux=200000; 
	  if(Lux<0)
			    Lux=0;
	 }
	else
		Lux=0;	
}
void MS561101BA_RESET(void)//�����ݶ���������������ܲ���ȥ����ע�͵��˴�I2C3_WaitAck();
{	
	I2C3_Start();
	I2C3_SendByte(MS561101BA_SlaveAddress);
	I2C3_WaitAck();
	//delay_ms(1);
	I2C3_SendByte(MS561101BA_RST);
	I2C3_WaitAck();
	//delay_ms(1);
	I2C3_Stop();
}
//��PROM��ȡ����У׼����
void MS561101BA_PROM_READ(void)
{
	u16 d1,d2;
	u8 i;
	for(i=0;i<=6;i++)
	{
		I2C3_Start();
		I2C3_SendByte(MS561101BA_SlaveAddress);
		I2C3_WaitAck();
		I2C3_SendByte((MS561101BA_PROM_RD+i*2));
		I2C3_WaitAck();

		I2C3_Start();
		I2C3_SendByte(MS561101BA_SlaveAddress+0x01);
		I2C3_WaitAck();
		d1=I2C3_ReceiveByte();
		I2C3_Ack();
		d2=I2C3_ReceiveByte();
		I2C3_NoAck();
		I2C3_Stop();

		delay_ms(10);
		Cal_C[i]=(d1<<8)|d2;
	}
//��ӡPROM��ȡ����У׼���ݣ�������ݴ����Ƿ�����
//	printf("C1 =%d\r\n",Cal_C[1]);
//	printf("C2 =%d\r\n",Cal_C[2]);
//	printf("C3 =%d\r\n",Cal_C[3]);
//	printf("C4 =%d\r\n",Cal_C[4]);
//	printf("C5 =%d\r\n",Cal_C[5]);
//	printf("C6 =%d\r\n",Cal_C[6]);
}
u8 InitReadQiya()
{
	MS561101BA_RESET();
	delay_ms(100);
	MS561101BA_PROM_READ();
	delay_ms(100);
	return 0;
}

void delay_my_ms(u16 time) 
{
	u16 i=0;      
	while(time--)    
	{        
		i=12000;  //�Լ�����       
		while(i--)  ;       
	} 
}
u32 MS561101BA_DO_CONVERSION(u8 command)
{
	u32 conversion=0;
	u32 conv1,conv2,conv3; 
	I2C3_Start();
	I2C3_SendByte(MS561101BA_SlaveAddress);
	I2C3_WaitAck();
	I2C3_SendByte(command);	
	I2C3_WaitAck();
	I2C3_Stop();
	delay_my_ms(20);	
	I2C3_Start();
	I2C3_SendByte(MS561101BA_SlaveAddress);
	I2C3_WaitAck();
	I2C3_SendByte(0x00);
	I2C3_WaitAck();
	I2C3_Stop();

	I2C3_Start();
	I2C3_SendByte(MS561101BA_SlaveAddress+1);
	I2C3_WaitAck();
	conv1=I2C3_ReceiveByte();
	I2C3_Ack();
	
	conv2=I2C3_ReceiveByte();
	I2C3_Ack();
	conv3=I2C3_ReceiveByte();
	I2C3_NoAck();
	I2C3_Stop();
	conversion= (conv1<<16) + (conv2<<8) + conv3;
	return conversion;
}
void MS561101BA_readdata(defMS5611data *ms5611data)
{
	double dT,readdata,T1,T2,Aux,OFF2,SENS2,Qiya;
	double mOFF,SENS;  //ʵ���¶ȵ���,ʵ���¶�������
	readdata= MS561101BA_DO_CONVERSION(MS561101BA_D2_OSR_4096);	
	delay_my_ms(10);
//	printf("%u /n",D2_Temp);
	dT=readdata - (((u32)Cal_C[5])<<8);
	T1=(2000+dT*((u32)Cal_C[6])/8388608);
	T1=T1/10*10;
//	ms5611data->temperature=T1;
	readdata= MS561101BA_DO_CONVERSION(MS561101BA_D1_OSR_4096);
	mOFF=(u32)(Cal_C[2]<<16)+((u32)Cal_C[4]*dT)/128;
	SENS=(u32)(Cal_C[1]<<15)+((u32)Cal_C[3]*dT)/256;
	//�¶Ȳ���
 if(T1 < 2000)// second order temperature compensation when under 20 degrees C
	{
		T2 = (dT*dT) / 0x80000000;
		Aux = (T1-2000)*(T1-2000);
		OFF2 = 2.5*Aux;
		SENS2 = 1.25*Aux;
		if(T1 < -1500)
		{
			Aux = (T1+1500)*(T1+1500);
			OFF2 = OFF2 + 7*Aux;
			SENS2 = SENS + 5.5*Aux;
		}
	}
 else  //(Temperature > 2000)
	{
		T2 = 0;
		OFF2 = 0;
		SENS2 = 0;
	}	
	T1 -= T2;
	mOFF = mOFF - OFF2;
	SENS = SENS - SENS2;	
	//ms5611data->pressure=(u32)((readdata*SENS/2097152-OFF)/32768);
	//ms5611data->temperature=T1;
	//printf("�¶�:T1:%f",T1);
	Qiya=(readdata*SENS/2097152-mOFF)/32768;	
	//printf("����ѹ:T1:%f\r\n",Qiya);
	DQQY=Qiya;
	//Tem=T1/10;
}

