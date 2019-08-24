#ifndef __VT100_H__
#define __VT100_H__


// http://ascii-table.com/ansi-escape-sequences.php
/*             VT100              */
/* +----------------------------+ */
/* |(0, 0)              (0, 79) | */
/* |                            | */
/* |                            | */
/* |(24, 0)             (24, 79)| */
/* +----------------------------+ */
/*                                */

// Foreground Color
#define VT_F_BLACK      30
#define VT_F_RED        31
#define VT_F_GREEN      32
#define VT_F_YELLOW     33
#define VT_F_BLUE       34
#define VT_F_PURPLE     35
#define VT_F_CYAN       36
#define VT_F_WHITE      37

// Background Color
#define VT_B_BLACK      40
#define VT_B_RED        41
#define VT_B_GREEN      42
#define VT_B_YELLOW     43
#define VT_B_BLUE       44
#define VT_B_PURPLE     45
#define VT_B_CYAN       46
#define VT_B_WHITE      47

void vt_clear(void);
void vt_clear_attr(void);

void vt_hide_cursor(void);
void vt_show_cursor(void);

void vt_move_up(int step);
void vt_move_down(int step);
void vt_move_right(int step);
void vt_move_left(int step);
void vt_move_to(int row, int col);

void vt_set_font_color(int color);
void vt_set_bg_color(int color);

void vt_draw_char(char ch);
void vt_draw_char_at(int row, int col, char ch);
void vt_draw_str(char* ch);
void vt_draw_str_at(int row, int col, char* ch);

void vt_draw_hline(int row, int col, int len, char ch);
void vt_draw_vline(int row, int col, int len, char ch);

void vt_fill_box(int s_row, int s_col, int n_rows, int n_cols, char ch);
void vt_draw_box(int s_row, int s_col, int n_rows, int n_cols, char h_fill, char v_fill, char c_fill);

void vt_draw_bitmap(int s_row, int s_col, int n_rows, int n_cols, const rt_uint8_t* bitmap, char f_color, char b_color);

#endif // __VT100_H__
