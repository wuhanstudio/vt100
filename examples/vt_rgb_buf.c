#include <rtthread.h>
#include <stdio.h>

#include <vt100.h>
#include "minions.h"

void vt_rgb_buf(int argc, char* arvg[])
{
    vt_draw_rgb888_cwh(minions, minions_w, minions_h);
}
MSH_CMD_EXPORT(vt_rgb_buf, draw RGB image in console)
