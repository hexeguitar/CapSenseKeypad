/*
 * mk_term.c
 *
 *  Created on: 06-04-2013
 *      Author: Miros³aw Kardaœ
 *
 *
 *  ported to PSoc4 by Piotr Zapart /06.2016
 */

#include <stdlib.h>
#include "mk_term.h"

#define BUFSIZE (sizeof(long) * 8 + 1)
const char UCLS[]  = { "\x1b""[2J" };

const char UHOME[]  = { "\x1b""[;H" };

const char UCUR_HIDE[]  = { "\x1b""[?25l" };
const char UCUR_SHOW[]  = { "\x1b""[?25h" };

const char U_ATTR_OFF[]  = { "\x1b""[m" };


//##############################################################################
void tr_cursor_hide( uint8_t hide ) {
	   
    if(hide)    UART_UartPutString(UCUR_HIDE);
	else        UART_UartPutString(UCUR_SHOW);
}
//##############################################################################
void tr_cls(uint8_t cur_onoff) {

    UART_UartPutString(U_ATTR_OFF);
	tr_cursor_hide(cur_onoff);
    UART_UartPutString(UCLS);
	tr_attr(0,7,0);
    UART_UartPutString(UHOME);
}
//##############################################################################
void tr_fill_line( char ascii, uint8_t cnt ) {
    uint8_t i;
	for(i=0; i<cnt; i++) UART_UartPutChar(ascii);
}
//##############################################################################
void tr_attr( uint8_t atr, uint8_t fg, uint8_t bg ) {
	UART_UartPutChar( 0x1b );
	UART_UartPutChar( '[' );
	UART_UartPutChar( atr+'0' );
	UART_UartPutChar( ';' );
	UART_UartPutChar( '3' );
	UART_UartPutChar( fg+'0' );
	UART_UartPutChar( ';' );
	UART_UartPutChar( '4' );
	UART_UartPutChar( bg+'0' );
	UART_UartPutChar( 'm' );
}
//##############################################################################
void tr_pen_color( uint8_t cl ) {
	UART_UartPutChar( 0x1b );
	UART_UartPutChar( '[' );
	UART_UartPutChar( '3' );
	UART_UartPutChar( cl+'0' );
	UART_UartPutChar( 'm' );
}
//##############################################################################
void tr_brush_color( uint8_t cl ) {
	UART_UartPutChar( 0x1b );
	UART_UartPutChar( '[' );
	UART_UartPutChar( '4' );
	UART_UartPutChar( cl+'0' );
	UART_UartPutChar( 'm' );
}
//##############################################################################
void tr_locate( uint8_t y, uint8_t x ) {

	UART_UartPutChar( 0x1b );
	UART_UartPutChar( '[' );
	uart_putlong( y, 10 );
	UART_UartPutChar( ';' );
	uart_putlong( x, 10 );
	UART_UartPutChar( 'H' );
}
//##############################################################################
void uart_putlong( uint32_t value, uint8_t base ) {
	char buf[17];
    
	ltoa( value, buf, base );
	UART_UartPutString( buf );
}
//##############################################################################

char *ltoa(long N, char *str, int base)
{
      register int i = 2;
      long uarg;
      char *tail, *head = str, buf[BUFSIZE];

      if (36 < base || 2 > base)
            base = 10;                    /* can only use 0-9, A-Z        */
      tail = &buf[BUFSIZE - 1];           /* last character position      */
      *tail-- = '\0';

      if (10 == base && N < 0L)
      {
            *head++ = '-';
            uarg    = -N;
      }
      else  uarg = N;

      if (uarg)
      {
            for (i = 1; uarg; ++i)
            {
                  register ldiv_t r;

                  r       = ldiv(uarg, base);
                  *tail-- = (char)(r.rem + ((9L < r.rem) ?
                                  ('A' - 10L) : '0'));
                  uarg    = r.quot;
            }
      }
      else  *tail-- = '0';

      memcpy(head, ++tail, i);
      return str;
}