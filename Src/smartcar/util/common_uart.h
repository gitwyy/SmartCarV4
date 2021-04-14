//
// Created by wangyangyang on 2021-04-12.
//

#ifndef SMARTCARV4_COMMON_UART_H
#define SMARTCARV4_COMMON_UART_H

/**
 * uart 通用通讯协议
 */
#ifdef __cplusplus
extern "C" {
#endif
#include "usart.h"
#include "stm32f1xx_hal.h"


extern DMA_HandleTypeDef hdma_usart1_rx;
extern UART_HandleTypeDef huart1;

//// 初始化
void common_uart_init();

void common_uart_idle_handle(UART_HandleTypeDef *huart1);

void common_uart_send(uint8_t *data, uint16_t size);

__weak void common_uart_idle_callback(uint8_t receive_buf[], uint16_t receive_len);


#ifdef __cplusplus
}
#endif

#endif //SMARTCARV4_COMMON_UART_H
