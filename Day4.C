#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Checks how many matches a line has and assigns points accordingly
int arrayCompare(long  array1[], long array2[]){
    int c = 0;
    int d = 0;
    int total = 0;
    int flag = 0;
    int midtotal = 0;
    while (c <= 9){  // Should be made into for loops
        while(d <= 24){
            if(array1[c] == array2[d]){

                if (flag == 0){
                    midtotal = 1;
                    flag = 1;
                } else if (flag == 1){
                    midtotal = midtotal * 2;
                }
            }
            d ++;
        }
        d = 0;
        c ++;
    }
    total = total + midtotal;
    return total;
}

int main(){

    unsigned int sum = 0;
    char line[1024];
    int counter;
    int wincounter;

    //As of now hard coded array sizes, could generalize by parsing the input further.
    long cardNums[9];
    long winningNums[25];

    //File needs to be padded with a line BEFORE data entries
    FILE *f = fopen("<your-filepath-here>","r");
    while (fgets(line, sizeof(line), f)) {
        fscanf(f, "%[^\n]", line);

        counter = 0;
        wincounter = 0;

        char *p = line;
        while (*p) { // Loops until no more characters to process through
            if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p + 1)))) {
                // Input has a number
                long val = strtol(p, &p, 10); // Get the number
                if (counter > 0 && counter <= 10){
                    cardNums[counter-1] = val;
                    counter ++;
                } else if (counter > 10){
                    winningNums[wincounter] = val;
                    wincounter ++;
                } else counter ++;
                printf("%ld ", val);
            } else { // No numeral found, moving to next one.
                p++;
            }
        }
        sum = sum +arrayCompare(cardNums, winningNums);
        printf("| Sum of all total wins: %u\n",sum);
    }
    fclose(f);
    return 0;
}
