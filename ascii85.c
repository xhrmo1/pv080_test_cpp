#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void increment(uint8_t* my_string,uint32_t* bin_num ){
    const uint8_t divider = 85;
    const uint8_t move_by = 33;
    for (int8_t pointer = 4; pointer >= 0; pointer--) {
        my_string[pointer] = (*bin_num % divider) + move_by;
        *bin_num /= divider;
    }
}

void move_bin(uint32_t* bin_num,int16_t ch){
    const uint8_t bits = 8;
    *bin_num = *bin_num << (unsigned) bits;
    *bin_num = *bin_num | (unsigned) ch;
}

int encode (void) {
    int16_t ch;
    uint8_t ammount = 0;
    uint8_t my_string[5] = "";
    uint32_t bin_num = 0;
    while ((ch = getchar()) != EOF) {
        ammount ++ ;
        if (ammount == 4) {
            ammount = 0;
            move_bin(&bin_num,ch);
            increment((uint8_t *) &my_string, &bin_num);
            for (uint8_t i = 0; i<5 ; i++){
                printf("%c",my_string[i]);}
            bin_num = 0;
            continue;
        }
        move_bin(&bin_num,ch);
    }
    if (ammount == 0) {
        printf("\n");
        return 0;
    }

    while (ammount < 4){
        bin_num = bin_num << (unsigned ) 8;
        ammount++;
    }
    increment((uint8_t *) &my_string, &bin_num);
    for (uint8_t i = 0; i<5 ; i++){
        printf("%c",my_string[i]);
    }
    printf("\n");

    return 0;
}

int decode(void)
{
    int16_t ch;
    uint8_t ammount = 0;
    uint32_t sum = 0;
    uint8_t my_string[5] = "";
    const uint8_t max_value = 117; // value that can not be overcome
    const uint8_t multiplier = 85;
    const uint8_t min_value = 33; // also we use as subtract from numb
    while ((ch=getchar()) != EOF)  {
        if (isspace(ch))
            continue;
        ammount++;
        if ((ch < min_value) || (ch > max_value))
            return 1;
        sum = sum * multiplier + (ch - min_value);
        if (ammount == 5){
            for(uint8_t i = 4; i>0 ; i--){
                my_string[i] = sum & (unsigned) 0xFF;
                sum = sum >> (unsigned) 8;
            }
            for (uint8_t i = 1; i<5 ; i++){
                printf("%c",my_string[i]);
            }
            ammount = 0;
            sum = 0;
        }
    }
    if(ammount != 0)
        return 1;

    //printf("%s",my_string);
    return 0;
}

// ================================
// DO NOT MODIFY THE FOLLOWING CODE
// ================================
int main(int argc, char *argv[])
{
    int retcode = 1;

    if (argc == 1 || (argc == 2 && strcmp(argv[1], "-e") == 0)) {
        retcode = encode();
    } else if (argc == 2 && strcmp(argv[1], "-d") == 0) {
        retcode = decode();
    } else {
        fprintf(stderr, "usage: %s [-e|-d]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (retcode != 0) {
        fprintf(stderr, "an error occured\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
