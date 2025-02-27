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
void addTranslation(entryType *entries, int *countEntry)
{
  char choice = 'y';
  int matchedIndexes[MAX_ENTRY] = {0};
  int matchCount = 0;
  Str20 language, translation;
  int selectedIndex = 0;
  int i;

  getLanguageTranslation(language, translation); // Prompt the user to enter the language and translation pair to search for

  matchCount = isDuplicate(entries, countEntry, language, translation, matchedIndexes); // Check if an entry exists with the given language and translation
  // Store matching entry indexes in matchedIndexes and count in matchCount

  if (!matchCount) // If no matching entry is found
  {
    printf("The entry doesn't exist.\nAdd entry? (y/n): "); // Inform the user that no entry exists
    choice = getChoice(choice);                             // Suggest using the Add Entry option

    if (choice == 'y')
    {
      addEntry(entries, countEntry); // Call the addEntry function
    }
    else
    {
      return; // exit the function (but needs to be changed)
    }
  }
  else // if matching entry was/were found
  {
    showEntries(entries, matchedIndexes, matchCount); // Display all matched entries

    if (matchCount == 1) // If only one matching entry exists
    {
      if (entries[matchedIndexes[0]].pairCount >= MAX_PAIRS)
      {
        printf("The entry has already the max number of pairs.\n");
        return; // exit the function (but needs to be changed)
      }
      else // add that to the entry
      {
        updateLanguageTranslationPair(&entries[matchedIndexes[0]], language, translation);
      }
    }
    else // Else if multiple matching entries exist
    {
      do
      {
        printf("Tangina mo anong entry number gusto mo iadd sa new translation (1-%d)", matchCount); // Ask the user to select which entry to update
        scanf("%d", &selectedIndex);
      } while (selectedIndex < 1 || selectedIndex > matchCount); // Validate user input to ensure a valid selection

      selectedIndex = matchedIndexes[selectedIndex - 1]; // convert user input to actual index

      // check if the selected entry has space for more translations
      // If the entry already has the maximum number of translation pairs
      if (entries[selectedIndex].pairCount >= MAX_PAIRS)
      {
        printf("The selected entry already has the maximumm number of translation pairs.\n");
        return; // Inform the user and exit the function
      }
      else
      {
        do
        {
          getLanguageTranslation(language, translation);
          updateLanguageTranslationPair(&entries[selectedIndex], language, translation);

          printf("Add language-translation pair? (y/n): ");
          choice = getChoice(choice);
        } while (choice == 'y');
      }
    }
  }
  // loop to add multiple translations
  //  Prompt the user to enter the new language and translation pair

  // Add the new language-translation pair to the selected entry
  // Increment the pair count for that entry

  // Inform the user that the translation was added successfully
  // Ask the user if they want to add another translation
}

char getChoice(char choice)
{
  scanf(" %c", &choice);
  tolower(choice);
  return choice;
}

updateLanguageTranslationPair(entryType *entry, Str20 language, Str20 translation)
{
  strcpy(entry->pair[entry->pairCount].lang, language);
  strcpy(entry->pair[entry->pairCount].trans, translation);
  entry->pairCount++; // update the pair count
}

void showEntries(entryType entries[], int matchedIndexes[], int matchCount)
{
  int i, j;
  for (i = 0; i < matchCount; i++) // loops for all match count (same entry)
  {
    entryType *entry = &entries[matchedIndexes[i]]; // prints all the matched index
    printf("Entry %d:\n", matchedIndexes[i] + 1);

    for (j = 0; j < entry->pairCount; j++) // prints members of that entry
    {
      printf("Langauge:%s\tTranslation:%s\n", entry->pair[j].lang, entry->pair[j].trans);
    }
  }
}

int isDuplicate(entryType entries[], int countEntry, Str20 language, Str20 translate, int matchedIndexes[]) //Can be revised into isDuplicateLangTransPair
{
  int matchPairCount = 0;
  int found;
  for (int i = 0; i < countEntry; i++) // checks index for each entry
  {
    found = 0; // Reset flag for each entry
    for (int j = 0; j < entries[i].pairCount; j++) // Checks each pair of translation for that entry
    {
      if (!strcmp(entries[i].pair[j].lang, language) && !strcmp(entries[i].pair[j].trans, translate)) // BRUTE FIRE FORCE VIA LINEAR SEARCH
      {
        if(!found)
        {
          matchedIndexes[matchPairCount++] = i; // Store the index of the entry that contains the lang-trans pair
          found = 1; //Set flag to prevent counting this entry again
        }
      }
    }
  }
  return matchPairCount; // No match found
}

void getLanguageTranslation(Str20 language, Str20 translation)
{
  do
  {
    printf("Input for language-translation pair:\n");
    printf("Enter language: ");
    scanf("%s", language);
    printf("Enter translation: ");
    scanf("%s", translation);
  } while (!strlen(language) && !strlen(translation)); // loop while language and translation each doesn't have at least 1 character
}

/*
 * addEntry - Adds a new word with its first language-translation pair.
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

void addEntry(entryType *entries, int *countEntry)
{
  char choice = 'y';
  int matchedIndexes[MAX_ENTRY] = {0};
  int matchCount = 0;
  int entryFlag = 1;
  Str20 language, translation; // temporary string to store the input

  if (*countEntry >= MAX_ENTRY) // check if max entry concept count has been reached
  {
    printf("Cannot add more entries. Dictionary is full!\n");
    entryFlag = 0;
  }
  else
  {
    while (choice == 'y' && entryFlag)
    {
      getLanguageTranslation(language, translation);

      // Make a new entry
      entryType *entry = &entries[*countEntry]; // make a pointer directly to the correct Index we are adding the new bitchass word and language

      // check if max pairs in that entry has been reached
      if (entry->pairCount >= MAX_PAIRS)
      {
        printf("This entry already has the maximum number of translation pairs!");
        entryFlag = 0;
      }

      // if not, contrinue to add the new pair
      else
      {
        // Check if the language-translation pair already exists and saves the index of same entry in matchedIndexes
        matchCount = isDuplicate(entries, countEntry, language, translation, matchedIndexes);

        if (matchCount > 0)
        {
          showEntries(entries, matchedIndexes, matchCount);
          printf("This language-translation pair already exists!\nIs this a new entry? (y/n): ");
          choice = getChoice(choice);
          if (choice == 'n')
            entryFlag = 0;
        }

        // if user wants to continue adding a new translation pair to that entry
        if (choice == 'y')
        {
          updateLanguageTranslationPair(entries, language, translation);
          printf("Add language-translation pair? (y/n): ");
          choice = getChoice(choice);
        }
      }
    }
  }
  if (entryFlag) // checks if the user did not
  {
    (*countEntry)++; // increment total entries count
    printf("New entry added successfully!\n");
  }
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

  countEntry = 151; // Total number of entries added

  int choice;
  do
  {
    choice = displayMainMenu();
    switch (choice)
    {
    case 1:
      printf("Manage Data Menu.\n");
      addEntry(entry, &countEntry);
      break;
    case 2:
      printf("Translate Menu\n");
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
//Change the argument to a specific struct only, not the whole struct of the MP 
