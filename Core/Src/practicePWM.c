#include "stm32f4xx_hal.h"
#include <stdint.h>


#include "practicePWM.h"
//
///*================= Configuration Constants =================*/
//
//#define DSHOT600_TIMER_PERIOD     140
//#define DSHOT600_ONE_HIGH_TICKS   104  // Approx. for logic '1'
//#define DSHOT600_ZERO_HIGH_TICKS   52  // Approx. for logic '0'
//#define DSHOT600_PACKET_LENGTH    16
//
///*================= Global Handles =================*/
//
//// Using TIM1 for all 4 channels.
//TIM_HandleTypeDef htim1;
//
//// DMA handles for each TIM1 channel (adjust the instance names according to your MCU)
//DMA_HandleTypeDef hdma_tim1_ch1;
//DMA_HandleTypeDef hdma_tim1_ch2;
//DMA_HandleTypeDef hdma_tim1_ch3;
//DMA_HandleTypeDef hdma_tim1_ch4;
//
///* Mapping from motor index to timer channel */
//uint32_t motorTimChannels[4] = { TIM_CHANNEL_1, TIM_CHANNEL_2, TIM_CHANNEL_3, TIM_CHANNEL_4 };
//
///* Array of pointers to DMA handles for each motor */
//DMA_HandleTypeDef* motorDmaHandles[4] = { &hdma_tim1_ch1, &hdma_tim1_ch2, &hdma_tim1_ch3, &hdma_tim1_ch4 };
//
///*================= Function Prototypes =================*/
//void SystemClock_Config(void);
//void PWM_DMA_Init(void);
//static void Error_Handler(void);


//void setMotorSpeed_DMA(int motor, int speed);
//
///*================= Implementation =================*/
//
/////**
////  * @brief  Initialize TIM1 PWM for 4 channels with corresponding DMA channels.
////  */
////void PWM_DMA_Init(void)
////{
////    TIM_OC_InitTypeDef sConfigOC = {0};
////
////    /* Enable clocks */
////    __HAL_RCC_TIM1_CLK_ENABLE();
////    __HAL_RCC_DMA2_CLK_ENABLE(); // Adjust if needed for your device
////
////    /* Configure TIM1 base */
////    htim1.Instance = TIM1;
////    htim1.Init.Prescaler = 0;  // Ensure proper timer clock frequency
////    htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
////    htim1.Init.Period = DSHOT600_TIMER_PERIOD - 1;
////    htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
////    htim1.Init.RepetitionCounter = 0;
////    if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
////    {
////        Error_Handler();
////    }
////
////    /* Configure all 4 PWM channels */
////    sConfigOC.OCMode = TIM_OCMODE_PWM1;
////    sConfigOC.Pulse = 0;  // Updated via DMA later.
////    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
////    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
////
////    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
////        Error_Handler();
////    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
////        Error_Handler();
////    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
////        Error_Handler();
////    if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
////        Error_Handler();
////
////    /*
////     * Configure the DMA streams for each TIM1 channel.
////     * The following is an example and the actual DMA stream/channel numbers must be
////     * verified with your STM32F4 documentation.
////     */
////
////    /* DMA configuration for TIM1_CH1 */
////    hdma_tim1_ch1.Instance = DMA2_Stream1;
////    hdma_tim1_ch1.Init.Channel = DMA_CHANNEL_6;
////    hdma_tim1_ch1.Init.Direction = DMA_MEMORY_TO_PERIPH;
////    hdma_tim1_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
////    hdma_tim1_ch1.Init.MemInc = DMA_MINC_ENABLE;
////    hdma_tim1_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
////    hdma_tim1_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
////    hdma_tim1_ch1.Init.Mode = DMA_NORMAL;
////    hdma_tim1_ch1.Init.Priority = DMA_PRIORITY_HIGH;
////    hdma_tim1_ch1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
////    if (HAL_DMA_Init(&hdma_tim1_ch1) != HAL_OK)
////        Error_Handler();
////    __HAL_LINKDMA(&htim1, hdma[TIM_DMA_ID_CC1], hdma_tim1_ch1);
////
////    /* Repeat similar DMA initialization for TIM1_CH2, CH3, and CH4.
////       (Below is a simplified version; adjust DMA stream, channel, and IRQ priorities as needed.)
////    */
////    hdma_tim1_ch2.Instance = DMA2_Stream2;
////    hdma_tim1_ch2.Init.Channel = DMA_CHANNEL_6;
////    hdma_tim1_ch2.Init.Direction = DMA_MEMORY_TO_PERIPH;
////    hdma_tim1_ch2.Init.PeriphInc = DMA_PINC_DISABLE;
////    hdma_tim1_ch2.Init.MemInc = DMA_MINC_ENABLE;
////    hdma_tim1_ch2.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
////    hdma_tim1_ch2.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
////    hdma_tim1_ch2.Init.Mode = DMA_NORMAL;
////    hdma_tim1_ch2.Init.Priority = DMA_PRIORITY_HIGH;
////    hdma_tim1_ch2.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
////    if (HAL_DMA_Init(&hdma_tim1_ch2) != HAL_OK)
////        Error_Handler();
////    __HAL_LINKDMA(&htim1, hdma[TIM_DMA_ID_CC2], hdma_tim1_ch2);
////
////    hdma_tim1_ch3.Instance = DMA2_Stream3;
////    hdma_tim1_ch3.Init.Channel = DMA_CHANNEL_6;
////    hdma_tim1_ch3.Init.Direction = DMA_MEMORY_TO_PERIPH;
////    hdma_tim1_ch3.Init.PeriphInc = DMA_PINC_DISABLE;
////    hdma_tim1_ch3.Init.MemInc = DMA_MINC_ENABLE;
////    hdma_tim1_ch3.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
////    hdma_tim1_ch3.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
////    hdma_tim1_ch3.Init.Mode = DMA_NORMAL;
////    hdma_tim1_ch3.Init.Priority = DMA_PRIORITY_HIGH;
////    hdma_tim1_ch3.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
////    if (HAL_DMA_Init(&hdma_tim1_ch3) != HAL_OK)
////        Error_Handler();
////    __HAL_LINKDMA(&htim1, hdma[TIM_DMA_ID_CC3], hdma_tim1_ch3);
////
////    hdma_tim1_ch4.Instance = DMA2_Stream4;
////    hdma_tim1_ch4.Init.Channel = DMA_CHANNEL_6;
////    hdma_tim1_ch4.Init.Direction = DMA_MEMORY_TO_PERIPH;
////    hdma_tim1_ch4.Init.PeriphInc = DMA_PINC_DISABLE;
////    hdma_tim1_ch4.Init.MemInc = DMA_MINC_ENABLE;
////    hdma_tim1_ch4.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
////    hdma_tim1_ch4.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
////    hdma_tim1_ch4.Init.Mode = DMA_NORMAL;
////    hdma_tim1_ch4.Init.Priority = DMA_PRIORITY_HIGH;
////    hdma_tim1_ch4.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
////    if (HAL_DMA_Init(&hdma_tim1_ch4) != HAL_OK)
////        Error_Handler();
////    __HAL_LINKDMA(&htim1, hdma[TIM_DMA_ID_CC4], hdma_tim1_ch4);
////
////    /* Configure NVIC for DMA streams (example for Stream1; repeat for others as needed) */
////    HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0, 0);
////    HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);
////    // Similarly, enable IRQ for DMA2_Stream2, Stream3, and Stream4.
////}
////
/////**
////  * @brief  Build a DShot600 packet from a throttle value.
////  */

 void BuildDShotPacket(uint16_t throttle, uint16_t *packet)
{
    uint16_t dshotPacket = throttle << 5; // Bits 15:5 = throttle, bit 4 = telemetry (0)
    uint16_t c = dshotPacket;
    uint16_t checksum = 0;
    for (int i = 0; i < 3; i++) {
        checksum ^= (c & 0xF);
        c >>= 4;
    }
    dshotPacket |= (checksum & 0xF);
    *packet = dshotPacket;
}

///**
//  * @brief  Set motor speed via PWM with DMA for the specified motor.
//  * @param  motor: Motor index (0-3). Each motor is mapped to a separate channel.
//  * @param  speed: Speed value (0–200), scaled to throttle (0–2047).
//  */
//void setMotorSpeed_DMA(int motor, int speed)
//{
//    // Ensure motor index is valid.
//    if (motor < 0 || motor >= 4)
//        return;
//
//    // Scale the speed (0-100) to throttle (0–2047)
//    uint16_t throttle = (speed * 2047) / 200;
//    uint16_t packet;
//    BuildDShotPacket(throttle, &packet);
//
//    // Prepare a buffer for 16 PWM compare values.
//    uint16_t pwmBuffer[DSHOT600_PACKET_LENGTH];
//
//    // Build the compare values for each bit (MSB first)
//    for (int i = 0; i < DSHOT600_PACKET_LENGTH; i++) {
//        int bitPos = 15 - i;
//        if (packet & (1 << bitPos))
//            pwmBuffer[i] = DSHOT600_ONE_HIGH_TICKS;
//        else
//            pwmBuffer[i] = DSHOT600_ZERO_HIGH_TICKS;
//    }
//
//    /* Start PWM with DMA on the appropriate TIM1 channel.
//       This call uses the DMA handle associated with the specified motor.
//    */
//    if (HAL_TIM_PWM_Start_DMA(&htim1, motorTimChannels[motor],
//                              (uint32_t *)pwmBuffer, DSHOT600_PACKET_LENGTH) != HAL_OK)
//    {
//        Error_Handler();
//    }
//
//    // Wait for the DMA transfer to complete (in a production system, use a callback).
//    while (HAL_DMA_GetState(motorDmaHandles[motor]) != HAL_DMA_STATE_READY)
//    {
//        ;  // Optionally implement a timeout.
//    }
//
//    HAL_TIM_PWM_Stop_DMA(&htim1, motorTimChannels[motor]);
//
//    HAL_Delay(1); // Optional delay between packets
//}
//
///**
//  * @brief  Main entry point.
//  */
////int main(void)
////{
////    HAL_Init();
////    SystemClock_Config();  // Configure system clock as needed.
////    PWM_DMA_Init();        // Initialize TIM1 PWM and DMA.
////    // Optionally, initialize GPIO here if needed.
////
////    /* Example loop: Ramp speed from 0 to 99 and output on motor 0 (TIM1_CH1). */
////    int speed = 0;
////
////    while (1)
////    {
////
////        HAL_Delay(200);// wait for 200 ms
////        setMotorSpeed_DMA(0, speed);
////        setMotorSpeed_DMA(1, speed);
////        setMotorSpeed_DMA(2, speed);
////        setMotorSpeed_DMA(3, speed++);
////        if (speed >= 190)
////            speed = 0;
////    }
////}
//
///**
//  * @brief  Dummy System Clock Configuration.
//  *         Replace with your actual clock configuration.
//  */
////void SystemClock_Config(void)
////{
////    // This is a placeholder; in a real system you would configure the clock properly.
////}
//
///**
//  * @brief  Error Handler.
//  */
//static void Error_Handler(void)
//{
//    while (1)
//    {
//        // Stay here in case of error.
//    }
//}
//
///**
//  * @brief  DMA interrupt handler.
//  */
//void DMA2_Stream1_IRQHandler(void)
//{
//    HAL_DMA_IRQHandler(&hdma_tim1_ch1);
//}
