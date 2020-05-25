/* 25.05.2020 Automotive Mechatronics Lab_1
 *LOOPBACKMODE
 * Controller: STM32F407VG
 *      Group: A
 *      Member Nr.: 7
 *    Author: Mohamed Amine, El Omari Alaoui
 *    SystemCoreClock = 168 MHz
 */


/* Includes */

#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "stdint.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_can.h"
#include "misc.h"

void PIN_Configuration(void);
void CAN_Configuration(void);
void CANEXT_Intteruption(void);
void msDelay(uint32_t msTime);

void msDelay(uint32_t msTime)
{
	for(uint32_t i=0; i<msTime*2000;i++);
}

int main(void)
{
	// Enable Peripherie-Cores:

	SystemInit();

	// Call programmed functions:
	PIN_Configuration();
	CAN_Configuration();
	CANEXT_Intteruption();

  while (1)
  {
	  //Standby Mode:
	__WFI();

  }
}
//Pin configuration (Port D/A):
void PIN_Configuration(void)
{
	// Activation of the clocks for GPIO Port D:
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	// Activation of the clocks for GPIO Port A:
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


	GPIO_InitTypeDef GPIO_Config;
	// GPIO configuration for the green LED:
	GPIO_Config.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Config.GPIO_OType = GPIO_OType_PP;
	GPIO_Config.GPIO_Pin = GPIO_Pin_12;
	GPIO_Config.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Config.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOD, &GPIO_Config);


	//only for testing purposes: will quickly switch on and off each time the user btn is pressed
	GPIO_InitTypeDef GPIO_LEDblue;
	GPIO_LEDblue.GPIO_Pin = GPIO_Pin_15;
	GPIO_LEDblue.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_LEDblue.GPIO_OType = GPIO_OType_PP;
	GPIO_LEDblue.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOD,&GPIO_LEDblue);

	//only for testing purposes: will turn on and off each time can1 receives msgid 0x42
	GPIO_InitTypeDef GPIO_LEDorange;
	GPIO_LEDorange.GPIO_Pin = GPIO_Pin_13;
	GPIO_LEDorange.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_LEDorange.GPIO_OType = GPIO_OType_PP;
	GPIO_LEDorange.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOD,&GPIO_LEDorange);


	// GPIO configuration for the can:
	GPIO_Config.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Config.GPIO_OType = GPIO_OType_PP;
	GPIO_Config.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Config.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Config.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOD, &GPIO_Config);
	// Connection between can and pin:
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);

	GPIO_InitTypeDef GPIOA_Config;
	// GPIO configuration for the User Button:
    GPIOA_Config.GPIO_Mode = GPIO_Mode_IN;
	GPIOA_Config.GPIO_Pin = GPIO_Pin_0;
	GPIOA_Config.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIOA_Config);



}

// CAN configuration for CAN1:
void CAN_Configuration(void)
{
	// Enable the clock for CAN1:
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

	// configuration for CAN:
	CAN_InitTypeDef CAN_Config;
	CAN_StructInit(&CAN_Config);
	//Baudrate setting to 250Kbit/s
	CAN_Config.CAN_SJW = CAN_SJW_1tq;
	CAN_Config.CAN_BS1 = CAN_BS1_12tq;
	CAN_Config.CAN_BS2 = CAN_BS2_5tq;
	CAN_Config.CAN_Prescaler = 16;
	CAN_Config.CAN_Mode = 0x01;
	CAN_Init(CAN1, &CAN_Config);

	//Creating a filter which enables the reception of messages

	CAN_FilterInitTypeDef CAN_Filter;
	CAN_Filter.CAN_FilterActivation = ENABLE;
	CAN_Filter.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	CAN_Filter.CAN_FilterIdHigh = 0;
	CAN_Filter.CAN_FilterIdLow = 0;
	CAN_Filter.CAN_FilterMaskIdHigh = 0;
	CAN_Filter.CAN_FilterMaskIdLow = 0;
	CAN_Filter.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_Filter.CAN_FilterNumber = 0;
	CAN_Filter.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInit(&CAN_Filter);
}

// Function for CAN1 & EXTI0 Interrupt:

void CANEXT_Intteruption(void)
{
	// Enable Can interrupt:
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);

	// Configuration CAN interrupt control:
	NVIC_InitTypeDef NVICCAN_Config;

	NVICCAN_Config.NVIC_IRQChannel = CAN1_RX0_IRQn ;
	NVICCAN_Config.NVIC_IRQChannelCmd = ENABLE;
	NVICCAN_Config.NVIC_IRQChannelPreemptionPriority = 2;
	NVICCAN_Config.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVICCAN_Config);

	// Enable clock for SYSCFG */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	// Tell system that you will use PA0 for EXTI_Line0 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

   	EXTI_InitTypeDef EXTI_Config;
   	// PA0 is connected to EXTI_Line0
   	EXTI_Config.EXTI_Line = EXTI_Line0;
   	// Enable interrupt
   	EXTI_Config.EXTI_LineCmd = ENABLE;
   	// Interrupt mode
   	EXTI_Config.EXTI_Mode = EXTI_Mode_Interrupt;
   	// Triggers on rising and falling edge
   	EXTI_Config.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
   	// Add to EXTI
   	EXTI_Init(&EXTI_Config);

	// Configuration EXTI0 interrupt control:

   	NVIC_InitTypeDef NVICEXTI0_Config;
	NVICEXTI0_Config.NVIC_IRQChannel = EXTI0_IRQn ;
	NVICEXTI0_Config.NVIC_IRQChannelCmd = ENABLE;
	NVICEXTI0_Config.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVICEXTI0_Config.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_Init(&NVICEXTI0_Config);

}

// Function for EXTI0 the Handler: // Case for  2. condition:
void EXTI0_IRQHandler(void)
{
	CanTxMsg Send;
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		/* Do your stuff when PA0 is PRESSED */
		Send.IDE = CAN_Id_Standard;
		Send.StdId = 0x27A;
		Send.ExtId = 0;
		Send.DLC = 1;
		Send.RTR = CAN_RTR_Data;

		Send.Data[0] = 00000111;
		CAN_Transmit(CAN1, &Send);

		// Switch on the LED
		GPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_SET);
		msDelay(500);
		GPIO_WriteBit(GPIOD, GPIO_Pin_15, Bit_RESET);

		Send.IDE = CAN_Id_Standard;
		Send.StdId = 0x37A;
		Send.ExtId = 0;
		Send.DLC = 5;
		Send.RTR = CAN_RTR_Data;

		Send.Data[0] = 0xFF;
		Send.Data[1] = 0xFF;
		Send.Data[2] = 0xFF;
		Send.Data[3] = 0xFF;
		Send.Data[4] = 0xFF;
		CAN_Transmit(CAN1, &Send);

		// Clear interrupt flag
		EXTI_ClearITPendingBit(EXTI_Line0);
		}
}

// Function for CAN1 the Handler: // Case for  1. condition:
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg Receive;
	CanTxMsg Send;

	uint8_t counter;
	uint16_t large = 0x00;

	// Getting message:
	if(SET != CAN_GetFlagStatus(CAN1, CAN_FLAG_FMP0))
	{
	// Wait until status is set:
	 return;
	}

	CAN_Receive(CAN1, CAN_FIFO0, &Receive);
	GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
	msDelay(500);
	if( Receive.StdId== 0x42)
	{
			// receiving message:
			Send.IDE = CAN_Id_Standard;
			Send.StdId = 0x17A;
			Send.ExtId = 0;
			Send.DLC = 1;
			Send.RTR = CAN_RTR_Data;

			/// Find the largest byte in the message:
			for(counter = 0; counter< Receive.DLC; counter++)
			{
				if (Receive.Data[counter]> large)
				{
					large = Receive.Data[counter];
				}
			}
	           //Send the message
			Send.Data[0] = large;
			CAN_Transmit(CAN1, &Send);
            // Switch on the LED
			GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_SET);
			msDelay(500);
			GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_RESET);

	}
	else
	{
			Send.IDE = CAN_Id_Standard;
			Send.StdId = 0x42;
			Send.ExtId = 0;
			Send.DLC = 4;
			Send.RTR = CAN_RTR_Data;

			Send.Data[0] = 0x007;
			Send.Data[1] = 0x049;
			Send.Data[2] = 0x015;
			Send.Data[3] = 0x0BA;
			CAN_Transmit(CAN1,&Send);
}

}
