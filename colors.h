#include <string.h>
#include <stdarg.h>

#ifndef NOCOLOR

// Container for foreground color code aliases
struct __ANSI_COLOR_ESCAPE_TYPES_STRUCT_FOREGROUND__ {
    const char *black;
    const char *red;
    const char *green;
    const char *yellow;
    const char *blue;
    const char *magenta;
    const char *cyan;
    const char *white;
    const char *br_black;
    const char *br_red;
    const char *br_green;
    const char *br_yellow;
    const char *br_blue;
    const char *br_magenta;
    const char *br_cyan;
    const char *br_white;
    const char *reset;
};

// Container for background color code aliases
struct __ANSI_COLOR_ESCAPE_TYPES_STRUCT_BACKGROUND__ {
    const char *black;
    const char *red;
    const char *green;
    const char *yellow;
    const char *blue;
    const char *magenta;
    const char *cyan;
    const char *white;
    const char *br_black;
    const char *br_red;
    const char *br_green;
    const char *br_yellow;
    const char *br_blue;
    const char *br_magenta;
    const char *br_cyan;
    const char *br_white;
    const char *reset;
};

/*  Color escape sequences are contained in the Color_t struct, aliased by their
    name via a struct member. ANSI color codes are escaped with "\x1b[", but for
    simplicity only the integer portion of the code is contained here for colors
    (as String literals).

    https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
*/

struct __ANSI_COLOR_ESCAPE_TYPES_STRUCT__ {
    struct __ANSI_COLOR_ESCAPE_TYPES_STRUCT_FOREGROUND__ fg;
    struct __ANSI_COLOR_ESCAPE_TYPES_STRUCT_BACKGROUND__ bg;
    const char *reset;
} static Color_t = {
    {
        "30",
        "31",
        "32",
        "33",
        "34",
        "35",
        "36",
        "37",
        "90",
        "91",
        "92",
        "93",
        "94",
        "95",
        "96",
        "97",
        "39"
    },
    {
        "40",
        "41",
        "42",
        "43",
        "44",
        "45",
        "46",
        "47",
        "100",
        "101",
        "102",
        "103",
        "104",
        "105",
        "106",
        "107",
        "49"
    },
    "\x1b[0m" // resets BG and FG
};

#define ANSI_COLOR_COUNT 9

/*  Mutable struct type to transport color codes as objects. Struct members "fg"
    and "bg" are String representations of the respective colors defined by the
    color code held in the code member.
*/

typedef struct {
    char fg[20];
    char bg[20];
    char code[20];
} ColorCode;

#define NOCOLOR (ColorCode){ "\0", "\0", "\0" }

int __FIND_COLOR_INDEX__(const char *color);

int __FIND_BRIGHT_COLOR_INDEX__(const char *color);

const char* __GET_CONST_COLOR_CODE__(const char *color, int isFG);

ColorCode parseColorCode(const char *color, int isFG);

ColorCode parseBackgroundColorCode(const char *color);

ColorCode parseForegroundColorCode(const char *color);

ColorCode parseColorCodes(const char *foreground, const char *background);

int countColorCodes(const char *format);

int nextColorCodeEnd(const char *format, int start);

int nextColorCodeStart(const char *format, int start);

ColorCode getColorFromCapture(const char *cursor);

int cvfprintf(FILE *stream, const char *format, va_list args);

int cfprintf(FILE *stream, const char *format, ...);

int cprintf(const char *format, ...);

#endif
