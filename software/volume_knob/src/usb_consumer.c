// ===================================================================================
// USB HID Consumer Keyboard Functions for CH551, CH552 and CH554
// ===================================================================================

#include "usb_consumer.h"
#include "usb_hid.h"
#include "usb_handler.h"

#define CON_sendReport()  HID_sendReport(CON_report, sizeof(CON_report))

// Consumer Keyboard HID report
__xdata uint8_t  CON_report[3] = {1,0,0};

// Press a consumer key on keyboard
void CON_press(uint8_t key) {
  CON_report[1] = key;
  CON_sendReport();
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
