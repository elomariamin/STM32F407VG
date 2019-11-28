/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
//#include <stdio.h>
/**
 * sfsdgfsdfsd
 */
void msDelay(uint32_t msTime);
GPIO_InitTypeDef GPIO_LEDgreen;
GPIO_InitTypeDef GPIO_LEDred;
GPIO_InitTypeDef GPIO_LEDorange;
GPIO_InitTypeDef GPIO_LEDblue;
void msDelay(uint32_t msTime)
{
	for(uint32_t i=0; i<msTime*4000;i++);
}

int main(void)
{

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
/////////////////////////////////////////////////

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
