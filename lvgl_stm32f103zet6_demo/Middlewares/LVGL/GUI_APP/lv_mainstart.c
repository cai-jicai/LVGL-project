/**
 ****************************************************************************************************
 * @file        lv_mainstart.c
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
 
#include "LVGL/GUI_APP/lv_mainstart.h"

#include <stdio.h>


/* 获取当前活动屏幕的宽高 */
#define scr_act_width() lv_obj_get_width(lv_scr_act())
#define scr_act_height() lv_obj_get_height(lv_scr_act())

static lv_obj_t *list;              /* 定义右边列表 */
//static lv_obj_t *list_label;        /* 定义右边标签 */
static const lv_font_t *font;       /* 定义字体 */

#if 1
/* pe尝试 */

lv_obj_t* g_left_area;      // 左边动态列表容器
lv_obj_t* g_right_area;     // 右边静态容器
lv_obj_t* g_current_table;   // 当前显示的左侧表格
lv_obj_t* root;							//全局界面
uint8_t 	current_table_index = 0 ;
// 全局对象定义
//#define LEFT_WIDTH (lv_obj_get_width(g_left_area) * 0.8)  // 左侧占70%宽度
#define TABLE_ROWS 13                    // 表格行数（含表头）
#define TABLE_COLS 4                     // 表格列数

// 预创建的表格对象池（支持3个独立表格）
#define MAX_TABLES 9
lv_obj_t* g_table_pool[MAX_TABLES];

/*------------------------------ 表格管理 ----------------------------*/
float temp[5][13] = 
{ 
	0 ,3.6 ,3.5 ,3.4 , 3.4 , 3.2 ,3.9 ,5.2 ,6.2 ,61.3 , 2.6 , 2.8 ,3.9 ,
	0 ,3.5 ,3.9 ,3.6 , 3.4 , 3.2 ,3.9 ,5.2 ,6.2 ,61.3 , 2.6 , 2.8 ,3.9 ,
	0 ,3.4 ,3.2 ,3.4 , 3.4 , 3.2 ,3.9 ,5.2 ,6.2 ,61.3 , 2.6 , 2.8 ,3.9 ,
	0 ,3.3 ,3.1 ,3.2 , 3.4 , 3.2 ,3.9 ,5.2 ,6.2 ,61.3 , 2.6 , 2.8 ,3.9 	
} ;
static char format_buf[64];  // 全局缓冲区
static char blance_status[2][10];  // 全局缓冲区		0代表no 1代表yes
void update_test(lv_obj_t* g_current_table)
{
			if( current_table_index != 0 )
			{
				uint8_t i = 0 ;
				for ( i = 1; i < TABLE_ROWS; i++) 
				{
					snprintf(format_buf, sizeof(format_buf), "%.2f",temp[current_table_index-1][i]);		
					lv_table_set_cell_value(g_current_table, i, 1, format_buf);	//电压
					
					snprintf(format_buf, sizeof(format_buf), "97.1");		
					lv_table_set_cell_value(g_current_table, i, 2, format_buf);	//soc
					
					lv_table_set_cell_value(g_current_table, i, 3, blance_status[0]);	//均衡	
				}						
			}						
			
}
void test(int j)
{
			if( j != 0 )
			{
				uint8_t i = 0 ;

				for ( i = 1; i < TABLE_ROWS; i++) 
				{
					lv_table_set_cell_value_fmt(g_table_pool[j], i, 0, "%02d", i+(j-1)*12);	//编号
					snprintf(format_buf, sizeof(format_buf), "%.2f",temp[j-1][i]);		
					lv_table_set_cell_value(g_table_pool[j], i, 1, format_buf);	//电压
					snprintf(format_buf, sizeof(format_buf), "97.1");		
					lv_table_set_cell_value(g_table_pool[j], i, 2, format_buf);	//soc
					
					lv_table_set_cell_value(g_table_pool[j], i, 3, blance_status[0]);	//均衡	
				}								
			}
}
// 创建所有左侧界面table
void create_sub_table_ui(void)
{


		//主界面表格
		snprintf(format_buf, sizeof(format_buf), "10.52");
		lv_table_set_cell_value(g_table_pool[0], 1, 0, format_buf);
		snprintf(format_buf, sizeof(format_buf), "25.6");
		lv_table_set_cell_value(g_table_pool[0], 1, 1, format_buf);	
	
		//子界面表格
		test(1);
		test(2);
		test(3);
		test(4);	
    //填充测试数据
//		uint8_t i = 0;
//		uint8_t j = 0 ;
//		for( j = 1 ;j < 5 ;j ++ )
//		{
//			for ( i = 1; i < TABLE_ROWS; i++) 
//			{
//				lv_table_set_cell_value_fmt(g_table_pool[j], i, 0, "%02d", i+(j-1)*12);	//编号
//				snprintf(format_buf, sizeof(format_buf), "%.2f",temp[j-1][i]);		
//				lv_table_set_cell_value(g_table_pool[j], i, 1, format_buf);	//电压
//				snprintf(format_buf, sizeof(format_buf), "97.1");		
//				lv_table_set_cell_value(g_table_pool[j], i, 2, format_buf);	//soc
//				snprintf(format_buf, sizeof(format_buf), "yes");		
//				lv_table_set_cell_value(g_table_pool[j], i, 3, format_buf);	//均衡	
//			}						
//		}	
}
// 初始化表格设置与表头
void init_table(lv_obj_t* table,int table_idx) {
		if( table_idx != 0 )
		{
				// 设置列宽（总宽度需适配LEFT_WIDTH）
				lv_table_set_col_width(table, 0, lv_obj_get_width(g_left_area) * 0.8 * 15 / 100);  // 编号列15%
				lv_table_set_col_width(table, 1, lv_obj_get_width(g_left_area) * 0.8 * 30 / 100);  // 电压列30%
				lv_table_set_col_width(table, 2, lv_obj_get_width(g_left_area) * 0.8 * 30 / 100);  // SOC列30%
				lv_table_set_col_width(table, 3, lv_obj_get_width(g_left_area) * 0.8 * 22 / 100);  // 均衡状态25%

				// 设置表头
				lv_table_set_cell_value(table, 0, 0, "ID");
				lv_table_set_cell_value(table, 0, 1, "Voltage(V)");
				lv_table_set_cell_value(table, 0, 2, "SOC(%)");
				lv_table_set_cell_value(table, 0, 3, "Balance");
		}
		else
  	{
				// 设置列宽（总宽度需适配LEFT_WIDTH）
				lv_table_set_col_width(table, 0, lv_obj_get_width(g_left_area) * 0.8 * 50 / 100);  // 编号列15%
				lv_table_set_col_width(table, 1, lv_obj_get_width(g_left_area) * 0.8 * 50 / 100);  // 电压列30%

				// 设置表头
				lv_table_set_cell_value(table, 0, 0, "Current(A)");
				lv_table_set_cell_value(table, 0, 1, "temperature(C)");		  
		}
}
static lv_style_t style_table;					//全局或静态变量（避免栈变量被释放后出现野指针)
static void create_table(int i, int cols, int rows) {
        g_table_pool[i] = lv_table_create(g_left_area);
        lv_obj_add_style(g_table_pool[i], &style_table, 0);	// 应用样式
        lv_table_set_col_cnt(g_table_pool[i], cols);	// 设置列数
        lv_table_set_row_cnt(g_table_pool[i], rows);	// 设置行数
        lv_obj_set_size(g_table_pool[i], lv_obj_get_width(g_left_area) * 0.8, lv_obj_get_height(g_left_area) * 0.9 );	// 尺寸控制
        lv_obj_add_flag(g_table_pool[i], LV_OBJ_FLAG_HIDDEN);				// 初始隐藏
        init_table(g_table_pool[i] , i);																//初始化表格表头
				lv_obj_center(g_table_pool[i]); 
}
// 预创建表格对象池
void precreate_tables(void) {

    lv_style_init(&style_table);						//单元格样式
    lv_style_set_pad_all(&style_table, 2);	// 统一内边距
   
		create_table(0 ,5 ,2) ;
	//初始化表格表头	
    for (int i = 1; i < MAX_TABLES; i++) {
				create_table( i , TABLE_COLS , TABLE_ROWS) ;
	
    }
    g_current_table = g_table_pool[0];
    lv_obj_clear_flag(g_current_table, LV_OBJ_FLAG_HIDDEN);					//只显示首页表格
		// 填充测试数据
    create_sub_table_ui();
}
// 切换到指定表格
void switch_left_table(int table_idx) {
    if (table_idx >= MAX_TABLES) return;

    lv_obj_add_flag(g_current_table, LV_OBJ_FLAG_HIDDEN); // 隐藏旧table
    g_current_table = g_table_pool[table_idx];
		current_table_index = table_idx ;
	
		test(table_idx) ;	//切换时这一刻更新
		
    lv_obj_clear_flag(g_current_table, LV_OBJ_FLAG_HIDDEN); // 显示新表格
    lv_obj_scroll_to(g_current_table, 0, 0, LV_ANIM_OFF);   // 复位滚动位置
}
// 切换到子界面1的回调
static void switch_to_sub_screen_1(lv_event_t* e) {
		if( current_table_index != 1 )
		{
				switch_left_table(1);
		}
}
static void switch_to_sub_screen_2(lv_event_t* e) {
		if( current_table_index != 2 )
		{
				switch_left_table(2);
		}
}
static void switch_to_sub_screen_3(lv_event_t* e) {
		if( current_table_index != 3 )
		{
				switch_left_table(3);
		}
}
static void switch_to_sub_screen_4(lv_event_t* e) {
		if( current_table_index != 4 )
		{
				switch_left_table(4);
		}
}
static void switch_to_sub_screen_5(lv_event_t* e) {
		if( current_table_index != 5 )
		{
				switch_left_table(5);
		}
}
static void switch_to_sub_screen_6(lv_event_t* e) {
		if( current_table_index != 6 )
		{
				switch_left_table(6);
		}
}
static void switch_to_sub_screen_7(lv_event_t* e) {
		if( current_table_index != 7 )
		{
				switch_left_table(7);
		}
}
static void switch_to_sub_screen_8(lv_event_t* e) {
		if( current_table_index != 8 )
		{
				switch_left_table(8);
		}
}
// 切换回主界面的回调
static void switch_to_main_screen(lv_event_t* e) {
		switch_left_table(0);
}


// 初始化界面
void create_ui_init(void) {
	  /* 根据屏幕大小设置字体 */
    if (scr_act_width() <= 320)
    {
        font = &lv_font_montserrat_14;
    }
    else if (scr_act_width() <= 480)
    {
        font = &lv_font_montserrat_16;
    }
    else
    {
        font = &lv_font_montserrat_18;
    }
		
    // 创建根容器（全屏）
    root = lv_scr_act();
    lv_obj_set_flex_flow(root, LV_FLEX_FLOW_ROW);	//水平排列

    // 左边动态区域（占屏幕70%宽度）
	  g_left_area = lv_obj_create(root);
	  lv_obj_set_width(g_left_area, scr_act_width() * 0.7);                              /* 设置宽度 */
    lv_obj_set_height(g_left_area, scr_act_height() * 1);                            /* 设置高度 */
    lv_obj_align(g_left_area, LV_ALIGN_LEFT_MID, 5, 0);                                /* 设置位置 */
    lv_obj_update_layout(g_left_area);                                                 /* 强制立即更新参数，手动更新物体的参数 */
		lv_obj_set_scroll_dir(g_left_area, LV_DIR_VER); // 启用垂直滚动
		
    // 右边静态区域（占30%宽度）
    g_right_area = lv_obj_create(root);
    lv_obj_set_width(g_right_area, scr_act_width() - lv_obj_get_width(g_left_area) - 15); /* 设置宽度 */
    lv_obj_set_height(g_right_area, lv_obj_get_height(g_left_area));                      /* 设置高度 */
    lv_obj_align_to(g_right_area, g_left_area, LV_ALIGN_OUT_RIGHT_MID, 5, 0);             /* 设置位置 */
    lv_obj_update_layout(g_right_area);  
		
    // 初始化右侧静态内容（仅一次）
    /* 创建列表 */
    list = lv_list_create(g_right_area);                                                /* 创建列表 */
    lv_obj_set_width(list, lv_obj_get_width(g_right_area) - 13);                       /* 设置列表宽度 */
    lv_obj_set_height(list, lv_obj_get_height(g_right_area) * 0.9);                     /* 设置列表高度 */
    lv_obj_center(list);          	                                            			/* 设置列表的位置 ，居中对齐于其父容器 g_right_area*/
    lv_obj_set_style_text_font(list, font, LV_PART_MAIN);  
    /* 为列表添加按钮 */
    lv_obj_t*  btn_right;		
    btn_right = lv_list_add_btn(list, LV_SYMBOL_FILE, "Group1");                             /* 添加按钮 */
		lv_obj_add_event_cb(btn_right, switch_to_sub_screen_1, LV_EVENT_CLICKED, NULL);				  /* 添加按钮回调 */
    btn_right = lv_list_add_btn(list, LV_SYMBOL_FILE, "Group1_2");                             /* 添加按钮 */
    lv_obj_add_event_cb(btn_right, switch_to_sub_screen_2, LV_EVENT_CLICKED, NULL);            /* 添加按钮回调 */	
    btn_right = lv_list_add_btn(list, LV_SYMBOL_FILE, "Group2");                             /* 添加按钮 */
    lv_obj_add_event_cb(btn_right, switch_to_sub_screen_3, LV_EVENT_CLICKED, NULL);            /* 添加按钮回调 */
    btn_right = lv_list_add_btn(list, LV_SYMBOL_FILE, "Group2_2");                             /* 添加按钮 */
    lv_obj_add_event_cb(btn_right, switch_to_sub_screen_4, LV_EVENT_CLICKED, NULL);            /* 添加按钮回调 */		
    btn_right = lv_list_add_btn(list, LV_SYMBOL_FILE, "Group3");                             /* 添加按钮 */
    lv_obj_add_event_cb(btn_right, switch_to_sub_screen_5, LV_EVENT_CLICKED, NULL);            /* 添加按钮回调 */	
    btn_right = lv_list_add_btn(list, LV_SYMBOL_FILE, "Group3_2");                             /* 添加按钮 */
    lv_obj_add_event_cb(btn_right, switch_to_sub_screen_6, LV_EVENT_CLICKED, NULL);            /* 添加按钮回调 */	
    btn_right = lv_list_add_btn(list, LV_SYMBOL_FILE, "Group4");                             /* 添加按钮 */
    lv_obj_add_event_cb(btn_right, switch_to_sub_screen_7, LV_EVENT_CLICKED, NULL);            /* 添加按钮回调 */	
    btn_right = lv_list_add_btn(list, LV_SYMBOL_FILE, "Group4_2");                             /* 添加按钮 */
    lv_obj_add_event_cb(btn_right, switch_to_sub_screen_8, LV_EVENT_CLICKED, NULL);            /* 添加按钮回调 */			
		btn_right = lv_list_add_btn(list, LV_SYMBOL_CLOSE,"Return home");                             /* 添加按钮 */
    lv_obj_add_event_cb(btn_right, switch_to_main_screen, LV_EVENT_CLICKED, NULL);  
}


static void lv_pe_screens(void)
{
// 初始化所有界面
		create_ui_init();
		precreate_tables();
}
#endif

void lv_mainstart(void)
{
		lv_pe_screens();
}



