#ifndef __SLAVE_H
#define __SLAVE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "agile_modbus.h"
#include "agile_modbus_slave_util.h"

#ifndef NULL
#define NULL 0
#endif // !NULL

extern const agile_modbus_slave_util_t slave_util;
void RS485_Init(void);
void RS485_Data_copy(uint8_t *data, uint16_t len);
void modbus_rtu_handler(void *param);
#ifdef __cplusplus
}
#endif

#endif /* __SLAVE_H */
