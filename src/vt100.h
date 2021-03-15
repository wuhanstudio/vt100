/*
 * @Description: VT100 drawing library
 * @Author: Wu Han
 * @Date: 2019-08-24 20:16:50
 * @LastEditTime: 2019-08-24 21:04:40
 * @LastEditors: Please set LastEditors
 */

#ifndef __VT100_H__
#define __VT100_H__

#include <stdint.h>

// http://ascii-table.com/ansi-escape-sequences.php
/*             VT100              */
/* +----------------------------+ */
/* |(0, 0)              (0, 79) | */
/* |                            | */
/* |                            | */
/* |(24, 0)             (24, 79)| */
/* +----------------------------+ */
/*                                */

/* foreground Color */
typedef enum
{
    VT_F_BLACK  = 30,
    VT_F_RED    = 31,
    VT_F_GREEN  = 32,
    VT_F_YELLOW = 33,
    VT_F_BLUE   = 34,
    VT_F_PURPLE = 35,
    VT_F_CYAN   = 36,
    VT_F_WHITE  = 37
}vt_fore_color;

/* background Color */
typedef enum
{
    VT_B_BLACK  = 40,
    VT_B_RED    = 41,
    VT_B_GREEN  = 42,
    VT_B_YELLOW = 43,
    VT_B_BLUE   = 44,
    VT_B_PURPLE = 45,
    VT_B_CYAN   = 46,
    VT_B_WHITE  = 47
}vt_back_color;

void vt_clear(void);
void vt_clear_scrollback(void);
void vt_clearall(void);
void vt_clear_attr(void);

void vt_hide_cursor(void);
void vt_show_cursor(void);

void vt_move_up(uint16_t step);
void vt_move_down(uint16_t step);
void vt_move_right(uint16_t step);
void vt_move_left(uint16_t step);
void vt_move_to(uint16_t row, uint16_t col);

void vt_set_font_color(vt_fore_color color);
void vt_set_bg_color(vt_back_color color);

void vt_draw_char(char ch);
void vt_draw_char_at(uint16_t row, uint16_t col, char ch);
void vt_draw_str(char* str);
void vt_draw_str_at(uint16_t row, uint16_t col, char* ch);

void vt_draw_hline(uint16_t row, uint16_t col, uint16_t len, char ch);
void vt_draw_vline(uint16_t row, uint16_t col, uint16_t len, char ch);

void vt_fill_box(uint16_t s_row, uint16_t s_col, uint16_t n_rows, uint16_t n_cols, char ch);
void vt_draw_box(uint16_t s_row, uint16_t s_col, uint16_t n_rows, uint16_t n_cols, char h_fill, char v_fill, char c_fill);

void vt_draw_bitmap(uint16_t s_row, uint16_t s_col, uint16_t n_rows, uint16_t n_cols, const uint8_t* bitmap,
                    vt_back_color color_on, vt_back_color color_off);

/* channel width height */
void vt_draw_rgb888_cwh(uint8_t* buffer, uint16_t n_rows, uint16_t n_cols);

/* width height channel */
void vt_draw_rgb888_whc(uint8_t* buffer, uint16_t n_rows, uint16_t n_cols);

#endif /*__VT100_H__*/
