#include "rtu_slave.h"
//只读bit 02
// uint8_t _tab_input_bits[16] = {0, 1, 1, 0, 0, 1, 1, 0, 0, 1};
static uint8_t _tab_input_bits[16]; //默认初始化成0
static int get_map_buf(void *buf, int bufsz)
{
    uint8_t *ptr = (uint8_t *)buf;

    // pthread_mutex_lock(&slave_mtx);
    for (int i = 0; i < sizeof(_tab_input_bits); i++) {
        ptr[i] = _tab_input_bits[i];
    }
    // pthread_mutex_unlock(&slave_mtx);

    return 0;
}

const agile_modbus_slave_util_map_t input_bit_maps[1] = {
    {0, 0x0F, get_map_buf, NULL}};
