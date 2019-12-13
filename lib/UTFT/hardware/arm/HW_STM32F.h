// *** Hardwarespecific functions ***

//#define FSMC_TFT
   #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-parameter"

  #pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif



void UTFT::_hw_special_init(void)
{
 // STM_FSMC_LCD_Init();
#if defined(STM32F107xC) ||defined(MKS_TFT)
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, 0xffff, GPIO_PIN_RESET);

  /*Configure GPIO pins : Pin1_Pin Pin2_Pin */
  GPIO_InitStruct.Pin = 0xffff;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
 // GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct); 
  
  pinMode(LCD_RS,OUTPUT);
  pinMode(LCD_WR,OUTPUT);
  pinMode(LCD_CS,OUTPUT);
  pinMode(LCD_RD,OUTPUT);
  digitalWrite(LCD_CS,LOW);
  digitalWrite(LCD_RS,HIGH);
  digitalWrite(LCD_WR,HIGH);
  digitalWrite(LCD_RD,HIGH);
  //pinMode(LCD_BACKLIGHT_PIN,OUTPUT);
  //digitalWrite(LCD_BACKLIGHT_PIN,LOW); 
  //digitalWrite(LCD_BACKLIGHT_PIN,HIGH);
  //while(1);
  #endif
}


void UTFT::LCD_Writ_Bus(char VH,char VL, byte mode)

{   

#if defined(STM32F107xC)
	if (VH==0) 
	{
		GPIOE->ODR = (uint16_t)VL;
		HAL_GPIO_WritePin(LCD_nWR_GPIO_Port,LCD_nWR_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LCD_nWR_GPIO_Port,LCD_nWR_Pin, GPIO_PIN_SET);
	}
	else
	{

		GPIOE->ODR=(uint16_t)((VH<<8)+VL);
		HAL_GPIO_WritePin(LCD_nWR_GPIO_Port,LCD_nWR_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LCD_nWR_GPIO_Port,LCD_nWR_Pin, GPIO_PIN_SET);
	}
#else
{
	     if (VH == 0) TFT_LCD->REG = VL;
            else TFT_LCD->RAM = VL;
		
}
#endif
   	
   
}

void UTFT::LCD_Write_Bus_8(char com1)
{   

#if defined(STM32F107xC)
	GPIOE->ODR = (uint16_t)com1;
	HAL_GPIO_WritePin(LCD_nWR_GPIO_Port,LCD_nWR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_nWR_GPIO_Port,LCD_nWR_Pin, GPIO_PIN_SET);
	
#else
	TFT_LCD->REG = com1;
	HAL_GPIO_WritePin(LCD_nWR_GPIO_Port,LCD_nWR_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_nWR_GPIO_Port,LCD_nWR_Pin, GPIO_PIN_SET);
	#endif
 

   	
   
}

void UTFT::_set_direction_registers(byte mode)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	switch(mode)
	{
	case 0:
        __HAL_RCC_GPIOE_CLK_ENABLE();
        HAL_GPIO_WritePin(GPIOE, 0xffff, GPIO_PIN_RESET);
        GPIO_InitStruct.Pin = 0xffff;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  break;
  case 1:
  default:
  __HAL_RCC_GPIOE_CLK_ENABLE();
  HAL_GPIO_WritePin(GPIOE, 0xffff, GPIO_PIN_SET);
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT ;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  break;
	}
}

void UTFT::_fast_fill_16(int ch, int cl, long pix)
{ 
   
	volatile long i;
	for(i=0;i<pix;i++)
	{
		
		LCD_Write_DATA(ch,cl);		  
		
	}
}

void UTFT::_fast_fill_8(int ch, long pix)
{
	 
	volatile long  i; 
	for(i=0;i<pix;i++)
	{
		
		LCD_Write_DATA(ch>>8);
		
	}

}
void set_register(byte mode)
{
GPIO_InitTypeDef GPIO_InitStruct;
	//0 output and 1 input
	switch(mode)
	{
	case 0:
        __HAL_RCC_GPIOE_CLK_ENABLE();
        HAL_GPIO_WritePin(GPIOE, 0xffff, GPIO_PIN_RESET);
        GPIO_InitStruct.Pin = 0xffff;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  break;
  case 1:
  
  __HAL_RCC_GPIOE_CLK_ENABLE();
  HAL_GPIO_WritePin(GPIOE, 0xffff, GPIO_PIN_SET);
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT ;
  GPIO_InitStruct.Pin = 0xffff; 
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
  break;
  default:
  break;
	}	
}

/*******************************************************************************
* Function Name  : LCD_ReadRAM
* Description    : Reads the LCD RAM.
* Input          : None
* Output         : None
* Return         : LCD RAM Value.
* Attention		 : None
*******************************************************************************/
/*
__inline uint16_t UTFT::LCD_ReadData16(void)
{  
#if defined(STM32F107xC) && defined(MKS_TFT)
  HAL_GPIO_WritePin(LCD_nRD_GPIO_Port,LCD_nRD_Pin, GPIO_PIN_SET); //Read data clock high
  HAL_GPIO_WritePin(LCD_nWR_GPIO_Port,LCD_nWR_Pin, GPIO_PIN_SET);  //write data clock high
  HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin, GPIO_PIN_SET); //reg select high

  set_register(1);
  delay(10);
   //first clock is dummy so remember to throw those away
  
  HAL_GPIO_WritePin(LCD_nRD_GPIO_Port,LCD_nRD_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_nRD_GPIO_Port,LCD_nRD_Pin, GPIO_PIN_SET); 
  uint8_t  hi_bytes = GPIOE->IDR;

  HAL_GPIO_WritePin(LCD_nRD_GPIO_Port,LCD_nRD_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_nRD_GPIO_Port,LCD_nRD_Pin, GPIO_PIN_SET); 
  uint8_t lo_bytes = GPIOE->IDR;
  uint16_t data =(uint16_t)((hi_bytes<<8)+lo_bytes);

   
  set_register(0);


	return data;
}*/

__inline uint16_t UTFT::LCD_ReadData(void)
{  

  HAL_GPIO_WritePin(LCD_nRD_GPIO_Port,LCD_nRD_Pin, GPIO_PIN_SET); //Read data clock high
  HAL_GPIO_WritePin(LCD_nWR_GPIO_Port,LCD_nWR_Pin, GPIO_PIN_SET);  //write data clock high
  HAL_GPIO_WritePin(LCD_RS_GPIO_Port,LCD_RS_Pin, GPIO_PIN_SET); //reg select high

  set_register(1);
  delay(10);
   //first clock is dummy so remember to throw those away
  
  HAL_GPIO_WritePin(LCD_nRD_GPIO_Port,LCD_nRD_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_nRD_GPIO_Port,LCD_nRD_Pin, GPIO_PIN_SET); 
  uint8_t  hi_bytes = GPIOE->IDR;

  HAL_GPIO_WritePin(LCD_nRD_GPIO_Port,LCD_nRD_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_nRD_GPIO_Port,LCD_nRD_Pin, GPIO_PIN_SET); 
  uint8_t lo_bytes = GPIOE->IDR;
  uint16_t data =(uint16_t)((hi_bytes<<8)+lo_bytes);

   
  set_register(0);


	return data;
}


#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif
