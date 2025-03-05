
#ifndef MP2_H
#define MP2_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LETTER 20 // Max length for words
#define MAX_PAIRS 10  // Max language-translation pairs per entry
#define MAX_ENTRY 150 // Max dictionary entries

typedef char Str20[MAX_LETTER + 1]; // String type (20 characters + null terminator)

// Structures
typedef struct translationPairTag
{ // holds pair for word
  Str20 lang; 
  Str20 trans;
} translationPairType;

typedef struct entryTag
{ // holds each word
  translationPairType pair[MAX_PAIRS];
  int pairCount; // how many translation pair there is in an entry
} entryType;

char getChoice(char choice);
void toLowerString(char *str);
void inputWord(char sentence[]);
void updateLanguageTranslationPair(entryType *entry, Str20 language, Str20 translation);
void showEntries(entryType entries[], int matchedIndexes[], int matchCount);
int isDuplicate(entryType entries[], int countEntry, Str20 language, Str20 translate, int matchedIndexes[]); //Can be revised into isDuplicateLangTransPair
void getLanguageTranslation(Str20 language, Str20 translation);
void addEntry(entryType *entries, int *countEntry);
void addTranslation(entryType *entries, int *countEntry);
void displayAllEntries(entryType entry[], int countEntry);
void deleteEntry(entryType entries[], int *countEntry);
int displayMainMenu();

#include "MP2.c"
#endif
