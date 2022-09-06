#include <bsp/board.h>
#include <tusb.h>

#include <hardware/gpio.h>
#include <pico/bootrom.h>

#include "our_descriptor.h"
#include "ws2812.h"

#define BUTTON_PIN 3
#define NUM_PIXELS 16

#define RED 0x004000
#define GREEN 0x400000

bool mute_state = false;
bool oncall_state = false;

void update_led() {
    uint32_t color = 0x000000;
    if (oncall_state) {
        if (mute_state) {
            color = RED;
        } else {
            color = GREEN;
        }
    }

    for (int i = 0; i < NUM_PIXELS; i++) {
        put_pixel(color);
    }
}

int main() {
    board_init();
    tusb_init();
    neopixel_init();

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

/*
    sleep_ms(10);
    if (!gpio_get(BUTTON_PIN)) {
        reset_usb_boot(0, 0);
    }
*/

    update_led();

    uint8_t report;

    bool prev_button_state = false;
    absolute_time_t pressed_at = nil_time;

    while (true) {
        tud_task();
        if (!tud_hid_ready()) {
            continue;
        }

        bool button_state = !gpio_get(BUTTON_PIN);
        if (button_state && !prev_button_state) {
            report = !mute_state;
            tud_hid_report(REPORT_ID, &report, 1);
            pressed_at = get_absolute_time();
        }

        if (!button_state && prev_button_state) {
            if (!mute_state && (absolute_time_diff_us(pressed_at, get_absolute_time()) > 500000)) {
                report = 1;
                tud_hid_report(REPORT_ID, &report, 1);
            }
        }

        prev_button_state = button_state;
        sleep_ms(4);
    }

    return 0;
}

void tud_hid_set_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    if (bufsize >= 1) {
        oncall_state = buffer[0] & 0x01;
        mute_state = buffer[0] & 0x02;
        update_led();
    }
}

uint16_t tud_hid_get_report_cb(uint8_t itf, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    return 0;
}
