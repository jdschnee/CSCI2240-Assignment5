 /* 
 * File:   jschnee.h
 * Author: Joshua Schnee
 *
 * Created on November 7, 2020, 10:01 AM
 */

#ifndef JSCHNEE_H
#define JSCHNEE_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define DELIM " .,/!?\r\n"
#define BUFF_MAX 1000
#define WORDS_MAX 200
#define WORD_MAX 31

//struct that will be used to create an array of Words and keep track of the number of duplicate occurrences of the same word.
typedef struct Word {
    char word[WORD_MAX];
    unsigned occurrences;
} Word, *WordP;

void initializeOccurrences(Word *Words);
void tokenize(char *ln, Word *TokenWord, unsigned *uniqueCount);
void orderWords(Word *NonAlpha, const unsigned SZ);
void output(Word *Alpha, unsigned SZ, FILE *aHandler);

#endif /* JSCHNEE_H */

