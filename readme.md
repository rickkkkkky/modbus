# 					how to use

首先向原作者致敬 我只是从原来的linux系统移植到了单片机上
链接 [洛格/agile_modbus](https://github.com/loogg/agile_modbus/tree/master)

## 1.找到"rtu_slave.h"文件中以下内容并修改

```c
/**
 * @brief 初始化函数 可以在这个函数中加入串口初始化函数
 * @param  
 */
void RS485_Init( void )
{
    ctx = &ctx_rtu._ctx;
    agile_modbus_rtu_init(
        &ctx_rtu, ctx_send_buf, sizeof( ctx_send_buf ), ctx_read_buf, sizeof( ctx_read_buf ) );
    agile_modbus_set_slave( ctx, 1 );
}

/**
 * @brief 在串口空闲中断时调用 
 * @param data 
 * @param len 
 */
void RS485_Recv( uint8_t* data, uint16_t len )
{
    memcpy( ctx_read_buf, data, len );
    read_len = ( int )len;
}
//移植需要包含的头文件以实现485发送函数 
 #include "main.h"
 #include "usart.h"
 // #include "gd32f10x.h"
 #define GPIO_RX_485() HAL_GPIO_WritePin( UC_RS485_EN_GPIO_Port, UC_RS485_EN_Pin, GPIO_PIN_RESET )
 #define GPIO_TX_485() HAL_GPIO_WritePin( UC_RS485_EN_GPIO_Port, UC_RS485_EN_Pin, GPIO_PIN_SET )
 //--------------------------------------
 
 /**
  * @brief 不同的芯片的串口发送函数可能不同，需要自己实现
  * @param data 
  * @param len 
  */
 void RS485_Send( uint8_t* data, uint16_t len )
 {
     GPIO_TX_485();
     // HAL_UART_Transmit_DMA( &huart2, data, len );
     HAL_UART_Transmit( &huart2, data, len, 1000 );
     GPIO_RX_485();
     // gpio_bit_write(GPIOA, GPIO_PIN_15, SET);
     // usart_buf_transmit(UART3, ctx->send_buf, (uint16_t)send_len);
     // while (usart_flag_get(UART3, USART_FLAG_TC) == RESET);
     // gpio_bit_write(GPIOA, GPIO_PIN_15, RESET);
 }
 /**
  * @brief 在主循环中轮询
  * @param param 
  */
 void modbus_rtu_handler( void* param )
 {
     if ( read_len > 0 ) {
         int send_len = agile_modbus_slave_handle(
             ctx, read_len, 0, agile_modbus_slave_util_callback, &slave_util, NULL );
         if ( send_len > 0 ) {
 
             RS485_Send( ctx->send_buf, ( uint16_t )send_len );
             read_len = 0;
         }
     }
 }
 
 ```
 
## 2.在以下文件中增加你的寄存器地址映射
 
 |      文件名       |      描述      |
 | ---------------   | ------------ |
 |      bits.c       | 可读写位寄存器 |
 |    registers.c    |  可读写寄存器  |
 |   input_bits.c    |  输入位寄存器  |
 | input_registers.c |   输入寄存器   |
 
 

