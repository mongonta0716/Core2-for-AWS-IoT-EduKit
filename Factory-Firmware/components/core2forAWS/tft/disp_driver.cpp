/**
 * @file disp_driver.c
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

#define LGFX_M5STACK_CORE2
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <LGFX_AUTODETECT.hpp>

static LGFX gfx;

#include "disp_driver.h"

extern "C" {
    void disp_driver_init(void) {
        gfx.init();
        gfx.setRotation(1);
        gfx.startWrite();
    }

    void disp_driver_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_map) {
        uint32_t w = (area->x2 - area->x1 + 1);
        uint32_t h = (area->y2 - area->y1 + 1);
        gfx.setAddrWindow(area->x1, area->y1, w, h);
        gfx.writePixelsDMA(&color_map->full, w*h, false);
        //gfx.pushImageDMA(area->x1, area->y1, w, h, &color_map->full);
        //gfx.endWrite();
        lv_disp_flush_ready(drv); // tell lvgl that flushing is done
    }
}
