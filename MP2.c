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
char getChoice(char choice)
{
  scanf(" %c", &choice);
  tolower(choice);
  return choice;
}

void updateLanguageTranslationPair(entryType *entry, Str20 language, Str20 translation)
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
        matchCount = isDuplicate(entries, *countEntry, language, translation, matchedIndexes);

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

void addTranslation(entryType *entries, int *countEntry)
{
  char choice = 'y';
  int matchedIndexes[MAX_ENTRY] = {0};
  int matchCount = 0;
  Str20 language, translation;
  int selectedIndex = 0;
  int i;

  getLanguageTranslation(language, translation);                                         // Prompt the user to enter the language and translation pair to search for

  matchCount = isDuplicate(entries, *countEntry, language, translation, matchedIndexes);  // Check if an entry exists with the given language and translation
                                                                                         // Store matching entry indexes in matchedIndexes and count in matchCount

  if (!matchCount)                                                                       // If no matching entry is found
  {
    printf("The entry doesn't exist.\nAdd entry? (y/n): ");                              // Inform the user that no entry exists
    choice = getChoice(choice);                                                          // Suggest using the Add Entry option

    if (choice == 'y')                                                                    
    {
      addEntry(entries, countEntry);                                                     // if user answers 'Y', Call the addEntry function
    }
    else 																				 // else, exit the function (but needs to be changed)                
    {
      return;                                                                                             
    }
  }
  else                                                                                   // But if matching entry was/were found
  {
    showEntries(entries, matchedIndexes, matchCount);                                    // Display all matched entries

    if (matchCount == 1 )                                                                // If only one matching entry exists
    {
      if (entries[matchedIndexes[0]].pairCount >= MAX_PAIRS)							
      {
        printf("The entry has already the max number of pairs.\n");
        return;                                                                          
      }
      else                                                                               // Else add that to the entry
      {
        updateLanguageTranslationPair(&entries[matchedIndexes[0]], language, translation);
      }
    }
    else                                                                                 // Else if multiple matching entries exist
    {
      do                                                                                
      {
        printf("Enter Entry Number to add translation: (1-%d)", matchCount);             // Ask the user to select which entry to update
        scanf("%d", &selectedIndex);
      } while (selectedIndex < 1 || selectedIndex > matchCount);                         // Validate user input to ensure a valid selection

      selectedIndex = matchedIndexes[selectedIndex - 1];                                 // convert user input to actual index

      if (entries[selectedIndex].pairCount >= MAX_PAIRS)                                 // Check if the entry already has the maximum number of translation pairs
      {
        printf("The selected entry already has the maximumm number of translation pairs.\n");
        return;                                                                
      }
      else                                                                               
      {
        do																			     //loop to add multiple translations
        {
          getLanguageTranslation(language, translation);							     //  Prompt the user to enter the new language and translation pair
          updateLanguageTranslationPair(&entries[selectedIndex], language, translation); // Add the new language-translation pair to the selected entry

          printf("Add language-translation pair? (y/n): ");   							 // Ask the user if they want to add another translation
          choice = getChoice(choice);
        } while (choice == 'y');
      }
    }
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

