#include "sd.h"
#include "SPI.h"

#define SDCARD_SPI     SPI
uint8_t  SD_Type=0;  


uint8_t SD_SPI_Read_Write_Byte( uint8_t data)
{
  //return SPI_Read_Write(SD_SPI,data);	
  return SDCARD_SPI.transfer(data);	
}


void SD_SPI_CS_Set(uint8_t level)
{
  digitalWrite(SDCARD_CS, level);
}


//SD_CD insert detect
void SD_CD_WP_Init(void)
{
  pinMode(SDCARD_DT, INPUT_PULLUP);
}

uint8_t SD_CD_Inserted(void)
{
  return digitalRead(SDCARD_DT);
}

void SD_SPI_Init(void)
{  

  SD_CD_WP_Init();


  pinMode(SDCARD_CS, OUTPUT);
  SDCARD_SPI.begin();
  SD_SPI_CS_Set(1);
}

void SD_DeInit(void)
{
  SD_SPI_CS_Set(1);
}

void SD_SetLowSpeed(void)
{
  SDCARD_SPI.setClockDivider(SPI_BAUDRATEPRESCALER_4);
}

void SD_SetHighSpeed(void)
{
  SDCARD_SPI.setClockDivider(SPI_BAUDRATEPRESCALER_2);
}

void SD_Cancel_CS(void)
{
  SD_SPI_CS_Set(1);
  SD_SPI_Read_Write_Byte(0xff);
}

uint8_t SD_Select(void)
{
  SD_SPI_CS_Set(0);
  if(SD_Wait_Ready()==0)return 0;
  SD_Cancel_CS();
  return 1;
}


uint8_t SD_Wait_Ready(void)
{
  uint32_t t=0;
  do
  {
    if(SD_SPI_Read_Write_Byte(0XFF)==0XFF)return 0;
    t++;		  	
  }while(t<0XFFFFFF);
  return 1;
}

uint8_t SD_Get_Ack(uint8_t Response)
{
  uint16_t Count=0xFFFF;   						  
  while ((SD_SPI_Read_Write_Byte(0XFF)!=Response) && Count)  Count--; 
  
  if (Count==0)
    return SD_RESPONSE_FAILURE;
  else 
    return SD_RESPONSE_NO_ERROR;
}


uint8_t SD_RecvData(uint8_t*buf,uint16_t len)
{			  	  
  if(SD_Get_Ack(0xFE))return 1;
  while(len--)
  {
    *buf=SD_SPI_Read_Write_Byte(0xFF);
    buf++;
  }
  SD_SPI_Read_Write_Byte(0xFF);
  SD_SPI_Read_Write_Byte(0xFF);									  					    
  return 0;
}


uint8_t SD_Send_Data(uint8_t*buf,uint8_t cmd)
{	
  uint16_t t;		  	  
  if(SD_Wait_Ready())  return 1;  
  SD_SPI_Read_Write_Byte(cmd);
  if(cmd!=0XFD)
  {
    for(t=0;t<512;t++)SD_SPI_Read_Write_Byte(buf[t]);

    SD_SPI_Read_Write_Byte(0xFF); 
    SD_SPI_Read_Write_Byte(0xFF);
    t = SD_SPI_Read_Write_Byte(0xFF); 
    if((t&0x1F) != 0x05)return 2;   						  					    
  }						 									  					    
  return 0;
}
									  
uint8_t SD_SendCmd(uint8_t cmd, uint32_t arg, uint8_t crc)
{
  uint8_t r1;	
  uint8_t Retry=0; 
  SD_Cancel_CS();             
  if(SD_Select())  return 0XFF;
  SD_SPI_Read_Write_Byte(cmd | 0x40);
  SD_SPI_Read_Write_Byte(arg >> 24);
  SD_SPI_Read_Write_Byte(arg >> 16);
  SD_SPI_Read_Write_Byte(arg >> 8);
  SD_SPI_Read_Write_Byte(arg);	  
  SD_SPI_Read_Write_Byte(crc); 
  if(cmd==CMD12)  SD_SPI_Read_Write_Byte(0xff);//Skip a stuff byte when stop reading
  Retry=0X1F;
  do
  {
    r1=SD_SPI_Read_Write_Byte(0xFF);
  }while((r1&0X80) && Retry--);	 
  return r1;
}	

uint8_t SD_GetCID(uint8_t *cid_data)
{
  uint8_t r1;	   
  r1=SD_SendCmd(CMD10,0,0x01);
  if(r1==0x00)
  {
    r1=SD_RecvData(cid_data,16);	 
  }
  SD_Cancel_CS();
  if(r1)  return 1;
  else    return 0;
}	


uint8_t SD_GetCSD(uint8_t *csd_data)
{
  uint8_t r1;	 
  r1=SD_SendCmd(CMD9,0,0x01);    
  if(r1==0)
  {
    r1=SD_RecvData(csd_data, 16);
  }
  SD_Cancel_CS();//ȡ��Ƭѡ
  if(r1)  return 1;
  else    return 0;
}  


uint32_t SD_Get_Sector_Count(void)
{
  uint8_t csd[16];
  uint32_t Capacity;  
  uint8_t n;
  uint16_t csize;  					    
  if(SD_GetCSD(csd) != 0) return 0;	
  if((csd[0]&0xC0) == 0x40)	       
  {	
    csize = csd[9] + ((uint16_t)csd[8] << 8) + 1;
    Capacity = (uint32_t)csize << 10; 		   
  }
  else//V1.XX�Ŀ� 
  {	
    n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
    csize = (csd[8] >> 6) + ((uint16_t)csd[7] << 2) + ((uint16_t)(csd[6] & 3) << 10) + 1;
    Capacity= (uint32_t)csize << (n - 9);  
  }
  return Capacity;
}

uint8_t SD_Init(void)
{
  uint8_t r1;      
  uint16_t retry;  
  uint8_t buf[4];  
  uint16_t i;

  SD_SPI_Init();		
  SD_SetLowSpeed();
  for(i=0;i<10;i++)SD_SPI_Read_Write_Byte(0XFF); 
  retry=20;
  do
  {
    r1 = SD_SendCmd(CMD0,0,0x95);//����IDLE״̬ ����
  }while((r1!=0X01) && retry--);
  SD_Type=0;   //Ĭ���޿�
  if(r1==0X01)
  {
    if(SD_SendCmd(CMD8,0x1AA,0x87)==1)  //SD V2.0
    {
      for(i=0;i<4;i++)buf[i]=SD_SPI_Read_Write_Byte(0XFF);	
      if(buf[2]==0X01&&buf[3]==0XAA)    
      {
        retry = 0XFFFE;
        do
        {
          SD_SendCmd(CMD55,0,0X01);	    
          r1 = SD_SendCmd(CMD41,0x40000000,0X01);
        }while(r1 && retry--);
        if(retry&&SD_SendCmd(CMD58,0,0X01) == 0)
        {
          for(i=0;i<4;i++)buf[i]=SD_SPI_Read_Write_Byte(0XFF);
          if(buf[0]&0x40)SD_Type=SD_TYPE_V2HC;    
          else SD_Type=SD_TYPE_V2;   
        }
      }
    }
    else//SD V1.x/ MMC	V3
    {
      SD_SendCmd(CMD55,0,0X01);		
      r1 = SD_SendCmd(CMD41,0,0X01);	
      if(r1 <= 1)
      {		
        SD_Type = SD_TYPE_V1;
        retry = 0XFFFE;
        do //IDLE
        {
          SD_SendCmd(CMD55,0,0X01);	
          r1 = SD_SendCmd(CMD41,0,0X01);
        }while(r1 && retry--);
      }
      else
      {
        SD_Type = SD_TYPE_MMC;//MMC V3
        retry = 0XFFFE;
        do //IDLE
        {											    
          r1 = SD_SendCmd(CMD1,0,0X01);
        }while(r1 && retry--);  
      }
      if(retry==0 || SD_SendCmd(CMD16,512,0X01)!=0)
        SD_Type = SD_TYPE_ERR;
    }
  }
  SD_Cancel_CS();    
  SD_SetHighSpeed();
  if(SD_Type) return 0;
  else if(r1) return r1; 	   
  return 0xaa;
}

uint8_t SD_ReadDisk(uint8_t*buf,uint32_t sector,uint8_t cnt) 	//fatfs/usb
{
  uint8_t r1;
  if(SD_Type != SD_TYPE_V2HC) sector <<= 9;
  if(cnt == 1)
  {
    r1 = SD_SendCmd(CMD17, sector, 0X01);
    if(r1 == 0)									
    {
      r1 = SD_RecvData(buf,512);		   
    }
  }else
  {
    r1 = SD_SendCmd(CMD18, sector, 0X01);
    do
    {
      r1 = SD_RecvData(buf, 512);
      buf += 512;  
    }while(--cnt && r1==0); 	
    SD_SendCmd(CMD12, 0, 0X01);
  }   
  SD_Cancel_CS();//ȡ��Ƭѡ
  return r1;//
}

uint8_t SD_WriteDisk(uint8_t*buf,uint32_t sector,uint8_t cnt)	//fatfs/usb
{
  uint8_t r1;
  if(SD_Type!=SD_TYPE_V2HC) sector *= 512;
  if(cnt == 1)
  {
    r1 = SD_SendCmd(CMD24, sector, 0X01);
    if(r1 == 0)//ָ��ͳɹ�
    {
      r1 = SD_Send_Data(buf, 0xFE);  
    }
  }else
  {
    if(SD_Type != SD_TYPE_MMC)
    {
      SD_SendCmd(CMD55, 0, 0X01);	
      SD_SendCmd(CMD23, cnt, 0X01);
    }
    r1 = SD_SendCmd(CMD25, sector, 0X01);
    if(r1 == 0)
    {
      do
      {
        r1 = SD_Send_Data(buf, 0xFC); 
        buf += 512;  
      }while(--cnt && r1==0);
      r1 = SD_Send_Data(0, 0xFD);
    }
  }   
  SD_Cancel_CS();
  return r1;
}	

