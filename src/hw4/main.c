/**
 * @file main.c
 * @brief Basic demonstration for Supervised Learning Algorithm.
*/

#include <stdio.h>
#include "./lib/config_read.h"

config_t config;
config_line_t config_line1[MAX_LINE_CNT];

/**
 * @brief main function
 * @retval 0
 */
int main (void) {
    // config_init(&config, 10, 10, 10);
    // config_line_init(&config_line1, 10, 10, 10);
    // config_print(&config);
    // config_line_print(&config_line1);
    config_read(&config, &config_line1, "./config.ini");
    return 0;
}
