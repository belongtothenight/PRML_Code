#include <stdio.h>
#include <stdlib.h>
#include "output_format.h"

void get_format(output_format* pFormat){
    pFormat->style.reset = "\033[0m";
    pFormat->style.bold = "\033[1m";
    pFormat->style.underline = "\033[4m";
    pFormat->style.inverse = "\033[7m";
    pFormat->foreground.black = "\033[30m";
    pFormat->foreground.red = "\033[31m";
    pFormat->foreground.green = "\033[32m";
    pFormat->foreground.yellow = "\033[33m";
    pFormat->foreground.blue = "\033[34m";
    pFormat->foreground.magenta = "\033[35m";
    pFormat->foreground.cyan = "\033[36m";
    pFormat->foreground.white = "\033[37m";
    pFormat->background.black = "\033[40m";
    pFormat->background.red = "\033[41m";
    pFormat->background.green = "\033[42m";
    pFormat->background.yellow = "\033[43m";
    pFormat->background.blue = "\033[44m";
    pFormat->background.magenta = "\033[45m";
    pFormat->background.cyan = "\033[46m";
    pFormat->background.white = "\033[47m";
    pFormat->strong_foreground.black = "\033[90m";
    pFormat->strong_foreground.red = "\033[91m";
    pFormat->strong_foreground.green = "\033[92m";
    pFormat->strong_foreground.yellow = "\033[93m";
    pFormat->strong_foreground.blue = "\033[94m";
    pFormat->strong_foreground.magenta = "\033[95m";
    pFormat->strong_foreground.cyan = "\033[96m";
    pFormat->strong_foreground.white = "\033[97m";
    pFormat->strong_background.black = "\033[100m";
    pFormat->strong_background.red = "\033[101m";
    pFormat->strong_background.green = "\033[102m";
    pFormat->strong_background.yellow = "\033[103m";
    pFormat->strong_background.blue = "\033[104m";
    pFormat->strong_background.magenta = "\033[105m";
    pFormat->strong_background.cyan = "\033[106m";
    pFormat->strong_background.white = "\033[107m";
    return;
}
