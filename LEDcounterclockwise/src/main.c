/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
//#include <stdio.h>

void msDelay(uint32_t msTime);
GPIO_InitTypeDef GPIO_LEDgreen;
GPIO_InitTypeDef GPIO_LEDred;
GPIO_InitTypeDef GPIO_LEDorange;
GPIO_InitTypeDef GPIO_LEDblue;
GPIO_InitTypeDef GPIOA_Config;
void EXTI0_IRQHandler();
void msDelay(uint32_t msTime)
{
	for(uint32_t i=0; i<msTime*4000;i++);
}

int main(void)
{

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


//  configuration for the User Button:
  GPIOA_Config.GPIO_Mode = GPIO_Mode_IN;
  GPIOA_Config.GPIO_Pin = GPIO_Pin_0;
  GPIOA_Config.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(GPIOA, &GPIOA_Config);

GPIO_LEDgreen.GPIO_Pin = GPIO_Pin_12;
GPIO_LEDgreen.GPIO_Mode = GPIO_Mode_OUT;
GPIO_LEDgreen.GPIO_OType = GPIO_OType_PP;
GPIO_LEDgreen.GPIO_Speed = GPIO_Speed_50MHz ;
GPIO_LEDred.GPIO_Pin = GPIO_Pin_14;
GPIO_LEDred.GPIO_Mode = GPIO_Mode_OUT;
GPIO_LEDred.GPIO_OType = GPIO_OType_PP;
GPIO_LEDred.GPIO_Speed = GPIO_Speed_50MHz ;
GPIO_LEDorange.GPIO_Pin = GPIO_Pin_13;
GPIO_LEDorange.GPIO_Mode = GPIO_Mode_OUT;
GPIO_LEDorange.GPIO_OType = GPIO_OType_PP;
GPIO_LEDorange.GPIO_Speed = GPIO_Speed_50MHz ;
GPIO_LEDblue.GPIO_Pin = GPIO_Pin_15;
GPIO_LEDblue.GPIO_Mode = GPIO_Mode_OUT;
GPIO_LEDblue.GPIO_OType = GPIO_OType_PP;
GPIO_LEDblue.GPIO_Speed = GPIO_Speed_50MHz ;

GPIO_Init(GPIOD,&GPIO_LEDgreen);
GPIO_Init(GPIOD,&GPIO_LEDred);
GPIO_Init(GPIOD,&GPIO_LEDblue);
GPIO_Init(GPIOD,&GPIO_LEDorange);

/* Enable clock for SYSCFG */
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	    /* Tell system that you will use PA0 for EXTI_Line0 */
	    	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	    	EXTI_InitTypeDef EXTI_Config;
	    	/* PA0 is connected to EXTI_Line0 */
	    	EXTI_Config.EXTI_Line = EXTI_Line0;
	    	/* Enable interrupt */
	    	EXTI_Config.EXTI_LineCmd = ENABLE;
	    	/* Interrupt mode */
	    	EXTI_Config.EXTI_Mode = EXTI_Mode_Interrupt;
	    	/* Triggers on rising and falling edge */
	    	EXTI_Config.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	    	/* Add to EXTI */
	    	EXTI_Init(&EXTI_Config);

	// Configuration EXTI0 interrupt control:
		NVIC_InitTypeDef NVICEXTI0_Config;

		NVICEXTI0_Config.NVIC_IRQChannel = EXTI0_IRQn ;
		NVICEXTI0_Config.NVIC_IRQChannelCmd = ENABLE;
		NVICEXTI0_Config.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVICEXTI0_Config.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_Init(&NVICEXTI0_Config);

		EXTI0_IRQHandler();


  /* Initialize LEDs */
 // STM_EVAL_LEDInit(LED3);
  //STM_EVAL_LEDInit(LED4);
  //STM_EVAL_LEDInit(LED5);
 // STM_EVAL_LEDInit(LED6);

  /* Turn on LEDs */
  //STM_EVAL_LEDOn(LED3);
  /*STM_EVAL_LEDOn(LED4);
  STM_EVAL_LEDOn(LED5);
  STM_EVAL_LEDOn(LED6);*/

  /* Infinite loop */
//int i=1;
//int k=1;
  while (1)
  {

	  GPIO_WriteBit(GPIOD, GPIO_Pin_14, Bit_SET);
	  msDelay(1000);
	  GPIO_WriteBit(GPIOD, GPIO_Pin_14, Bit_RESET);
	  msDelay(1000);
	  GPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
	  msDelay(1000);
	  GPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);
	  msDelay(1000);
	  GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_SET);
	  msDelay(1000);
	  GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_RESET);
	  msDelay(1000);
	  GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_SET);
	  msDelay(1000);
	  GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_RESET);
	  msDelay(1000);
	 // printf("%i",sizeof(char));
	 // k++;
	 // if(k==5){
		  //i=0;
		  //printf("%i",sizeof(char));

		//cout << "Size of int : " <<sizeof(int);
	  //}
//------------------------------------------------------------------------------------------------//





  }
}

void EXTI0_IRQHandler(void){

	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {

		/* Do your stuff when PA0 is PRESSED */
			GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_SET);
			msDelay(1000);
			GPIO_WriteBit(GPIOD, GPIO_Pin_12, Bit_RESET);}
			/* Clear interrupt flag */
				EXTI_ClearITPendingBit(EXTI_Line0);


		}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /*TODO, implement your code here */
return -1;
}
