#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

//"Borrowed": https://stackoverflow.com/questions/1068849/how-do-i-determine-the-number-of-digits-of-an-integer-in-c
int numPlaces (int n) {
    if (n < 0) n = (n == INT_MIN) ? INT_MAX : -n;
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    else return 0;
}

int main() {

    unsigned int sum = 0;
    int flag = 0;
    long temp;

    char line[1024];
    FILE *f = fopen("<your-filepath-here>","r");
    while (fgets(line, sizeof(line), f)) {
        fscanf(f, "%[^\n]", line);
        printf("%s\n", line);

        long asum = 0;
        flag = 0;

        char *p = line;
        while (*p) { // Loops until no more characters to process through
            if (isdigit(*p) || ((*p == '-' || *p == '+') && isdigit(*(p + 1)))) {
                // Input has a number
                long val = strtol(p, &p, 10); // Get the number

                if (flag == 0){
                    temp = val;


                    // Get the first part of the number in case it happens to be more than 2 digits in base 10
                    while(temp >= 10)
                    {
                        temp = temp / 10;
                    }

                    flag = 1;
                }
                //Relics of old, incorrect implementation
                switch (numPlaces(val)) {
                    case 1:
                        asum = asum * 10 + val;
                        break;

                    case 2:
                        asum = asum * 100 + val;
                        break;

                    case 3:
                        asum = asum * 1000 + val;
                        break;

                    case 4:
                        asum = asum * 10000 + val;
                        break;

                    case 5:
                        asum = asum * 100000 + val;
                        break;
                }


            } else {
                // No numeral found, moving to next one.
                p++;
            }
        }
        //Gets the lat numeral of a given integer (might not be just 1!)
        if (numPlaces(asum) != 1){
            temp = temp * 10 + asum % 10;
        }
        else temp = temp * 10 + temp;

        //Some debugging information
        printf("%ld\n",temp);
        sum = sum + temp;
        printf("%u\n",sum);
    }

    fclose(f);
    printf("%u\n",sum);
    return 0;
}
