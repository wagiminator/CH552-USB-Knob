// ===================================================================================
// USB HID Consumer Keyboard Functions for CH551, CH552 and CH554
// ===================================================================================

#pragma once
#include <stdint.h>
#include "usb_hid.h"

// Functions
void CON_press(uint8_t key);          // press a consumer key on keyboard
void CON_release(void);               // release a consumer key on keyboard
void CON_type(uint8_t key);           // press and release a consumer key

// Consumer Keyboard Keycodes
#define CON_SYS_POWER       0x30
#define CON_SYS_RESET       0x31
#define CON_SYS_SLEEP       0x32

#define CON_VOL_MUTE        0xE2
#define CON_VOL_UP          0xE9
#define CON_VOL_DOWN        0xEA

#define CON_MEDIA_PLAY      0xB0
#define CON_MEDIA_PAUSE     0xB1
#define CON_MEDIA_RECORD    0xB2
#define CON_MEDIA_FORWARD   0xB3
#define CON_MEDIA_REWIND    0xB4
#define CON_MEDIA_NEXT      0xB5
#define CON_MEDIA_PREV      0xB6
#define CON_MEDIA_STOP      0xB7
#define CON_MEDIA_EJECT     0xB8
#define CON_MEDIA_RANDOM    0xB9

#define CON_MENU            0x40
#define CON_MENU_PICK       0x41
#define CON_MENU_UP         0x42
#define CON_MENU_DOWN       0x43
#define CON_MENU_LEFT       0x44
#define CON_MENU_RIGHT      0x45
#define CON_MENU_ESCAPE     0x46
#define CON_MENU_INCR       0x47
#define CON_MENU_DECR       0x48
