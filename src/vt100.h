/*
 * @Description: VT100 drawing library
 * @Author: Wu Han
 * @Date: 2019-08-24 20:16:50
 * @LastEditTime: 2019-08-24 21:04:40
 * @LastEditors: Please set LastEditors
 */

#ifndef __VT100_H__
#define __VT100_H__

#include <rtdef.h>

// http://ascii-table.com/ansi-escape-sequences.php
/*               VT100              */
/*               cols               */
/*   +----------------------------+ */
/* r |(0, 0)              (0, 79) | */
/* o |                            | */
/* w |                            | */
/* s |(23, 0)             (23, 79)| */
/*   +----------------------------+ */
/*                                  */

#define VT_DEFAULT_ROW_SIZE   24
#define VT_DEFAULT_COL_SIZE   80

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

/* clear */
void vt_clear(void);
void vt_clear_scrollback(void);
void vt_clear_line(void);
void vt_clearall(void);

/* attribute */
void vt_clear_attr(void);

/* cursor */
void vt_restore_cursor(void);
void vt_store_cursor(void);
void vt_hide_cursor(void);
void vt_show_cursor(void);
void vt_move_up(rt_uint16_t step);
void vt_move_down(rt_uint16_t step);
void vt_move_right(rt_uint16_t step);
void vt_move_left(rt_uint16_t step);
void vt_move_to(rt_uint16_t row, rt_uint16_t col);

/* terminal screen */
void vt_store_screen(void);
void vt_restore_screen(void);
void vt_set_terminal_size(rt_uint16_t row, rt_uint16_t col);
void vt_set_terminal_default_size(void);
void vt_set_terminal_position(rt_uint16_t row_px, rt_uint16_t col_px);
#if RT_VER_NUM >= 0x40004
void vt_get_terminal_size(rt_uint16_t *row, rt_uint16_t *col);
#endif /* RT_VER_NUM >= 0x40004 */
void vt_maximize_terminal(void);
void vt_unmaximize_terminal(void);

/* drawing */
void vt_set_font_color(vt_fore_color color);
void vt_set_bg_color(vt_back_color color);

void vt_draw_char(char ch);
void vt_draw_char_at(rt_uint16_t row, rt_uint16_t col, char ch);
void vt_draw_str(char* str);
void vt_draw_str_at(rt_uint16_t row, rt_uint16_t col, char* str);

void vt_draw_hline(rt_uint16_t row, rt_uint16_t col, rt_uint16_t len, char ch);
void vt_draw_vline(rt_uint16_t row, rt_uint16_t col, rt_uint16_t len, char ch);

void vt_fill_box(rt_uint16_t s_row, rt_uint16_t s_col, rt_uint16_t n_rows, rt_uint16_t n_cols, char ch);
void vt_draw_box(rt_uint16_t s_row, rt_uint16_t s_col, rt_uint16_t n_rows, rt_uint16_t n_cols, char h_fill, char v_fill, char c_fill);

void vt_draw_bitmap(rt_uint16_t s_row, rt_uint16_t s_col, rt_uint16_t n_rows, rt_uint16_t n_cols, const rt_uint8_t* bitmap,
                    vt_back_color color_on, vt_back_color color_off);

/* channel width height */
void vt_draw_rgb888_cwh(rt_uint8_t* buffer, rt_uint16_t n_rows, rt_uint16_t n_cols);

/* width height channel */
void vt_draw_rgb888_whc(rt_uint8_t* buffer, rt_uint16_t n_rows, rt_uint16_t n_cols);

#endif /*__VT100_H__*/
