/* ====================================

File name: exerc_x_y.c (or cpp)
Date: 2018-mm-dd

Group Number:  #nr

Members of students contributed:

Name 1

Name 2

Name 3

Demonstration code: [<Examen code> <21690>]       Note that this is  Important , No code no bonus  !

====================================== */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    //Check input
    if(argc != 2){
        printf("illegal input\n");
        return 1;
    }

    //Input
    int input = (int)strtol(argv[1], NULL, 16);

    //Set outputs and error checking
    int engine_on = (0b10000000 &input) >> 7;
    int gear_pos = (0b01110000 &input) >> 4;
    int key_pos = (0b00001100 &input) >> 2;
    
    if(gear_pos > 4){
        printf("gear pos too high %i\n", gear_pos);
        return 1;
    }
    if(key_pos > 2){
        printf("key pos too high %i\n", key_pos);
        return 1;
    }
    int brake1 = (0b00000010 &input) >> 1;
    int brake2 = 0b00000001 &input;

    //Print out the values
    printf("\n");
    printf("Name\t Value\n");
    printf("engine_on = %i\n", engine_on);
    printf("gear_pos = %i\n", gear_pos);
    printf("key_pos = %i\n", key_pos);
    printf("brake1 = %i\n", brake1);
    printf("brake2 = %i\n", brake2);
    printf("\n");
    return 0;
}
