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
  translationPairType pairs[MAX_PAIRS];
  int count; // how many translation pair there is in an entry
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

void showEntries(entryType entries[], int entryIndex)
{
  int i;
  for (i = 0; i < entries[entryIndex].count; i++)
  {
    printf("Langauge:%s\tTranslation:%s\n", entries[entryIndex].pairs[i].lang, entries[entryIndex].pairs[i].trans);
  }
}

int entryExists(entryType entries[], int countEntry, Str20 language, Str20 translate)
{
  int existFlag = -1;
  for (int i = 0; i < countEntry; i++) // checks index for each entry
  {
    for (int j = 0; j < entries[i].count; j++) // Checks each pair of translation for that entry
    {
      if (strcmp(entries[i].pairs[j].lang, language) == 0 && strcmp(entries[i].pairs[j].trans, translate) == 0) // BRUTE FIRE FORCE VIA LINEAR SEARCH
      {
        existFlag = i; // Found existing entry
      }
    }
  }
  return existFlag; // No match found
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

  if (*countEntry >= MAX_ENTRY)
  { // check if max entry concept count has been reached
    printf("Cannot add more entries. Dictionary is full!\n");
    entryFlag = -1; // fail to add since max has been reached
  }
  else
  {

    Str20 language, translate; // temporary sting to store the input

    printf("Enter language: ");
    scanf("%s", language);
    printf("Enter translation: ");
    scanf("%s", translate);

    // Check if the language-translation pair already exists
    int existingIndex = entryExists(entries, *countEntry, language, translate);

    if (existingIndex != -1)
    {
      printf("A word in this language already exists!\n");
      showEntries(entries, existingIndex);
      entryFlag = 0; // word exists
    }
    else
    {
      // Make a new entry
      entryType *entry = &entries[*countEntry]; //make a pointer directly to the correct Index we are adding the new bitchass word and language
      
      strcpy(entry->pairs[0].lang, language);
      strcpy(entry->pairs[0].trans, translate);
      entry->count = 1;

      (*countEntry)++; // Increase total entries count
      printf("New entry added successfully!\n");
      entryFlag = 1; // success
    }
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
  strcpy(entry[0].pairs[0].lang, "English");
  strcpy(entry[0].pairs[0].trans, "love");
  strcpy(entry[0].pairs[1].lang, "Tagalog");
  strcpy(entry[0].pairs[1].trans, "mahal");
  strcpy(entry[0].pairs[2].lang, "Spanish");
  strcpy(entry[0].pairs[2].trans, "amor");
  strcpy(entry[0].pairs[3].lang, "English");
  strcpy(entry[0].pairs[3].trans, "hate");
  entry[0].count = 4;
  countEntry = 1;

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
