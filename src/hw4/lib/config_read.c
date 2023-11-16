#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config_read.h"
#include "../../libc/output_format.h"

void config_read_status_print(int config_read_status, char *message){
    output_format format;
    get_format(&format);
    switch (config_read_status) {
        case 0:
            printf("%sSuccess%s: %s\n", format.status.success, format.style.reset, message);
            break;
        case -1:
            printf("%sFailure: Failed to open file.%s: %s\n", format.status.error, format.style.reset, message);
            break;
        case 1:
            printf("%sFailure: Invalid initial_step.%s: %s\n", format.status.error, format.style.reset, message);
            break;
        case 2:
            printf("%sFailure: Invalid dynamic_step.%s: %s\n", format.status.error, format.style.reset, message);
            break;
        case 3:
            printf("%sFailure: Invalid line_cnt.%s: %s\n", format.status.error, format.style.reset, message);
            break;
        case 4:
            printf("%sFailure: Invalid line_param1.%s: %s\n", format.status.error, format.style.reset, message);
            break;
        case 5:
            printf("%sFailure: Invalid line_param2.%s: %s\n", format.status.error, format.style.reset, message);
            break;
        case 6:
            printf("%sFailure: Invalid line_param3.%s: %s\n", format.status.error, format.style.reset, message);
            break;
        default:
            printf("%sFailure: Unknown error.%s: %s\n", format.status.error, format.style.reset, message);
            break;
    }
    return;
}

void config_init(config_t *config){
    config->initial_step = 0.0;
    config->dynamic_step = false;
    config->line_cnt = 0;
    config->param_cnt = 0;
    return;
}

void config_line_init(config_line_t *config_line){
    config_line->line_param1 = 0.0;
    config_line->line_param2 = 0.0;
    config_line->line_param3 = 0.0;
    return;
}

void config_print(config_t *config){
    printf("initial_step: %lf\n", config->initial_step);
    if (config->dynamic_step == 1) printf("dynamic_step: true\n"); else if (config->dynamic_step == 0) printf("dynamic_step: false\n");
    printf("line_cnt: %d\n", config->line_cnt);
    printf("param_cnt: %d\n", config->param_cnt);
    return;
}

void config_line_print(config_line_t *config_line){
    printf("line_param1: %lf\n", config_line->line_param1);
    printf("line_param2: %lf\n", config_line->line_param2);
    printf("line_param3: %lf\n", config_line->line_param3);
}

int config_parse(char *buf, config_t *config){
    char dummy[CONFIG_LINE_MAX_SIZE];
    // printf("buf: %s", buf);
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
    return CONFIG_READ_STATUS_FAILURE; // Syntax error
}

int config_line_parse(char *buf, config_line_t *config_line, int *line_cnt){
    char dummy[CONFIG_LINE_MAX_SIZE];
    printf("buf: %s", buf);
    if (sscanf(buf, " %s", dummy) == EOF) return CONFIG_READ_STATUS_SUCCESS; // Empty line
    if (sscanf(buf, " %[#]", dummy) == 1) return CONFIG_READ_STATUS_SUCCESS; // Comment line
    if (sscanf(buf, " line_param1 = %s", dummy) == 1) {
        config_line->line_param1 = strtod(dummy, NULL);
        line_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " line_param2 = %s", dummy) == 1) {
        config_line->line_param2 = strtod(dummy, NULL);
        line_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    if (sscanf(buf, " line_param3 = %s", dummy) == 1) {
        config_line->line_param3 = strtod(dummy, NULL);
        line_cnt += 1;
        return CONFIG_READ_STATUS_SUCCESS;
    }
    return CONFIG_READ_STATUS_FAILURE; // Syntax error
}

int config_read(config_t *config, config_line_t (*config_line)[], char *filename){
    // Open file
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        config_read_status_print(CONFIG_READ_STATUS_FAILURE, "");
        return CONFIG_READ_STATUS_FAILURE;
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
        config_line_init(&(*config_line)[i]);
    }
    // Read file
    while (fgets(buf, sizeof(buf), fp)) {
        ++current_line;
        if (config->param_cnt <= CONFIG_GLOBAL_SET_NUM) {
            int err = config_parse(buf, config);
            if (err) {
                sprintf(msg, "line %d: Buf: %s", current_line, buf);
                config_read_status_print(err, msg);
                memset(msg, 0, sizeof(msg)); // Clear buffer
            }
        } else {
            line_index = current_line / 3;
            printf("line_index: %d\n", line_index);
            int err = config_line_parse(buf, &(*config_line)[line_index], &line_param_cnt);
            if (err) {
                sprintf(msg, "line %d: Buf: %s", current_line, buf);
                config_read_status_print(err, msg);
                memset(msg, 0, sizeof(msg)); // Clear buffer
            }
        }
    }
    // Close file
    fclose(fp);
    return CONFIG_READ_STATUS_SUCCESS;
}
