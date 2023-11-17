/**
 * @file config_read.h
 * References:
 * 1. https://stackoverflow.com/questions/48413430/c-code-to-read-config-file-and-parse-directives
 * 2. https://stackoverflow.com/questions/16201607/c-pointer-to-array-of-structs
 * 3. https://stackoverflow.com/questions/13801196/does-sscanf-support-boolean-type
 * 4. https://www.tutorialspoint.com/c_standard_library/c_function_strtod.htm
 * 5. https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c
 * 6. https://stackoverflow.com/questions/260915/how-can-i-create-a-dynamically-sized-array-of-structs
*/

#ifndef CONFIG_READ_H
#define CONFIG_READ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define CONFIG_LINE_MAX_SIZE    (256)   ///< Maximum size of config file line (changing number small can take more config lines, weird)
#define CONFIG_SET_MAX_SIZE     (128)   ///< Maximum size of config file settting in memory
#define MAX_LINE_CNT            (4)     ///< Maximum number of specified lines in config file
#define CONFIG_GLOBAL_SET_NUM   (11)     ///< Number of global settings in config file
// #define CONFIG_GNUPLOT_SET_NUM  (5)     ///< Number of gnuplot settings in config file
#define CONFIG_LINE_SET_NUM     (5)     ///< Number of each line settings in config file

#define CONFIG_READ_STATUS_SUCCESS (0)           ///< Success
#define CONFIG_READ_STATUS_FAILURE (-1)          ///< Can't open file

#define DISPLAY_CONFIG_READ_BUF (0)               ///< Display config read or not
#define DISPLAY_CONFIG_PARSING_BUF (0)            ///< Display config parsing or not
#define DISPLAY_CONFIG_LINE_PARSING_BUF (1)       ///< Display config line parsing or not

/**
 * @brief Data structure for config file general settings
*/
typedef struct {
    double initial_step;                        ///< learning rate
    bool   dynamic_step;                        ///< dynamic learning rate or not
    int    line_cnt;                            ///< number of lines in config file
    char*  output_file[CONFIG_SET_MAX_SIZE];   ///< output file name
    double initial_x;                           ///< initial x
    double initial_y;                           ///< initial y
    char*  font[CONFIG_SET_MAX_SIZE];          ///< font
    int    font_size;                           ///< font size
    int    plot_x_size;                         ///< plot x size
    int    plot_y_size;                         ///< plot y size
    char*  plot_filetype[CONFIG_SET_MAX_SIZE]; ///< plot filetype
    int    param_cnt;                           ///< number of parameters in config file
} config_t;

/**
 * @brief Data structure for config file individual line settings
*/
typedef struct {
    char*  line_title[CONFIG_SET_MAX_SIZE];  ///< line title (ex: Line 1)
    char*  line_symbol[CONFIG_SET_MAX_SIZE]; ///< line symbol (ex: f(x))
    double line_param1;                       ///< a_x1
    double line_param2;                       ///< b_y1
    double line_param3;                       ///< c_1
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
 * @brief Print all structs available
 * @param config Pointer to config_t struct
 * @param config_lines Pointer to a list of config_line_t structs
 * @retval void
*/
void config_all_print(config_t *config, config_line_t (*config_lines)[]);

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
 * @param line_cnt Pointer to line_cnt
 * @retval config_read_status
*/
int config_line_parse(char *buf, config_line_t *config_line, int *line_cnt);

/**
 * @brief Read config file and parse directives
 * @param config Pointer to config_t struct
 * @param config_line Pointer to a list of config_line_t struct
 * @param filename Name of config file
 * @retval config_read_status
*/
int config_read(config_t *config, config_line_t (*config_lines)[], char *filename);

#endif // CONFIG_READ_H
