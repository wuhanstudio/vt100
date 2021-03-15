/*
 * @Description: VT100 drawing library
 * @Author: Wu Han
 * @Date: 2019-08-24 20:16:50
 * @LastEditTime: 2019-08-24 20:35:52
 * @LastEditors: Please set LastEditors
 */

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
 * @description: Delete all lines saved in the scrollback buffer
 * @param void
 * @return: void
 */
void vt_clear_scrollback(void)
{
    printf("\033[3J");
}

/**
 * @description: Clear screen & delete all lines saved in the scrollback buffer & move cursor to (0,0)
 * @param void
 * @return: void
 */
void vt_clearall(void)
{
    vt_clear();
    vt_clear_scrollback();
    vt_move_to(0,0);
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
void vt_move_up(uint16_t step)
{
    printf("\033[%dA", step);
}

/**
 * @description: Move cursor down
 * @param step Number of steps to move down
 * @return: void
 */
void vt_move_down(uint16_t step)
{
    printf("\033[%dB", step);
}

/**
 * @description: Move cursor right
 * @param step Number of steps to move right
 * @return: void
 */
void vt_move_right(uint16_t step)
{
    printf("\033[%dC", step);
}

/**
 * @description: Move cursor left
 * @param step Number of steps to move left
 * @return: void
 */
void vt_move_left(uint16_t step)
{
    printf("\033[%dD", step);
}

/**
 * @description: Move cursor to (row, column)
 * @param row destination row number, starting from 0
 * @param col destination column number, starting from 0
 * @return: void
 */
void vt_move_to(uint16_t row, uint16_t col)
{
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
void vt_set_font_color(vt_fore_color color)
{
    printf("\033[%dm", color);
}

/**
 * @description: Set background color
 * @param color background color
 * @return: void
 */
void vt_set_bg_color(vt_back_color color)
{
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
void vt_draw_char_at(uint16_t row, uint16_t col, char ch)
{
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
void vt_draw_str_at(uint16_t row, uint16_t col, char* ch)
{
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
void vt_draw_hline(uint16_t row, uint16_t col, uint16_t len, char ch)
{
    uint16_t i;

    vt_move_to(row, col);
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
void vt_draw_vline(uint16_t row, uint16_t col, uint16_t len, char ch)
{
    uint16_t i;
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
void vt_fill_box(uint16_t s_row, uint16_t s_col, uint16_t n_rows, uint16_t n_cols, char ch)
{
    uint16_t row = 0;
    uint16_t col = 0;
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
void vt_draw_box(uint16_t s_row, uint16_t s_col, uint16_t n_rows, uint16_t n_cols, char h_fill, char v_fill, char c_fill)
{
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
void vt_draw_bitmap(uint16_t s_row, uint16_t s_col, uint16_t n_rows, uint16_t n_cols, const uint8_t* bitmap,
                    vt_back_color color_on, vt_back_color color_off)
{
    uint16_t row = 0;
    uint16_t col = 0;
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

void vt_draw_rgb888_cwh(uint8_t* buffer, uint16_t n_rows, uint16_t n_cols)
{
    uint16_t row = 0;
    uint16_t col = 0;
    for (row = 0; row < n_rows; row++)
    {
        for (col = 0; col < n_cols; col++)
        {
            uint8_t r = buffer[row * n_cols + col];
            uint8_t g = buffer[n_rows * n_cols + row * n_cols + col];
            uint8_t b = buffer[n_rows * n_cols * 2 + row * n_cols + col];
            printf("\x1b[48;2;%d;%d;%dm\x1b[38;2;%d;%d;%dm◾\x1b[39m\x1b[49m", r, g, b, r, g, b);
        }
        printf("\n");
    }
}

void vt_draw_rgb888_whc(uint8_t* buffer, uint16_t n_rows, uint16_t n_cols)
{
    uint16_t row = 0;
    uint16_t col = 0;
    for (row = 0; row < n_rows; row++)
    {
        for (col = 0; col < n_cols; col++)
        {
            uint8_t r = buffer[row * n_cols * 3 + col * 3];
            uint8_t g = buffer[row * n_cols * 3 + col * 3 + 1];
            uint8_t b = buffer[row * n_cols * 3 + col * 3 + 2];
            printf("\x1b[48;2;%d;%d;%dm\x1b[38;2;%d;%d;%dm◾\x1b[39m\x1b[49m", r, g, b, r, g, b);
        }
        printf("\n");
    }
}
