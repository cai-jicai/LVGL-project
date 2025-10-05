/**
 ****************************************************************************************************
 * @file        lv_mainstart.h
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2022-03-23
 * @brief       LVGL lv_list(�б�) ʵ��
 * @license     Copyright (c) 2020-2032, �������������ӿƼ����޹�˾
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

#ifndef __LV_MAINSTART_H
#define __LV_MAINSTART_H

#include "lvgl/lvgl.h"

/* ������ʱ��� */
void create_sub_table_ui(void);
void update_test(lv_obj_t *g_current_table);

extern float temp[5][13];
extern lv_obj_t *g_current_table;

void lv_mainstart(void);

#endif
