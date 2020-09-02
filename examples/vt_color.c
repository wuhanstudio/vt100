/*
 * @Description: VT100 Color demo
 * @Author: Wu Han
 * @Date: 2019-08-24 21:02:52
 * @LastEditTime: 2019-08-24 21:34:44
 * @LastEditors: Please set LastEditors
 */

#include <rtthread.h>
#include <stdio.h>

#include "vt100.h"

void vt_color(int argc, char* argv[])
{
    vt_hide_cursor();
    vt_clear();

    // 1. Corlor Bar
    for (int i = 0; i < 8; i++)
    {
        if(i == 0)
        {
            vt_set_font_color(VT_F_WHITE);
        }
        else
        {
            vt_set_font_color(VT_F_BLACK + i - 1 );
        }
        vt_set_bg_color(VT_B_BLACK + i);
        vt_draw_hline(i, 0, 80, ' ');
        vt_draw_str_at(i, 31, "Put your text here");
    }

    // 2. Boxes
    vt_set_font_color(VT_F_WHITE);
    vt_set_bg_color(VT_B_BLACK);
    for (int i = 0; i < 7; i++)
    {
        vt_draw_box(8 + i, 0, 16 - i * 2, 40 - i * 2, '-', '|', '+');
    }

    // 3. Logo
    char rt_str[30];
    vt_draw_str_at(14, 40, " \\ | /");
    vt_draw_str_at(15, 40, "- RT -     Thread Operating System\n");
    sprintf(rt_str, " / | \\     %ld.%ld.%ld build %s\n", RT_VERSION, RT_SUBVERSION, RT_REVISION, __DATE__);
    vt_draw_str_at(16, 40, rt_str);
    vt_draw_str_at(17, 40, " 2006 - 2019 Copyright by rt-thread team\n");

    // 4. Fill box
    for (int i = 0; i < 6; i++)
    {
        vt_set_bg_color(VT_B_RED + i);
        vt_fill_box(9, 43 + i * 6, 4, 4, ' ');
    }

    for (int i = 5; i >= 0; i--)
    {
        vt_set_bg_color(VT_B_WHITE - i);
        vt_fill_box(19, 43 + i * 6, 4, 4, ' ');
    }

    vt_set_bg_color(VT_B_BLACK);
    vt_move_to(23, 0);
    printf("\n");

    vt_clear_attr();
    vt_show_cursor();

}
MSH_CMD_EXPORT(vt_color, vt color demo)
