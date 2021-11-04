/* 
 * File:   main.c
 * Author: Joshua Schnee
 *
 * Created on November 6, 2020, 1:22 PM
 */
#include "jschnee.h"

/*
*FUNCTION NAME: main
*DESCRIPTION: This function takes an input file and output file as command line arguments. It takes the input file and alphabetizes all of the words and lists them in the 
 output file in order along with the number of times each word occurred.
*INPUT: This function takes two command line arguments. The first argument is the number of command line arguments that have been input and for this program we will be looking
 for three. The next argument is an array that contains the actual arguments. The first index is the name of the file path. The second index being the input file name that we 
 will be reading from. The third being the output file name that we will create and append to.
*RETURN: This function returns an integer that signals whether the program has ran successfully.
*OUTPUT: This function outputs the words from the input file in alphabetical order and also lists the number of times each word appeared.
*/
int main(int argc, char const *argv[]) {
    Word Words[WORDS_MAX];
    initializeOccurrences(Words);
    FILE *rHandler, *wHandler, *aHandler;
    char buffer[BUFF_MAX] = {0};
    unsigned uniqueTotal = 0;


    if (argc != 3) {
        fprintf(stderr, "Usage: %s <FILE-PATH>\n", argv[0]);
        fprintf(stderr, "Invalid Number of Arguments: (Both one pre-existing input .txt file and one output .txt file name to be generated is required)\n");
        return EXIT_FAILURE;
    }

    if ((rHandler = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "Error in opening %s\n", argv[1]);
        return (EXIT_FAILURE);
    }

    if ((wHandler = fopen(argv[2], "w")) == NULL) {
        fprintf(stderr, "Error in creating or overwriting %s\n", argv[2]);
        return (EXIT_FAILURE);
    }

    if ((aHandler = fopen(argv[2], "a")) == NULL) {
        fprintf(stderr, "Error in creating %s\n", argv[2]);
        return (EXIT_FAILURE);
    }

    while ((fgets(buffer, BUFF_MAX, rHandler)) != NULL) tokenize(buffer, Words, &uniqueTotal);
    
    orderWords(Words, uniqueTotal);
    output(Words, uniqueTotal, aHandler);

    return (EXIT_SUCCESS);
}