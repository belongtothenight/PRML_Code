#include <stdio.h>
#include "../libc/output_format.h"
#include "./lib/data_proc.h"

int main(void){
    print_hello();
    output_format format;
    get_format(&format);
    printf("%sHello World!%s\n", format.foreground.red, format.style.reset);
    print_hello1();
    printf("Hello World!\n");
    return 0;
}
