/**
 * @file config_read.h
*/

/**
 * References:
 * 1. https://stackoverflow.com/questions/48413430/c-code-to-read-config-file-and-parse-directives
 * 2. https://stackoverflow.com/questions/16201607/c-pointer-to-array-of-structs
*/

#ifndef CONFIG_READ_H
#define CONFIG_READ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CONFIG_LINE_MAX_SIZE (64)       ///< Maximum size of config file
#define MAX_LINE_CNT         (4)        ///< Maximum number of specified lines in config file

/**
 * @brief Enum for config file read status
*/
enum config_read_status {
    CONFIG_READ_SUCCESS = 0,                ///< Success
    CONFIG_READ_FAILURE = -1,               ///< Can't open file
    CONFIG_READ_INITIAL_STEP_INVALID = 1,   ///< Invalid initial_step
    CONFIG_READ_DYNAMIC_STEP_INVALID = 2,   ///< Invalid dynamic_step
    CONFIG_READ_LINE_CNT_INVALID = 3,       ///< Invalid line_cnt
    CONFIG_READ_LINE_PARAM1_INVALID = 4,    ///< Invalid line_param1
    CONFIG_READ_LINE_PARAM2_INVALID = 5,    ///< Invalid line_param2
    CONFIG_READ_LINE_PARAM3_INVALID = 6,    ///< Invalid line_param3
};

/**
 * @brief Data structure for config file general settings
*/
typedef struct {
    double  initial_step;               ///< learning rate
    bool    dynamic_step;               ///< dynamic learning rate or not
    int     line_cnt;                   ///< number of lines in config file
    unsigned set;                       ///< set or not
    int     initial_step_CONF_MAX_LEN;  ///< Maximum length of initial_step in config file
    int     dynamic_step_CONF_MAX_LEN;  ///< Maximum length of dynamic_step in config file
    int     line_cnt_CONF_MAX_LEN;      ///< Maximum length of line_cnt in config file
} config_t;

/**
 * @brief Data structure for config file individual line settings
*/
typedef struct {
    double  line_param1;                ///< a_x1
    double  line_param2;                ///< b_y1
    double  line_param3;                ///< c_1
    unsigned set;                       ///< set or not
    int     line_param1_CONF_MAX_LEN;   ///< Maximum length of a_x1 in config file
    int     line_param2_CONF_MAX_LEN;   ///< Maximum length of b_y1 in config file
    int     line_param3_CONF_MAX_LEN;   ///< Maximum length of c_1  in config file
} config_line_t;

/**
 * @brief Set config_t struct to default values
 * @param config Pointer to config_t struct
 * @param initial_step_CONF_MAX_LEN Maximum length of initial_step in config file
 * @param dynamic_step_CONF_MAX_LEN Maximum length of dynamic_step in config file
 * @param line_cnt_CONF_MAX_LEN Maximum length of line_cnt in config file
 * @retval void
*/
void config_init(config_t *config, int initial_step_CONF_MAX_LEN, int dynamic_step_CONF_MAX_LEN, int line_cnt_CONF_MAX_LEN);

/**
 * @brief Set config_line_t struct to default values
 * @param config_line Pointer to config_line_t struct
 * @param line_param1_CONF_MAX_LEN Maximum length of a_x1 in config file
 * @param line_param2_CONF_MAX_LEN Maximum length of b_y1 in config file
 * @param line_param3_CONF_MAX_LEN Maximum length of c_1  in config file
 * @retval void
*/
void config_line_init(config_line_t *config_line, int line_param1_CONF_MAX_LEN, int line_param2_CONF_MAX_LEN, int line_param3_CONF_MAX_LEN);

/**
 * @brief Print config_t struct
 * @param config Pointer to config_t struct
 * @retval void
*/
void config_print(config_t *config);

/**
 * @brief Print config_line_t struct
 * @param config_line Pointer to config_line_t struct
 * @retval void
*/
void config_line_print(config_line_t *config_line);

/**
 * @brief Read config file and parse directives
 * @param config Pointer to config_t struct
 * @param config_line Pointer to a list of config_line_t struct
 * @param filename Name of config file
 * @retval config_read_status
*/
int config_read(config_t *config, config_line_t (*config_line)[], char *filename);

#endif // CONFIG_READ_H
