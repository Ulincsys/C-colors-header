#include <string.h>
#include <stdarg.h>

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
} Color_t = {
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

/*  Immutable definitions for simplifying the transport of color information
    between library functions.
*/

const int __COLOR_COUNT__ = 9;
const char *__COLOR_HR_RG__[] = { "black", "red", "green", "yellow", "blue", "magenta", "cyan", "white", "reset" };
const char *__COLOR_HR_BR__[] = { "br_black", "br_red", "br_green", "br_yellow", "br_blue", "br_magenta", "br_cyan", "br_white", "reset" };

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

/*  Returns the index of the given color in the global color index array. Will
    return -1 if the color name is invalid
*/

int __FIND_COLOR_INDEX__(const char *color) {
    for(int i = 0; i < __COLOR_COUNT__; ++i) {
        if(!strcmp(color, __COLOR_HR_RG__[i])) {
            return i;
        }
    }
    return -1;
}

/*  Returns the index of the given bright color in the global color index array.
    Will return -1 if the color name is invalid
*/

int __FIND_BRIGHT_COLOR_INDEX__(const char *color) {
    for(int i = 0; i < __COLOR_COUNT__; ++i) {
        if(!strcmp(color, __COLOR_HR_BR__[i])) {
            return i;
        }
    }
    return -1;
}

/*  Probably would be just as well done with a static array, but I was really
    tied to the idea of using a struct for everything and I like how it turned
    out.
*/

const char* __GET_CONST_COLOR_CODE__(const char *color, int isFG) {
    int colorIndex;
    if((colorIndex = __FIND_COLOR_INDEX__(color)) != -1) {
        if(isFG) {
            switch(colorIndex) {
                case 0:
                    return Color_t.fg.black;
                case 1:
                    return Color_t.fg.red;
                case 2:
                    return Color_t.fg.green;
                case 3:
                    return Color_t.fg.yellow;
                case 4:
                    return Color_t.fg.blue;
                case 5:
                    return Color_t.fg.magenta;
                case 6:
                    return Color_t.fg.cyan;
                case 7:
                    return Color_t.fg.white;
                case 8:
                    return Color_t.fg.reset;
            }
        } else {
            switch(colorIndex) {
                case 0:
                    return Color_t.bg.black;
                case 1:
                    return Color_t.bg.red;
                case 2:
                    return Color_t.bg.green;
                case 3:
                    return Color_t.bg.yellow;
                case 4:
                    return Color_t.bg.blue;
                case 5:
                    return Color_t.bg.magenta;
                case 6:
                    return Color_t.bg.cyan;
                case 7:
                    return Color_t.bg.white;
                case 8:
                    return Color_t.bg.reset;
            }
        }
    } else if((colorIndex = __FIND_BRIGHT_COLOR_INDEX__(color)) != -1) {
        if(isFG) {
            switch(colorIndex) {
                case 0:
                    return Color_t.fg.br_black;
                case 1:
                    return Color_t.fg.br_red;
                case 2:
                    return Color_t.fg.br_green;
                case 3:
                    return Color_t.fg.br_yellow;
                case 4:
                    return Color_t.fg.br_blue;
                case 5:
                    return Color_t.fg.br_magenta;
                case 6:
                    return Color_t.fg.br_cyan;
                case 7:
                    return Color_t.fg.br_white;
                case 8:
                    return Color_t.fg.reset;
            }
        } else {
            switch(colorIndex) {
                case 0:
                    return Color_t.bg.br_black;
                case 1:
                    return Color_t.bg.br_red;
                case 2:
                    return Color_t.bg.br_green;
                case 3:
                    return Color_t.bg.br_yellow;
                case 4:
                    return Color_t.bg.br_blue;
                case 5:
                    return Color_t.bg.br_magenta;
                case 6:
                    return Color_t.bg.br_cyan;
                case 7:
                    return Color_t.bg.br_white;
                case 8:
                    return Color_t.bg.reset;
            }
        }
    }
    return NULL;
}

/*  Composes and returns a ColorCode struct with either a foreground or
    background color code defined, as specified by the "isFG" parameter, or
    NOCOLOR if it does not exist.
*/

ColorCode parseColorCode(const char *color, int isFG) {
    const char *CC = __GET_CONST_COLOR_CODE__(color, isFG);
    if(!CC) {
        return NOCOLOR;
    }
    ColorCode cc;
    char *template = "\x1b[";
    int CCSize = strlen(CC), templateSize = strlen(template);
    if(isFG) {
        strncpy(cc.fg, color, 20);
        strncpy(cc.bg, "\0", 20);
    } else {
        strncpy(cc.bg, color, 20);
        strncpy(cc.fg, "\0", 20);
    }
    char *buffer = cc.code;
    int index = templateSize;
    strncpy(buffer, template, templateSize);
    strncpy(buffer + index, CC, CCSize);
    index += CCSize;
    buffer[index++] = 'm';
    buffer[index] = '\0';
    return cc;
}

/*  Composes and returns a ColorCode struct with a background color defined, or
    NOCOLOR if it does not exist.
*/

ColorCode parseBackgroundColorCode(const char *color) {
    return parseColorCode(color, 0);
}

/*  Composes and returns a ColorCode struct with a foreground color defined, or
    NOCOLOR if it does not exist.
*/

ColorCode parseForegroundColorCode(const char *color) {
    return parseColorCode(color, 1);
}

/*  Composes and returns a ColorCode struct with both a foreground and
    background color code defined, or NOCOLOR if either does not exist.
*/

ColorCode parseColorCodes(const char *foreground, const char *background) {
    const char *fgcc = __GET_CONST_COLOR_CODE__(foreground, 1);
    const char *bgcc = __GET_CONST_COLOR_CODE__(background, 0);
    if(!fgcc || !bgcc) {
        return NOCOLOR;
    }
    ColorCode cc;
    char *template = "\x1b[";
    int fgccSize = strlen(fgcc), bgccSize = strlen(bgcc),
        templateSize = strlen(template);
    strncpy(cc.fg, foreground, 20);
    strncpy(cc.bg, background, 20);
    char *buffer = cc.code;
    int index = templateSize;
    strncpy(buffer, template, templateSize);
    strncpy(buffer + index, fgcc, fgccSize);
    index += fgccSize;
    buffer[index++] = ';';
    strncpy(buffer + index, bgcc, bgccSize);
    index += bgccSize;
    buffer[index++] = 'm';
    buffer[index] = '\0';
    return cc;
}

/*  Counts the number of color code capture groups contained within a character
    String. Capture groupd begin with a "&(" and end with a ")&", and capture
    groups may not contain other capture groups. Everything within a capture
    group is considered to be a color code. Will parse until a null terminator
    is encountered.
*/

int countColorCodes(const char *format) {
    int count = 0;
    for(int i = 0; *format != '\0'; ++i) {
        // The beginning of a capture group has been found
        if(*format == '&' && *(format + 1) == '(') {
            while(*format != '\0') {
                // The end of the capture group has been found
                if(*format == ')' && *(format + 1) == '&') {
                    ++count;
                    break;
                } else {
                    ++format;
                }
            }
        } else {
            ++format;
        }
    }
    return count;
}

/*  Returns the end index of the next capture group in the given String,
    starting from the start index given.
*/

int nextColorCodeEnd(const char *format, int start) {
    format += start;
    for(int i = start; *format != '\0'; ++i) {
        if(*format == ')' && *(format + 1) == '&') {
            return ++i;
        } else {
            ++format;
        }
    }
    return -1;
}

/*  Returns the start index of the next capture group in the given String,
    starting from the start index given.
*/

int nextColorCodeStart(const char *format, int start) {
    format += start;
    for(int i = start; *format != '\0'; ++i) {
        if(*format == '&' && *(format + 1) == '(') {
            // while(*format != '\0') {
            //     if(*format == ')' && *(format + 1) == '&') {
            //         return i;
            //     } else {
            //         ++format;
            //     }
            // }
            if(nextColorCodeEnd(format, 0) != -1) {
                return i;
                // makes sure that the capture group actually ends
            } else {
                ++format;
            }
        } else {
            ++format;
        }
    }
    return -1;
}

/*  Parse and return the color of the next capture group in the String. Does not
    advance the character pointer or manipulate the String.
*/

ColorCode getColorFromCapture(const char *cursor) {
    cursor += 2;
    int i = nextColorCodeEnd(cursor, 0);
    char buffer[i];
    strncpy(buffer, cursor, i - 1);
    buffer[i - 1] = '\0';
    if(*buffer == '_') {
        return parseBackgroundColorCode(buffer + 1);
    } else {
        return parseForegroundColorCode(buffer);
    }
}

/*  Variadic color fprintf function with color parsing. Accepts a String with 0
    or more embedded color capture groups, and a variadic argument list. Expects
    the VA list to have been initialized with va_start, and will *not* close the
    list upon completion.
*/

int cvfprintf(FILE *stream, const char *format, va_list args) {
    int s = nextColorCodeStart(format, 0);
    if(s != -1) {
        const char *cursor = format;
        int index = 0;
        // All the color codes are shorter than their captures
        char buffer[strlen(format) + 10];
        // making room for the reset at the end
        while(s != -1) {
            if(s) {
                strncpy(buffer + index, cursor, s);
                index += s;
                cursor += s;
            }
            ColorCode c = getColorFromCapture(cursor);
            strncpy(buffer + index, c.code, strlen(c.code));
            cursor += nextColorCodeEnd(cursor, 0) + 1;
            s = nextColorCodeStart(cursor, 0);
            index += strlen(c.code);
        }
        int remaining = strlen(cursor);
        if(remaining) {
            strncpy(buffer + index, cursor, remaining);
            index += remaining;
        }
        strncpy(buffer + index, Color_t.reset, strlen(Color_t.reset));
        index += strlen(Color_t.reset);
        buffer[index] = '\0';
        return vfprintf(stream, buffer, args);
    }
    return vfprintf(stream, format, args);
}

/*  Color fprintf function with color parsing. Accepts variable arguments.
*/

int cfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int i = cvfprintf(stream, format, args);
    va_end(args);
    return i;
}

/*  Color printf function with color parsing. Accepts variable arguments.
*/

int cprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int i = cvfprintf(stdout, format, args);
    va_end(args);
    return i;
}
