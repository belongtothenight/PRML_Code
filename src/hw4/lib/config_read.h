// This code is heavily referenced from https://stackoverflow.com/questions/48413430/c-code-to-read-config-file-and-parse-directives

#ifndef CONFIG_READ_H
#define CONFIG_READ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct config {
    double line1_param1; // a_x1
    double line1_param2; // b_y1
    double line1_param3; // c_1
    double line2_param1; // a_x2
    double line2_param2; // b_y2
    double line2_param3; // c_2
    double initial_step; // learning rate
    bool   dynamic_step; // dynamic learning rate or not
}

#endif // CONFIG_READ_H
