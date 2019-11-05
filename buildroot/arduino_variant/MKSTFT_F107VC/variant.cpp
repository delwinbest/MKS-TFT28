/*
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#include "pins_arduino.h"
#include "stm32f1xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

// Pin number
const PinName digitalPin[] = {
  // Right side
  PB_11, //D0
  PB_10, //D1
  PB_2,  //D2
  PB_0,  //D3
  PA_7,  //D4
  PA_6,  //D5
  PA_5,  //D6
  PA_4,  //D7
  PA_3,  //D8
  PA_2,  //D9
  PA_1,  //D10
  PA_0,  //D11
  PC_15, //D12
  PC_14, //D13
  PC_13, //D14
  // Left side
  PB_7,  //D15
  PB_6,  //D16
  PB_5,  //D17
  PB_4,  //D18
  PB_3,  //D19
  PA_15, //D20
  PA_14, //D21 - SWCLK
  PA_13, //D22 - SWDI0
  PA_12, //D23 - USB DP
  PA_11, //D24 - USB DM
  PA_10, //D25
  PA_9,  //D26
  PA_8,  //D27
  PB_15, //D28
  PB_14, //D29
  PB_13, //D30
  PB_12, //D31
  // Other
  PB_8,  //D32 - BOOT0 - User buttons
  PB_1,  //D33 - LED
  PB_9,  //D34 - USB DISC
  PD_14,//D35 LCD Backlight
  PD_15,//D36 LCD RS
  PC_8,//D37 LCD CS
  PC_5,//D38 Touch input IRQ
  PD_11,//D39 SDCARD chip select 
  PD_15,//D40 LCD_RD
  PC_12,//D41 unknown yet
  // Duplicated pins to avoid issue with analogRead
  // A0 have to be greater than NUM_ANALOG_INPUTS
  PB_0,  //D35/A0 = D3
  PA_7,  //D36/A1 = D4
  PA_6,  //D37/A2 = D5
  PA_5,  //D38/A3 = D6
  PA_4,  //D39/A4 = D7
  PA_3,  //D40/A5 = D8
  PA_2,  //D41/A6 = D9
  PA_1,  //D42/A7 = D10
  PA_0   //D43/A8 = D11
};

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 72000000
  *            HCLK(Hz)                       = 72000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            PLL_Source                     = HSE
  *            PLL_Mul                        = 9
  *            Flash Latency(WS)              = 2
  *            ADC Prescaler                  = 6
  *            USB Prescaler                  = 1.5
  * @param  None
  * @retval None
  */

#if defined(STM32F107xC) && defined(MKS_TFT)
//extern HCD_HandleTypeDef hhcd_USB_OTG_FS;
//extern TIM_HandleTypeDef htim2;
//extern UART_HandleTypeDef huart3;
#elif defined(STM32F103xE) && defined(CZMINI)
extern SD_HandleTypeDef hsd;
#endif

extern DMA_HandleTypeDef hdma_usart2_rx;
extern TIM_HandleTypeDef htim7;
//extern UART_HandleTypeDef huart2;

  
void kill_dog(void)
{
/*	while (1)
	{
	}
	//HAL_Init();
	SCB->VTOR = (FLASH_BASE | 0x8000);
WWDG->SR = 0;
asm volatile("cpsid i");
__disable_irq();
//__HAL_DBGMCU_FREEZE_WWDG();

//HAL_SuspendTick();
*/
}

void initVariant_old(void)
{
	
WWDG->SR = 0;
HAL_RCC_DeInit();
TIM1->CR1=0;
TIM2->CR1=0;

TIM1->BDTR=0;
BKP->CR=0;
HAL_NVIC_DisableIRQ(TIM1_TRG_COM_IRQn);
HAL_NVIC_DisableIRQ(TIM1_CC_IRQn);
HAL_NVIC_DisableIRQ(TIM1_BRK_IRQn);
HAL_NVIC_DisableIRQ(TAMPER_IRQn);
HAL_NVIC_DisableIRQ(SPI3_IRQn);
HAL_NVIC_DisableIRQ(SPI2_IRQn);
HAL_NVIC_DisableIRQ(SPI1_IRQn);
//SCB->VTOR = (FLASH_BASE | 0x8000);
__HAL_DBGMCU_FREEZE_WWDG();
//HAL_SuspendTick();

//MX_GPIO_Init();
}

void WWDG_IRQHandler_exp(void)
{
   
    //WWDG_ClearFlag();    /*Remove pre wakeup interrupt flag*/
    __HAL_RCC_CLEAR_RESET_FLAGS(); 
    
    //LED1 = ~LED1;         /*LED state turnover */
}

void WWDG_IRQHandler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  //while (1)
 // {
 // }
 WWDG_IRQHandler_exp();
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}
void HardFault_Handler(void)
{
  __asm volatile (
    " movs r0,#4       \n"
    " movs r1, lr      \n"
    " tst r0, r1       \n"
    " beq _MSP         \n"
    " mrs r0, psp      \n"
    " b _HALT          \n"
  "_MSP:               \n"
    " mrs r0, msp      \n"
  "_HALT:              \n"
    " ldr r1,[r0,#20]  \n"
    " bkpt #0          \n"
  );
}

WEAK void SystemInit_B (void)
{
  /* Reset the RCC clock configuration to the default reset state(for debug purpose) */
  /* Set HSION bit */
  //return;
  RCC->CR |= (uint32_t)0x00000001;

  /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
#if !defined(STM32F105xC) && !defined(STM32F107xC)
  RCC->CFGR &= (uint32_t)0xF0FF0000;
#else
  RCC->CFGR &= (uint32_t)0xF0FF0000;
#endif /* STM32F105xC */

  /* Reset HSEON, CSSON and PLLON bits */
  RCC->CR &= (uint32_t)0xFEF6FFFF;

  /* Reset HSEBYP bit */
  RCC->CR &= (uint32_t)0xFFFBFFFF;

  /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
  RCC->CFGR &= (uint32_t)0xFF80FFFF;

#if defined(STM32F105xC) || defined(STM32F107xC)
  /* Reset PLL2ON and PLL3ON bits */
  RCC->CR &= (uint32_t)0xEBFFFFFF;

  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x00FF0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;
#elif defined(STM32F100xB) || defined(STM32F100xE)
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x009F0000;

  /* Reset CFGR2 register */
  RCC->CFGR2 = 0x00000000;
#else
  /* Disable all interrupts and clear pending bits  */
  RCC->CIR = 0x0010000;
#endif /* STM32F105xC */


#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif

}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  *
  * @note   Each time the core clock (HCLK) changes, this function must be called
  *         to update SystemCoreClock variable value. Otherwise, any configuration
  *         based on this variable will be incorrect.
  *
  * @note   - The system frequency computed by this function is not the real
  *           frequency in the chip. It is calculated based on the predefined
  *           constant and the selected clock source:
  *
  *           - If SYSCLK source is HSI, SystemCoreClock will contain the HSI_VALUE(*)
  *
  *           - If SYSCLK source is HSE, SystemCoreClock will contain the HSE_VALUE(**)
  *
  *           - If SYSCLK source is PLL, SystemCoreClock will contain the HSE_VALUE(**)
  *             or HSI_VALUE(*) multiplied by the PLL factors.
  *
  *         (*) HSI_VALUE is a constant defined in stm32f1xx.h file (default value
  *             8 MHz) but the real value may vary depending on the variations
  *             in voltage and temperature.
  *
  *         (**) HSE_VALUE is a constant defined in stm32f1xx.h file (default value
  *              8 MHz or 25 MHz, depending on the product used), user has to ensure
  *              that HSE_VALUE is same as the real frequency of the crystal used.
  *              Otherwise, this function may have wrong result.
  *
  *         - The result of this function could be not correct when using fractional
  *           value for HSE crystal.
  * @param  None
  * @retval None
  */
  
WEAK void SystemCoreClockUpdate_B (void)
{
  uint32_t tmp = 0, pllmull = 0, pllsource = 0;

#if defined(STM32F105xC) || defined(STM32F107xC)
  uint32_t prediv1source = 0, prediv1factor = 0, prediv2factor = 0, pll2mull = 0;
#endif /* STM32F105xC */

#if defined(STM32F100xB) || defined(STM32F100xE)
  uint32_t prediv1factor = 0;
#endif /* STM32F100xB or STM32F100xE */

  /* Get SYSCLK source -------------------------------------------------------*/
  tmp = RCC->CFGR & RCC_CFGR_SWS;
tmp=0x4;
  switch (tmp)
  {
    case 0x00:  /* HSI used as system clock */
      SystemCoreClock = HSI_VALUE;
      break;
    case 0x04:  /* HSE used as system clock */
      SystemCoreClock = HSE_VALUE;
      break;
    case 0x08:  /* PLL used as system clock */

      /* Get PLL clock source and multiplication factor ----------------------*/
      pllmull = RCC->CFGR & RCC_CFGR_PLLMULL;
      pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;

#if !defined(STM32F105xC) && !defined(STM32F107xC)
      pllmull = ( pllmull >> 18) + 2;

      if (pllsource == 0x00)
      {
        /* HSI oscillator clock divided by 2 selected as PLL clock entry */
        SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
      }
      else
      {
 #if defined(STM32F100xB) || defined(STM32F100xE)
       prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1;
       /* HSE oscillator clock selected as PREDIV1 clock entry */
       SystemCoreClock = (HSE_VALUE / prediv1factor) * pllmull;
 #else
        /* HSE selected as PLL clock entry */
        if ((RCC->CFGR & RCC_CFGR_PLLXTPRE) != (uint32_t)RESET)
        {/* HSE oscillator clock divided by 2 */
          SystemCoreClock = (HSE_VALUE >> 1) * pllmull;
        }
        else
        {
          SystemCoreClock = HSE_VALUE * pllmull;
        }
 #endif
      }
#else
      pllmull = pllmull >> 18;

      if (pllmull != 0x0D)
      {
         pllmull += 2;
      }
      else
      { /* PLL multiplication factor = PLL input clock * 6.5 */
        pllmull = 13 / 2;
      }

      if (pllsource == 0x00)
      {
        /* HSI oscillator clock divided by 2 selected as PLL clock entry */
        SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
      }
      else
      {/* PREDIV1 selected as PLL clock entry */

        /* Get PREDIV1 clock source and division factor */
        prediv1source = RCC->CFGR2 & RCC_CFGR2_PREDIV1SRC;
        prediv1factor = (RCC->CFGR2 & RCC_CFGR2_PREDIV1) + 1;

        if (prediv1source == 0)
        {
          /* HSE oscillator clock selected as PREDIV1 clock entry */
          SystemCoreClock = (HSE_VALUE / prediv1factor) * pllmull;
        }
        else
        {/* PLL2 clock selected as PREDIV1 clock entry */

          /* Get PREDIV2 division factor and PLL2 multiplication factor */
          prediv2factor = ((RCC->CFGR2 & RCC_CFGR2_PREDIV2) >> 4) + 1;
          pll2mull = ((RCC->CFGR2 & RCC_CFGR2_PLL2MUL) >> 8 ) + 2;
          SystemCoreClock = (((HSE_VALUE / prediv2factor) * pll2mull) / prediv1factor) * pllmull;
        }
      }
#endif /* STM32F105xC */
      break;

    default:
      SystemCoreClock = HSI_VALUE;
      break;
  }

  /* Compute HCLK clock frequency ----------------*/
  /* Get HCLK prescaler */
  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
  /* HCLK clock frequency */
  SystemCoreClock >>= tmp;
}



WEAK void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
#if defined(STM32F107xC) && defined(MKS_TFT)
    RCC_PeriphCLKInitTypeDef PeriphClkInit;
#endif
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
#if defined(STM32F107xC) && defined(MKS_TFT)
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV5;
    RCC_OscInitStruct.Prediv1Source = RCC_PREDIV1_SOURCE_PLL2;
    RCC_OscInitStruct.PLL2.PLL2State = RCC_PLL2_ON;
    RCC_OscInitStruct.PLL2.PLL2MUL = RCC_PLL2_MUL8;
    RCC_OscInitStruct.PLL2.HSEPrediv2Value = RCC_HSE_PREDIV2_DIV5;
#endif
#if defined(STM32F103xE) && defined(CZMINI)
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
#endif
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
        Error_Handler();

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
            |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
        Error_Handler();

#if defined(STM32F107xC) && defined(MKS_TFT)
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV3;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
        Error_Handler();
#endif

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
#if defined(STM32F107xC) && defined(MKS_TFT)
    __HAL_RCC_PLLI2S_ENABLE();
#endif
    HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}






void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void TIM1_TRG_COM_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */

 // HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

#if defined(STM32F107xC) && defined(MKS_TFT)
/**
* @brief This function handles EXTI line0 interrupt.
*/

void PendSV_Handler(void)
{
}
void PVD_IRQHandler(void)
{
	
}
void OTG_FS_WKUP_IRQHandler(void)
{
}

void TAMPER_IRQHandler(void)
{
	
}

void SVC_Handler (void)
{
}

void SPI3_IRQHandler(void)
{
}

void SPI2_IRQHandler(void)
{
}
void SPI1_IRQHandler(void)
{
}
void RTC_IRQHandler (void)
{
}
void RCC_IRQHandler(void)
{
}

WEAK void EXTI0_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_IRQn 0 */

  /* USER CODE END EXTI0_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
  /* USER CODE BEGIN EXTI0_IRQn 1 */

  /* USER CODE END EXTI0_IRQn 1 */
}
/*
void TIM1_CC_IRQHandler(void)
{
	
}
*/
void TIM1_BRK_IRQHandler(void)
{
	
}

/**
* @brief This function handles EXTI line1 interrupt.
*/
WEAK void EXTI1_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI1_IRQn 0 */

  /* USER CODE END EXTI1_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
  /* USER CODE BEGIN EXTI1_IRQn 1 */

  /* USER CODE END EXTI1_IRQn 1 */
}


/**
* @brief This function handles USB OTG FS global interrupt.
*/
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
  //HAL_HCD_IRQHandler(&hhcd_USB_OTG_FS);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}
#endif
#ifdef __cplusplus
}
#endif
