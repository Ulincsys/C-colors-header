#include <stdio.h>
#include "colors.h"

int main() {
    // printf("%sTest%s\n", Colors("red", "yellow").code, Color.reset);
    // printf("%sTest%s\n", Colors("blue", "white").code, Color.reset);
    // printf("%sTest%s\n", Colors("red", "black").code, Color.reset);
    // printf("%sTest%s\n", Colors("red", "br_white").code, Color.reset);
    // printf("%sTest%s\n", Colors("yellow", "black").code, Color.reset);
    // printf("%sTest%s\n", Colors("black", "br_red").code, Color.reset);
    // printf("%sTest%s\n", Colors("green", "black").code, Color.reset);

    // printf("%d\n", countColorCodes("&(blue)&Testing this code for &(red)& accurracy"));
    // printf("%sTesting Br_Blue FG%s\n", FGColor("br_blue").code, Color.reset);
    // printf("%sTesting Br_Blue BG%s\n", BGColor("br_blue").code, Color.reset);
    // printf("Sizeof(red): %zu vs Sizeof(&(red)&): %zu\n", sizeof("\x1b[31m"), sizeof("&(red)&"));

    char *str = "&(blue)&Testing this code for &(red)& accurracy";
    int i = nextColorCodeStart(str, 0);
    int j = nextColorCodeEnd(str, i);
    printf("First capture group: %d, %d\n", i, j);
    i = nextColorCodeStart(str, j);
    j = nextColorCodeEnd(str, i);
    printf("Second capture group: %d, %d\n", i, j);
    cprintf("This &(_br_white)&&(blue)&is&(reset)& a&(_reset)& %d test of the &(green)&cprintf()&(reset)& &(_black)&function\n", 359);
}
