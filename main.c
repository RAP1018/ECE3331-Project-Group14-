#include <stdio.h>
#include <stdlib.h> // the allows us to have an exit code if return =1
#include <string.h>
// these headers allow us to do common cammand like print, scan, 
//allows strings and the standard library.

int Match(int const char *pattern, const char *text);
// declaring our function

int main(int x, char *arr[]){
    FILE *fin;
    char line[256]; // i made this as a buffer hold each line from the test file.
    int line_number =0; // counter for the line.

    // we can start to check input for the filename and pattern.
    if(x != 3){
        printf("Usage: %s <filename> <pattern>\n", arr[0]);
        return 1; 
    } // this also allows us to exit the code.

    // Let's open the input file for reading.
    fin = fopen(arr[1], "r");
    if(fin == NULL){
        printf("Error: cannot open file %s\n", arr[1]);
        // We make this to help know if the file can be opened.
        return 1; // we will exit if file is invaild.
    }
// We can assume the file is vaild, now we can read each line of the file.
    while(fget(line, sizeof(line), fin )!= NULL){
        // if these are all vaild.
        line_number++;// count each line.

        // In most general txt files there are \n characters, 
        // we need to remove them in this code so we can overwrite on the lines later on.
        if(line[strlen(line) -1] == '\n'){
            // we need to replace newline with end of line. this also allows us to stop at the end of the line of the phrases.
            line[strlen(line)-1] = '\0'; 
            // We reached the end of the line YAAAY!!
        }
        // Let's check if pattern matches with line.
        if(Match(arr[2], line)){
            // if matches then print line numbers and the line.
            printf("%3d: %s\n", line_number,line);
        }
    }
    // I think now we can close the file.
    fclose(fin);
    return 0; // It should be vaild !!!!!!

}