#ifndef __RTU_SLAVE_H
#define __RTU_SLAVE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "agile_modbus.h"
#include "agile_modbus_slave_util.h"

#ifndef NULL
#define NULL 0
#endif  // !NULL
extern uint8_t  _tab_bits_status[];
extern uint8_t  _tab_bits_control[];
extern uint16_t _tab_registers[];
extern uint16_t _tab_registers_state[];
extern uint16_t _tab_registers_dbg[];

extern const agile_modbus_slave_util_map_t bit_maps[2];
extern const agile_modbus_slave_util_map_t input_bit_maps[1];
extern const agile_modbus_slave_util_map_t register_maps[3];
extern const agile_modbus_slave_util_map_t input_register_maps[1];
extern const agile_modbus_slave_util_t     slave_util;
void                                       RS485_Init( void );
void                                       RS485_Recv( uint8_t* data, uint16_t len );
void                                       RS485_Send( uint8_t* data, uint16_t len );
void                                       modbus_rtu_handler( void* param );
#ifdef __cplusplus
}
#endif

#endif /* __RTU_SLAVE_H */
