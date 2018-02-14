#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    unsigned int outByte = 0x00;

    if (argc != 6) {
        printf("Wrong number of input arguments\n");
        return 1;
    }

    int engine_on = atoi(*(argv+1));
    int gear_pos = atoi(*(argv+2));
    int key_pos = atoi(*(argv+3));
    int brake1 = atoi(*(argv+4));
    int brake2 = atoi(*(argv+5));

    //Checking the input arguments
    if(engine_on > 1 || gear_pos > 4 || key_pos > 2 || brake1 > 1 || brake2 > 1){
        printf("Wrong input");
        return 1;
    }

    // Write the bytes to the char outByte
    outByte = outByte | engine_on << 7;
    outByte = outByte | gear_pos << 4;
    outByte = outByte | key_pos << 2;
    outByte = outByte | brake1 << 1;
    outByte = outByte | brake2;

    printf("Hex: %x\n", outByte);

    return 0;
}


