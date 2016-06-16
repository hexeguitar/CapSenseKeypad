/*
 * mk_term.h
 *
 *  Created on: 06-04-2013
 *      Author: Miros³aw Kardaœ
 */

#ifndef MK_TERM_H_
#define MK_TERM_H_

    #include <project.h>

// char attributes
#define MKTERM_RESET		0
#define MKTERM_BOLD 		1
#define MKTERM_DIM			2
#define MKTERM_UNDERLINE 	3
#define MKTERM_BLINK		4
#define MKTERM_REVERSE		7
#define MKTERM_HIDDEN		8

// font & background colors
#define MKTERM_BLACK 		0
#define MKTERM_RED			1
#define MKTERM_GREEN		2
#define MKTERM_YELLOW		3
#define MKTERM_BLUE		    4
#define MKTERM_MAGENTA		5
#define MKTERM_CYAN		    6
#define	MKTERM_WHITE	    7


void tr_cls(uint8_t cur_onoff);						// clear screen, cursor on/off
void tr_cursor_hide(uint8_t hide);				    // show cursor on/off
void tr_locate(uint8_t y, uint8_t x);				// set coordinates
void tr_pen_color(uint8_t cl);					    // font color
void tr_brush_color(uint8_t cl);			        // background color
void tr_attr(uint8_t atr, uint8_t fg, uint8_t bg);  // set attributes: char attr., font color, background color

void tr_fill_line(char ascii, uint8_t cnt);			// display a line cnt long using ascii char
void uart_putlong(uint32_t value, uint8_t radix);
char *ltoa(long N, char *str, int base);

#endif /* MK_TERM_H_ */
