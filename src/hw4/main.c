/**
 * @file main.c
 * @brief Basic demonstration for Supervised Learning Algorithm.
*/

#include <stdio.h>
#include "./lib/config_read.h"
#include "./lib/plot_iter.h"
#include "./lib/iter.h"
#include "./lib/plot_cost.h"
#include "../libc/signal_handler.h"

config_t config;
config_line_t config_lines[MAX_LINE_CNT];
iter_history_t iter_history;
dotted_line_cord_t dotted_line_cord;

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
    FILE* iter_gnuplot = iter_plot_open(&config);
    FILE* iter_point_file = iter_file_open(&config, 1);
    FILE* iter_dt_file = iter_file_open(&config, 2);
    FILE* cost_gnuplot = cost_plot_open(&config);
    FILE* cost_file = cost_file_open(&config);
    if (config.plot_iter_with_line) {
        add_line(iter_gnuplot, &config, &config_lines);
    }
    if (config.plot_iter_with_dotted_line) {
        dotted_line_cord_generate(&config, &config_lines, &dotted_line_cord, iter_dt_file);
    }
    iter_history_init(&iter_history, &config, &config_lines);

    printf("\nStart Iteration\n");
    iter_history_print(&iter_history);

    for (int i = 0; i < config.max_iter; i++){
        iter_history_iterate(&iter_history, &config, &config_lines);
        iter_history_print(&iter_history);
        if (config.plot_iter) {
            iter_file_flush(iter_point_file, &iter_history, &config);
        }
        if (config.plot_cost) {
            cost_file_flush(cost_file, &iter_history, &config);
        }
        if (config.show_progress) {
            iter_plot_update(iter_gnuplot, &config, &config_lines, &iter_history, iter_point_file, iter_dt_file);
            cost_plot_update(cost_gnuplot, &config, &iter_history, cost_file);
        }
    }

    if (iter_history.iter_min_set) {
        printf("iteration enters plot view at cnt %d\n", iter_history.iter_min);
    } else {
        printf("iteration never enters plot view\n");
    }

    if (config.plot_iter) {
        iter_plot_reset(iter_gnuplot, &config);
        iter_plot_update(iter_gnuplot, &config, &config_lines, &iter_history, iter_point_file, iter_dt_file);
    }
    if (config.plot_cost) {
        cost_plot_reset(cost_gnuplot, &config, &iter_history);
        cost_plot_update(cost_gnuplot, &config, &iter_history, cost_file);
    }

    fclose(iter_point_file);
    fclose(iter_dt_file);
    iter_plot_close(iter_gnuplot);
    fclose(cost_file);
    cost_plot_close(cost_gnuplot);
    return 0;
}
