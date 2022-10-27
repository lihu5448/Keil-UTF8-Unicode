#include "include.h"
#include "main.h"
#include "wchar.h"
#include "locale.h"
//此工程 delay_ms delay_us   不准  慎用
wchar_t temp_data[40];
char sendbuf[20];
void Utf8ToUnicode (wchar_t *unicode,const char *utf8 ) 
{
  int ulen = strlen(utf8);
  int pos = 0;
  for(int i=0;i<ulen; )
	{
    int bytes = !(utf8[i]&0x80) ? 1 : !((utf8[i]<<2)&0x80) ? 2 : !((utf8[i]<<3)&0x80) ? 3 : 4;
    if(bytes < 2)
		{
        unicode [pos++] = utf8[i++];
        continue;
		}
		
    int V = utf8[i++] & (0xFF>>(bytes+1));
    for(int j=1;j<bytes;j++)
		 {
       V <<= 6;
       V |= utf8[i++] & 0x3F;
		 }
		 
    unsigned char c = (V >> 24)&0xFF;
    if(c)
		{
		  unicode[pos] =  c;
		}
		
    c = (V >> 16) & 0xFF;
    if(c)
		{
     unicode[pos] = (unicode[pos] << 8) + c;
     pos++;				
		}

   c = (V>>8) & 0xFF;
   unicode[pos] = c;
   c = V & 0xFF;
   if(c)
	 {
    unicode[pos] = (unicode[pos] << 8) + c;
    pos++;	  
	 }
 }

}
 
int i, k = 0,len=0;
 short* p ;
 int LEN = 1000;

u16 data_temp;
int main(void)
{ 
	SystemInit();
	InitALL();
	int c = 100;
	unsigned char data[100] = {0};
  wchar_t str[50] = {0};	

	sprintf(data,"Olá:%d",c);	
  Utf8ToUnicode(str,data);
 	len = wcslen(str);	
	while(1)
	{
	
	}
} 




















