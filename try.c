#include <stdio.h>
#include <string.h>

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

/*
  Visualization:

  entries[0]:
   //entryType[0].pairs[0] +-- English -> love
   //entryType[0].pairs[1] +-- Tagalog -> mahal
   //entryType[0].pairs[2] +-- Spanish -> amor
   //entryType[0].pairs[3] +-- Hiligaynon -> gugma

   //entryType[0].count = 4

  entries[1]:
   //entryType[1].pairs[0] +-- English -> expensive
   //entryType[1].pairs[1] +-- Tagalog -> mahal
   //entryType[1].pairs[2] +-- Kapampangan -> mal

   //entryType[1].count = 3
*/

// Functions

void showEntries(entryType entries[], int matchedIndexes[], int matchCount)
{
  int i, j;
  for (i = 0; i < matchCount; i++)
  {
    entryType *entry = &entries[matchedIndexes[i]];
    printf("Entry %d:\n", matchedIndexes[i]);

    for (j = 0; j < entry->pairCount; j++)
    {
      printf("Langauge:%s\tTranslation:%s\n", entry->pair[j].lang, entry->pair[j].trans);
    }
  }
}

int entryExists(entryType entries[], int countEntry, Str20 language, Str20 translate, int matchedIndexes[])
{
  int matchCount = 0;
  int foundLang = 0, foundTrans;
  for (int i = 0; i < countEntry; i++) // checks index for each entry
  {
    for (int j = 0; j < entries[i].pairCount; j++) // Checks each pair of translation for that entry
    {
      foundLang = strcmp(entries[i].pair[j].lang, language);
      foundTrans = strcmp(entries[i].pair[j].trans, translate);
      if (!foundLang && foundTrans) // BRUTE FIRE FORCE VIA LINEAR SEARCH
      {
        matchedIndexes[matchCount++] = i; // Store the index of the entry that contains the lang-trans pair
      }
    }
  }
  return matchCount; // No match found
}

/*
 * getEntry - Adds a new word with its first language-translation pair.
 *
 * This function checks if an entry with the same language-translation pair
 * already exists. If found, it displays matching entries and asks if a new
 * entry should be created. If confirmed, a new entry is added, and the user
 * can input more translations until they choose to stop.
 *
 * Constraints:
 * - Each entry can store up to MAX_PAIRS (10) translations.
 * - Both language and translation must have at least one character.
 * - No more than MAX_ENTRY (150) entries can be stored.
 *
 * @param entries[] - Array storing all existing entries. Initialized in Main Function.
 * @param countEntry - Number of entries in the dictionary.
 */

int addEntry(entryType entries[], int *countEntry)
{
  int entryFlag = 0;
  int matchedIndexes[MAX_ENTRY] = {0};
  int matchCount = 0;
  Str20 language, translate; // temporary sting to store the input

  // Starting from this line to line 131, it should be inside a while loop wherein the 
  // user will be asked if they still want to add another translation pair or not
  if (*countEntry >= MAX_ENTRY)
  { // check if max entry concept count has been reached
    printf("Cannot add more entries. Dictionary is full!\n");
    entryFlag = -1; // fail to add since max has been reached
  }
  else
  {
    printf("Enter language: ");
    scanf("%s", language);
    printf("Enter translation: ");
    scanf("%s", translate);

    // Check if the language-translation pair already exists
    matchCount = entryExists(entries, countEntry, language, translate, matchedIndexes);

    if (matchCount > 0)
    {
      printf("A word in this language already exists!\n");
      showEntries(entries, matchedIndexes, matchCount);
      entryFlag = 0; // word exists
    }
    else
    {
      // Make a new entry
      entryType *entry = &entries[*countEntry]; // make a pointer directly to the correct Index we are adding the new bitchass word and language

      strcpy(entry->pair[0 /*gawin mo tong i*/].lang, language);
      strcpy(entry->pair[0  /*gawin mo tong i*/].trans, translate);
      entry->pairCount = 1;
      /*lagay ka dito increment of i*/
    }

    (*countEntry)++; // Increase total entries count
    printf("New entry added successfully!\n");
    entryFlag = 1; // success
  }

  return entryFlag;
}

int displayMainMenu()
{
  int choice;
  do
  {
    printf("\n===== MAIN MENU =====\n");
    printf("1. Put a new word\n");
    printf("2. Display (Not yet implemented)\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1)
    {
      while (getchar() != '\n')
        ; // Clear input buffer
      printf("Invalid input! Please enter a number between 1 and 3.\n");
      choice = 0;
    }
    else if (choice < 1 || choice > 3)
    {
      printf("Invalid choice! Please enter a number between 1 and 3.\n");
    }

  } while (choice < 1 || choice > 3);

  return choice;
}

int main()
{
  entryType entry[MAX_ENTRY];
  int countEntry = 0;

  // Initialize test data
  // Entry 0: Translations related to "love" and "hate"
  strcpy(entry[0].pair[0].lang, "English");
  strcpy(entry[0].pair[0].trans, "love");
  strcpy(entry[0].pair[1].lang, "Tagalog");
  strcpy(entry[0].pair[1].trans, "mahal");
  strcpy(entry[0].pair[2].lang, "Spanish");
  strcpy(entry[0].pair[2].trans, "amor");
  strcpy(entry[0].pair[3].lang, "English");
  strcpy(entry[0].pair[3].trans, "hate");
  entry[0].pairCount = 4;
  /*
  Alternative for manually computing for the pairCount 
  sizeof(entry[0].pairs) / sizeof(entry[0].pairs[0]);
  printf("Total pairs in entry[0]: %d\n", pairCount);
  */
 
  // Entry 1: Translations for "happy"
  strcpy(entry[1].pair[0].lang, "English");
  strcpy(entry[1].pair[0].trans, "happy");
  strcpy(entry[1].pair[1].lang, "Tagalog");
  strcpy(entry[1].pair[1].trans, "masaya");
  strcpy(entry[1].pair[2].lang, "Spanish");
  strcpy(entry[1].pair[2].trans, "feliz");
  strcpy(entry[1].pair[3].lang, "French");
  strcpy(entry[1].pair[3].trans, "heureux");
  entry[1].pairCount = 4;

  // Entry 2: Translations for "beautiful"
  strcpy(entry[2].pair[0].lang, "English");
  strcpy(entry[2].pair[0].trans, "beautiful");
  strcpy(entry[2].pair[1].lang, "Tagalog");
  strcpy(entry[2].pair[1].trans, "maganda");
  strcpy(entry[2].pair[2].lang, "Spanish");
  strcpy(entry[2].pair[2].trans, "hermosa");
  strcpy(entry[2].pair[3].lang, "Italian");
  strcpy(entry[2].pair[3].trans, "bella");
  entry[2].pairCount = 4;

  // Entry 3: Translations for "strong"
  strcpy(entry[3].pair[0].lang, "English");
  strcpy(entry[3].pair[0].trans, "strong");
  strcpy(entry[3].pair[1].lang, "Tagalog");
  strcpy(entry[3].pair[1].trans, "malakas");
  strcpy(entry[3].pair[2].lang, "Japanese");
  strcpy(entry[3].pair[2].trans, "tsuyoi");
  strcpy(entry[3].pair[3].lang, "German");
  strcpy(entry[3].pair[3].trans, "stark");
  entry[3].pairCount = 4;

  // Entry 4: Translations for "fast"
  strcpy(entry[4].pair[0].lang, "English");
  strcpy(entry[4].pair[0].trans, "fast");
  strcpy(entry[4].pair[1].lang, "Tagalog");
  strcpy(entry[4].pair[1].trans, "mabilis");
  strcpy(entry[4].pair[2].lang, "Spanish");
  strcpy(entry[4].pair[2].trans, "rápido");
  strcpy(entry[4].pair[3].lang, "Korean");
  strcpy(entry[4].pair[3].trans, "ppalli");
  entry[4].pairCount = 4;

  // Entry 5: Translations for "love"
  strcpy(entry[5].pair[0].lang, "English");
  strcpy(entry[5].pair[0].trans, "love");
  strcpy(entry[5].pair[1].lang, "Tagalog");
  strcpy(entry[5].pair[1].trans, "mahal");
  strcpy(entry[5].pair[2].lang, "Spanish");
  strcpy(entry[5].pair[2].trans, "amor");
  strcpy(entry[5].pair[3].lang, "English");
  strcpy(entry[5].pair[3].trans, "hate");
  entry[5].pairCount = 4;

  countEntry = 6; // Total number of entries added

  int choice;
  do
  {
    choice = displayMainMenu();
    switch (choice)
    {
    case 1:
      addEntry(entry, &countEntry);
      break;
    case 2:
      printf("Feature not yet implemented.\n");
      break;
    case 3:
      printf("Exiting program...\n");
      break;
    default:
      printf("Invalid choice! Try again.\n");
    }
  } while (choice != 3);

  return 0;
}
