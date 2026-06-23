#include "lvgl.h"
#include "lvgl/drivers/sdl/lv_sdl_window.h"
#include "lvgl/drivers/sdl/lv_sdl_mouse.h"
#include "lvgl/drivers/sdl/lv_sdl_keyboard.h"

#include <cstdio>

int main()
{
    lv_init();

    lv_display_t * display = lv_sdl_window_create(800, 480);
    if (!display) {
        printf("Failed to create SDL display\n");
        return 1;
    }

    lv_sdl_mouse_create();
    lv_sdl_keyboard_create();

    lv_obj_t * label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "LVGL Playground");
    lv_obj_center(label);

    printf("LVGL SDL app started\n");

    while (true) {
        lv_timer_handler();
        lv_delay_ms(5);
    }

    return 0;
}