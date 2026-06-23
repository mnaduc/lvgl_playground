#include "lvgl.h"
#include <cstdio>

int main()
{
    printf("app started\n");
    fflush(stdout);

    lv_init();

    // TODO: SDL display driver

    while (true)
    {
        lv_timer_handler();
        lv_delay_ms(5);
    }

    return 0;
}