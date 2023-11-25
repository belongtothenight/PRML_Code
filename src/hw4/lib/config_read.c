#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config_read.h"
#include "../../libc/output_format.h"

void config_read_status_print(int config_read_status, char *message){
    output_format format;
    get_format(&format);
    switch (config_read_status) {
        case CONFIG_READ_STATUS_SUCCESS:
            printf("%s%s\n", format.status.success, message);
            break;
        case CONFIG_READ_STATUS_FAILURE:
            printf("%sFailed to open file.: %s\n", message);
            break;
        default:
            printf("%sUnknown error.: %s\n", message);
            break;
    }
    return;
}

void config_init(config_t *config){
    config->initial_step = 0.1;
    config->dynamic_step = true;
    config->line_cnt = 2;
    config->initial_x = 0.0;
    config->initial_y = 0.0;
    config->max_iter = 1000;
    config->show_progress = true;
    config->debug_mode = false;
    memset(config->output_file, 0, sizeof(config->output_file)); // Clear buffer
    memset(config->iter_img, 0, sizeof(config->iter_img)); // Clear buffer
    memset(config->iter_point_tmp, 0, sizeof(config->iter_point_tmp)); // Clear buffer
    memset(config->iter_dt_tmp, 0, sizeof(config->iter_dt_tmp)); // Clear buffer
    memset(config->cost_img, 0, sizeof(config->cost_img)); // Clear buffer
    memset(config->cost_tmp, 0, sizeof(config->cost_tmp)); // Clear buffer
    memset(config->font, 0, sizeof(config->font)); // Clear buffer
    config->font_size = 20;
    config->plot_x_size = 1080;
    config->plot_y_size = 1080;
    memset(config->plot_filetype, 0, sizeof(config->plot_filetype)); // Clear buffer
    config->plot_x_min = -10;
    config->plot_x_max = 10;
    config->plot_y_min = -10;
    config->plot_y_max = 10;
    config->plot_iter = true;
    config->plot_iter_with_line = true;
    config->plot_iter_with_dotted_line = true;
    config->plot_cost = true;
    config->iter_dotted_line_range = 0.5;
    config->iter_dotted_line_step = 0.1;
    config->iter_dotted_line_num_per_x = 1;
    config->param_cnt = 0; // should set as 0
    return;
}

void config_line_init(config_line_t *config_line){
    memset(config_line->line_title, 0, sizeof(config_line->line_title)); // Clear buffer
    memset(config_line->line_symbol, 0, sizeof(config_line->line_symbol)); // Clear buffer
    config_line->line_param1 = 0.0;
    config_line->line_param2 = 0.0;
    config_line->line_param3 = 0.0;
    return;
}

void config_print(config_t *config){
    printf("initial_step: %lf\n", config->initial_step);
    if (config->dynamic_step == 1) printf("dynamic_step: true\n"); else if (config->dynamic_step == 0) printf("dynamic_step: false\n");
    printf("line_cnt: %d\n", config->line_cnt);
    printf("initial_x: %lf\n", config->initial_x);
    printf("initial_y: %lf\n", config->initial_y);
    printf("max_iter: %d\n", config->max_iter);
    if (config->show_progress == 1) printf("show_progress: true\n"); else if (config->show_progress == 0) printf("show_progress: false\n");
    if (config->debug_mode == 1) printf("debug_mode: true\n"); else if (config->debug_mode == 0) printf("debug_mode: false\n");
    printf("output_file: %s\n", config->output_file);
    printf("iter_img: %s\n", config->iter_img);
    printf("iter_point_tmp: %s\n", config->iter_point_tmp);
    printf("iter_dt_tmp: %s\n", config->iter_dt_tmp);
    printf("cost_img: %s\n", config->cost_img);
    printf("cost_tmp: %s\n", config->cost_tmp);
    printf("font: %s\n", config->font);
    printf("font_size: %d\n", config->font_size);
    printf("plot_x_size: %d\n", config->plot_x_size);
    printf("plot_y_size: %d\n", config->plot_y_size);
    printf("plot_filetype: %s\n", config->plot_filetype);
    printf("plot_x_min: %lf\n", config->plot_x_min);
    printf("plot_x_max: %lf\n", config->plot_x_max);
    printf("plot_y_min: %lf\n", config->plot_y_min);
    printf("plot_y_max: %lf\n", config->plot_y_max);
    if (config->plot_iter == 1) printf("plot_iter: true\n"); else if (config->plot_iter == 0) printf("plot_iter: false\n");
    if (config->plot_iter_with_line == 1) printf("plot_iter_with_line: true\n"); else if (config->plot_iter_with_line == 0) printf("plot_iter_with_line: false\n");
    if (config->plot_iter_with_dotted_line == 1) printf("plot_iter_with_dotted_line: true\n"); else if (config->plot_iter_with_dotted_line == 0) printf("plot_iter_with_dotted_line: false\n");
    if (config->plot_cost == 1) printf("plot_cost: true\n"); else if (config->plot_cost == 0) printf("plot_cost: false\n");
    printf("iter_dotted_line_range: %lf\n", config->iter_dotted_line_range);
    printf("iter_dotted_line_step: %lf\n", config->iter_dotted_line_step);
    printf("iter_dotted_line_num_per_x: %d\n", config->iter_dotted_line_num_per_x);
    return;
}

void config_line_print(config_line_t *config_line){
    printf("line_title: %s\n", config_line->line_title);
    printf("line_symbol: %s\n", config_line->line_symbol);
    printf("line_param1: %lf\n", config_line->line_param1);
    printf("line_param2: %lf\n", config_line->line_param2);
    printf("line_param3: %lf\n", config_line->line_param3);
}

void config_all_print(config_t *config, config_line_t (*config_lines)[]){
    printf("\nconfig settings:\n");
    config_print(config);
    for (int i = 0; i < config->line_cnt; i++) {
        config_line_print(&(*config_lines)[i]);
    }
    printf("\n");
    return;
}

int config_parse(char *buf, config_t *config){
    char dummy[CONFIG_LINE_MAX_SIZE];
    if (config->debug_mode == true) printf("config_parse buf: %s", buf);
    if (sscanf(buf, " %s", dummy) == EOF) return CONFIG_READ_STATUS_SUCCESS; // Empty line
    if (sscanf(buf, " %[#]", dummy) == 1) return CONFIG_READ_STATUS_SUCCESS; // Comment line
    if (sscanf(buf, " initial_step = %s", dummy) == 1) {
        config->initial_step = strtod(dummy, NULL);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " dynamic_step = %[TtRrUuEe]", dummy) == 1) {
        config->dynamic_step = true;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " dynamic_step = %[FfAaLlSsEe]", dummy) == 1) {
        config->dynamic_step = false;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " line_cnt = %s", dummy) == 1) {
        config->line_cnt = strtol(dummy, NULL, 10);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " initial_x = %s", dummy) == 1) {
        config->initial_x = strtod(dummy, NULL);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " initial_y = %s", dummy) == 1) {
        config->initial_y = strtod(dummy, NULL);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " max_iter = %s", dummy) == 1) {
        config->max_iter = strtol(dummy, NULL, 10);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " show_progress = %[TtRrUuEe]", dummy) == 1) {
        config->show_progress = true;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " show_progress = %[FfAaLlSsEe]", dummy) == 1) {
        config->show_progress = false;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " debug_mode = %[TtRrUuEe]", dummy) == 1) {
        config->debug_mode = true;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " debug_mode = %[FfAaLlSsEe]", dummy) == 1) {
        config->debug_mode = false;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " output_file = %s", config->output_file) == 1) {
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " iter_img = %s", config->iter_img) == 1) {
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " iter_point_tmp = %s", config->iter_point_tmp) == 1) {
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " iter_dt_tmp = %s", config->iter_dt_tmp) == 1) {
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " cost_img = %s", config->cost_img) == 1) {
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " cost_tmp = %s", config->cost_tmp) == 1) {
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " font = %s", config->font) == 1) {
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " font_size = %s", dummy) == 1) {
        config->font_size = strtol(dummy, NULL, 10);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_x_size = %s", dummy) == 1) {
        config->plot_x_size = strtol(dummy, NULL, 10);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_y_size = %s", dummy) == 1) {
        config->plot_y_size = strtol(dummy, NULL, 10);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_filetype = %s", config->plot_filetype) == 1) {
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_x_min = %s", dummy) == 1) {
        config->plot_x_min = strtod(dummy, NULL);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_x_max = %s", dummy) == 1) {
        config->plot_x_max = strtod(dummy, NULL);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_y_min = %s", dummy) == 1) {
        config->plot_y_min = strtod(dummy, NULL);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_y_max = %s", dummy) == 1) {
        config->plot_y_max = strtod(dummy, NULL);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_iter = %[TtRrUuEe]", dummy) == 1) {
        config->plot_iter = true;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_iter = %[FfAaLlSsEe]", dummy) == 1) {
        config->plot_iter = false;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_iter_with_line = %[TtRrUuEe]", dummy) == 1) {
        config->plot_iter_with_line = true;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_iter_with_line = %[FfAaLlSsEe]", dummy) == 1) {
        config->plot_iter_with_line = false;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_iter_with_dotted_line = %[TtRrUuEe]", dummy) == 1) {
        config->plot_iter_with_dotted_line = true;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_iter_with_dotted_line = %[FfAaLlSsEe]", dummy) == 1) {
        config->plot_iter_with_dotted_line = false;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_cost = %[TtRrUuEe]", dummy) == 1) {
        config->plot_cost = true;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " plot_cost = %[FfAaLlSsEe]", dummy) == 1) {
        config->plot_cost = false;
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " iter_dotted_line_range = %s", dummy) == 1) {
        config->iter_dotted_line_range = strtod(dummy, NULL);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " iter_dotted_line_step = %s", dummy) == 1) {
        config->iter_dotted_line_step = strtod(dummy, NULL);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " iter_dotted_line_num_per_x = %s", dummy) == 1) {
        config->iter_dotted_line_num_per_x = strtol(dummy, NULL, 10);
        config->param_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    return CONFIG_READ_STATUS_FAILURE; // Syntax error
}

int config_line_parse(char *buf, config_line_t *config_line, int *line_cnt, config_t *config){
    char dummy[CONFIG_LINE_MAX_SIZE];
    if (config->debug_mode == true) printf("config_line_parse buf: %s", buf);
    if (sscanf(buf, " %s", dummy) == EOF) return CONFIG_READ_STATUS_SUCCESS; // Empty line
    if (sscanf(buf, " %[#]", dummy) == 1) return CONFIG_READ_STATUS_SUCCESS; // Comment line
    if (sscanf(buf, " line_title = %s", config_line->line_title) == 1){
        *line_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " line_symbol = %s", config_line->line_symbol) == 1){
        *line_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " line_param1 = %s", dummy) == 1) {
        config_line->line_param1 = strtod(dummy, NULL);
        *line_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " line_param2 = %s", dummy) == 1) {
        config_line->line_param2 = strtod(dummy, NULL);
        *line_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " line_param3 = %s", dummy) == 1) {
        config_line->line_param3 = strtod(dummy, NULL);
        *line_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    
    return CONFIG_READ_STATUS_FAILURE; // Syntax error
}

int config_read(config_t *config, config_line_t (*config_lines)[], char *filename){
    // Open file
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        config_read_status_print(CONFIG_READ_STATUS_FAILURE, "");
        return CONFIG_READ_STATUS_FAILURE;
    } else {
        config_read_status_print(CONFIG_READ_STATUS_SUCCESS, "Opened config file successfully.");
    }
    // Initialize variables
    int current_line = 0;
    int line_index = 0;
    int line_param_cnt = 0;
    char buf[CONFIG_LINE_MAX_SIZE];
    memset(buf, 0, sizeof(buf)); // Clear buffer
    char msg[CONFIG_LINE_MAX_SIZE];
    memset(msg, 0, sizeof(msg)); // Clear buffer
    config_init(config);
    for (int i = 0; i < MAX_LINE_CNT; i++){
        config_line_init(&(*config_lines)[i]);
    }
    // Read file
    while (fgets(buf, sizeof(buf), fp)) {
        ++current_line;
        if (config->debug_mode == true) printf("Line %d: %s", current_line, buf);
        if (config->param_cnt < CONFIG_GLOBAL_SET_NUM) {
            // Read global settings
            int err = config_parse(buf, config);
            if (err) {
                sprintf(msg, "line %d: Buf: %s", current_line, buf);
                config_read_status_print(err, msg);
                memset(msg, 0, sizeof(msg)); // Clear buffer
            }
        } else {
            // Read line settings
            line_index = line_param_cnt / CONFIG_LINE_SET_NUM;
            int err = config_line_parse(buf, &(*config_lines)[line_index], &line_param_cnt, config);
            if (err) {
                sprintf(msg, "line %d: Buf: %s", current_line, buf);
                config_read_status_print(err, msg);
                memset(msg, 0, sizeof(msg)); // Clear buffer
            }
        }
        buf[strlen(buf)-1] = '\0'; // Remove '\n'
    }
    // Close file
    fclose(fp);
    printf("Finished reading config file.\n");
    return CONFIG_READ_STATUS_SUCCESS;
}
