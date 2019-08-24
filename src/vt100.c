#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vt100.h"

void vt_clear(void)
{
    printf("\033[2J");
}

void vt_clear_attr(void)
{
    printf("\033[0m");
}

void vt_move_up(int step)
{
    RT_ASSERT(step >= 0);

    printf("\033[%dA", step);
}

void vt_move_down(int step)
{
    RT_ASSERT(step >= 0);

    printf("\033[%dB", step);
}

void vt_move_right(int step)
{
    RT_ASSERT(step >= 0);

    printf("\033[%dC", step);
}

void vt_move_left(int step)
{
    RT_ASSERT(step >= 0);

    printf("\033[%dD", step);
}

void vt_move_to(int row, int col)
{
    RT_ASSERT(row >= 0 && col >= 0);

    printf("\033[%d;%dH", row + 1, col + 1);
}

void vt_hide_cursor(void)
{
    printf("\033[?25l");
}

void vt_show_cursor(void)
{
    printf("\033[?25h");
}

void vt_set_font_color(int color)
{
    RT_ASSERT(color >= 30 && color <= 37);

    printf("\033[%dm", color);
}

void vt_set_bg_color(int color)
{
    RT_ASSERT(color >= 40 && color <= 47);

    printf("\033[%dm", color);
}

void vt_draw_char(char ch)
{
    printf("%c", ch);
}

void vt_draw_str(char* ch)
{
    printf("%s", ch);
}

void vt_draw_char_at(int row, int col, char ch)
{
    RT_ASSERT(row >= 0 && col >= 0);

    vt_move_to(row, col);
    printf("%c", ch);
}

void vt_draw_str_at(int row, int col, char* ch)
{
    RT_ASSERT(row >= 0 && col >= 0);

    vt_move_to(row, col);
    printf("%s", ch);
}

void vt_draw_hline(int row, int col, int len, char ch)
{
    RT_ASSERT(row >= 0 && col >= 0 && len >= 0);

    vt_move_to(row, col);
    int i;
    for(i = col; i < (col + len); i++){
        vt_draw_char(ch);
    }
}

void vt_draw_vline(int row, int col, int len, char ch)
{
    RT_ASSERT(row >= 0 && col >= 0 && len >= 0);
    int i;
    for(i = row; i < (row + len); i++){
        vt_draw_char_at(i, col, ch);
    }
}

void vt_fill_box(int s_row, int s_col, int n_rows, int n_cols, char ch)
{
    RT_ASSERT(s_row >= 0 && s_col >= 0);
    RT_ASSERT(n_rows >= 0 && n_cols >= 0);

    int row = 0;
    int col = 0;
    for (row = s_row; row < (s_row + n_rows); row++){
        vt_move_to(row, s_col);
        for (col = s_col; col < (s_col + n_cols); col++){
            vt_draw_char(ch);
        }
    }
}

void vt_draw_box(int s_row, int s_col, int n_rows, int n_cols, char h_fill, char v_fill, char c_fill)
{
    RT_ASSERT(s_row >= 0 && s_col >= 0);
    RT_ASSERT(n_rows >= 0 && n_cols >= 0);

    vt_draw_hline(s_row, s_col, n_cols, h_fill);
    vt_draw_hline(s_row + n_rows - 1, s_col, n_cols, h_fill);
    vt_draw_vline(s_row, s_col, n_rows, v_fill);
    vt_draw_vline(s_row, s_col + n_cols - 1, n_rows, v_fill);

    vt_draw_char_at(s_row, s_col, c_fill);
    vt_draw_char_at(s_row, s_col + n_cols - 1, c_fill);
    vt_draw_char_at(s_row + n_rows - 1, s_col, c_fill);
    vt_draw_char_at(s_row + n_rows - 1, s_col + n_cols - 1, c_fill);
}

void vt_draw_bitmap(int s_row, int s_col, int n_rows, int n_cols, const rt_uint8_t* bitmap, char color_on, char color_off)
{
    RT_ASSERT(s_row >= 0 && s_col >= 0);
    RT_ASSERT(n_rows >= 0 && n_cols >= 0);
    RT_ASSERT(color_on >= 40 && color_on <= 47);
    RT_ASSERT(color_off >= 40 && color_off <= 47);

    int row = 0;
    int col = 0;
    for (row = s_row; row < (s_row + n_rows); row++)
    {
        vt_move_to(row, s_col);
        for (col = 0; col < (n_cols * 8); col++)
        {
            if((bitmap[row] & (1 << col)))
            {
                vt_set_bg_color(color_on);
            }
            else
            {
                vt_set_bg_color(color_off);
            }
            vt_draw_char(' ');
        }
    }
}
