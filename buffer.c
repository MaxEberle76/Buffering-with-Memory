#define MIN     0
#define MAX     1
#define ODD     2
#define EVEN    3
#define MINMAX  4
#define ODDEVEN 5

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "memory.h"
#include "buffer.h"

//We start by setting up our pointers
int *inputBuffer = NULL;
int *outputBuffer = NULL;

// this function prints the contents of each buffer
void print_buffer(int*);

// two functions provided to you (defined in io.h and io.c) are:

// int get_value(void);
//       this function generates a single value
//       you use it to obtain this value and put it into an input buffer

// int submit_results(int[]);
//       you use this function to submit the data processing results
//       for validation (your results are checked inside this function)

//Here is the reading function
int reading() {

    printf("Reading...\n");

    //We get the ID first
    int ID = get_value();

    //If it is -1, the function exits
    if(ID != -1) {

        //Getting the number of results
        int results = get_value();

        //Here is where we allocate memory for the input buffer and give it the first two get_value values
        inputBuffer = (int *) my_malloc((results+2) * sizeof(int));
        inputBuffer[0] = ID;
        inputBuffer[1] = results;

        //Then we fill the rest of the input buffer with values...
        for(int i = 0; i < results; i++) {

            inputBuffer[i+2] = get_value();
        }

        //Display it...
        printf("The input buffer is: \n");
        print_buffer(inputBuffer);

        //And return the number of data points
        return results;
    }
    else {
        //If the ID is -1 then the function returns -1
        printf("End of stored data\n");
        return -1;
    }
}

//Here is the function to transfer the input buffer to the local buffer
void transferringTOlocal(int* localBuffer) {

    printf("Transferring to local buffer...\n");

    //A loop to copy the contents
    for(int j = 0; j < inputBuffer[1] + 2; j++) {

        localBuffer[j] = inputBuffer[j];
    }
    //And we free the memory allocated to the input buffer once we are done with it
    my_free(inputBuffer);

    printf("The local buffer is: \n");
    print_buffer(localBuffer);
}

//Next we have the processing function
void processing(int *localBuffer) {

    printf("Processing...\n");

    int max, min, num_odd = 0, num_even = 0;

    //Here is where we read the operation ID
    switch(localBuffer[0]) {

        case MIN: //This loop finds the minimum value
            min = localBuffer[2];

            //It sorts through each value, replacing 'min' if the next value is smaller
            for(int n = 3; n < localBuffer[1] + 2; n++) {

                if(localBuffer[n] < min) {
                    min = localBuffer[n];
                }
            }
            //The output buffer will only have 1 result
            localBuffer[1] = 1;
            localBuffer[2] = min;
            break;

        case MAX: //This loop finds the maximum value
            max = localBuffer[2];

            //It sorts through each value, replacing 'max' if the next value is larger
            for(int n = 3; n < localBuffer[1]+ 2; n++) {

                if(localBuffer[n] > max) {
                    max = localBuffer[n];
                }
            }
            //The output buffer will only have 1 result
            localBuffer[1] = 1;
            localBuffer[2] = max;
            break;

        case ODD: //This loop finds the number of odd values

            //It modulo divides each number by 2, and increments the counter if the result is 1
            for(int n = 2; n < localBuffer[1] + 2; n++) {

                if((localBuffer[n] % 2) == 1) {

                    ++num_odd;
                }
            }
            //The output buffer will only have 1 result
            localBuffer[1] = 1;
            localBuffer[2] = num_odd;
            break;

        case EVEN: //This loop finds the number of odd values

            //It modulo divides each number by 2, and increments the counter if the result is 0
            for(int n = 2; n < localBuffer[1] + 2; n++) {

                if((localBuffer[n] % 2) == 0) {

                    ++num_even;
                }
            }
            //The output buffer will only have 1 result
            localBuffer[1] = 1;
            localBuffer[2] = num_even;
            break;

        case MINMAX: //This loop finds both the min and max by combining the MIN and MAX conditions above

            min = localBuffer[2];

            for(int n = 3; n < localBuffer[1] + 2; n++) {

                if(localBuffer[n] < min) {
                    min = localBuffer[n];
                }
            }

            max = localBuffer[2];

            for(int n = 3; n < localBuffer[1]+ 2; n++) {

                if(localBuffer[n] > max) {
                    max = localBuffer[n];
                }
            }
            //The output buffer will have 2 results
            localBuffer[1] = 2;
            localBuffer[2] = min;
            localBuffer[3] = max;
            break;

        case ODDEVEN: //This loop finds the number of odd and even values by combining the ODD and EVEN conditions above

            for(int n = 2; n < localBuffer[1] + 2; n++) {

                if((localBuffer[n] % 2) == 1) {

                    ++num_odd;
                }
            }
            for(int n = 2; n < localBuffer[1] + 2; n++) {

                if((localBuffer[n] % 2) == 0) {

                    ++num_even;
                }
            }
            //The output buffer will have 2 results
            localBuffer[1] = 2;
            localBuffer[2] = num_odd;
            localBuffer[3] = num_even;
            break;
    }
}

//Here is the function to transfer the local buffer's contents to the output buffer
void transferringFROMlocal(int *localBuffer) {

    printf("Transferring to output buffer...\n");

    //We need to allocate memory for the output buffer
    outputBuffer = (int *)my_malloc((localBuffer[1] + 2) * sizeof(int));

    //A loop to copy the contents
    for(int i = 0; i < localBuffer[1] + 2; i++) {

        outputBuffer[i] = localBuffer[i];
    }

    printf("The output buffer is: \n");
    print_buffer(outputBuffer);
}

//Finally, we have the submitting function
void submitting() {

    printf("Submitting...\n");


    //If the result of the submit_results function is 1, the results are incorrect. If 0, then correct
    if(submit_results(outputBuffer)) {

        printf("The results are not correct\n");
    }
    else {

        printf("The results are correct\n");
    }

    //And we free the memory allocated to the output buffer after we are done with it
    my_free(outputBuffer);
    printf("\n");
}


//Here is the function to print each buffer, it takes all three buffers as an input
void print_buffer(int* Buffer) {

    //This function employs loops to print each integer individually

    for (int x = 0; x < Buffer[1] + 2; x++) {
        printf("%5d", Buffer[x]);
    }
    printf("\n");
}