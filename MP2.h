/********************************************************************************************************* 
This is to certify that this project is our work, based on our personal efforts in studying and applying the concepts 
learned. We have constructed the functions and their respective algorithms and corresponding code by ourselves. The 
program was run, tested, and debugged by our own efforts. We further certify that we have not copied in part or whole or 
otherwise plagiarized the work of other students and/or persons.
																Edriene James A. Paingan, DLSU ID# 12413984
																Marc Andre M. Santos, DLSU ID# 12413844
*********************************************************************************************************/

#ifndef simpleTranslator_H
#define simpleTranslator_H

#include <stdio.h>
#include <string.h>
#include <strings.h> // Include to make use of function strcasecmp();
#include <conio.h> // Include to make use of function getch();
#include <ctype.h> // Include to make use of function toupper();

#define MAX_LETTER 20 // Max length for language and translation
#define MAX_PAIRS 10  // Max language-translation pairs per entry
#define MAX_ENTRY 150 // Max dictionary entries
#define MAX_CHARACTERS 150 // Max characters inputted in translate text file
#define MAX_WORDS 75 // Max words in text input
#define MAX_FILENAME 30 

#define GREEN "\x1B[32m" //code for green
#define RED "\033[31m" // code for red 
#define RESET "\x1B[0m" // Resets the color to default

typedef char Str20[MAX_LETTER + 1]; // String type mainly for language and translation strings (20 characters + null terminator)
typedef char Str30[MAX_FILENAME + 1]; // String type mainly for file name strings (30 characters + null terminator)

// A blueprint (called structure) for different language translation pairs
typedef struct translationPairTag
{
	Str20 lang;
	Str20 trans;
} translationPairType;

// A blueprint (called structure) for different entries
typedef struct entryTag
{
	translationPairType pair[MAX_PAIRS]; // Array of language-translation pair structure (max of 10 pairs)
	int pairCount; // Count of existing pairs in an entry
} entryType;

// Function prototpyes for manageData.c
char getChoice();
void updateLanguageTranslationPair(entryType *entry, Str20 language, Str20 translation);
void showMatchedEntries(entryType entries[], int matchedIndexes[], int matchCount, Str20 translationInput, Str20 languageInput);
int isDuplicate(entryType entries[], int countEntry, Str20 language, Str20 translate, int matchedIndexes[], int currentEntryIndex);
void inputString(char sentence[], int MAX, char prompt[]);
void getLanguageTranslation(char language[], char translation[]);
int countEntryIsZero(int countEntry);
void sortEntry(entryType *entry, int countEntry);
void addEntry(entryType *entries, int *countEntry);
void addTranslation(entryType *entries, int *countEntry);
void displayAllEntries(entryType entry[], int countEntry);
void displayUpdatedEntry(entryType entry, int entryNumber);
void deleteEntry(entryType entries[], int *countEntry);
void deleteTranslation(entryType *entries, int *countEntry);
void searchWord(entryType *entries, int countEntry);
void searchTranslation(entryType *entries, int countEntry);
void exportFile(entryType *entries, int countEntry);
int importFile(entryType *entries, int *countEntry, char prompt[]);
int exitFunction(entryType *entries, int *countEntry);
int manageDataMenu();
int translateMenu();
int mainMenu();

// Function prototpyes for translateFunction.c
int filterWords(char *textInput, Str20 filteredWords[]);
void printFilteredWords(Str20 filteredWords[], int wordCount);
void translateWord(entryType entries[], int countEntry, Str20 filteredWord, Str20 sourceLanguage, Str20 outputLanguage, Str20 translatedWord);
void translateTextInput(entryType *entries, int countEntry);
void translateSentence(entryType entries[], int countEntry, char *sentence, char sourceLanguage[], char outputLanguage[], char *translatedSentence);
void translateTextFile(entryType *entries, int countEntry);

// Included C source file that utilizes this header file
#include "manageData.c"
#include "translateFunction.c"
#endif
