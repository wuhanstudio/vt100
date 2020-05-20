#include <rtthread.h>
#include <stdio.h>

#include <vt100.h>
#include "wuhanstudios.h"

void vt_rgb_buf(int argc, char* arvg[])
{
    vt_draw_rgb888(wuhanstudios, wuhanstudios_w, wuhanstudios_h);
}
MSH_CMD_EXPORT(vt_rgb_buf, draw RGB image in console)
