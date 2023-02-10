// ===================================================================================
// User Configurations for CH552E USB Rotary Encoder
// ===================================================================================

#pragma once

// Pin definitions
#define PIN_NEO             P14       // pin connected to NeoPixel
#define PIN_ENC_A           P15       // pin connected to rotary encoder A
#define PIN_ENC_B           P16       // pin connected to rotary encoder B
#define PIN_ENC_SW          P17       // pin connected to rotary encoder switch

// NeoPixel configuration
#define NEO_GRB                       // type of pixel: NEO_GRB or NEO_RGB

// USB device descriptor
#define USB_VENDOR_ID       0x16C0    // VID (shared www.voti.nl)
#define USB_PRODUCT_ID      0x05DF    // PID (shared HID-keyboards)
#define USB_DEVICE_VERSION  0x0100    // v1.0 (BCD-format)

// USB configuration descriptor
#define USB_MAX_POWER_mA    50        // max power in mA 

// USB descriptor strings
#define MANUFACTURER_STR    'w','a','g','i','m','i','n','a','t','o','r'
#define PRODUCT_STR         'T','i','n','y','K','n','o','b'
#define SERIAL_STR          'C','H','5','5','2','x','H','I','D'
#define INTERFACE_STR       'H','I','D','-','K','e','y','b','o','a','r','d'
