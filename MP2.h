#ifndef MP2_H
#define MP2_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_ENTRY 150
#define MAX_PAIRS 10

typedef char Str20[21];

typedef struct {
    Str20 lang;
    Str20 trans;
} pairType;

typedef struct {
    pairType pair[MAX_PAIRS];
    int pairCount;
} entryType;

char getChoice(char choice);
void updateLanguageTranslationPair(entryType *entry, Str20 language, Str20 translation);
void showEntries(entryType entries[], int matchedIndexes[], int matchCount);
int isDuplicate(entryType entries[], int countEntry, Str20 language, Str20 translate, int matchedIndexes[]);
void getLanguageTranslation(Str20 language, Str20 translation);
void addEntry(entryType *entries, int *countEntry);
void addTranslation(entryType *entries, int *countEntry);
int displayMainMenu();

#include "MP2.c"
#endif
