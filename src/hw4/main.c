/**
 * @file main.c
 * @brief Basic demonstration for Supervised Learning Algorithm.
*/

#include <stdio.h>
#include "./lib/config_read.h"
#include "./lib/plot_iter.h"
#include "./lib/iter.h"
#include "../libc/signal_handler.h"

config_t config;
config_line_t config_lines[MAX_LINE_CNT];
iter_history_t iter_history;

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
    FILE* iter_file = iter_file_open(&config);
    add_line(gnuplot, &config, &config_lines);
    iter_history_init(&iter_history, &config, &config_lines);
    iter_history_print(&iter_history);
    plot_update(gnuplot, &config, &config_lines, &iter_history, iter_file);

    for (int i = 0; i < config.max_iter; i++){
        // iter_history_iterate1(&iter_history, &config, &config_lines);
        iter_history_iterate(&iter_history, &config, &config_lines);
        iter_history_print(&iter_history);
        iter_file_flush(iter_file, &iter_history, &config);
        plot_update(gnuplot, &config, &config_lines, &iter_history, iter_file);
    }

    // plot_update(gnuplot, &config, &config_lines, &iter_history, iter_file);

    fclose(iter_file);
    plot_close(gnuplot);
    return 0;
}
