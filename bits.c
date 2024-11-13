#include "rtu_slave.h"
#include <string.h>
//读写位寄存器的映射表 十进制功能码01 05 15
// uint8_t _tab_bits_status[26] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
uint8_t    _tab_bits_status[ 16 ];
uint8_t    _tab_bits_control[ 26 ];
static int get_map_buf( void* buf, int bufsz )
{
    uint8_t* ptr = ( uint8_t* )buf;
    for ( int i = 0; i < sizeof( _tab_bits_status ); i++ ) {
        ptr[ i ] = _tab_bits_status[ i ];
    }
    return 0;
}

static int set_map_buf( int index, int len, void* buf, int bufsz )
{
    uint8_t* ptr = ( uint8_t* )buf;
    for ( int i = 0; i < len; i++ ) {
        _tab_bits_status[ index + i ] = ptr[ index + i ];
    }
    return 0;
}


static int get_map_control_buf( void* buf, int bufsz )
{
    uint8_t* ptr = ( uint8_t* )buf;
    memcpy( ptr, _tab_bits_control, sizeof( _tab_bits_control ) );
    return 0;
}

static int set_map_control_buf( int index, int len, void* buf, int bufsz )
{
    uint8_t* ptr = ( uint8_t* )buf;
    memcpy( &_tab_bits_control[ index ], &ptr[ index ], len );
    return 0;
}

const agile_modbus_slave_util_map_t bit_maps[ 2 ] = {
    { 0, 0x0F, get_map_buf, set_map_buf }, 
    { 0x20, 0x39, get_map_control_buf, set_map_control_buf }
};
