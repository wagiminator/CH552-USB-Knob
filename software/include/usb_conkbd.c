// ===================================================================================
// USB HID Consumer Keyboard Functions for CH551, CH552 and CH554
// ===================================================================================

#include "usb_conkbd.h"
#include "usb_hid.h"
#include "usb_handler.h"

#define KBD_sendReport()  HID_sendReport(KBD_report, sizeof(KBD_report))

// ===================================================================================
// Keyboard HID report
// ===================================================================================
__xdata uint8_t KBD_report[3] = {1,0,0};

// ===================================================================================
// Press a key on keyboard
// ===================================================================================
void KBD_press(uint8_t key) {
  if(key != KBD_report[1]) {                    // new key?
    KBD_report[1] = key;                        // set key in report
    KBD_sendReport();                           // send report
  }
}

// ===================================================================================
// Release a key on keyboard
// ===================================================================================
void KBD_release(void) {
  if(KBD_report[1]) {                           // key previously pressed?
    KBD_report[1] = 0;                          // set no key in report
    KBD_sendReport();                           // send report
  }
}

// ===================================================================================
// Press and release a key on keyboard
// ===================================================================================
void KBD_type(uint8_t key) {
  KBD_press(key);
  KBD_release();
}
