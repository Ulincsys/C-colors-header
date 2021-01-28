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
} Color = {
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

typedef struct __ANSI_COLOR_ESCAPE_CODE__ {
    char fg[20];
    char bg[20];
    char code[20];
} ColorCode;

int numColors = 9;
char *colors[] = { "black", "red", "green", "yellow", "blue", "magenta", "cyan", "white", "reset" };
char *br_colors[] = { "br_black", "br_red", "br_green", "br_yellow", "br_blue", "br_magenta", "br_cyan", "br_white", "reset" };

int findColorIndex(char *color) {
    for(int i = 0; i < numColors; ++i) {
        if(!strcmp(color, colors[i])) {
            return i;
        }
    }
    return -1;
}

int findBRColorIndex(char *color) {
    for(int i = 0; i < numColors; ++i) {
        if(!strcmp(color, br_colors[i])) {
            return i;
        }
    }
    return -1;
}

const char* getColorCode(char *color, int isFG) {
    int colorIndex;
    if((colorIndex = findColorIndex(color)) != -1) {
        if(isFG) {
            switch(colorIndex) {
                case 0:
                    return Color.fg.black;
                case 1:
                    return Color.fg.red;
                case 2:
                    return Color.fg.green;
                case 3:
                    return Color.fg.yellow;
                case 4:
                    return Color.fg.blue;
                case 5:
                    return Color.fg.magenta;
                case 6:
                    return Color.fg.cyan;
                case 7:
                    return Color.fg.white;
                case 8:
                    return Color.fg.reset;
            }
        } else {
            switch(colorIndex) {
                case 0:
                    return Color.bg.black;
                case 1:
                    return Color.bg.red;
                case 2:
                    return Color.bg.green;
                case 3:
                    return Color.bg.yellow;
                case 4:
                    return Color.bg.blue;
                case 5:
                    return Color.bg.magenta;
                case 6:
                    return Color.bg.cyan;
                case 7:
                    return Color.bg.white;
                case 8:
                    return Color.bg.reset;
            }
        }
    } else if((colorIndex = findBRColorIndex(color)) != -1) {
        if(isFG) {
            switch(colorIndex) {
                case 0:
                    return Color.fg.br_black;
                case 1:
                    return Color.fg.br_red;
                case 2:
                    return Color.fg.br_green;
                case 3:
                    return Color.fg.br_yellow;
                case 4:
                    return Color.fg.br_blue;
                case 5:
                    return Color.fg.br_magenta;
                case 6:
                    return Color.fg.br_cyan;
                case 7:
                    return Color.fg.br_white;
                case 8:
                    return Color.fg.reset;
            }
        } else {
            switch(colorIndex) {
                case 0:
                    return Color.bg.br_black;
                case 1:
                    return Color.bg.br_red;
                case 2:
                    return Color.bg.br_green;
                case 3:
                    return Color.bg.br_yellow;
                case 4:
                    return Color.bg.br_blue;
                case 5:
                    return Color.bg.br_magenta;
                case 6:
                    return Color.bg.br_cyan;
                case 7:
                    return Color.bg.br_white;
                case 8:
                    return Color.bg.reset;
            }
        }
    }
    return NULL;
}

ColorCode singleColor(char *color, int isFG) {
    const char *CC = getColorCode(color, isFG);
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

ColorCode BGColor(char *color) {
    return singleColor(color, 0);
}

ColorCode FGColor(char *color) {
    return singleColor(color, 1);
}

ColorCode Colors(char *foreground, char *background) {
    const char *fgcc = getColorCode(foreground, 1);
    const char *bgcc = getColorCode(background, 0);
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
        return BGColor(buffer + 1);
    } else {
        return FGColor(buffer);
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
        strncpy(buffer + index, Color.reset, strlen(Color.reset));
        index += strlen(Color.reset);
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
