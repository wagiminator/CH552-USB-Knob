// ===================================================================================
// USB HID Consumer Keyboard Functions for CH551, CH552 and CH554
// ===================================================================================

#pragma once
#include <stdint.h>
#include "usb_hid.h"

// Functions
#define KBD_init() HID_init()         // init keyboard
void KBD_press(uint8_t key);          // press a key on keyboard
void KBD_release(void);               // release a key on keyboard
void KBD_type(uint8_t key);           // press and release a key

// Consumer Keyboard Keycodes
#define KBD_CON_SYS_POWER     0x30
#define KBD_CON_SYS_RESET     0x31
#define KBD_CON_SYS_SLEEP     0x32

#define KBD_CON_VOL_MUTE      0xE2
#define KBD_CON_VOL_UP        0xE9
#define KBD_CON_VOL_DOWN      0xEA

#define KBD_CON_MEDIA_PLAY    0xB0
#define KBD_CON_MEDIA_PAUSE   0xB1
#define KBD_CON_MEDIA_RECORD  0xB2
#define KBD_CON_MEDIA_FORWARD 0xB3
#define KBD_CON_MEDIA_REWIND  0xB4
#define KBD_CON_MEDIA_NEXT    0xB5
#define KBD_CON_MEDIA_PREV    0xB6
#define KBD_CON_MEDIA_STOP    0xB7
#define KBD_CON_MEDIA_EJECT   0xB8
#define KBD_CON_MEDIA_RANDOM  0xB9

#define KBD_CON_MENU          0x40
#define KBD_CON_MENU_PICK     0x41
#define KBD_CON_MENU_UP       0x42
#define KBD_CON_MENU_DOWN     0x43
#define KBD_CON_MENU_LEFT     0x44
#define KBD_CON_MENU_RIGHT    0x45
#define KBD_CON_MENU_ESCAPE   0x46
#define KBD_CON_MENU_INCR     0x47
#define KBD_CON_MENU_DECR     0x48
