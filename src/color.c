/*
 * color.c - Custom xterm 256-color support for CircleMUD
 *
 * Provides functions to parse |N and |number color tags and output ANSI xterm 256-color codes.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Converts |number to ANSI xterm 256-color code
// Example: |201 -> \033[38;5;201m
//          |n   -> \033[0m
void parse_xterm_tags(const char *input, char *output) {
    const char *src = input;
    char *dst = output;
    while (*src) {
        if (src[0] == '|' && isdigit(src[1])) {
            // Parse color number
            int num = 0, len = 1;
            num = src[1] - '0';
            if (isdigit(src[2])) { num = num * 10 + (src[2] - '0'); len++; }
            if (isdigit(src[2+1])) { num = num * 10 + (src[2+1] - '0'); len++; }
            dst += sprintf(dst, "\033[38;5;%dm", num);
            src += 1 + len;
        } else if (src[0] == '|' && src[1] == 'n') {
            dst += sprintf(dst, "\033[0m");
            src += 2;
        } else {
            *dst++ = *src++;
        }
    }
    *dst = '\0';
}

// Example usage:
// char buf[8192];
// parse_xterm_tags(greetings, buf);
// write_to_output(d, "%s", buf);
