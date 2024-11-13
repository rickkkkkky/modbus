#include <string.h>
#include "rtu_slave.h"



//十进制功能码03 06 16 23
// static uint16_t _tab_registers[10] = {0, 1, 2, 3, 4, 5, 10, 7, 8, 9};
uint16_t   _tab_registers[ 52 ];
uint16_t   _tab_registers_state[ 8 ];
uint16_t   _tab_registers_dbg[ 22 ];
static int get_map_buf( void* buf, int bufsz )
{
    uint16_t* ptr = ( uint16_t* )buf;
    for ( int i = 0; i < sizeof( _tab_registers ) / sizeof( _tab_registers[ 0 ] ); i++ ) {
        ptr[ i ] = _tab_registers[ i ];
    }
    return 0;
}

static int set_map_buf( int index, int len, void* buf, int bufsz )
{
    uint16_t* ptr = ( uint16_t* )buf;
    for ( int i = 0; i < len; i++ ) {
        _tab_registers[ index + i ] = ptr[ index + i ];
    }
    return 0;
}

static int get_state_buf( void* buf, int bufsz )
{
    uint16_t* ptr = ( uint16_t* )buf;
    memcpy( ptr, _tab_registers_state, sizeof( _tab_registers_state ) );
    return 0;
}
static int set_state_buf( int index, int len, void* buf, int bufsz )
{
    uint16_t* ptr = ( uint16_t* )buf;
    memcpy( &_tab_registers_state[ index ], &ptr[index], len * sizeof( uint16_t ) );
    return 0;
}

static int get_dbg_buf( void* buf, int bufsz )
{
    uint16_t* ptr = ( uint16_t* )buf;

    memcpy( ptr, _tab_registers_dbg, sizeof( _tab_registers_dbg ) );
    return 0;
}
static int set_dbg_buf( int index, int len, void* buf, int bufsz )
{
    uint16_t* ptr = ( uint16_t* )buf;
    memcpy( &_tab_registers_dbg[ index ], &ptr[index], len * sizeof( uint16_t ) );
    return 0;
}
const agile_modbus_slave_util_map_t register_maps[ 3 ] = {
    { 0x60, 0x94, get_map_buf, set_map_buf },
    { 0x40, 0x57, get_state_buf, set_state_buf },
    { 0x200, 0x215, get_dbg_buf, set_dbg_buf },
};
