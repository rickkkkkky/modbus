#include <string.h>
#include "rtu_slave.h"


// #include "gd32f10x.h"
// #include "init.h"
// extern const agile_modbus_slave_util_map_t bit_maps[];
// extern const agile_modbus_slave_util_map_t input_bit_maps[];
// extern const agile_modbus_slave_util_map_t register_maps[];
// extern const agile_modbus_slave_util_map_t input_register_maps[];

static int addr_check( agile_modbus_t* ctx, struct agile_modbus_slave_info* slave_info )
{
    int slave = slave_info->sft->slave;
    if ( ( slave != ctx->slave ) && ( slave != AGILE_MODBUS_BROADCAST_ADDRESS )
         && ( slave != 0xFF ) )
        return -AGILE_MODBUS_EXCEPTION_UNKNOW;

    return 0;
}

const agile_modbus_slave_util_t slave_util = {
    bit_maps,
    sizeof( bit_maps ) / sizeof( bit_maps[ 0 ] ),
    input_bit_maps,
    sizeof( input_bit_maps ) / sizeof( input_bit_maps[ 0 ] ),
    register_maps,
    sizeof( register_maps ) / sizeof( register_maps[ 0 ] ),
    input_register_maps,
    sizeof( input_register_maps ) / sizeof( input_register_maps[ 0 ] ),
    addr_check,
    NULL,
    NULL
};

agile_modbus_rtu_t ctx_rtu;
agile_modbus_t*    ctx;
uint8_t            ctx_send_buf[ AGILE_MODBUS_MAX_ADU_LENGTH ];
uint8_t            ctx_read_buf[ AGILE_MODBUS_MAX_ADU_LENGTH ];
int                read_len;

void RS485_Init( void )
{
    ctx = &ctx_rtu._ctx;
    agile_modbus_rtu_init(
        &ctx_rtu, ctx_send_buf, sizeof( ctx_send_buf ), ctx_read_buf, sizeof( ctx_read_buf ) );
    agile_modbus_set_slave( ctx, 1 );
}

void RS485_Recv( uint8_t* data, uint16_t len )
{
    memcpy( ctx_read_buf, data, len );
    read_len = ( int )len;
}
//移植需要修改的地方
#include "main.h"
#include "usart.h"
#define GPIO_RX_485() HAL_GPIO_WritePin( UC_RS485_EN_GPIO_Port, UC_RS485_EN_Pin, GPIO_PIN_RESET )
#define GPIO_TX_485() HAL_GPIO_WritePin( UC_RS485_EN_GPIO_Port, UC_RS485_EN_Pin, GPIO_PIN_SET )
void RS485_Send( uint8_t* data, uint16_t len )
{
    //移植需要修改的地方
    GPIO_TX_485();
    // HAL_UART_Transmit_DMA( &huart2, data, len );
    HAL_UART_Transmit( &huart2, data, len, 1000 );
    GPIO_RX_485();
    // gpio_bit_write(GPIOA, GPIO_PIN_15, SET);
    // usart_buf_transmit(UART3, ctx->send_buf, (uint16_t)send_len);
    // while (usart_flag_get(UART3, USART_FLAG_TC) == RESET);
    // gpio_bit_write(GPIOA, GPIO_PIN_15, RESET);
}
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
    // }
}
