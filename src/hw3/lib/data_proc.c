#include <stdio.h>
#include "../../libc/output_format.h"

void print_hello(void){
    output_format format;
    get_format(&format);
    printf("%sHello World!%s\n", format.foreground.red, format.style.reset);
}
