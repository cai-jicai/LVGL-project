/**
 ****************************************************************************************************
 * @file        lv_mainstart.h
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-03-23
 * @brief       LVGL lv_list(列表) 实验
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32F103开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */
 
#ifndef __LV_MAINSTART_H
#define __LV_MAINSTART_H

#include "lvgl.h"

/* 测试临时存放 */
void create_sub_table_ui(void);
void update_test(lv_obj_t* g_current_table);

extern float temp[5][13] ;
extern lv_obj_t* g_current_table;

void lv_mainstart(void);

#endif
