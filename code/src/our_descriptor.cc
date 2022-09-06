#include "our_descriptor.h"

const uint8_t our_report_descriptor[] = {
    0x05, 0x0B,       // Usage Page (Telephony)
    0x09, 0x01,       // Usage (Phone)
    0xA1, 0x01,       // Collection (Application)
    0x85, REPORT_ID,  //   Report ID (REPORT_ID)
    0x09, 0x2F,       //   Usage (Phone Mute)
    0x15, 0x00,       //   Logical Minimum (0)
    0x25, 0x01,       //   Logical Maximum (1)
    0x95, 0x01,       //   Report Count (1)
    0x75, 0x01,       //   Report Size (1)
    0x81, 0x22,       //   Input (Data,Var,Abs,No Wrap,Linear,No Preferred State,No Null Position)
    0x95, 0x07,       //   Report Count (7)
    0x81, 0x03,       //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x08,       //   Usage Page (LEDs)
    0x85, 0x02,       //   Report ID (2)
    0x09, 0x17,       //   Usage (Off-Hook)
    0x95, 0x01,       //   Report Count (1)
    0x91, 0x02,       //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x09, 0x09,       //   Usage (Mute)
    0x91, 0x02,       //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x95, 0x06,       //   Report Count (6)
    0x91, 0x03,       //   Output (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,             // End Collection
};

const uint32_t our_report_descriptor_length = sizeof(our_report_descriptor);
