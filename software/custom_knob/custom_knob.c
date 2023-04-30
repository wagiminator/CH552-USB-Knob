// ===================================================================================
// Project:   USB Rotary Encoder for CH551, CH552 and CH554 - Custom Control
// Version:   v1.0
// Year:      2023
// Author:    Stefan Wagner
// Github:    https://github.com/wagiminator
// EasyEDA:   https://easyeda.com/wagiminator
// License:   http://creativecommons.org/licenses/by-sa/3.0/
// ===================================================================================
//
// Description:
// ------------
// Customize your USB Rotary Encoder Knob.
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
// - Clock: 16 MHz internal
// - Adjust the firmware parameters in src/config.h if necessary.
// - Customize the macro functions in the corresponding section below.
// - Make sure SDCC toolchain and Python3 with PyUSB is installed.
// - Press BOOT button on the board and keep it pressed while connecting it via USB
//   with your PC.
// - Run 'make flash' immediatly afterwards.
// - To compile the firmware using the Arduino IDE, follow the instructions in the 
//   .ino file.
//
// Operating Instructions:
// -----------------------
// - Costomize your rotary encoder knob below in this firmware.
// - Connect the board via USB to your PC. It should be detected as a HID composite
//   device with keyboard, mouse and game controller interface.
// - Turn the rotary encoder or press the encoder switch.
// - To enter bootloader hold down the rotary encoder switch while connecting the 
//   device to USB. The NeoPixels will light up white as long as the device is in 
//   bootloader mode (about 10 seconds).


// ===================================================================================
// Libraries, Definitions and Macros
// ===================================================================================

// Libraries
#include "src/config.h"                   // user configurations
#include "src/system.h"                   // system functions
#include "src/delay.h"                    // delay functions
#include "src/neo.h"                      // NeoPixel functions
#include "src/usb_composite.h"            // USB HID composite functions

// Prototypes for used interrupts
void USB_interrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USB_interrupt();
}

// ===================================================================================
// Macro Functions which associate Actions with Events (Customize your USB Knob here!)
// ===================================================================================
//
// The list of available USB HID functions can be found in src/usb_composite.h

// Rotary encoder example -> volume control knob
// ---------------------------------------------

// Define action(s) if encoder was rotated clockwise
inline void ENC_CW_ACTION() {
  CON_press(CON_VOL_UP);                              // press VOLUME UP key
}

// Define action(s) after encoder was rotated clockwise
inline void ENC_CW_RELEASED() {
  CON_release();                                      // release VOLUME UP KEY
}

// Define action(s) if encoder was rotated counter-clockwise
inline void ENC_CCW_ACTION() {
  CON_press(CON_VOL_DOWN);                            // press VOLUME DOWN key
}

// Define action(s) after encoder was rotated counter-clockwise
inline void ENC_CCW_RELEASED() {
  CON_release();                                      // release VOLUME DOWN KEY
}

// Define action(s) if encoder switch was pressed
inline void ENC_SW_PRESSED() {
  CON_press(CON_VOL_MUTE);                            // press VOLUME MUTE key
}

// Define action(s) if encoder switch was released
inline void ENC_SW_RELEASED() {
  CON_release();                                      // release VOLUME MUTE key
}

// ===================================================================================
// Main Function
// ===================================================================================
void main(void) {

  // Variables
  uint8_t i;                              // temp variable
  uint8_t cnt = 1;                        // hue cycle counter
  uint8_t hue = 0;                        // hue cycle value
  __bit isSwitchPressed = 0;              // state of rotary encoder switch

  // Setup
  NEO_init();                             // init NeoPixels
  CLK_config();                           // configure system clock
  DLY_ms(10);                             // wait for clock to settle

  // Enter bootloader if encoder switch is pressed
  if(!PIN_read(PIN_ENC_SW)) {             // encoder switch pressed?
    for(i=6; i; i--) NEO_sendByte(127);   // light up all pixels
    BOOT_now();                           // enter bootloader
  }

  // Init USB keyboard
  HID_init();                             // init USB HID consumer keyboard
  DLY_ms(500);                            // wait for Windows...
  WDT_start();                            // start watchdog timer

  // Loop
  while(1) {
    if(!PIN_read(PIN_ENC_A)) {                            // encoder turned ?
      if(PIN_read(PIN_ENC_B)) {                           // clockwise ?
        ENC_CW_ACTION();                                  // take proper action
        DLY_ms(5);                                        // debounce
        ENC_CW_RELEASED();                                // take proper action
      }
      else {                                              // counter-clockwise ?
        ENC_CCW_ACTION();                                 // take proper action
        DLY_ms(5);                                        // debounce
        ENC_CCW_RELEASED();                               // take proper action
      }
      while(!PIN_read(PIN_ENC_A));                        // wait until next detent
    } 
    else {
      if(!isSwitchPressed && !PIN_read(PIN_ENC_SW)) {     // switch previously pressed?
        ENC_SW_PRESSED();                                 // take proper action
        isSwitchPressed = 1;
      }
      else if(isSwitchPressed && PIN_read(PIN_ENC_SW)) {  // switch previously released?
        ENC_SW_RELEASED();                                // take proper action
        isSwitchPressed = 0;                              // update switch state
      }
    }
    if(!--cnt) {                                          // time to cycle hue?
      NEO_writeHue(hue, 0); NEO_writeHue(hue, 0);         // set NeoPixels hue value
      if(!hue--) hue = 191;                               // cycle hue value
    }
    DLY_ms(1);                                            // slow down a little
    WDT_reset();                                          // reset watchdog
  }
}
