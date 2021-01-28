# ANSI C terminal colors library
This library attempts to provide a single include header solution to easily printing in color at the terminal using C. This project is a personal proof-of-concept that I developed out of my own curiosity, and it has not been rigorously tested.

TODO; This documentation is incomplete

## Usage
This header provides an implementation for the set of [4-bit ANSI color escape codes](https://en.wikipedia.org/wiki/ANSI_escape_code#Colors), in the form of a struct (Color) containing `const char *` representations of all of the codes required for constructing Background ; Foreground color pairs. 

There are several main functions included in the header.
* `int cprintf(const char *format, ...);`
	* A wrapper for `cvfprintf()` which passes `stdout` along with the provided `va_list` and format string to `cvfprintf()`
	* The equivalent of `printf()`, but with color!
* `ColorCode Colors(char *foreground, char *background);`
	* This function constructs a foreground;background color code pair representing the two colors (or instructions) provided. For instance, a call of `Colors("red", "reset");` will return a ColorCode struct with the values:
```
ColorCode {
	fg = "red";
	bg = "reset";
	code = "\x1b[31;49m";
}
```

* `ColorCode singleColor(char *color, int isFG);`
	* this function accepts a string representation of a color or instruction, as well as a boolean `isFG` which indicates to the function whether to pick from the foreground or background palette. The return is a ColorCode struct containing only the selected color code (leaving the other member occupied by an empty string).

All functions which return a ColorCode struct will return the following value if the color could not be found:
```
return (ColorCode){ "\0", "\0", "\0" };
```