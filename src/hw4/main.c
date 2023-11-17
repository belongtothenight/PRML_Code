/**
 * @file main.c
 * @brief Basic demonstration for Supervised Learning Algorithm.
*/

#include <stdio.h>
#include "./lib/config_read.h"
#include "./lib/plot_iter.h"
#include "../libc/signal_handler.h"

config_t config;
config_line_t config_lines[MAX_LINE_CNT];

/**
 * @brief main function
 * @retval 0
 */
int main (int argc, char *argv[]) {
    register_all_signal_handlers();
    if (argc != 2) {
        fprintf(stderr, "Usage: %s CONFIG_FILE\n", argv[0]);
        return 1;
    }
    config_read(&config, &config_lines, argv[1]);
    config_all_print(&config, &config_lines);
    FILE* gnuplot = plot_open(&config);
    add_line(gnuplot, &config_lines[0]);
    add_line(gnuplot, &config_lines[1]);
    plot_update(gnuplot, &config, &config_lines);
    // plot_close(gnuplot);
    return 0;
}
