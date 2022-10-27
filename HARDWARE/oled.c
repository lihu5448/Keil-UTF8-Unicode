#include "include.h"
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
//OLED���Դ�
//��Ÿ�ʽ����.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
/**********************************************
//IIC Start
**********************************************/
void IIC_Start(void)
{
	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop(void)
{
	OLED_SDIN_Clr();
	OLED_SCLK_Set();
	OLED_SDIN_Set();
	
}

void IIC_Wait_Ack(void)
{
	OLED_SCLK_Set();
	OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	OLED_SCLK_Clr();
	
	da=IIC_Byte;
	for(i=0;i<8;i++)		
	{
		m=da;
		m=m&0x80;
		if(m==0x80)
			OLED_SDIN_Set();
		else       
			OLED_SDIN_Clr();
		
		da=da<<1;	
		delay_us(4);
		OLED_SCLK_Set();
		delay_us(4);
	  OLED_SCLK_Clr();
	}		
}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);      //Slave address,SA0=0	
	 IIC_Wait_Ack();
   Write_IIC_Byte(0x00);			//write command
	 IIC_Wait_Ack();
   Write_IIC_Byte(IIC_Command); 
	 IIC_Wait_Ack();
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
		 IIC_Wait_Ack();
   Write_IIC_Byte(0x40);			//write data
	 IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
		 IIC_Wait_Ack();
   IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
   Write_IIC_Data(dat);
	else 	
   Write_IIC_Command(dat);
}
/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}
/***********************Delay****************************************/
void Delay_50ms(unsigned int Del_50ms)
{
	unsigned int m;
	for(;Del_50ms>0;Del_50ms--)
		for(m=6245;m>0;m--);
}

void Delay_1ms(unsigned int Del_1ms)
{
	unsigned char j;
	while(Del_1ms--)
	{	
		for(j=0;j<123;j++);
	}
}

//��������

void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
}   	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{	
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF

}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}
void OLED_On(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA); 
	} //������ʾ
}
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	unsigned char c=0,i=0;	
		c=chr-' ';//�õ�ƫ�ƺ��ֵ			
		if(x>Max_Column-1){x=0;y=y+2;}
		if(Char_Size ==16)
			{
			OLED_Set_Pos(x,y);	
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i],OLED_DATA);
			OLED_Set_Pos(x,y+1);
			for(i=0;i<8;i++)
			OLED_WR_Byte(F8X16[c*16+i+8],OLED_DATA);
			}
			else {	
				OLED_Set_Pos(x,y);
				for(i=0;i<6;i++)
				OLED_WR_Byte(F6x8[i],OLED_DATA);
				
			}
}
void OLED_ShowCharh(u8 x,u8 y,u8 chr)
{      	

}
void OLED_ShowCharm(u8 x,u8 y,u8 chr)
{      	
		unsigned char c=0,i=0;	
		c=chr;//�õ�ƫ�ƺ��ֵ			
		if(x>Max_Column-1){x=0;y=y+2;}

		//16 X 32,ԭ����24*48
		OLED_Set_Pos(x,y);	
		for(i=0;i<16;i++)
		OLED_WR_Byte(F28X16[c*64+i],OLED_DATA);
		
		OLED_Set_Pos(x,y+1);
		for(i=0;i<16;i++)
		OLED_WR_Byte(F28X16[c*64+i+16],OLED_DATA);
		
		OLED_Set_Pos(x,y+2);
		for(i=0;i<16;i++)
		OLED_WR_Byte(F28X16[c*64+i+32],OLED_DATA);			

		OLED_Set_Pos(x,y+3);
		for(i=0;i<16;i++)
		OLED_WR_Byte(F28X16[c*64+i+48],OLED_DATA);
		OLED_Set_Pos(x,y+4);

}
//��ʾһ���ַ��Ŵ�
void OLED_ShowStringh(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{
		if(chr[j]<='9'&&chr[j]>='0')
			if(Char_Size)
			OLED_ShowCharh(x,y,chr[j]+1-'0');
			else
			OLED_ShowCharm(x,y,chr[j]+1-'0');	
		else
			if(Char_Size)
			OLED_ShowCharh(x,y,0);
			else
			OLED_ShowCharm(x,y,0);	
			if(Char_Size)
			x+=24;
			else
			x+=16;	
		if(x>120){x=0;y+=2;}
			j++;
	}
}
//m^n����
u32 oled_pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		OLED_ShowChar(x,y,chr[j],Char_Size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

////��ʾ����
//void OLED_ShowCHinese(u8 x,u8 y,u8 no)
//{      			    
//	u8 t,adder=0;
//	OLED_Set_Pos(x,y);	
//    for(t=0;t<16;t++)
//		{
//				OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
//				adder+=1;
//     }	
//		OLED_Set_Pos(x,y+1);	
//    for(t=0;t<16;t++)
//			{	
//				OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
//				adder+=1;
//      }					
//}
/***********������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
    for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 

//��ʼ��SSD1306					    
void OLED_Init(void)
{ 	
	delay_ms(800);
	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x40,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	OLED_Clear();
}  

void ShowOLED(void)
{
	u8 text[25];
	//0 ��T 1��L 2��Q 3T+L 4Q+L			5�ǵ�ʪ�� 			6�ǵ��¶�
	if(cof_showstyle_last != cof_showstyle)
	{
	  cof_showstyle_last = cof_showstyle;
		OLED_Clear();
		delay_us(10);
	}
	
	if(cof_showstyle==0)
	{
   if(Tem>=0)
		{
		sprintf((char*)text,"TEM:");
		OLED_ShowString(0,2,text,16);
		sprintf((char*)text," ");
		OLED_ShowString(32,1,text,16);				
		sprintf((char*)text,"%2d",Tem/10);
		OLED_ShowStringh(40,0,text,0);
		sprintf((char*)text,".");
		OLED_ShowString(72,2,text,16);		
		sprintf((char*)text,"%d",Tem%10);
		OLED_ShowStringh(80,0,text,0);
		sprintf((char*)text,"C");
		OLED_ShowString(100,2,text,16);		
			
		sprintf((char*)text,"HUM:");
		OLED_ShowString(0,6,text,16);		
		sprintf((char*)text,"%2d",Hum/10);
		OLED_ShowStringh(40,4,text,0);
		sprintf((char*)text,".");
		OLED_ShowString(72,6,text,16);		
		sprintf((char*)text,"%d",Hum%10);
		OLED_ShowStringh(80,4,text,0);
		sprintf((char*)text,"%%");
		OLED_ShowString(100,6,text,16);
	  MODS_Poll();						/* ����MODS_Poll() */
		}
		else
		{
		sprintf((char*)text,"TEM:");
		OLED_ShowString(0,2,text,16);
		sprintf((char*)text,"-");
		OLED_ShowString(32,1,text,16);	
		sprintf((char*)text,"%2d",(-Tem)/10);
		OLED_ShowStringh(40,0,text,0);
		sprintf((char*)text,".");
		OLED_ShowString(72,2,text,16);		
		sprintf((char*)text,"%d",(-Tem)%10);
		OLED_ShowStringh(80,0,text,0);
		sprintf((char*)text,"C");
		OLED_ShowString(100,2,text,16);	
			
		sprintf((char*)text,"HUM:");
		OLED_ShowString(0,6,text,16);		
		sprintf((char*)text,"%2d",Hum/10);
		OLED_ShowStringh(40,4,text,0);
		sprintf((char*)text,".");
		OLED_ShowString(72,6,text,16);		
		sprintf((char*)text,"%d",Hum%10);
		OLED_ShowStringh(80,4,text,0);
		sprintf((char*)text,"%%");
		OLED_ShowString(100,6,text,16);
		MODS_Poll();						/* ����MODS_Poll() */
		}
	}
	else if(cof_showstyle==1||cof_showstyle==3)  //��ǿ
	{
		sprintf((char*)text,"   JX SENSOR");
		OLED_ShowString(0,0,text,16);	
		sprintf((char*)text,"%6d",Lux);
		OLED_ShowStringh(0,2,text,0);		
		sprintf((char*)text,"LUX");
		OLED_ShowString(96,4,text,16);	
	  MODS_Poll();						/* ����MODS_Poll() */
	}
	else if(cof_showstyle==2||cof_showstyle==4)   //CO2
	{
		sprintf((char*)text,"   JX SENSOR");
		OLED_ShowString(0,0,text,16);	
		sprintf((char*)text,"%6d",CO2);
		OLED_ShowStringh(0,2,text,0);		
		sprintf((char*)text,"PPM");
		OLED_ShowString(96,4,text,16);
   	MODS_Poll();						/* ����MODS_Poll() */		
	}		
	if(cof_showstyle==3||cof_showstyle==4)
	{
		sprintf((char*)text,"T:%2d.%dC H:%2d.%d%%",Tem/10,Tem%10,Hum/10,Hum%10);
		OLED_ShowString(0,6,text,16);
   	MODS_Poll();						/* ����MODS_Poll() */		
	}
	else if(cof_showstyle==5)			//��ʪ�� 	
	{
		sprintf((char*)text,"   JX SENSOR");
		OLED_ShowString(0,0,text,16);	
		sprintf((char*)text,"HUM:");
		OLED_ShowString(0,6,text,16);		
		sprintf((char*)text,"%2d",Hum/10);;
		OLED_ShowStringh(32,4,text,0);
		sprintf((char*)text,".");
		OLED_ShowString(64,6,text,16);		
		sprintf((char*)text,"%d",Hum%10);;
		OLED_ShowStringh(72,4,text,0);
		sprintf((char*)text,"%%");
		OLED_ShowString(92,6,text,16);	
   	MODS_Poll();						/* ����MODS_Poll() */		
	}
  else if(cof_showstyle==6)			//������ѹǿ
	{
   	sprintf((char*)text,"   JX SENSOR");
		OLED_ShowString(0,0,text,16);	
		
		sprintf((char*)text,"%4d",(int)pressure/100);;
		OLED_ShowStringh(10,2,text,0);
		sprintf((char*)text,".");
		OLED_ShowString(75,4,text,16);
    if((int)pressure%100==0)
    {
		  sprintf((char*)text,"00");
		  OLED_ShowStringh(80,2,text,0);		  
		}
    else if((int)pressure%100<10)	
	  {
	 		sprintf((char*)text,"0%d",(int)pressure%100);;
		  OLED_ShowStringh(80,2,text,0);
	  }		 
		else 
		{
		  sprintf((char*)text,"%2d",(int)pressure%100);;
		  OLED_ShowStringh(80,2,text,0);
		}
		sprintf((char*)text,"MBAR");
		OLED_ShowString(70,6,text,16);
   	MODS_Poll();						/* ����MODS_Poll() */		
	}
	else if(cof_showstyle==7)
	{
		sprintf((char*)text,"   JX SENSOR");
		OLED_ShowString(0,0,text,16);	
		sprintf((char*)text,"TEM:");
		OLED_ShowString(2,5,text,16);			
		if(Tem>=0)
		{
		
			sprintf((char*)text,"%2d",Tem/10);
			OLED_ShowStringh(32,4,text,0);
			sprintf((char*)text,".");
			OLED_ShowString(64,6,text,16);		
			sprintf((char*)text,"%d",Tem%10);
			OLED_ShowStringh(72,4,text,0);
			sprintf((char*)text,"C");
			OLED_ShowString(96,5,text,16);		
		}
		else
		{
			sprintf((char*)text,"-");
			OLED_ShowString(32,5,text,16);	
			sprintf((char*)text,"%2d",(-Tem)/10);
			OLED_ShowStringh(43,4,text,0);
			sprintf((char*)text,".");
			OLED_ShowString(75,6,text,16);		
			sprintf((char*)text,"%d",(-Tem)%10);
			OLED_ShowStringh(83,4,text,0);
			sprintf((char*)text,"C");
			OLED_ShowString(106,5,text,16);	
		}
		MODS_Poll();						/* ����MODS_Poll() */		
	}
}

