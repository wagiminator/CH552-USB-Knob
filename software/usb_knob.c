// ===================================================================================
// Project:   USB Rotary Encoder for CH551, CH552 and CH554
// Version:   v1.1
// Year:      2023
// Author:    Stefan Wagner
// Github:    https://github.com/wagiminator
// EasyEDA:   https://easyeda.com/wagiminator
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Controls PC volume via rotary encoder.
//
// References:
// -----------
// - Blinkinlabs: https://github.com/Blinkinlabs/ch554_sdcc
// - Deqing Sun: https://github.com/DeqingSun/ch55xduino
// - Ralph Doncaster: https://github.com/nerdralph/ch554_sdcc
// - WCH Nanjing Qinheng Microelectronics: http://wch.cn
// - ATtiny85 TinyKnob: https://github.com/wagiminator/ATtiny85-TinyKnob
//
// Compilation Instructions:
// -------------------------
// - Chip:  CH551, CH552 or CH554
// - Clock: min. 12 MHz internal
// - Adjust the firmware parameters in include/config.h if necessary.
// - Make sure SDCC toolchain and Python3 with PyUSB is installed.
// - Press BOOT button on the board and keep it pressed while connecting it via USB
//   with your PC.
// - Run 'make flash'.
//
// Operating Instructions:
// -----------------------
// - Connect the board via USB to your PC. It should be detected as a HID device.
// - Turn the rotary endoder to increase/decrease volume.
// - Press rotary encoder button to mute.


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================

// Libraries
#include <config.h>                       // user configurations
#include <system.h>                       // system functions
#include <delay.h>                        // delay functions
#include <neo.h>                          // NeoPixel functions
#include <usb_conkbd.h>                   // USB HID consumer keyboard functions

// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USB_interrupt();
}

// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {
  // Variables
  uint8_t cnt = 1;                        // hue cycle counter
  uint8_t hue = 0;                        // hue cycle value
  uint8_t currentKey;                     // current key to be sent
  __bit isSwitchPressed = 0;              // state of rotary encoder switch

  // Setup
  CLK_config();                           // configure system clock
  DLY_ms(5);                              // wait for clock to settle
  KBD_init();                             // init USB HID keyboard
  NEO_init();                             // init NeoPixel
  WDT_start();                            // start watchdog timer

  // Loop
  while(1) {
    WDT_reset();                                          // reset watchdog
    currentKey = 0;                                       // clear key variable
    if(!PIN_read(PIN_ENC_A)) {                            // encoder turned ?
      if(PIN_read(PIN_ENC_B)) currentKey = CON_VOL_UP;    // clockwise?
      else                    currentKey = CON_VOL_DOWN;  // counter-clockwise?
      DLY_ms(10);                                         // debounce
      while(!PIN_read(PIN_ENC_A));                        // wait until next detent
    } 
    else {
      if(!isSwitchPressed && !PIN_read(PIN_ENC_SW)) {     // switch previously pressed?
        currentKey = CON_VOL_MUTE;
        isSwitchPressed = 1;
      }
      else if(isSwitchPressed && PIN_read(PIN_ENC_SW)) {  // switch previously released?
        isSwitchPressed = 0;
      }
    }
    if(currentKey) CON_press(currentKey);                 // press corresponding key ...
    else CON_releaseAll();                                // ... or release last key
    if(!--cnt) {                                          // time to cycle hue?
      NEO_writeHue(hue, 0); NEO_writeHue(hue, 0);         // set NeoPixels hue value
      if(!hue--) hue = 191;                               // cycle hue value
    }
  }
}
