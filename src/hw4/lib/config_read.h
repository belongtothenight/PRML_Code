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

#define CONFIG_LINE_MAX_SIZE    (1024)  ///< Maximum size of config file
#define MAX_LINE_CNT            (4)     ///< Maximum number of specified lines in config file
#define CONFIG_GLOBAL_SET_NUM   (3)     ///< Number of global settings in config file

#define CONFIG_READ_STATUS_SUCCESS (0)  ///< Success
#define CONFIG_READ_STATUS_FAILURE (-1) ///< Can't open file
#define CONFIG_READ_STATUS_INITIAL_STEP_INVALID (1)  ///< Invalid initial_step
#define CONFIG_READ_STATUS_DYNAMIC_STEP_INVALID (2)  ///< Invalid dynamic_step
#define CONFIG_READ_STATUS_LINE_CNT_INVALID (3)      ///< Invalid line_cnt
#define CONFIG_READ_STATUS_LINE_PARAM1_INVALID (4)   ///< Invalid line_param1
#define CONFIG_READ_STATUS_LINE_PARAM2_INVALID (5)   ///< Invalid line_param2
#define CONFIG_READ_STATUS_LINE_PARAM3_INVALID (6)   ///< Invalid line_param3

/**
 * @brief Data structure for config file general settings
*/
typedef struct {
    double  initial_step;               ///< learning rate
    bool    dynamic_step;               ///< dynamic learning rate or not
    int     line_cnt;                   ///< number of lines in config file
    unsigned set;                       ///< set or not
} config_t;

/**
 * @brief Data structure for config file individual line settings
*/
typedef struct {
    double  line_param1;                ///< a_x1
    double  line_param2;                ///< b_y1
    double  line_param3;                ///< c_1
    unsigned set;                       ///< set or not
} config_line_t;

/**
 * @brief Print config_read_status
 * @param config_read_status config_read_status
 * @param message Message to print
*/
void config_read_status_print(int config_read_status, char *message);

/**
 * @brief Set config_t struct to default values
 * @param config Pointer to config_t struct
 * @retval void
*/
void config_init(config_t *config);

/**
 * @brief Set config_line_t struct to default values
 * @param config_line Pointer to config_line_t struct
 * @retval void
*/
void config_line_init(config_line_t *config_line);

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
 * @brief Parse config file and assign values to config_t
 * @param buf Pointer to read buffer
 * @param config Pointer to config_t struct
 * @retval config_read_status
*/
int config_parse(char *buf, config_t *config);

/**
 * @brief Parse config file and assign values to config_line_t
 * @param buf Pointer to read buffer
 * @param config_line Pointer to config_line_t struct
 * @retval config_read_status
*/
int config_line_parse(char *buf, config_line_t *config_line);

/**
 * @brief Read config file and parse directives
 * @param config Pointer to config_t struct
 * @param config_line Pointer to a list of config_line_t struct
 * @param filename Name of config file
 * @retval config_read_status
*/
int config_read(config_t *config, config_line_t (*config_line)[], char *filename);

#endif // CONFIG_READ_H
