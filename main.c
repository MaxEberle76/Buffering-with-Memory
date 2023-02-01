#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "memory.h"

//#define _CRT_SECURE_NO_WARNINGS


int main(void) {

    int dataSize;
    int *localBuffer = NULL;


    //We use the variable 'dataSize' to get the first value of the input buffer
    dataSize = reading();

    //If it is not -1, then the program enters a while loop
    while (dataSize !=-1) {

        //We allocate memory for the local buffer here
        localBuffer = (int *)my_malloc((dataSize + 2) * sizeof(int));

        //Then we use the following functions for our operations
        transferringTOlocal(localBuffer);
        processing(localBuffer);
        transferringFROMlocal(localBuffer);

        //And we free the local buffer's memory here
        my_free(localBuffer);

        submitting();

        //Then the program continues as long as it doesn't receive -1
        dataSize = reading();
    }
    return 0;
}