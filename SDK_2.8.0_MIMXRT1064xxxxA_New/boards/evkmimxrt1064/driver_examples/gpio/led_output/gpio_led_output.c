/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define EXAMPLE_LED_GPIO     BOARD_USER_LED_GPIO
#define EXAMPLE_LED_GPIO_PIN BOARD_USER_LED_GPIO_PIN
#define EXAMPLE_DELAY_COUNT  8000000


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief delay a while.
 */
void delay(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* The PIN status */
volatile bool g_pinSet = false;
volatile bool heartbeat = false;
/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < EXAMPLE_DELAY_COUNT; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {kGPIO_DigitalOutput, 0, kGPIO_NoIntmode};

    /* Board pin, clock, debug console init */
    BOARD_ConfigMPU();
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Print a note to terminal. */
    PRINTF("\r\n GPIO Driver example\r\n");
    PRINTF("\r\n The LED is blinking.\r\n");
 
    /* Init output LED GPIO. */
    GPIO_PinInit(EXAMPLE_LED_GPIO, EXAMPLE_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(EXAMPLE_LED_GPIO, 1, &led_config);
    GPIO_PinInit(EXAMPLE_LED_GPIO, 0, &led_config);
    
    for(int i=0; i<15; i++){
          GPIO_PinWrite(EXAMPLE_LED_GPIO, 2, 1);
          SDK_DelayAtLeastUs(50000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
          GPIO_PinWrite(EXAMPLE_LED_GPIO, 2, 0);
          SDK_DelayAtLeastUs(90000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    }

    while (1)
    {
      if(heartbeat){
        for(int i=0; i<2; i++){
          GPIO_PinWrite(EXAMPLE_LED_GPIO, 1, 1);
          SDK_DelayAtLeastUs(50000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
          GPIO_PinWrite(EXAMPLE_LED_GPIO, 1, 0);
          SDK_DelayAtLeastUs(90000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        }
        SDK_DelayAtLeastUs(2000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
      }
      //lightshow
      else{ 
        //slow individual 
        for(int i=0; i<2; i++){
          for(int j=0; j<3; j++){       
            GPIO_PinWrite(EXAMPLE_LED_GPIO, j, 1);
            SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
            GPIO_PinWrite(EXAMPLE_LED_GPIO, j, 0);
            SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
          }
        }
        //fast individual
        for(int i=0; i<10; i++){
          for(int j=0; j<3; j++){       
            GPIO_PinWrite(EXAMPLE_LED_GPIO, j, 1);
            SDK_DelayAtLeastUs(50000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
            GPIO_PinWrite(EXAMPLE_LED_GPIO, j, 0);
            SDK_DelayAtLeastUs(50000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
          }
        }
        
        //Rainbow
        for(int i=0; i<3; i++){
          GPIO_PinWrite(EXAMPLE_LED_GPIO, 2, 1);
          SDK_DelayAtLeastUs(500000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
          GPIO_PinWrite(EXAMPLE_LED_GPIO, 0, 1);
          SDK_DelayAtLeastUs(500000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
          GPIO_PinWrite(EXAMPLE_LED_GPIO, 1, 1);
          SDK_DelayAtLeastUs(1000000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
          
          GPIO_PinWrite(EXAMPLE_LED_GPIO, 1, 0);
          SDK_DelayAtLeastUs(500000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
          GPIO_PinWrite(EXAMPLE_LED_GPIO, 0, 0);
          SDK_DelayAtLeastUs(500000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
          GPIO_PinWrite(EXAMPLE_LED_GPIO, 2, 0);
          SDK_DelayAtLeastUs(500000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        }
        
        //flashing
        for(int i=0; i<10; i++){
          for(int j=0; j<3; j++){
            GPIO_PinWrite(EXAMPLE_LED_GPIO, j, 1);
          }
          SDK_DelayAtLeastUs(50000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
          for(int j=0; j<3; j++){
            GPIO_PinWrite(EXAMPLE_LED_GPIO, j, 0);
          }
          SDK_DelayAtLeastUs(80000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
        }
      }
    }
}
