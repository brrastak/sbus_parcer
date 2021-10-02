#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "inc.h"

typedef struct test{
    uint8_t input[25];
    uint16_t output[18];
}test_t;
int main()
{
    test_t t1 = {
    .input = {15, 41,107,214,235, 44,169,  3, 33,187,239, 95, 95, 76,252, 16,236,190,212,237, 81,  6, 69, 77,  0},
    .output = {809, 717, 943,1174,  58,1602,1006, 767,1119,1929,  67,1910,1355, 987, 404, 552,2047,   0}
    };


    // two parts
    test_t t21 = {
    .input = {0, 0, 0, 15, 41,107,214,235, 44,169,  3, 33,187,239, 95, 95, 76,252, 16,236,190,212,237, 81,  6},
    .output = {809, 717, 943,1174,  58,1602,1006, 767,1119,1929,  67,1910,1355, 987, 404, 552,2047,   0}
    };
    test_t t22 = {
    .input = {69, 77, 0, 0, 0, 44,169,  3, 33,187,239, 95, 95, 76,252, 16,236,190,212,237, 81,  6, 69, 77,  0},
    .output = {809, 717, 943,1174,  58,1602,1006, 767,1119,1929,  67,1910,1355, 987, 404, 552,2047,   0}
    };

    // five parts
    test_t t31 = {
    .input = {0, 0, 0, 0, 0, 15, 41,107,214,235},
    .output = {}
    };
    test_t t32 = {
    .input = {44,169,  3, 33,187},
    .output = {}
    };
    test_t t33 = {
    .input = {239, 95, 95, 76,252},
    .output = {}
    };
    test_t t34 = {
    .input = {16,236,190,212,237},
    .output = {}
    };
    test_t t35 = {
    .input = {81,  6, 69, 77,  0, 1, 2, 3, 4, 5},
    .output = {}
    };



    printf( "TEST1\n");
    parceSbus(t1.input, 25);
    printArrU16(t1.output, 18);
    printSbusSt(print);
    if (memcmp(sbus_st.channel, t1.output, 10) == 0) {
        printf("TEST DONE\n\n");
    }
    else {
        printf("TEST FAILED\n\n");
    }



    printf( "TEST2\n");
    parceSbus(t21.input, 25);
    parceSbus(t22.input, 25);
    printArrU16(t1.output, 18);
    printSbusSt(print);
    if (memcmp(sbus_st.channel, t1.output, 10) == 0) {
        printf("TEST DONE\n\n");
    }
    else {
        printf("TEST FAILED\n\n");
    }


    printf( "TEST3\n");
    parceSbus(t31.input, 10);
    parceSbus(t32.input, 5);
    parceSbus(t33.input, 5);
    parceSbus(t34.input, 5);
    parceSbus(t35.input, 10);
    printArrU16(t1.output, 18);
    printSbusSt(print);
    if (memcmp(sbus_st.channel, t1.output, 10) == 0) {
        printf("TEST DONE\n\n");
    }
    else {
        printf("TEST FAILED\n\n");
    }



}
