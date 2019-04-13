#ifndef __OV7725_H__
#define __OV7725_H__


#include "stm32f10x.h"
#include "sccb.h"

#define OV7725_MID				0X7FA2    
#define OV7725_PID				0X7721

/************************** OV7725 连接引脚定义********************************/
// FIFO 输出使能，即模块中的OE
#define      OV7725_OE_GPIO_CLK                       RCC_APB2Periph_GPIOG
#define      OV7725_OE_GPIO_PORT                      GPIOG
#define      OV7725_OE_GPIO_PIN                       GPIO_Pin_15

// FIFO 写复位
#define      OV7725_WRST_GPIO_CLK                     RCC_APB2Periph_GPIOD
#define      OV7725_WRST_GPIO_PORT                    GPIOD
#define      OV7725_WRST_GPIO_PIN                     GPIO_Pin_6

// FIFO 读复位
#define      OV7725_RRST_GPIO_CLK                     RCC_APB2Periph_GPIOG
#define      OV7725_RRST_GPIO_PORT                    GPIOG
#define      OV7725_RRST_GPIO_PIN                     GPIO_Pin_14

// FIFO 读时钟
#define      OV7725_RCLK_GPIO_CLK                     RCC_APB2Periph_GPIOB
#define      OV7725_RCLK_GPIO_PORT                    GPIOB
#define      OV7725_RCLK_GPIO_PIN                     GPIO_Pin_4

// FIFO 写使能
#define      OV7725_WE_GPIO_CLK                       RCC_APB2Periph_GPIOB
#define      OV7725_WE_GPIO_PORT                      GPIOB
#define      OV7725_WE_GPIO_PIN                       GPIO_Pin_3


// 8位数据口
#define      OV7725_DATA_GPIO_CLK                     RCC_APB2Periph_GPIOC
#define      OV7725_DATA_GPIO_PORT                    GPIOC
#define      OV7725_DATA_0_GPIO_PIN                   GPIO_Pin_0
#define      OV7725_DATA_1_GPIO_PIN                   GPIO_Pin_1
#define      OV7725_DATA_2_GPIO_PIN                   GPIO_Pin_2
#define      OV7725_DATA_3_GPIO_PIN                   GPIO_Pin_3
#define      OV7725_DATA_4_GPIO_PIN                   GPIO_Pin_4
#define      OV7725_DATA_5_GPIO_PIN                   GPIO_Pin_5
#define      OV7725_DATA_6_GPIO_PIN                   GPIO_Pin_6
#define      OV7725_DATA_7_GPIO_PIN                   GPIO_Pin_7

// OV7725场中断
#define      OV7725_VSYNC_GPIO_CLK                    RCC_APB2Periph_GPIOA
#define      OV7725_VSYNC_GPIO_PORT                   GPIOA
#define      OV7725_VSYNC_GPIO_PIN                    GPIO_Pin_8



#define      OV7725_VSYNC_EXTI_SOURCE_PORT            GPIO_PortSourceGPIOA
#define      OV7725_VSYNC_EXTI_SOURCE_PIN             GPIO_PinSource8
#define      OV7725_VSYNC_EXTI_LINE                   EXTI_Line8
#define      OV7725_VSYNC_EXTI_IRQ                    EXTI9_5_IRQn
#define      OV7725_VSYNC_EXTI_INT_FUNCTION           EXTI9_5_IRQHandler

/***************************************************************************************/



#define FIFO_OE_H()     OV7725_OE_GPIO_PORT->BSRR =OV7725_OE_GPIO_PIN	  
#define FIFO_OE_L()     OV7725_OE_GPIO_PORT->BRR  =OV7725_OE_GPIO_PIN	  /*拉低使FIFO输出使能*/

#define FIFO_WRST_H()   OV7725_WRST_GPIO_PORT->BSRR =OV7725_WRST_GPIO_PIN	  /*拉高允许FIFO写(数据from摄像头)指针运动 */
#define FIFO_WRST_L()   OV7725_WRST_GPIO_PORT->BRR  =OV7725_WRST_GPIO_PIN	  /*拉低使FIFO写(数据from摄像头)指针复位*/

#define FIFO_RRST_H()   OV7725_RRST_GPIO_PORT->BSRR =OV7725_RRST_GPIO_PIN	  /*拉高允许FIFO读(数据从FIFO输出)指针运动 */
#define FIFO_RRST_L()   OV7725_RRST_GPIO_PORT->BRR  =OV7725_RRST_GPIO_PIN	  /*拉低使FIFO读(数据从FIFO输出)指针复位 */

#define FIFO_RCLK_H()   OV7725_RCLK_GPIO_PORT->BSRR =OV7725_RCLK_GPIO_PIN	  
#define FIFO_RCLK_L()   OV7725_RCLK_GPIO_PORT->BRR  =OV7725_RCLK_GPIO_PIN	  /*FIFO输出数据时钟*/

#define FIFO_WE_H()     OV7725_WE_GPIO_PORT->BSRR =OV7725_WE_GPIO_PIN	  /*拉高使FIFO写允许*/
#define FIFO_WE_L()     OV7725_WE_GPIO_PORT->BRR  =OV7725_WE_GPIO_PIN




#define READ_FIFO_PIXEL(RGB565)   	do{\
	                                  RGB565=0;\
	                                  FIFO_RCLK_L();\
	                                  RGB565 = (OV7725_DATA_GPIO_PORT->IDR) & 0xFF;\
	                                  FIFO_RCLK_H();\
									  RGB565<<=8;\
									  FIFO_RCLK_L();\
	                                  RGB565 |= (OV7725_DATA_GPIO_PORT->IDR) & 0xFF;\
	                                  FIFO_RCLK_H();\
                                    }while(0)



#define FIFO_PREPARE                do{\
	                                  FIFO_RRST_L();\
	                                  FIFO_RCLK_L();\
	                                  FIFO_RCLK_H();\
	                                  FIFO_RRST_H();\
	                                  FIFO_RCLK_L();\
	                                  FIFO_RCLK_H();\
                                    }while(0)





void SCCB_WriteByte(u16 WriteAddress, u8 Sendbyte);
void SCCB_ReadBuf(u8*pBuff, u16 length, u8 ReadAddress);
u8   SCCB_ReadByte(u8 ReadAddress);

u8 ov7725_init(void);

void OV7725_Light_Mode(u8 mode);
void OV7725_Color_Saturation(s8 sat);
void OV7725_Brightness(s8 bright);
void OV7725_Contrast(s8 contrast);
void OV7725_Special_Effects(u8 eft);
void OV7725_Window_Set(u16 width,u16 height,u8 mode);


void OV_Lcd_Display(u16 sx,u16 sy,u16 width,u16 height);









#endif








