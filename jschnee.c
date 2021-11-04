/* 
 * File:   jschnee.h
 * Author: Joshua Schnee
 *
 * Created on November 7, 2020, 10:01 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "jschnee.h"

/*
*FUNCTION NAME: initializeOccurrences
*DESCRIPTION: This function initializes all of the Word structs with a initial occurance of 0
*INPUT: This function takes an array of Word structs
*RETURN: This function returns nothing.
*OUTPUT: This function outputs nothing
*/
void initializeOccurrences(Word *Words) {
    for (int i = 0; i < WORDS_MAX; i++) {
        Words[i].occurrences = 0;
    }
}

/*
*FUNCTION NAME: tokenize
*DESCRIPTION: This function gets rid of all delimiters and saves non duplicate words into the array of structs called Words. 
 Also, if there is a duplicate then this function add one to the occurrence for every duplicate that it encounters. Last this
 function increases the unique word count when it encounters a new word and uses this value as an index for the array of structs.
*INPUT: This function takes a single line from the input file, an array of Word structs, and the variable that keeps track of the
 number of unique or non-duplicate words.
*RETURN: This function returns nothing.
*OUTPUT: This function outputs nothing
*/
void tokenize(char *ln, Word *TokenWord, unsigned *uniqueCount) {
    char *piece = strtok(ln, DELIM);

    if (piece == NULL) return;
    
    for(int i = 0; piece[i]; i++) piece[i] = tolower(piece[i]);
    
    enum REP_WORD {
        NON_DUP, DUP
    } WORD;

    for (unsigned i = 0; i < *uniqueCount; i++) {
        if (strcmp(piece, TokenWord[i].word) == 0) {
            TokenWord[i].occurrences++;
            WORD = DUP;
            break;
        }
    }

    if (WORD != DUP) {
        TokenWord[*uniqueCount].occurrences++;
        strncpy(TokenWord[(*uniqueCount)++].word, piece, WORD_MAX);
    }

    while ((piece = strtok(NULL, DELIM)) != NULL) {
        WORD = NON_DUP;
        
        for(int i = 0; piece[i]; i++) piece[i] = tolower(piece[i]);

        for (unsigned i = 0; i < *uniqueCount; i++) {
            if (strcmp(piece, TokenWord[i].word) == 0) {
                TokenWord[i].occurrences++;
                WORD = DUP;
                break;
            }
        }
        
        if (WORD == DUP) continue;
        
        TokenWord[*uniqueCount].occurrences++;
        strncpy(TokenWord[(*uniqueCount)++].word, piece, WORD_MAX);
    }
}

/*
*FUNCTION NAME: orderWords
*DESCRIPTION: This function takes the array of structs which is a collection of all the unique words along with their occurances
 and places these Words in ascending or alphabetical order.
*INPUT: This function takes the array of Word structs. The non-duplicate words that have been collected. Also, this function takes
 the size of the array or in other words the number of non-duplicate words. NO PUN INTENDED ;)
*RETURN: This function returns nothing.
*OUTPUT: This function outputs nothing
*/
void orderWords(Word *NonAlpha, const unsigned SZ) {
    unsigned min;

    for (unsigned i = 0; i < SZ - 1; i++) {
        min = i;
        
        for (unsigned j = i + 1; j < SZ; j++) {
            if (strcmp(NonAlpha[j].word, NonAlpha[min].word) < 0) {
                min = j;
            }
        }
        
        if (i != min) {
            Word Temp;
            
            strncpy(Temp.word, NonAlpha[i].word, WORD_MAX);
            Temp.occurrences = NonAlpha[i].occurrences;
            
            strncpy(NonAlpha[i].word, NonAlpha[min].word, WORD_MAX);
            NonAlpha[i].occurrences = NonAlpha[min].occurrences;
            
            strncpy(NonAlpha[min].word, Temp.word, WORD_MAX);
            NonAlpha[min].occurrences = Temp.occurrences;
        }
    }
}

/*
*FUNCTION NAME: output
*DESCRIPTION: This function outputs the words and the number of times each word occurred but appends it to a in alphabetical order.
*INPUT: This function takes the array of Word structs. The non-duplicate words that have been collected and priorly placed into alphabetical order. Also, this function takes
 the size of the array or in other words the number of non-duplicate words. Last this function takes a file pointer that allows us to append the result to output file.
*RETURN: This function returns nothing.
*OUTPUT: This function outputs the words from the input file in alphabetical order and also lists the number of times each word appeared.
*/
void output(Word *Alpha, unsigned SZ, FILE *aHandler) {
    for (int i = 0; i < SZ; i++) fprintf(aHandler, "%s %u\n", Alpha[i].word, Alpha[i].occurrences);
}