/**
 ****************************************************************************************************
 * @file        main.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-28
 * @brief       LVGL V8�޲���ϵͳ��ֲ ʵ��
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./USMART/usmart.h"
#include "./BSP/LED/led.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/KEY/key.h"
#include "./MALLOC/malloc.h"
#include "./BSP/TIMER/btim.h"
#include "./BSP/TOUCH/touch.h"

/* LVGL */
#include "lvgl.h"
#include "lv_port_indev_template.h"
#include "lv_port_disp_template.h"
//#include "lv_demo_stress.h"

#include "LVGL/GUI_APP/lv_mainstart.h"


int main(void)
{
    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    usart_init(115200);                 /* ���ڳ�ʼ��Ϊ115200 */
    usmart_dev.init(72);                /* ��ʼ��USMART */
    led_init();                         /* ��ʼ��LED */
    lcd_init();                         /* ��ʼ��LCD */
    key_init();                         /* ��ʼ������ */
    my_mem_init(SRAMIN);                /* ��ʼ���ڲ�SRAM�ڴ�� */
    tp_dev.init();                      /* ��������ʼ�� */
    btim_timx_int_init(10-1,7200-1);    /* ��ʼ����ʱ�� */
	
		MX_TIM7_Init();
	
    lv_init();                          /* lvglϵͳ��ʼ�� */
    lv_port_disp_init();                /* lvgl��ʾ�ӿڳ�ʼ��,����lv_init()�ĺ��� */
    lv_port_indev_init();               /* lvgl����ӿڳ�ʼ��,����lv_init()�ĺ��� */
    
    lv_mainstart();  /* demo */
	

    while(1)
    {
        lv_task_handler();
				delay_ms(5);

    }
}

