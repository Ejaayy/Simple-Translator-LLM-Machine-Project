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
void displayAllEntries(entryType entry[], int countEntry)
{
  int i, j;
  for (i = 0; i < countEntry; i++) // loops for all match count (same entry)
  {
    printf("Entry %d:\n", i + 1);

    for (j = 0; j < entry[i].pairCount; j++) // prints members of that entry
    {
      printf("Langauge: %-15s Translation: %s\n", entry[i].pair[j].lang, entry[i].pair[j].trans);
    }
    
    printf("\n"); // Add a newline for readability
  }
}
void deleteEntry(entryType entries[], int *countEntry)
{
    int selectedIndex;
    int validIndex = 1;
    int i;

    // Display all current entries before asking which one to delete
    displayAllEntries(entries, *countEntry);


	printf("Enter the entry number to delete (1-%d): ", *countEntry);
	scanf("%d", &selectedIndex);    
	
	if (selectedIndex < 1 || selectedIndex > *countEntry)
	{
	    printf("Invalid entry number! Redirecting back to Manage Data Menu.\n");
	    validIndex = 0; // Stay in the loop
	}
	else
	{
		validIndex = 1;	
	} 

    if (validIndex)
    {
	    // Convert 1-based index to 0-based index
	    selectedIndex--;
	
	    // Shift the entries left to remove the selected entry
	    for (i = selectedIndex; i < *countEntry - 1; i++)
	    {
	        entries[i] = entries[i + 1]; // Overwrite current entry with the next entry
	    }
	
	    // Reduce the entry count
	    (*countEntry)--;
	
	    printf("Entry deleted successfully!\n");
    }
}

void deleteTranslation(entryType *entries, int *countEntry)
{
	// Display all current entries before asking which one to delete
    displayAllEntries(entries, *countEntry);

    do 
	{
	    printf("Enter the entry number to delete (1-%d): ", *countEntry);
	    scanf("%d", &selectedIndex);    
	
	    if (selectedIndex < 1 || selectedIndex > *countEntry)
	    {
	        printf("Invalid entry number! Please try again.\n");
	        validIndex = 0; // Stay in the loop
	    }
	    else
	    {
	        validIndex = 1; // Exit the loop when input is valid
	    }
	} while (!validIndex);
    
    // Convert 1-based index to 0-based index
    selectedIndex--;
    
    do 
	{
	    printf("Enter the pair number to delete (1-%d): ", entries[selectedIndex].pairCount);
	    scanf("%d", &selectedIndexPair);    
	
	    if (selectedIndexPair < 1 || selectedIndexPair > entries[selectedIndex].pairCount)
	    {
	        printf("Invalid entry number! Please try again.\n");
	        validPairIndex = 0; // Stay in the loop
	    }
	    else
	    {
	        validPairIndex = 1; // Exit the loop when input is valid
	    }
	} while (!validPairIndex);
	selectedIndexPair--;
}

char getChoice(char choice) 
{
    int validChoice = 0;

    while (!validChoice) 
	{
        printf("Please enter 'y' or 'n': ");

        if (scanf(" %c", &choice) == 1) 
		{ // Read character input
            while (getchar() != '\n'); // Clear input buffer

            choice = tolower(choice); // Convert to lowercase
            
            if (choice == 'y' || choice == 'n') 
			{
                validChoice = 1;
            } 
			else 
			{
                printf("Invalid input. ");
            }
        } 
    }
    return choice;
}


void updateLanguageTranslationPair(entryType *entry, Str20 language, Str20 translation)
{
  strcpy(entry->pair[entry->pairCount].lang, language);
  strcpy(entry->pair[entry->pairCount].trans, translation);
  entry->pairCount++;
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
      printf("Language: %-15s Translation: %s\n", entry->pair[j].lang, entry->pair[j].trans);
    }
  }
}

int isDuplicate(entryType entries[], int countEntry, Str20 language, Str20 translate, int matchedIndexes[]) //Can be revised into isDuplicateLangTransPair
{
  int matchPairCount = 0;
  int found, i, j;
  for (i = 0; i < countEntry; i++) // checks index for each entry
  {
    found = 0; // Reset flag for each entry
    for (j = 0; j < entries[i].pairCount; j++) // Checks each pair of translation for that entry
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

void toLowerString(char *str) 
{
    int len = (int)strlen(str);
    int i;

    for (i = 0; i < len; i++) 
	{
        if (str[i] >= 'A' && str[i] <= 'Z') 
		{
            str[i] += 32; // Convert to lowercase
        }
    }
    str[len] = '\0'; // Proper null termination (optional, as it's already there)
}
void inputWord(char sentence[]) 
{
    int i = 0;
    char ch;

    // Skip any leading newline or spaces left in the input buffer
    while ((ch = getchar()) == '\n' || ch == ' ');

    do {
        sentence[i] = ch;  // Store the character in the array
        i++;
        ch = getchar();  // Read the next character
    } while (i < MAX_LETTER && ch != '\n'); // Stop condition
    
    sentence[i] = '\0'; // Null-terminate the string
}

// Function to get language-translation pair
void getLanguageTranslation(char language[], char translation[]) {
    printf("Input for language-translation pair:\n");
    printf("Language: ");
    inputWord(language);  // Get language input
    toLowerString(language) ;
    printf("Translation: ");
    inputWord(translation);  // Get translation input
	toLowerString(translation);
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
    int entryFlag = 1;
    char choice = 'y';
    int matchedIndexes[MAX_ENTRY] = {0};
    int matchCount = 0;
    Str20 language, translation;                                                          // temporary string to store the input

    if (*countEntry >= MAX_ENTRY)                                                         // check if max entry count has been reached
    {
        printf("Cannot add more entries. Dictionary is full!\n");
        entryFlag = 0;
    }
    else
    {
        while (choice == 'y' && entryFlag)                                                //Enter loop while the user wants to add an entry
        {
            getLanguageTranslation(language, translation);                                // input language translation pair
            
                                                                                          // Recalculate matchCount inside the loop (checks against all current entries)
            matchCount = isDuplicate(entries, *countEntry, language, translation, matchedIndexes);

            if (matchCount > 0)                                                           // if an existing pair matches what the user input
            {
                showEntries(entries, matchedIndexes, matchCount);                         // shows all matched entries
                
                printf("This language-translation pair already exists!");                 //Notify the user that it found a similar entry, Asks user if it this is a new entry
				printf("\nIs this a new entry? (y/n): ");
                
                choice = getChoice(choice);
                if (choice == 'n') {                                                      //If user said no, this is not a new entry, exits the loop
                    entryFlag = 0;                         
                }
                else if (choice == 'y') 
				{											      //If user said yes, this is a new entry                    
                    entries[*countEntry].pairCount = 0;                                   // Initialize new pair count for new entry
                    updateLanguageTranslationPair(&entries[*countEntry], language, translation); //update data base
					printf("New entry has been added successfully!\n");
					 													  // Increment countEntry because we added a new pair                 
					while (choice == 'y')												  
					{
						printf("Add another language-translation pair to the current entry? (y/n): ");
                    	choice = getChoice(choice);
                    	if (choice == 'y')
                    	{
                    		getLanguageTranslation(language, translation);
                    		updateLanguageTranslationPair(&entries[*countEntry], language, translation);
                    		printf("New lanugage-translation pair has been added successfully!\n");
                    	}
					}
					(*countEntry)++; 
                }
            }
            else                                                                         // Pair doesn't exist
            {
                printf("This language-translation pair does not exist!\nIs this a new entry? (y/n): ");
                choice = getChoice(choice);                                              // ask user if input is a new entry
                if (choice == 'n') {
                    entryFlag = 0;                                                       // User doesn't want to add a new entry
                }
                else if (choice == 'y') 
				{
                    // User wants to add this new pair
                    entries[*countEntry].pairCount = 0; 
                    updateLanguageTranslationPair(&entries[*countEntry], language, translation);
                    printf("New entry has been added successfully!\n");
                     													  // Increment countEntry because we added a new pair
                    
                    while (choice == 'y')
					{
						printf("Add another language-translation pair to the current entry? (y/n): ");
                    	choice = getChoice(choice);
                    	if (choice == 'y')
                    	{
                    		getLanguageTranslation(language, translation);
                    		updateLanguageTranslationPair(&entries[*countEntry], language, translation);
                    		printf("New lanugage-translation pair has been added successfully!\n");
                    	}
					} 
					(*countEntry)++; 
                }
            }
        }
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
	int entryFlag = 1;
	
    getLanguageTranslation(language, translation);                                         // Prompt the user to enter the language and translation pair to search for

    matchCount = isDuplicate(entries, *countEntry, language, translation, matchedIndexes); // Check if an entry exists with the given language and translation pair
                                                                                           // Store matching entry indexes in matchedIndexes and count in matchCount

    if (matchCount <= 0)                                                                   // If no matching entry is found
    {
        printf("The entry doesn't exist. Would you like to add a new one? (y/n): ");                            // Inform the user that no entry exists
        choice = getChoice(choice);                                                        // Suggest using the Add Entry option

        if (choice == 'y')                                                                 
        {
        	printf("Redirecting you to add entry.\nAdd entry:\n");
            addEntry(entries, countEntry);                                                 // If user answers 'Y', call the addEntry function           // Exit after adding an entry and prevent further logic here
        }
    }
    else                                                                                   // If matching entry was/were found
    {
    	printf("Existing entries has been found:\n");
        showEntries(entries, matchedIndexes, matchCount);                                  // Show all matched entries

        if (matchCount == 1)                                                                // If only one matching entry exists
        {
            if (entries[matchedIndexes[0]].pairCount >= MAX_PAIRS)                         // Check if the entry already has the max number of pairs
            {
                printf("The entry already has the maximum number of pairs.\n");			    // Exit function if the entry has reached its max pairs
                                                               
            }
            else                                                                           // Otherwise, add the new pair to the entry
            {
                getLanguageTranslation(language, translation);                             // Get the new language-translation pair
                updateLanguageTranslationPair(&entries[matchedIndexes[0]], language, translation);  // Update the entry with the new pair
                entries[matchedIndexes[0]].pairCount++;                                    // Update the pair count
            }
        }
        else                                                                                 // If multiple matching entries exist
        {
            do                                                                             
            {
                printf("Enter Entry Number to add translation: ");       // Prompt user to select which entry to update
                scanf("%d", &selectedIndex);                                                // Get the user input for the selected entry
            } while (selectedIndex < 1 || selectedIndex > *countEntry);                      // Validate user input to ensure a valid selection (within the number of matches)

            selectedIndex = matchedIndexes[selectedIndex - 1];                             // Convert 1-based user input to 0-based index

            if (entries[selectedIndex].pairCount >= MAX_PAIRS)                             // Check if the selected entry already has the max number of pairs
            {
                printf("The selected entry already has the maximum number of translation pairs.\n");                                                                   // Exit if the entry has reached its max pairs
            }

            do                                                                             
            {
                getLanguageTranslation(language, translation);                             // Prompt for the new language-translation pair
                updateLanguageTranslationPair(&entries[selectedIndex], language, translation);  // Add the new pair to the selected entry
                entries[selectedIndex].pairCount++;                                        // Update the pair count for the selected entry

                printf("Add another language-translation pair? (y/n): ");                 // Ask the user if they want to add another pair
                choice = getChoice(choice);                                                 // Get the user's choice
            } while (choice == 'y' && entries[selectedIndex].pairCount < MAX_PAIRS);        // Loop to add more translations, but prevent adding if the max count is reached
        }
    }
}

int displayMainMenu()
{
  int choice;
  do
  {
    printf("\n===== MAIN MENU =====\n");
    printf("1. Put a new entry\n");
    printf("2. Add a new Translation\n");
    printf("3. Display all Entries\n");
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
