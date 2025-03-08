
#ifndef MP2_H
#define MP2_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LETTER 20 // Max length for words
#define MAX_PAIRS 10  // Max language-translation pairs per entry
#define MAX_ENTRY 150 // Max dictionary entries
#define MAX_WORDS 50 //gawa gawa ko lang

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
void showMatchedEntries(entryType entries[], int matchedIndexes[], int matchCount);
int isDuplicate(entryType entries[], int countEntry, Str20 language, Str20 translate, int matchedIndexes[], int currentEntryIndex); //Can be revised into isDuplicateLangTransPair
void getLanguageTranslation(Str20 language, Str20 translation);
int countEntryIsZero(int countEntry);
void addEntry(entryType *entries, int *countEntry);
void addTranslation(entryType *entries, int *countEntry);
void displayModeAllEntries(entryType entry[], int countEntry);
void deleteEntry(entryType entries[], int *countEntry);
void deleteTranslation(entryType *entries, int *countEntry);
void searchWord(entryType *entries, int countEntry);
void searchTranslation(entryType *entries, int countEntry);
void exportFile(entryType *entries, int countEntry);
void importFile(entryType *entries, int *countEntry);
int exitFunction();
int displayManageDataMenu();
int translateMenu();
int displayMainMenu();

int filterWords(char *textInput, Str20 filteredWords[]);
void printFilteredWords(Str20 filteredWords[], int wordCount);
char* translateWord(entryType entries[], int countEntry, Str20 filteredWord, Str20 sourceLanguage, Str20 outputLanguage);
void translateTextInput(entryType *entries, int countEntry);
#include "MP2.c"
#include "translateFunction.c"
#endif
