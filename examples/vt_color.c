/*
 * @Description: VT100 Color demo
 * @Author: Wu Han
 * @Date: 2019-08-24 21:02:52
 * @LastEditTime: 2019-08-24 21:34:44
 * @LastEditors: Please set LastEditors
 */

#include <rtthread.h>
#include "vt100.h"

static void vt_color(int argc, char* argv[])
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
            vt_set_font_color((vt_fore_color)(VT_F_BLACK + i - 1));
        }
        vt_set_bg_color((vt_back_color)(VT_B_BLACK + i));
        vt_draw_hline(0, i, 80, ' ');
        vt_draw_str_at(31, i, "Put your text here");
    }

    // 2. Boxes
    vt_set_font_color(VT_F_WHITE);
    vt_set_bg_color(VT_B_BLACK);
    for (int i = 0; i < 7; i++)
    {
        vt_draw_box(0, 8 + i, 40 - i * 2, 16 - i * 2, '-', '|', '+');
    }

    // 3. Logo
    char rt_str[30];
    vt_draw_str_at(40, 14, " \\ | /");
    vt_draw_str_at(40, 15, "- RT -     Thread Operating System\n");
    rt_sprintf(rt_str, " / | \\     %ld.%ld.%ld build %s\n", RT_VERSION, RT_SUBVERSION, RT_REVISION, __DATE__);
    vt_draw_str_at(40, 16, rt_str);
    vt_draw_str_at(40, 17, " 2006 - 2019 Copyright by rt-thread team\n");

    // 4. Fill box
    for (int i = 0; i < 6; i++)
    {
        vt_set_bg_color((vt_back_color)(VT_B_RED + i));
        vt_fill_box(43 + i * 6, 9, 4, 4, ' ');
    }

    for (int i = 5; i >= 0; i--)
    {
        vt_set_bg_color((vt_back_color)(VT_B_WHITE - i));
        vt_fill_box(43 + i * 6, 19, 4, 4, ' ');
    }

    vt_set_bg_color(VT_B_BLACK);
    vt_move_to(0, 23);
    rt_kprintf("\n");

    vt_clear_attr();
    vt_show_cursor();

}
MSH_CMD_EXPORT(vt_color, vt color demo)
