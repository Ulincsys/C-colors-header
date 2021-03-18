#include <string.h>
#include <stdarg.h>

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

const int __COLOR_COUNT__ = 9;
const char *__COLOR_HR_FG__[] = { "black", "red", "green", "yellow", "blue", "magenta", "cyan", "white", "reset" };
const char *__COLOR_HR_BG__[] = { "br_black", "br_red", "br_green", "br_yellow", "br_blue", "br_magenta", "br_cyan", "br_white", "reset" };

typedef struct {
    char fg[20];
    char bg[20];
    char code[20];
} ColorCode;

// const int numColors = 9;
// char *colors[] = ;
// char *br_colors[] = ;

int __FIND_COLOR_INDEX__(char *color) {
    for(int i = 0; i < __COLOR_COUNT__; ++i) {
        if(!strcmp(color, __COLOR_HR_FG__[i])) {
            return i;
        }
    }
    return -1;
}

int __FIND_BACKGROUND_COLOR_INDEX__(char *color) {
    for(int i = 0; i < __COLOR_COUNT__; ++i) {
        if(!strcmp(color, __COLOR_HR_BG__[i])) {
            return i;
        }
    }
    return -1;
}

const char* __GET_CONST_COLOR_CODE__(char *color, int isFG) {
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
    } else if((colorIndex = __FIND_BACKGROUND_COLOR_INDEX__(color)) != -1) {
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

ColorCode singleColorCode(char *color, int isFG) {
    const char *CC = __GET_CONST_COLOR_CODE__(color, isFG);
    if(!CC) {
        return (ColorCode){ "\0", "\0", "\0" };
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

ColorCode toBackgroundColorCode(char *color) {
    return singleColorCode(color, 0);
}

ColorCode toForegroundColorCode(char *color) {
    return singleColorCode(color, 1);
}

ColorCode toColorCodes(char *foreground, char *background) {
    const char *fgcc = __GET_CONST_COLOR_CODE__(foreground, 1);
    const char *bgcc = __GET_CONST_COLOR_CODE__(background, 0);
    if(!fgcc || !bgcc) {
        return (ColorCode){ "\0", "\0", "\0" };
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

// Capture groups look like "&(Color)&" for foreground and "&(_color)&" for background
int countColorCodes(const char *format) {
    int count = 0;
    for(int i = 0; *format != '\0'; ++i) {
        if(*format == '&' && *(format + 1) == '(') {
            while(*format != '\0') {
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

int nextColorCodeStart(const char *format, int start) {
    format += start;
    for(int i = start; *format != '\0'; ++i) {
        if(*format == '&' && *(format + 1) == '(') {
            while(*format != '\0') {
                if(*format == ')' && *(format + 1) == '&') { // makes sure that the capture group actually ends
                    return i;
                } else {
                    ++format;
                }
            }
        } else {
            ++format;
        }
    }
    return -1;
}

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

ColorCode getColorFromCapture(const char *cursor) {
    cursor += 2;
    int i = nextColorCodeEnd(cursor, 0);
    char buffer[i];
    strncpy(buffer, cursor, i - 1);
    buffer[i - 1] = '\0';
    if(*buffer == '_') {
        return toBackgroundColorCode(buffer + 1);
    } else {
        return toForegroundColorCode(buffer);
    }
}

int cvfprintf(FILE *stream, const char *format, va_list args) {
    int s = nextColorCodeStart(format, 0);
    if(s != -1) {
        const char *cursor = format;
        int index = 0;
        char buffer[strlen(format) + 10]; // All the color codes are shorter than their captures
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

int cfprintf(FILE *stream, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int i = cvfprintf(stream, format, args);
    va_end(args);
    return i;
}

int cprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int i = cvfprintf(stdout, format, args);
    va_end(args);
    return i;
}
