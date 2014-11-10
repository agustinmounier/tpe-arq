#ifndef _keyboard_handler_
#define _keyboard_handler_

#define READ_PORT	(0x60)

#define INVALID         -1

#define ENTER			(0x1C)
#define BACKSPACE		(0x0E)
#define SPACE			(0x39)

#define NUMBER			0
#define ROW1			1
#define ROW2			2
#define ROW3			3

#define	NUMBER_INIT	(0x02)
#define	NUMBER_END	(0x0C)

#define ROW1_INIT	(0x10)
#define ROW1_END		(0x1B)

#define ROW2_INIT	(0x1E)
#define ROW2_END		(0x26)

#define ROW3_INIT	(0x2C)
#define ROW3_END		(0x35)

#define ASCII_BACKSPACE				8
#define ASCII_ENTER				10

#define BIT(x)			(1 << ((x)-1))
#define RELEASED		BIT(8)
#define IS_RELEASED(x)		((x) & RELEASED)
#define IS_PRESSED(x)		(!(IS_RELEASED(x)))

void keyboard_hand();
static char scancode_to_char(unsigned int scancode);
static int classify(unsigned int scancode);

#endif
