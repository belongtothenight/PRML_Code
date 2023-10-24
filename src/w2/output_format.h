#ifndef OUTPUT_FORMAT_H
#define OUTPUT_FORMAT_H

// https://stackoverflow.com/questions/2048509/how-to-echo-with-different-colors-in-the-windows-command-line
typedef struct{
    struct Styles{
        char *reset;
        char *bold;
        char *underline;
        char *inverse;
    } style;
    struct Foreground{
        char *black;
        char *red;
        char *green;
        char *yellow;
        char *blue;
        char *magenta;
        char *cyan;
        char *white;
    } foreground;
    struct Background{
        char *black;
        char *red;
        char *green;
        char *yellow;
        char *blue;
        char *magenta;
        char *cyan;
        char *white;
    } background;
    struct Strong_Foreground{
        char *black;
        char *red;
        char *green;
        char *yellow;
        char *blue;
        char *magenta;
        char *cyan;
        char *white;
    } strong_foreground;
    struct Strong_Background{
        char *black;
        char *red;
        char *green;
        char *yellow;
        char *blue;
        char *magenta;
        char *cyan;
        char *white;
    } strong_background;
} output_format;

void get_format(output_format* pFormat);

#endif
