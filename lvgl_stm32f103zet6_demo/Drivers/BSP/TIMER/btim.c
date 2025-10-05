/**
 ****************************************************************************************************
 * @file        btim.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2020-04-20
 * @brief       ������ʱ�� ��������
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
 * �޸�˵��
 * V1.0 20200420
 * ��һ�η���
 *
 ****************************************************************************************************
 */

#include "./BSP/LED/led.h"
#include "./BSP/TIMER/btim.h"
#include "lvgl.h"


TIM_HandleTypeDef g_timx_handle;      /* ��ʱ��x��� */
TIM_HandleTypeDef htim7;
/**
 * @brief       ������ʱ��TIMX��ʱ�жϳ�ʼ������
 * @note
 *              ������ʱ����ʱ������APB1,��PPRE1 �� 2��Ƶ��ʱ��
 *              ������ʱ����ʱ��ΪAPB1ʱ�ӵ�2��, ��APB1Ϊ36M, ���Զ�ʱ��ʱ�� = 72Mhz
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us.
 *              Ft=��ʱ������Ƶ��,��λ:Mhz
 *
 * @param       arr: �Զ���װֵ��
 * @param       psc: ʱ��Ԥ��Ƶ��
 * @retval      ��
 */
void btim_timx_int_init(uint16_t arr, uint16_t psc)
{
    BTIM_TIMX_INT_CLK_ENABLE();                                         /* ʹ��TIMxʱ�� */
    
    g_timx_handle.Instance = BTIM_TIMX_INT;                             /* ͨ�ö�ʱ��x */
    g_timx_handle.Init.Prescaler = psc;                                 /* ��Ƶ */
    g_timx_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                /* ���ϼ����� */
    g_timx_handle.Init.Period = arr;                                    /* �Զ�װ��ֵ */
    g_timx_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;          /* ʱ�ӷ�Ƶ���� */
    HAL_TIM_Base_Init(&g_timx_handle);
    
    HAL_NVIC_SetPriority(BTIM_TIMX_INT_IRQn, 1, 3);                     /* �����ж����ȼ�����ռ���ȼ�1�������ȼ�3 */
    HAL_NVIC_EnableIRQ(BTIM_TIMX_INT_IRQn);                             /* ����ITMx�ж� */
    
    HAL_TIM_Base_Start_IT(&g_timx_handle);                              /* ʹ�ܶ�ʱ��x�Ͷ�ʱ��x�����ж� */
    
    
}

/**
 * @brief       ��ʱ���жϷ�����
 * @param       ��
 * @retval      ��
 */
void BTIM_TIMX_INT_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&g_timx_handle);
}
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */

  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}
/**
 * @brief       ��ʱ�������жϻص�����
* @param        htim:��ʱ�����ָ��
 * @retval      ��
 */
#include "LVGL/GUI_APP/lv_mainstart.h"

uint8_t row,col ;
float num = 0.05 ;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == (&g_timx_handle))
    {
        lv_tick_inc(1);   /*lvgl��1ms����*/
    }
		if( htim == (&htim7) )
		{
					for( row = 1 ;row < 5 ;row ++ )
					{
						for ( col = 1; col < 13; col++) 
						{
							temp[row-1][col] += num;
						}						
					}
					update_test(g_current_table);		//ʵʱˢ����ֵ
		}
}





/* TIM7 init function */
void MX_TIM7_Init(void)
{

  /* USER CODE BEGIN TIM7_Init 0 */

  /* USER CODE END TIM7_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM7_Init 1 */

  /* USER CODE END TIM7_Init 1 */
  htim7.Instance = TIM7;
  htim7.Init.Prescaler = 7200-1;
  htim7.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim7.Init.Period = 10000-1;
  htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim7) != HAL_OK)
  {
    HardFault_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim7, &sMasterConfig) != HAL_OK)
  {
    HardFault_Handler();
  }
  /* USER CODE BEGIN TIM7_Init 2 */
    HAL_NVIC_SetPriority(TIM7_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM7_IRQn);
  	HAL_TIM_Base_Start_IT(&htim7);                              /* ʹ�ܶ�ʱ��x�Ͷ�ʱ��x�����ж� */
  /* USER CODE END TIM7_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM7)
  {
  /* USER CODE BEGIN TIM7_MspInit 0 */

  /* USER CODE END TIM7_MspInit 0 */
    /* TIM7 clock enable */
    __HAL_RCC_TIM7_CLK_ENABLE();

    /* TIM7 interrupt Init */
    HAL_NVIC_SetPriority(TIM7_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM7_IRQn);
  /* USER CODE BEGIN TIM7_MspInit 1 */

  /* USER CODE END TIM7_MspInit 1 */
  }
}





