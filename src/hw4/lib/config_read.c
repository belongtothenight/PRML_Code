#include <stdio.h>
#include <stdlib.h>
#include "config_read.h"

void config_init(config_t *config, int initial_step_CONF_MAX_LEN, int dynamic_step_CONF_MAX_LEN, int line_cnt_CONF_MAX_LEN){
    config->set = 0u;
    config->initial_step = 0.0;
    config->dynamic_step = false;
    config->line_cnt = 0;
    config->initial_step_CONF_MAX_LEN = initial_step_CONF_MAX_LEN;
    config->dynamic_step_CONF_MAX_LEN = dynamic_step_CONF_MAX_LEN;
    config->line_cnt_CONF_MAX_LEN = line_cnt_CONF_MAX_LEN;
    return;
}

void config_line_init(config_line_t *config_line, int line_param1_CONF_MAX_LEN, int line_param2_CONF_MAX_LEN, int line_param3_CONF_MAX_LEN){
    config_line->set = 0u;
    config_line->line_param1 = 0.0;
    config_line->line_param2 = 0.0;
    config_line->line_param3 = 0.0;
    config_line->line_param1_CONF_MAX_LEN = line_param1_CONF_MAX_LEN;
    config_line->line_param2_CONF_MAX_LEN = line_param2_CONF_MAX_LEN;
    config_line->line_param3_CONF_MAX_LEN = line_param3_CONF_MAX_LEN;
    return;
}

void config_print(config_t *config){
    printf("initial_step: %lf\n", config->initial_step);
    printf("dynamic_step: %d\n", config->dynamic_step);
    printf("line_cnt: %d\n", config->line_cnt);
    printf("initial_step_CONF_MAX_LEN: %d\n", config->initial_step_CONF_MAX_LEN);
    printf("dynamic_step_CONF_MAX_LEN: %d\n", config->dynamic_step_CONF_MAX_LEN);
    printf("line_cnt_CONF_MAX_LEN: %d\n", config->line_cnt_CONF_MAX_LEN);
    return;
}

void config_line_print(config_line_t *config_line){
    printf("line_param1: %lf\n", config_line->line_param1);
    printf("line_param2: %lf\n", config_line->line_param2);
    printf("line_param3: %lf\n", config_line->line_param3);
    printf("line_param1_CONF_MAX_LEN: %d\n", config_line->line_param1_CONF_MAX_LEN);
    printf("line_param2_CONF_MAX_LEN: %d\n", config_line->line_param2_CONF_MAX_LEN);
    printf("line_param3_CONF_MAX_LEN: %d\n", config_line->line_param3_CONF_MAX_LEN);
}

int config_read(config_t *config, config_line_t (*config_line)[], char *filename){
    // Get enum value of config_read_status
    enum config_read_status config_read_status_success = CONFIG_READ_SUCCESS;
    enum config_read_status config_read_status_failure = CONFIG_READ_FAILURE;
    enum config_read_status config_read_status_initial_step_invalid = CONFIG_READ_INITIAL_STEP_INVALID;
    enum config_read_status config_read_status_dynamic_step_invalid = CONFIG_READ_DYNAMIC_STEP_INVALID;
    enum config_read_status config_read_status_line_cnt_invalid = CONFIG_READ_LINE_CNT_INVALID;
    enum config_read_status config_read_status_line_param1_invalid = CONFIG_READ_LINE_PARAM1_INVALID;
    enum config_read_status config_read_status_line_param2_invalid = CONFIG_READ_LINE_PARAM2_INVALID;
    enum config_read_status config_read_status_line_param3_invalid = CONFIG_READ_LINE_PARAM3_INVALID;
    // Open file
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error: cannot open file %s\n", filename);
        return config_read_status_failure;
    }
    // Read file
    char buf[CONFIG_LINE_MAX_SIZE];
    
}
