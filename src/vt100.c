/*
 * @Description: VT100 drawing library
 * @Author: Wu Han
 * @Date: 2019-08-24 20:16:50
 * @LastEditTime: 2019-08-24 20:35:52
 * @LastEditors: Please set LastEditors
 */

#include <rtthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vt100.h"

/**
 * @description: Clear screen
 * @param void 
 * @return: void
 */
void vt_clear(void)
{
    printf("\033[2J");
}
/**
 * @description: Clear attributes such as colors
 * @param void
 * @return: void
 */
void vt_clear_attr(void)
{
    printf("\033[0m");
}

/**
 * @description: Move cursor up
 * @param step Number of steps to move up
 * @return: void
 */
void vt_move_up(int step)
{
    RT_ASSERT(step >= 0);

    printf("\033[%dA", step);
}

/**
 * @description: Move cursor down
 * @param step Number of steps to move down
 * @return: void
 */
void vt_move_down(int step)
{
    RT_ASSERT(step >= 0);

    printf("\033[%dB", step);
}

/**
 * @description: Move cursor right
 * @param step Number of steps to move right
 * @return: void
 */
void vt_move_right(int step)
{
    RT_ASSERT(step >= 0);

    printf("\033[%dC", step);
}

/**
 * @description: Move cursor left
 * @param step Number of steps to move left
 * @return: void
 */
void vt_move_left(int step)
{
    RT_ASSERT(step >= 0);

    printf("\033[%dD", step);
}

/**
 * @description: Move cursor to (row, column)
 * @param row destination row number
 * @param col destination column number
 * @return: void
 */
void vt_move_to(int row, int col)
{
    RT_ASSERT(row >= 0 && col >= 0);

    printf("\033[%d;%dH", row + 1, col + 1);
}

/**
 * @description: Hide cursor
 * @param void
 * @return: void
 */
void vt_hide_cursor(void)
{
    printf("\033[?25l");
}

/**
 * @description: Show cursor
 * @param void
 * @return: void
 */
void vt_show_cursor(void)
{
    printf("\033[?25h");
}

/**
 * @description: Set font color
 * @param color font color 
 * @return: void
 */
void vt_set_font_color(int color)
{
    RT_ASSERT(color >= 30 && color <= 37);

    printf("\033[%dm", color);
}

/**
 * @description: Set background color
 * @param color background color 
 * @return: void
 */
void vt_set_bg_color(int color)
{
    RT_ASSERT(color >= 40 && color <= 47);

    printf("\033[%dm", color);
}

/**
 * @description: Draw a single character at current position
 * @param ch character to draw 
 * @return: void
 */
void vt_draw_char(char ch)
{
    printf("%c", ch);
}

/**
 * @description: Draw a string at current position
 * @param str string to draw
 * @return: 
 */
void vt_draw_str(char* str)
{
    printf("%s", str);
}

/**
 * @description: Draw a single character at (row, col)
 * @param row 
 * @param col 
 * @param ch 
 * @return: void
 */
void vt_draw_char_at(int row, int col, char ch)
{
    RT_ASSERT(row >= 0 && col >= 0);

    vt_move_to(row, col);
    printf("%c", ch);
}

/**
 * @description: Draw a string at (row, col)
 * @param row 
 * @param col 
 * @param ch 
 * @return: void
 */
void vt_draw_str_at(int row, int col, char* ch)
{
    RT_ASSERT(row >= 0 && col >= 0);

    vt_move_to(row, col);
    printf("%s", ch);
}

/**
 * @description: Draw a horizontal line beginning at (row, col) with length of (len)
 * @param row
 * @param col
 * @param len
 * @param ch
 * @return: void
 */
void vt_draw_hline(int row, int col, int len, char ch)
{
    RT_ASSERT(row >= 0 && col >= 0 && len >= 0);

    vt_move_to(row, col);
    int i;
    for(i = col; i < (col + len); i++){
        vt_draw_char(ch);
    }
}

/**
 * @description: Draw a vertical line beginning at (row, col) with length of (len)
 * @param row 
 * @param col 
 * @param len 
 * @param ch 
 * @return: void
 */
void vt_draw_vline(int row, int col, int len, char ch)
{
    RT_ASSERT(row >= 0 && col >= 0 && len >= 0);
    int i;
    for(i = row; i < (row + len); i++){
        vt_draw_char_at(i, col, ch);
    }
}

/**
 * @description: Fill a box with upper left corner at (row, col) with n_rows and n_cols
 * @param s_row
 * @param s_col
 * @param n_row
 * @param n_cols
 * @param s_row
 * @return: void
 */
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

/**
 * @description: Draw a framed box with upper left corner at (row, col) with n_rows and n_cols
 * @param s_row   starting row
 * @param s_col   starting col
 * @param n_rows  width
 * @param n_cols  height
 * @param h_fill  horizontal border
 * @param v_fill  vertical border
 * @param c_fill  corner character
 * @return: void
 */
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

/**
 * @description: Draw a bitmap with n_rows and n_cols (bytes)
 * @param  s_row        starting row
 * @param  s_col        starting column
 * @param  n_rows       width
 * @param  n_cols       height
 * @param  bitmap 
 * @param  color_on     display background
 * @param  color off    non-display background
 * @return: void
 */

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
