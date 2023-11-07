#include <stdio.h>
#include <math.h>
#include <string.h>
#include "data_proc.h"
#include "../../libc/output_format.h"
#include "../../libc/distance.h"

double remove_neg_zero(double x){
    output_format format;
    get_format(&format);
    // double zero = 0.0;
    if (x == 0 && x < 0){
        printf("%sWarning: %f is negative zero.\n", format.status.warning, x);
        x = fabs(x);
    }
    return x;
}

void clear_data(data_t *data){
    for (int i = 0; i < data->num_rows; i++){
        for (int j = 0; j < data->num_cols; j++){
            data->coord_original[i][j] = 0.0;
            data->coord_pan[i][j] = 0.0;
            data->coord_zoom[i][j] = 0.0;
            data->coord_rotate[i][j] = 0.0;
        }
    }
    data->num_rows = 0;
    data->num_cols = 0;
    data->zoom = 0.0;
    data->rotate = 0.0;
}

void set_history(history_t *history){
    for (int i = 0; i < MAX_RECORDS; i++){
        history->category[i] = -1;
    }
    for (int i = 0; i < MAX_CATEGORY; i++){
        history->category_count[i] = 0;
    }
}

void sort_data(data_t *data, int mode){
    // soort array first with x+y value
    double temp[2];
    double sum;
    if (mode == 1){
        for (int i = 0; i < data->num_rows; i++){
            for (int j = i+1; j < data->num_rows; j++){
                sum = data->coord_zoom[i][0] + data->coord_zoom[i][1];
                if (sum > data->coord_zoom[j][0] + data->coord_zoom[j][1]){
                    temp[0] = data->coord_zoom[i][0];
                    temp[1] = data->coord_zoom[i][1];
                    data->coord_zoom[i][0] = data->coord_zoom[j][0];
                    data->coord_zoom[i][1] = data->coord_zoom[j][1];
                    data->coord_zoom[j][0] = temp[0];
                    data->coord_zoom[j][1] = temp[1];
                }
            }
        }
    } else if (mode == 2)
    {
        for (int i = 0; i < data->num_rows; i++){
            for (int j = i+1; j < data->num_rows; j++){
                sum = data->coord_rotate[i][0] + data->coord_rotate[i][1];
                if (sum > data->coord_rotate[j][0] + data->coord_rotate[j][1]){
                    temp[0] = data->coord_rotate[i][0];
                    temp[1] = data->coord_rotate[i][1];
                    data->coord_rotate[i][0] = data->coord_rotate[j][0];
                    data->coord_rotate[i][1] = data->coord_rotate[j][1];
                    data->coord_rotate[j][0] = temp[0];
                    data->coord_rotate[j][1] = temp[1];
                }
            }
        }
    }
}

void pan_data(data_t *data, double x, double y, int mode){
    if (mode == 1){
        double dx = data->coord_original[0][0] - x;
        double dy = data->coord_original[0][1] - y;
        data->pan_diff[0] = dx;
        data->pan_diff[1] = dy;
        for (int i = 0; i < data->num_rows; i++){
            data->coord_pan[i][0] = remove_neg_zero(data->coord_original[i][0] - dx);
            data->coord_pan[i][1] = remove_neg_zero(data->coord_original[i][1] - dy);
        }
    } else if (mode == 2)
    {
        double min_x = data->coord_rotate[0][0];
        double min_y = data->coord_rotate[0][1];
        for (int i = 0; i < data->num_rows; i++){
            if (data->coord_rotate[i][0] < min_x){
                min_x = data->coord_rotate[i][0];
            }
            if (data->coord_rotate[i][1] < min_y){
                min_y = data->coord_rotate[i][1];
            }
        }
        printf("min_x: %f\n", min_x);
        printf("min_y: %f\n", min_y);
        for (int i = 0; i < data->num_rows; i++){
            data->coord_rotate[i][0] = remove_neg_zero(data->coord_rotate[i][0] - min_x);
            data->coord_rotate[i][1] = remove_neg_zero(data->coord_rotate[i][1] - min_y);
        }
    }
    
}

void zoom_data(data_t *data, double max_length){
    double max = 0.0;
    double dist = 0.0;
    for (int i = 0; i < data->num_rows-1; i++){
        dist = distance_straightline(data->coord_pan[i][0], data->coord_pan[i][1], data->coord_pan[i+1][0], data->coord_pan[i+1][1]);
        if (dist > max){
            max = dist;
        }
    }
    double scale = max_length / max;
    printf("max: %f\n", max);
    for (int i = 0; i < data->num_rows; i++){
        data->coord_zoom[i][0] = remove_neg_zero(data->coord_pan[i][0] * scale);
        data->coord_zoom[i][1] = remove_neg_zero(data->coord_pan[i][1] * scale);
    }
    data->zoom = scale;
}

void get_range(data_t *data){
    // get original range
    double min_x = data->coord_original[0][0];
    double max_x = data->coord_original[0][0];
    double min_y = data->coord_original[0][1];
    double max_y = data->coord_original[0][1];
    for (int i = 0; i < data->num_rows; i++){
        if (data->coord_original[i][0] < min_x){
            min_x = data->coord_original[i][0];
        }
        if (data->coord_original[i][0] > max_x){
            max_x = data->coord_original[i][0];
        }
        if (data->coord_original[i][1] < min_y){
            min_y = data->coord_original[i][1];
        }
        if (data->coord_original[i][1] > max_y){
            max_y = data->coord_original[i][1];
        }
    }
    data->orignal_range[0] = min_x;
    data->orignal_range[1] = max_x;
    data->orignal_range[2] = min_y;
    data->orignal_range[3] = max_y;
    // get pan range
    min_x = data->coord_pan[0][0];
    max_x = data->coord_pan[0][0];
    min_y = data->coord_pan[0][1];
    max_y = data->coord_pan[0][1];
    for (int i = 0; i < data->num_rows; i++){
        if (data->coord_pan[i][0] < min_x){
            min_x = data->coord_pan[i][0];
        }
        if (data->coord_pan[i][0] > max_x){
            max_x = data->coord_pan[i][0];
        }
        if (data->coord_pan[i][1] < min_y){
            min_y = data->coord_pan[i][1];
        }
        if (data->coord_pan[i][1] > max_y){
            max_y = data->coord_pan[i][1];
        }
    }
    data->pan_range[0] = min_x;
    data->pan_range[1] = max_x;
    data->pan_range[2] = min_y;
    data->pan_range[3] = max_y;
    // get zoom range
    min_x = data->coord_zoom[0][0];
    max_x = data->coord_zoom[0][0];
    min_y = data->coord_zoom[0][1];
    max_y = data->coord_zoom[0][1];
    for (int i = 0; i < data->num_rows; i++){
        if (data->coord_zoom[i][0] < min_x){
            min_x = data->coord_zoom[i][0];
        }
        if (data->coord_zoom[i][0] > max_x){
            max_x = data->coord_zoom[i][0];
        }
        if (data->coord_zoom[i][1] < min_y){
            min_y = data->coord_zoom[i][1];
        }
        if (data->coord_zoom[i][1] > max_y){
            max_y = data->coord_zoom[i][1];
        }
    }
    data->zoom_range[0] = min_x;
    data->zoom_range[1] = max_x;
    data->zoom_range[2] = min_y;
    data->zoom_range[3] = max_y;
    // get rotate range
    min_x = data->coord_rotate[0][0];
    max_x = data->coord_rotate[0][0];
    min_y = data->coord_rotate[0][1];
    max_y = data->coord_rotate[0][1];
    for (int i = 0; i < data->num_rows; i++){
        if (data->coord_rotate[i][0] < min_x){
            min_x = data->coord_rotate[i][0];
        }
        if (data->coord_rotate[i][0] > max_x){
            max_x = data->coord_rotate[i][0];
        }
        if (data->coord_rotate[i][1] < min_y){
            min_y = data->coord_rotate[i][1];
        }
        if (data->coord_rotate[i][1] > max_y){
            max_y = data->coord_rotate[i][1];
        }
    }
    data->rotate_range[0] = min_x;
    data->rotate_range[1] = max_x;
    data->rotate_range[2] = min_y;
    data->rotate_range[3] = max_y;
}

void rotate_data(data_t *data, double angle_degree){
    double angle_radian = angle_degree * (double)acos(-1) / 180.0;
    double x, y, newx, newy;
    for (int i = 0; i < data->num_rows; i++){
        x = data->coord_zoom[i][0];
        y = data->coord_zoom[i][1];
        newx = x * cos(angle_radian) - y * sin(angle_radian);
        newy = x * sin(angle_radian) + y * cos(angle_radian);
        data->coord_rotate[i][0] = remove_neg_zero(newx);
        data->coord_rotate[i][1] = remove_neg_zero(newy);
    }
    data->rotate = angle_degree;
}

void hash_data(data_t *data, history_t *history, int index, int mode){
    // sort array based on x and y
    // append all x and y together
    char str[STR_LEN_FOR_HASH];
    memset(str, 0, sizeof(str));
    if (mode == 1) {
        for (int i = 0; i < data->num_rows; i++){
            sprintf(str, "%s%.2f", str, data->coord_zoom[i][0]);
            sprintf(str, "%s%.2f", str, data->coord_zoom[i][1]);
        }
    } else if (mode == 2) {
        for (int i = 0; i < data->num_rows; i++){
            sprintf(str, "%s%.2f", str, data->coord_rotate[i][0]);
            sprintf(str, "%s%.2f", str, data->coord_rotate[i][1]);
        }
    }
    
    strcpy(history->line[index], str);
    printf("str: %s\n", str);
    // hash the string
    char hash[256];
    FILE *fp;
    char command[STR_LEN_FOR_HASH+100];
    int len;
    len = snprintf(command, sizeof(command), "echo -n \"%s\" | openssl dgst -sha256", str);
    if (len <= sizeof(command)) fp = popen(command, "r");
    if (fp == NULL){
        printf("Failed to run command\n");
    }
    fgets(hash, sizeof(hash), fp);
    pclose(fp);
    // printf("hash: %s\n", hash);
    strcpy(history->hash[index], hash);
    // reset str
    memset(str, 0, sizeof(str));
    return;
}

void classify_data(data_t *data, history_t *history, int index){
    // sort_data(data, 1);
    rotate_data(data, -90);
    hash_data(data, history, index, 1);
    // if (index == 0) {
    //     history->category[index] = 0;
    //     history->category_count[0]++;
    // } else {
    //     int flag = 0;
    //     for (int i = 0; i < index-1; i++){
    //         if (strcmp(history->hash[index], history->hash[i]) == 0){
    //             history->category[index] = history->category[i];
    //             history->category_count[history->category[i]]++;
    //             flag = 1;
    //             break;
    //         }

    //     }
        // if (flag == 0) { // Rotate 90 degree
        //     printf("before rotate:\n");
        //     for (int i = 0; i < data->num_rows; i++){
        //         printf("  %f, %f\n", data->coord_zoom[i][0], data->coord_zoom[i][1]);
        //     }
        //     rotate_data(data, -90);
        //     printf("after rotate:\n");
        //     for (int i = 0; i < data->num_rows; i++){
        //         printf("  %f, %f\n", data->coord_rotate[i][0], data->coord_rotate[i][1]);
        //     }
        //     pan_data(data, 0, 0, 2);
        //     printf("after pan:\n");
        //     for (int i = 0; i < data->num_rows; i++){
        //         printf("  %f, %f\n", data->coord_rotate[i][0], data->coord_rotate[i][1]);
        //     }
        //     sort_data(data, 2);
        //     printf("after sort:\n");
        //     for (int i = 0; i < data->num_rows; i++){
        //         printf("  %f, %f\n", data->coord_rotate[i][0], data->coord_rotate[i][1]);
        //     }
        //     hash_data(data, history, index, 2);
        //     for (int i = 0; i < index-1; i++){
        //         if (strcmp(history->hash[index], history->hash[i]) == 0){
        //             history->category[index] = history->category[i];
        //             history->category_count[history->category[i]]++;
        //             flag = 1;
        //             break;
        //         }
        //     }
        // }
        // printf("strR: %s\n", history->line[index]);
        // printf("hashR: %s\n", history->hash[index]);
        // if (flag == 0) { // Rotate 180 degree
        //     rotate_data(data, -180);
        //     pan_data(data, 0, 0, 2);
        //     hash_data(data, history, index, 2);
        //     for (int i = 0; i < index-1; i++){
        //         if (strcmp(history->hash[index], history->hash[i]) == 0){
        //             history->category[index] = history->category[i];
        //             history->category_count[history->category[i]]++;
        //             flag = 1;
        //             break;
        //         }
        //     }
        // }
        // printf("str: %s\n", history->line[index]);
        // if (flag == 0) { // Rotate 270 degree
        //     rotate_data(data, -270);
        //     pan_data(data, 0, 0, 2);
        //     hash_data(data, history, index, 2);
        //     for (int i = 0; i < index-1; i++){
        //         if (strcmp(history->hash[index], history->hash[i]) == 0){
        //             history->category[index] = history->category[i];
        //             history->category_count[history->category[i]]++;
        //             flag = 1;
        //             break;
        //         }
        //     }
        // }
        // printf("str: %s\n", history->line[index]);
    //     if (flag == 0) {
    //         rotate_data(data, 0);
    //         hash_data(data, history, index, 1);
    //         history->category[index] = index;
    //         history->category_count[index]++;
    //     }
    // }
}

void print_data(data_t *data){
    printf("num_rows: %d\n", data->num_rows);
    printf("num_cols: %d\n", data->num_cols);
    printf("coord_original:\n");
    for (int i = 0; i < data->num_rows; i++){
        printf("  %f, %f\n", data->coord_original[i][0], data->coord_original[i][1]);
    }
    printf("coord_pan:\n");
    for (int i = 0; i < data->num_rows; i++){
        printf("  %f, %f\n", data->coord_pan[i][0], data->coord_pan[i][1]);
    }
    printf("coord_zoom:\n");
    for (int i = 0; i < data->num_rows; i++){
        printf("  %f, %f\n", data->coord_zoom[i][0], data->coord_zoom[i][1]);
    }
    printf("coord_rotate:\n");
    for (int i = 0; i < data->num_rows; i++){
        printf("  %f, %f\n", data->coord_rotate[i][0], data->coord_rotate[i][1]);
    }
}

void print_history(history_t *history){
    printf("line:\n");
    for (int i = 0; i < MAX_RECORDS; i++){
        printf("  %s\n", history->line[i]);
    }
    printf("hash:\n");
    for (int i = 0; i < MAX_RECORDS; i++){
        printf("  %s\n", history->hash[i]);
    }
    printf("category:\n");
    for (int i = 0; i < MAX_RECORDS; i++){
        printf("  %d\n", history->category[i]);
    }
    printf("category_count:\n");
    for (int i = 0; i < MAX_CATEGORY; i++){
        printf("  %d\n", history->category_count[i]);
    }
}
