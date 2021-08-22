#include <rtthread.h>
#include <vt100.h>
#include "minions.h"

static void vt_imshow(int argc, char* arvg[])
{
    vt_draw_rgb888_cwh(minions, minions_w, minions_h);
}
MSH_CMD_EXPORT(vt_imshow, draw RGB image in console)
