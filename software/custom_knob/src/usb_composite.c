// ===================================================================================
// USB HID Composite Device Functions for CH551, CH552 and CH554
// ===================================================================================

#include "usb_composite.h"
#include "usb_hid.h"
#include "usb_handler.h"

#define KBD_sendReport()    HID_sendReport(KBD_report, sizeof(KBD_report))
#define CON_sendReport()    HID_sendReport(CON_report, sizeof(CON_report))
#define JOY_sendReport()    HID_sendReport(JOY_report, sizeof(JOY_report))
#define MOUSE_sendReport()  HID_sendReport(MOUSE_report, sizeof(MOUSE_report))

// ===================================================================================
// HID reports
// ===================================================================================
__xdata uint8_t KBD_report[]   = {1,0,0,0,0,0,0,0};
__xdata uint8_t CON_report[]   = {2,0,0};
__xdata uint8_t MOUSE_report[] = {3,0,0,0,0};
__xdata uint8_t JOY_report[]   = {4,0,0,0};

// ===================================================================================
// ASCII to keycode mapping table
// ===================================================================================
__code uint8_t KBD_map[128] = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a, 0x2b, 0x28, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x2c, 0x9e, 0xb4, 0xa0, 0xa1, 0xa2, 0xa4, 0x34, 0xa6, 0xa7,
  0xa5, 0xae, 0x36, 0x2d, 0x37, 0x38, 0x27, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24,
  0x25, 0x26, 0xb3, 0x33, 0xb6, 0x2e, 0xb7, 0xb8, 0x9f, 0x84, 0x85, 0x86, 0x87, 0x88,
  0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96,
  0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x2f, 0x31, 0x30, 0xa3, 0xad, 0x35, 0x04,
  0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12,
  0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0xaf, 0xb1, 0xb0,
  0xb5, 0x00
};

// ===================================================================================
// Standard Keyboard Functions
// ===================================================================================

// Press a key on keyboard
void KBD_press(uint8_t key) {
  uint8_t i;

  // Convert key for HID report
  if(key >= 136) key -= 136;                    // non-printing key/not a modifier?
  else if(key >= 128) {                         // modifier key?
    KBD_report[1] |= (1<<(key-128));            // add modifier to report
    key = 0;
  }
  else {                                        // printing key?
    key = KBD_map[key];                         // convert ascii to keycode for report
    if(!key) return;                            // no valid key
    if(key & 0x80) {                            // capital letter/shift character?
      KBD_report[1] |= 0x02;                    // add left shift modifier
      key &= 0x7F;                              // remove shift from key itself
    }
  }

  // Check if key is already present in report
  for(i=3; i<8; i++) {
    if(KBD_report[i] == key) return;            // return if already in report
  }

  // Find an empty slot, insert key and transmit report
  for(i=3; i<8; i++) {
    if(KBD_report[i] == 0) {                    // empty slot?
      KBD_report[i] = key;                      // insert key
      KBD_sendReport();                         // send report
      return;                                   // and return
    }
  }
}

// Release a key on keyboard
void KBD_release(uint8_t key) {
  uint8_t i;

  // Convert key for HID report
  if(key >= 136) key -= 136;                    // non-printing key/not a modifier?
  else if(key >= 128) {                         // modifier key?
    KBD_report[1] &= ~(1<<(key-128));           // delete modifier in report
    key = 0;
  }
  else {                                        // printing key?
    key = KBD_map[key];                         // convert ascii to keycode for report
    if(!key) return;                            // no valid key
    if(key & 0x80) {                            // capital letter/shift character?
      KBD_report[1] &= ~0x02;                   // remove shift modifier
      key &= 0x7F;                              // remove shift from key itself
    }
  }

  // Delete key in report
  for(i=3; i<8; i++) {
    if(KBD_report[i] == key) KBD_report[i] = 0; // delete key in report
  }
  KBD_sendReport();                             // send report
}

// Press and release a key on keyboard
void KBD_type(uint8_t key) {
  KBD_press(key);
  KBD_release(key);
}

// Release all keys on keyboard
void KBD_releaseAll(void) {
  uint8_t i;
  for(i=7; i; i--) KBD_report[i] = 0;           // delete all keys in report
  KBD_sendReport();                             // send report
}

// Write text with keyboard
void KBD_print(char* str) {
  while(*str) KBD_type(*str++);
}

// ===================================================================================
// Consumer Multimedia Keyboard Functions
// ===================================================================================

// Press a consumer key on keyboard
void CON_press(uint8_t key) {
  CON_report[1] = key;
  CON_sendReport();                             // send report
}

// Release a consumer key on keyboard
void CON_release(void) {
  CON_report[1] = 0;
  CON_sendReport();
}

// Press and release a consumer key on keyboard
void CON_type(uint8_t key) {
  CON_press(key);
  CON_release();
}

// ===================================================================================
// Mouse Functions
// ===================================================================================

// Press mouse button(s)
void MOUSE_press(uint8_t buttons) {
  MOUSE_report[1] |= buttons;                   // press button(s)
  MOUSE_sendReport();                           // send HID report
}

// Release mouse button(s)
void MOUSE_release(uint8_t buttons) {
  MOUSE_report[1] &= ~buttons;                  // release button(s)
  MOUSE_sendReport();                           // send HID report
}

// Move mouse pointer
void MOUSE_move(int8_t xrel, int8_t yrel) {
  MOUSE_report[2] = (uint8_t)xrel;              // set relative x-movement
  MOUSE_report[3] = (uint8_t)yrel;              // set relative y-movement
  MOUSE_sendReport();                           // send HID report
  MOUSE_report[2] = 0;                          // reset movements
  MOUSE_report[3] = 0;
}

// Move mouse wheel
void MOUSE_wheel(int8_t rel) {
  MOUSE_report[4] = (uint8_t)rel;               // set relative wheel movement
  MOUSE_sendReport();                           // send HID report
  MOUSE_report[4] = 0;                          // reset movements
}

// ===================================================================================
// Joystick Functions
// ===================================================================================

// Press joystick button(s)
void JOY_press(uint8_t buttons) {
  JOY_report[1] |= buttons;                     // press button(s)
  JOY_sendReport();                             // send HID report
}

// Release joystick button(s)
void JOY_release(uint8_t buttons) {
  JOY_report[1] &= ~buttons;                    // release button(s)
  JOY_sendReport();                             // send HID report
}

// Move joystick
void JOY_move(int8_t xrel, int8_t yrel) {
  JOY_report[2] = (uint8_t)xrel;                // set x-movement
  JOY_report[3] = (uint8_t)yrel;                // set y-movement
  JOY_sendReport();                             // send HID report
}
