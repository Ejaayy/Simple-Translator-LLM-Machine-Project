/********************************************************************************************************* 
This is to certify that this project is our work, based on our personal efforts in studying and applying the concepts 
learned. We have constructed the functions and their respective algorithms and corresponding code by ourselves. The 
program was run, tested, and debugged by our own efforts. We further certify that we have not copied in part or whole or 
otherwise plagiarized the work of other students and/or persons.
																Edriene James A. Paingan, DLSU ID# 12413984
																Marc Andre M. Santos, DLSU ID# 12413844
*********************************************************************************************************/
/*
    Description: This function/program allows the user to add entry, add translations, delete entry/ies, delete translation/s
	display all entries, search for a word, search for a language-translation pair, export the database to a file, import data
	from a file, and exit the function/program.
    Programmed by: Marc Andre Santos and Edriene James Paingan, S11B
    Last modified: 03/30/2025
    Version: 1
*/

/*
 * Function Name: getChoice() 
 * Gets a valid user input ('Y' or 'N') and ensures input is clean.
 * @return char - returns either 'Y' or 'N' after validation.
 * Pre-condition: User must enter a single character ('Y' or 'N'). Extra input is discarded.
 */
char getChoice()
{

	
	char choice, 																					
		 trash;	// Variable to hold input buffer
	int validChoice = 0; // Flag to keep the loop of valid inputting

	while (validChoice == 0) // Loop to ensure that the user inputs a valid choice
	{ 

		printf("Enter [Y/N]: ");

		if (scanf(" %c%c", &choice, &trash) == 2 && trash == '\n') // If scanf takes two input (a character and a newline) proceeds to work on the choice
		{
			choice = toupper(choice);

			if (choice == 'Y' || choice == 'N')
			{
				validChoice = 1; // Mark as valid input, exit loop
			}
		}

		if (validChoice == 0) // If invalid input, then prompt the user to try again
		{
			printf("Invalid input. Please try again.\n");
			while (trash != '\n' && scanf("%c", &trash) == 1); // Clear input buffer in case of extra input
		}
	}

	return choice; // Return the valid choice after loop ends
}

/*
 * Function Name: updateLanguageTranslationPair()
 * Adds a new language-translation pair to an entry if not at max limit.
 * @param entry - array of entryType containing the dictionary entries.
 * @param language - the language of the new pair.
 * @param translation - the corresponding translation.
 * @return none
 * Pre-condition: The entry->pairCount should not be 10 (Max limit of translation pairs per entry).
 * Post-condition: If not full, a new language-translation pair is added, and pairCount is incremented.
 *                 If full, displays an error message and does not add the pair.
 */
void updateLanguageTranslationPair(entryType *entry, Str20 language, Str20 translation)
{

	int validFlag = 0; // Flag to ensure that the pair count of an entry is less than the MAX_PAIRS

	if (entry->pairCount < MAX_PAIRS) // If pair count is less than the MAX_PAIRS push through the program
	{ 
		validFlag = 1; // Set as valid
	}

	if (validFlag == 1)
	{
		strcpy(entry->pair[entry->pairCount].lang, language); // Update language in the pair
		strcpy(entry->pair[entry->pairCount].trans, translation); // Update translation in the pair
		entry->pairCount++; // Increment pairCount for the next addition
		printf("Language-translation pair added!\n");
	}
	else
	{
		printf("Unable to add more translations. Maximum limit (%d) reached.\n", MAX_PAIRS);
	}
}

/*
 * Funciton Name: showMatchedEntries() 
 * Displays all matched entries based on search results.
 * @param entries - array of entryType containing the dictionary entries.
 * @param matchedIndexes - array of indexes where matches were found.
 * @param matchCount - total number of matched entries.
 * @return none
 * Pre-condition: matchCount > 0 and matchedIndexes[] contains valid indexes within entries[].
 * Post-condition: Displays all matched entries with their respective language-translation pairs.
 */
void showMatchedEntries(entryType entries[], int matchedIndexes[], int matchCount, Str20 translationInput, Str20 languageInput) 
{
    int i, 
		j, 
		checktransOnly = 0;
    entryType *entry;

    if (strcasecmp(languageInput, "-1") == 0) 
	{ // Dereferencing to use the actual string
        checktransOnly = 1;
    }

    for (i = 0; i < matchCount; i++) 
	{
        entry = &entries[matchedIndexes[i]];
        printf("\n  +---------------------------------------------------+\n");
        printf("  |                    Entry %-3d                      |\n", matchedIndexes[i] + 1);
        printf("  +-----+----------------------+----------------------+\n");
        printf("  | No. | Language             | Translation          |\n");
        printf("  +-----+----------------------+----------------------+\n");

        for (j = 0; j < entry->pairCount; j++) 
		{
            if (checktransOnly == 1) 
			{
                if (strcasecmp(entry->pair[j].trans, translationInput) == 0) 
				{ 
                    printf("  |%s%2d%s   | %s%-20.20s%s | %s%-20.20s%s |\n", 
                           GREEN, j + 1, RESET, GREEN, entry->pair[j].lang, RESET, GREEN, entry->pair[j].trans, RESET);
                } else 
				{
                    printf("  | %-2d  | %-20.20s | %-20.20s |\n", j + 1, entry->pair[j].lang, entry->pair[j].trans);
                }
            } 
			else 
			{
                if (strcasecmp(entry->pair[j].trans, translationInput) == 0 && strcasecmp(entry->pair[j].lang, languageInput) == 0) 
				{ 
                    printf("  |%s%2d%s   | %s%-20.20s%s | %s%-20.20s%s |\n", 
                           GREEN, j + 1, RESET, GREEN, entry->pair[j].lang, RESET, GREEN, entry->pair[j].trans, RESET);
                } 
				else 
				{
                    printf("  | %-2d  | %-20.20s | %-20.20s |\n", j + 1, entry->pair[j].lang, entry->pair[j].trans);
                }
            }
        }
        printf("  +-----+----------------------+----------------------+\n");
    }
}

/*
 * Function Name: isDuplicate()
 * Checks if a given language-translation pair already exists in the entries.
 * Can check all entries or only a specific entry.
 * @param entries - array of entryType containing the dictionary entries.
 * @param countEntry - total number of entries in the list.
 * @param language - language to check for duplication.
 * @param translate - translation to check for duplication.
 * @param matchedIndexes - array to store indexes of matched entries.
 * @param currentEntryIndex - entry index to check (-1 to check all entries).
 * @return int - number of entries where the language-translation pair was found.
 *
 * Pre-condition: countEntry > 0, matchedIndexes is an empty array of sufficient size.
 * Post-condition: matchedIndexes contains indexes of entries with duplicate pairs.
 */

int isDuplicate(entryType entries[], int countEntry, Str20 language, Str20 translate, int matchedIndexes[], int currentEntryIndex)
{
	int matchPairCount = 0,	// Variable to hold the count of pairs in an entry similar to inputted pair					
		found, 																		
		i, 
		j,
		startIndex = 0, 																	
		endIndex = 0;

	if (currentEntryIndex == -1) // Check all entries available in the list
	{
		startIndex = 0;
		endIndex = countEntry;
	}
	else // Check only the current entry that is being added with lang-trans pair
	{
		startIndex = currentEntryIndex; 
		endIndex = currentEntryIndex + 1;
	}
	for (i = startIndex; i < endIndex; i++)	// Search for duplicates within the specified range
	{
		found = 0; // Reset flag for each entry
		for (j = 0; j < entries[i].pairCount; j++)
		{
			if (strcasecmp(entries[i].pair[j].lang, language) == 0 && 
				strcasecmp(entries[i].pair[j].trans, translate) == 0) // If the inputted lang-trans pair is same as the entry's pair then proceed
			{
				if (found == 0)																	
				{
					matchedIndexes[matchPairCount++] = i; // Store the index of the entry that has the similar lang-trans pair
					found = 1; // Prevent counting from an entry twice (even though it will never happen since there is a special case handling this)
				}
			}
		}
	}
	return matchPairCount; // Return the number of matched lang-trans pair in different entries
}

/*
 * Function Name: inputString()
 * Reads an entire line of input using fgets, ensuring it does not exceed MAX.
 * @param sentence - character array to store the input.
 * @param MAX - maximum number of characters the string can hold.
 * @return none
 * Pre-condition: sentence must be a valid character array of at least MAX size.
 * Post-condition: Stores the input string in 'sentence' and removes the trailing newline if present.
 *                 If input exceeds MAX, it prompts the user to enter again and clears the buffer.
 */
void inputString(char sentence[], int MAX, char prompt[])
{
    int lenSentence = 0, 
		ch,
		validFlag = 0;
    char *result;

	while(validFlag == 0) // Ensured that the user inputs a valid string
	{
		printf("%s", prompt); // Ask the user to input something depending on what function is being used
		result = fgets(sentence, MAX + 2, stdin); // Read up to MAX characters (+1 for newline and +1 for null)

		if (result != NULL)
		{
			lenSentence = strlen(sentence);	// Get the length of the sentence

			if (lenSentence > 0 && sentence[lenSentence - 1] == '\n')					
			{
				sentence[lenSentence - 1] = '\0'; // Remove the new line in the string since fgets also consumes/gets the newline
				lenSentence--; // Decrement to check whether the string only contains a newline or not	
			}

			if (lenSentence == 0) // If user accidentally pressed enter without any input
			{
				printf("Invalid input. You must enter at least 1 character. Try again.\n");
			}
			else if (lenSentence >= MAX + 1) // If inputted string is more than max 
			{
				printf("Invalid input. Exceeded %d characters. Try again.\n", MAX);
				while ((ch = getchar()) != '\n' && ch != EOF); // Consume to trash (throw away) until new line or EOF marker
			}
			else // The user finally inputted a valid string
			{
				validFlag = 1; // Flag to stop the loop
			}	
		}
		else
		{
			sentence[0] = '\0'; // In case of an error/eof, set the sentence to an empty string.
		}
	}
}

/*
 * Function Name: getLanguageTranslation()
 * Gets a language-translation pair from user input.
 * @param language - character array to store the language input.
 * @param translation - character array to store the translation input.
 * @return none
 * Pre-condition: language and translation must be valid character arrays of at least MAX_LETTER size.
 * Post-condition: Stores user input in 'language' and 'translation' after validation.
 */
void getLanguageTranslation(char language[], char translation[])
{
	printf("Input for language-translation pair:\n");
	inputString(language, MAX_LETTER, "Language: "); // Get language input
	inputString(translation, MAX_LETTER, "Translation: "); // Get translation input
}

/*
 * Function Name: countEntryIsZero()
 * Checks if there are existing entries.
 * @param countEntry - the total number of stored entries.
 * @return int - returns 1 if entries exist, 0 if no entries exist.
 * Pre-condition: countEntry is a non-negative integer.
 * Post-condition: Returns 0 if countEntry is 0 (indicating no entries exist),
 *                 otherwise returns 1 to allow further processing.
 */
int countEntryIsZero(int countEntry)
{
	int validIndex = 1; // Assume entries exist by default

	if (countEntry == 0)
	{
		validIndex = 0; // Prevent further processing if there are no entries
	}

	return validIndex;
}

/* Function Name: sortEntry()
*  sorts the given array of entries in two ways:
*  1. Inter-entry: Entries with English translations are sorted alphabetically
*  based on the English translation. Entries without an English translation
*  are placed after those that have English, sorting it based on its first pair.
*  2. Intra-entry: Each entry's language-translation pairs are sorted alphabetically
*  by language.
*  @param entry - array of entryType containing the dictionary entries.
*  @param countEntry - the total number of entries in the array
*  @return none
*  Pre-condition: Each entry can have up to MAX_LANG translations.
*/
void sortEntry(entryType *entry, int countEntry)
{
	entryType tempEntry[countEntry];
	int englishIndex[MAX_ENTRY] = {0}, // Store index of the entry that has English
		notEnglishIndex[MAX_ENTRY] = {0}, // Store index of the Non-English pair for each entry
		englishPairIndex[MAX_ENTRY] = {0}, // Store index of the English pair for each entry
		englishCount = 0, // Store how many entries have the English language
		notEnglishCount = 0, // Store how many entries don't have the English language
		i, j, k,
		found,
		idx1 = 0, 
		idx2 = 0, 
		pairIdx1 = 0, 
		pairIdx2 = 0,
		newIndex = 0,
		swapTemp = 0;
	
	// Separate entries into those with and without English
	for (i = 0; i < countEntry; i++)
	{
		found = 0; // Reset flag for each entry
		for (j = 0; j < entry[i].pairCount; j++)
		{
			if (strcasecmp("english", entry[i].pair[j].lang) == 0 && found == 0)
			{
				found = 1;							  
				englishIndex[englishCount] = i;		  
				englishPairIndex[englishCount++] = j; 
			}
		}
		if (found == 0)
		{											
			notEnglishIndex[notEnglishCount++] = i; 
		}
	}

	// STEP 1: INTRA-ENTRY SORT (Sort language-translation pairs inside each entry)
	for (i = 0; i < countEntry; i++)
	{
		for (j = 0; j < entry[i].pairCount - 1; j++)
		{
			for (k = 0; k < entry[i].pairCount - j - 1; k++)
			{
				if (strcasecmp(entry[i].pair[k].lang, entry[i].pair[k + 1].lang) < 0)
				{
					translationPairType tempPair = entry[i].pair[k];
					entry[i].pair[k] = entry[i].pair[k + 1];
					entry[i].pair[k + 1] = tempPair;
				}
			}
		}
	}

	// STEP 2: INTER-ENTRY SORT (Sort non-English entries based on their first pair translation)
	for (i = 0; i < notEnglishCount - 1; i++)
	{
		for (j = 0; j < notEnglishCount - i - 1; j++)
		{
			idx1 = notEnglishIndex[j];
			idx2 = notEnglishIndex[j + 1];

			if (strcasecmp(entry[idx1].pair[0].trans, entry[idx2].pair[0].trans) > 0)
			{
				// Swap the indices
				swapTemp = notEnglishIndex[j];
				notEnglishIndex[j] = notEnglishIndex[j + 1];
				notEnglishIndex[j + 1] = swapTemp;
			}
		}
	}

	// STEP 3: INTER-ENTRY SORT (Sort English entries based on English translation)
	for (i = 0; i < englishCount - 1; i++)
	{
		for (j = 0; j < englishCount - i - 1; j++)
		{
			idx1 = englishIndex[j];
			idx2 = englishIndex[j + 1];
			pairIdx1 = englishPairIndex[j];
			pairIdx2 = englishPairIndex[j + 1];

			if (strcasecmp(entry[idx1].pair[pairIdx1].trans, entry[idx2].pair[pairIdx2].trans) > 0)
			{
				// Swap the indices
				swapTemp = englishIndex[j];
				englishIndex[j] = englishIndex[j + 1];
				englishIndex[j + 1] = swapTemp;

				// Swap the corresponding englishPairIndex values
				swapTemp = englishPairIndex[j];
				englishPairIndex[j] = englishPairIndex[j + 1];
				englishPairIndex[j + 1] = swapTemp;
			}
		}
	}

	// STEP 4: MERGE SORTED ENTRIES BACK INTO ARRAY
	for (i = 0; i < englishCount; i++)
	{
		tempEntry[newIndex++] = entry[englishIndex[i]];
	}
	for (i = 0; i < notEnglishCount; i++)
	{
		tempEntry[newIndex++] = entry[notEnglishIndex[i]];
	}

	// Copy back the sorted entries to the original array
	for (i = 0; i < countEntry; i++)
	{
		entry[i] = tempEntry[i];
	}
}
/*
 * Function Name: addEntry()
 * Adds a new language-translation entry or updates an existing one.
 * This function first checks if an entry with the given language-translation pair
 * already exists. If an existing entry is found, it displays all matching entries
 * and asks the user whether they want to create a new entry or update an existing one.
 * If no matching entry exists, the program allows the user to create a new entry and
 * add multiple language-translation pairs to it. The function ensures that each entry
 * has at least one language-translation pair and does not exceed the maximum allowed
 * pairs (MAX_LANG = 10).
 * @param entries - array of entryType containing the dictionary entries.
 * @param countEntry - pointer to the total number of entries in the array
 * @return none
 * Pre-condition: The dictionary can store up to MAX_ENTRY entries, and each entry 
 *               can contain up to MAX_LANG language-translation pairs.
 */
void addEntry(entryType *entries, int *countEntry)
{
	int entryFlag = 1,	// Variable to store the flag for loop of adding entry
		checkAll = -1,	// Variable to check if all entry is needed to be checked
		matchedIndexes[MAX_ENTRY] = {0}, // An array containing the indeces of the entries that has the lang-trans pair similar to those inputted pair
		matchCount = 0;	// Variable containing the count of entries that contain the inputted pair
	char choice = 'Y';											
	Str20 language, // Temporary variable for inputted language
		  translation; // Temporary variable for inputted translation

	if (*countEntry >= MAX_ENTRY) // Condition where the count of the entry is already more than the MAX_ENTRY
	{
		printf("Cannot add more entries. Dictionary is full!\n");
		entryFlag = 0; // Exit the loop
	}
	else
	{
		while (choice == 'Y' && entryFlag)	// If entry count is still less than MAX_ENTRY and the user still wants to add entry
		{
			getLanguageTranslation(language, translation); // Function call for getting the language-translation pair

			matchCount = isDuplicate(entries, *countEntry, language, translation, matchedIndexes, checkAll); // Check for duplicates across all entries

			if (matchCount > 0)	// If language-translation pair already exist within an entry
			{
				showMatchedEntries(entries, matchedIndexes, matchCount, translation, language); // Display all the entries that have the similar lang-trans pair with the inputted pair
				printf("This language-translation pair already exists!\n");
				printf("Is this a new entry? ");
				choice = getChoice(); // Function call to getChoice of the user

				if (choice == 'N') // If the user said that it is not a new entry, then proceed to exit the addEntry function
				{
					entryFlag = 0; // Exit the loop
				}
				else if (choice == 'Y')	// If the user decided that it is a new entry
				{
					entries[*countEntry].pairCount = 0;	// Initialize the count of pair within an entry to zero (avoid garbage value)
					updateLanguageTranslationPair(&entries[*countEntry], language, translation); // Store the inputted language-translation pair 
					printf("New entry has been added successfully!\n");

					while (choice == 'Y') // Loop until the user doesn't want to add language-translation pair to the entry anymore
					{
						printf("Add another language-translation pair to the current entry? ");
						choice = getChoice(); // Function call to getChoice of the user

						if (choice == 'Y') // If the user chooses to add language-translation, then proceed to add entry
						{
							getLanguageTranslation(language, translation); // Function call for getting the language-translation pair
							matchCount = isDuplicate(entries, *countEntry, language, 
													translation, matchedIndexes, *countEntry);	// Check for duplicates **within the current entry**
							
							if (matchCount > 0)	// If the language-translation pair already exist within the entry
							{
								printf("This pair already exists within the current entry! \n...\n");
							}
							else															// If the language-translation pair doesn't exist within the entry
							{
								updateLanguageTranslationPair(&entries[*countEntry], language, translation); // Update language-translation pair
							}
						}
					}
					(*countEntry)++; // Increment the entry count once the user is done adding language-translation pair in the entry
					sortEntry(entries, *countEntry); // Function call to sort entries after adding a new entry
				}
			}
			else // If the inputted language-translation pair doesn't exist yet in any entry
			{
				printf("This language-translation pair does not exist!\nIs this a new entry? ");
				choice = getChoice(); // Function call to getChoice of the user 

				if (choice == 'N') // If the user chooses that the language-pair isn't a new entry
				{
					entryFlag = 0; // Exit the loop 
				}
				else if (choice == 'Y')	// If the user chooses that the language-translation pair will be part of a new entry
				{
					entries[*countEntry].pairCount = 0;	// Initialize the count of pair within an entry to zero (avoid garbage value) 
					updateLanguageTranslationPair(&entries[*countEntry], language, translation); // Store the inputted language-translation pair 
					printf("New entry has been added successfully!\n");

					while (choice == 'Y')// Loop until the user doesn't want to add language-translation pair to the entry anymore
					{
						printf("Add another language-translation pair to the current entry? ");
						choice = getChoice(); // Function call to getChoice of the user

						if (choice == 'Y') // If the user chooses to add language-translation, then proceed to add entry
						{
							getLanguageTranslation(language, translation); // Function call for getting the language-translation pair

							
							matchCount = isDuplicate(entries, *countEntry, language, 
													translation, matchedIndexes, *countEntry); // Check for duplicates **within the current entry**

							if (matchCount > 0) // If the language-translation pair already exist within the entry
							{
								printf("This pair already exists within the current entry! Skipping...\n");
							}
							else // If the language-translation pair doesn't exist within the entry
							{
								updateLanguageTranslationPair(&entries[*countEntry], language, translation); // Update language-translation pair
							}
						}
					}
					(*countEntry)++; // Increment the entry count once the user is done adding language-translation pair in the entry
					sortEntry(entries, *countEntry); // Function call to sort entries after adding a new entry
				}
			}
		}
	}
}

/*
 * Function Name: addTranslation()
 * Adds a new language-translation pair to an existing entry.
 * This function asks for a language and translation pair and checks if an entry with that
 * pair already exists. If no matching entry is found, the user is prompted to add a new entry
 * via addEntry(). If one or more matching entries are found, the function displays them.
 * - If only one matching entry exists, the user is prompted to add a new pair to that entry.
 *   After each successful addition, the entries are sorted using sortEntry(), and the user is
 *   repeatedly prompted whether to add another pair until either the maximum count (MAX_PAIRS)
 *   is reached or the user declines. Once the maximum count is reached, the function exits the
 *   addition loop and returns control to the Manage Data menu.
 * - If multiple matching entries exist, the user selects one (via an integer input), and then the
 *   same repeated prompt is used to add new translation pairs. In every addition, the code checks
 *   that the pair doesn't already exist in the selected entry. After each successful addition,
 *   sortEntry() is called to maintain sorted order.
 * @param entries - array of entryType containing the dictionary entries.
 * @param countEntry - pointer to the total number of entries in the dictionary.
 * @return none
 * Pre-condition: Each entry can have up to MAX_PAIRS translation pairs.
 */
void addTranslation(entryType *entries, int *countEntry)
{
    char choice = 'Y',
		 trash;
    int matchedIndexes[MAX_ENTRY] = {0}, // Array to store indexes of matching entries
    	matchCount = 0, // Number of matching entries found
		selectedIndex = 0, // Variable to store what index or what entry the user wants to add translation to
		checkAll = -1,
		idx = 0;
    Str20 language, 
		  translation; // Variables to store user input

    getLanguageTranslation(language, translation); // Prompt the user to enter the language-translation pair 
    matchCount = isDuplicate(entries, *countEntry, language, translation, matchedIndexes, checkAll); // Check if an entry exists with the given language-translation pair

    if (matchCount <= 0) // No matching entry found
    {
        printf("The entry doesn't exist. Would you like to add a new entry? ");
        choice = getChoice(); // Suggest using the addEntry() option

        if (choice == 'Y')
        {
            printf("Redirecting you to add entry.\nAdd entry:\n");
            addEntry(entries, countEntry); // Redirect to addEntry() to create a new entry
        }
    }
    else // Matching entry(ies) found
    {
        printf("Existing entries have been found:\n");
        showMatchedEntries(entries, matchedIndexes, matchCount, translation, language); // Display all matched entries

        if (matchCount == 1) // Only one matching entry exists
        {
            idx = matchedIndexes[0];
            if (entries[idx].pairCount >= MAX_PAIRS) // If the matching entry already have maximum number of pairs, then exit the addTranslation()
            {
                printf("The entry already has the maximum number of pairs.\n");
            }
            else
            {
                while (choice == 'Y' && entries[idx].pairCount < MAX_PAIRS) // Use a while loop to allow adding multiple pairs without re-prompting if max is reached.
                {
                    getLanguageTranslation(language, translation); // Prompt the user to enter the language-translation pair 
                    if (isDuplicate(entries, *countEntry, language, translation, matchedIndexes, idx) > 0) // Check for duplicate within the current entry (using idx as the check index)
                    {
                        printf("This pair already exists within the current entry! Skipping...\n");
                    }
                    else // No duplicate within the current entry
                    {
                        updateLanguageTranslationPair(&entries[idx], language, translation); // Store the inputted language-translation pair 	
                        sortEntry(entries, *countEntry); // Sort entries after successful addition
                    }
                    if (entries[idx].pairCount < MAX_PAIRS) // Pair count of the current entry doesn't exceed the maximum number of pairs
                    {
                        printf("Add another language-translation pair? ");			
                        choice = getChoice(); // Prompt the user to add language-translation pair or not
                    }
                    else // Pair count of the current entry already exceeds the maximum number of pairs
                    {
                        printf("The entry already has the maximum number of pairs. \n");
                        choice = 'N'; // Exit the loop of addTranslation()
                    }
                }
            }
        }
        else // Multiple matching entries exist
        {
            do // Prompt user to select which entry to add the language-translation pair to
            {
                printf("Enter Entry Number to add translation: ");
                scanf(" %d%c", &selectedIndex, &trash);
				if (selectedIndex < 1 || selectedIndex > matchCount)
				{
					printf("Invalid Entry Number. Try again.\n");
				}
                while (trash != '\n' && scanf("%c", &trash) == 1); // Flush remaining characters in the input buffer
            } while (selectedIndex < 1 || selectedIndex > matchCount);
            
            selectedIndex = matchedIndexes[selectedIndex - 1]; // Convert 1-based user input to index-0 from the matchedIndexes array

            if (entries[selectedIndex].pairCount >= MAX_PAIRS) // The selected entry already have the maximum number of pairs
            {
                printf("The selected entry already has the maximum number of translation pairs.\n");
            }
            else // Selected entry doesn't exceed the maximum number of pairs
            {
                while (choice == 'Y' && entries[selectedIndex].pairCount < MAX_PAIRS) // Use a while loop to allow adding multiple pairs without re-prompting if max is reached.
                {
                    getLanguageTranslation(language, translation); // Prompt the user to enter the language-translation pair
                    if (isDuplicate(entries, *countEntry, language, 
									translation, matchedIndexes, selectedIndex) > 0) // Check for duplicate within the current entry (using selectedIndex as the check index)
                    {
                        printf("This pair already exists within the current entry! Skipping...\n");
                    }
                    else // Inputted pair doesn't exist yet in the selected entry
                    {
                        updateLanguageTranslationPair(&entries[selectedIndex], language, translation); // Store the inputted language-translation pair 
                        sortEntry(entries, *countEntry); // Sort entries after successful addition
                    }
                    if (entries[selectedIndex].pairCount < MAX_PAIRS)					
                    {
                        printf("Add another language-translation pair? "); // Pair count of the selected entry doesn't exceed the maximum number of pairs
                        choice = getChoice();
                    }
                    else // Pair count of the selected entry already exceeds the maximum number of pairs
                    {
                        printf("The selected entry already has the maximum number of translation pairs.\n");
                        choice = 'N'; // Exit the loop of addTranslation()
                    }
                }
            }
        }
    }
}

/*
 * Function Name: displayAllEntries()
 * Displays dictionary entries one at a time.
 * This function lists all initialized entries in the dictionary along with each entry's
 * language-translation pairs (up to the entry's pairCount). It assumes that both intra-
 * entry and inter-entry sorting have already been done.
 * The user selects an entry to view and can navigate using:
 *    'N' or 'n' - Next entry,
 *    'P' or 'p' - Previous entry,
 *    'X' or 'x' - Exit display mode.
 * @param entry      - Array of entryType containing the dictionary entries.
 * @param countEntry - Total number of initialized entries.
 * @return none
 */
void displayAllEntries(entryType entry[], int countEntry)
{
	int i = 0, // Variable containing which entry to display
		j;
	char trash,
		choice;
	
	if (!countEntryIsZero(countEntry)) // No entry to display
	{
		printf("No entries available to display.\n");
	}

	else if(countEntry == 1) // There is only one entry that exists
	{
		printf("\n  +---------------------------------------------------+\n");
		printf("  |                   Entry %-3d                       |\n", countEntry);
		printf("  +-----+----------------------+----------------------+\n");
		printf("  | No. | Language             | Translation          |\n");
		printf("  +-----+----------------------+----------------------+\n");
			
		for (j = 0; j < entry[0].pairCount; j++) 
		{
			printf("  | %-2d  | %-20s | %-20s |\n", j + 1, entry[0].pair[j].lang, entry[0].pair[j].trans);
		}
			
		printf("  +-----+----------------------+----------------------+\n");
	}
	else // There is/are entry/ies to display
	{
		printf("You are now in Display View Mode.\n");
		printf("Press 'N' to go to the Next entry.\n");
		printf("Press 'P' to go to the Previous entry.\n");
		printf("Press 'X' to exit Display View.\n");

		do
		{
			printf("Select which entry to Display [1-%d]: ", countEntry);
			scanf(" %d%c", &i, &trash); // Prompt the user to input what entry to display
			
			while (trash != '\n' && scanf("%c", &trash) == 1);
			
			if (i < 1 || i > countEntry)
			{
				printf("Invalid Entry Number! Please try again.\n");
			}
		} while (i < 1 || i > countEntry); // Ensures that the user inputs a valid entry number 

		i--; // Decrement the selected index to index-0 to adjust to the program

		do
		{
			printf("\n  +---------------------------------------------------+\n");
			printf("  |                   Entry %-3d                       |\n", i + 1);
			printf("  +-----+----------------------+----------------------+\n");
			printf("  | No. | Language             | Translation          |\n");
			printf("  +-----+----------------------+----------------------+\n");
			
			for (j = 0; j < entry[i].pairCount; j++) 
			{
				printf("  | %-2d  | %-20s | %-20s |\n", j + 1, entry[i].pair[j].lang, entry[i].pair[j].trans);
			}
			
			printf("  +-----+----------------------+----------------------+\n");

			printf("\nEnter Choice [N/P/X]: ");	// Prompt the user if they want to display the next or previous entry or exit the function
			scanf(" %c%c", &choice, &trash); // Added a space before %c to handle previous newlines
			if (choice != 'N' || choice != 'n' || choice != 'P' || choice != 'p' || choice != 'X' || choice != 'x')
			{
				printf("Invalid choice. Try again.\n");
			}
			while (trash != '\n' && scanf("%c", &trash) == 1);

			if (choice == 'N' || choice == 'n')	// User's choice is to display the next entry
			{
				if (i >= countEntry - 1) // Already at the last entry
				{
					printf("WARNING: Already at the last entry!\n");
				}
				else // User is not yet in the last entry
				{
					i++; // Increment the index since the user wants to display the next entry
				}
			}
			else if (choice == 'P' || choice == 'p') // User's choice is to display the previous entry
			{
				if (i <= 0)	// Already at the first entry
				{
					printf("WARNING: Already at the first entry!\n");
				}
				else // User is not yet in the first entry
				{
					i--; // Decrement the index since the user wants to display the previous entry
				}
			}
		} while (choice != 'X' && choice != 'x'); // Loop while the user doesn't want to exit the function
		printf("Exiting Display View Mode...\n");
	}
}

/*
 * Function Name: displayUpdatedEntry() 
 * This is intended to be a helper function for delete translation where it prints the 
 * updated entry after the user intends to delete another translation from an entry again
 * @param entry - array of entryType containing the pairs where the user can choose to delete
 * @param entryNumber - integer containing what entry number the user chose to delete pairs from.
 * @return none
 */
void displayUpdatedEntry(entryType entry, int entryNumber)
{
	int i;
	printf("\n  +---------------------------------------------------+\n");
	printf("  |                   Entry %-3d                       |\n", entryNumber + 1);
	printf("  +-----+----------------------+----------------------+\n");
	printf("  | No. | Language             | Translation          |\n");
	printf("  +-----+----------------------+----------------------+\n");
	
	for (i = 0; i < entry.pairCount; i++) 
	{
		printf("  | %-2d  | %-20s | %-20s |\n", i + 1, entry.pair[i].lang, entry.pair[i].trans);
	}
	
	printf("  +-----+----------------------+----------------------+\n\n");
}

/*
 * Function Name: deleteEntry() 
 * Deletes a specified entry from the dictionary.
 * This function first displays all entries using displayAllEntries() (which shows all language-
 * translation pairs in each entry, with entry numbers starting at 1). It then prompts the user to 
 * enter the entry number they wish to delete. A valid input is any integer from 1 up to the number of 
 * entries currently initialized. If an invalid number is given, a message is displayed before going 
 * back to the Manage Data menu.
 * When a valid entry number is provided, the function deletes that entry by shifting all subsequent 
 * entries one position to the left. In deleting an entry, all language-translation pairs are cleared. 
 * The overall entry count is then decremented.
 * @param entries - array of entryType containing the dictionary entries.
 * @param countEntry - pointer to the total number of entries in the dictionary.
 * @return none
 * Pre-condition: The dictionary may contain zero or more entries.
 */
void deleteEntry(entryType entries[], int *countEntry)
{
    char trash;
	int selectedIndex,
    	i;
    
    if (!countEntryIsZero(*countEntry)) // There is no entry available to delete
    {
        printf("No entries available to delete.\n");
    }
    else // There is/are entry/ies to delete 
    {    
        displayAllEntries(entries, *countEntry); // Display all entries before deletion

        printf("Enter the entry number to delete [1-%d]: ", *countEntry); // Prompt user to enter the entry number to delete (1-based)
        scanf(" %d%c", &selectedIndex, &trash);
        while (trash != '\n' && scanf("%c", &trash) == 1);

        if (selectedIndex < 1 || selectedIndex > *countEntry) // Validate the selected index; if invalid, display an error message.
        {
            printf("Invalid entry number! Redirecting back to Manage Data Menu.\n");
        	printf("Press any key to continue...\n");
		    getch(); // Waits for any key	
        }
        else // Valid index number
        {
            selectedIndex--; // Convert from 1-based to 0-based index
            
            if (selectedIndex < *countEntry - 1) // Shift subsequent entries left to overwrite the deleted entry, only shift if it is not the last entry
            {
                for (i = selectedIndex; i < *countEntry - 1; i++)
                {
                    entries[i] = entries[i + 1]; // Shift subsequent entries left to overwrite the deleted entry
                }
            }
            
            for (i = 0; i < entries[*countEntry - 1].pairCount; i++) // Clear all language-translation pairs from the last entry (now duplicate)
            {
                entries[*countEntry - 1].pair[i].lang[0] = '\0';
				entries[*countEntry - 1].pair[i].trans[0] = '\0';
            }
            entries[*countEntry - 1].pairCount = 0;
            
            (*countEntry)--; // Reduce the entry count
            
            printf("Entry deleted successfully!\n");
        }
    }
	sortEntry(entries, *countEntry); // Sort entries after deletion
}

/*
 * Function Name: deleteTranslation() 
 * Deletes a language-translation pair from an existing entry.
 * This function allows the user to delete a specific language-translation pair from a selected entry.
 * It first displays all current entries using displayAllEntries(). The user is then prompted to enter the entry 
 * number from which they wish to delete a pair. A valid input must be an integer between 1 and the total 
 * number of entries. If an invalid entry number is provided, an error message is displayed before returning
 * to the Manage Data menu.
 * If a valid entry number is given, the user is then asked to specify which language-translation pair to 
 * delete by entering the pair's number. If an invalid pair number is provided, the user is notified with an error message and 
 * asked whether they wish to continue deleting pairs. If the user declines, control returns to the Manage 
 * Data menu.
 * The deletion process repeats as long as the user wishes to delete additional pairs from the same entry.
 * If the deletion results in an entry having no remaining language-translation pairs, then the entire 
 * entry is deleted.
 * @param entries    - array of entryType containing the dictionary entries.
 * @param countEntry - pointer to the total number of entries in the dictionary.
 * @return none
 * Pre-condition: The dictionary may contain zero or more entries, and each entry may have up to MAX_PAIRS translation pairs.
 */
void deleteTranslation(entryType *entries, int *countEntry)
{
	char trash,
		 choice = 'Y';
	int selectedIndex = 0, // Variable to store what entry the user wants to delete
		selectedPairIndex = 0, // Variable to store what language-translation pair the user wants to delete
		validIndex = 1, // Flag if the user select a valid entry number. Used also for stopping loops
		i,
		j;

	if (countEntryIsZero(*countEntry) == 0) // No entry available to display
	{
		printf("No entries available. Language-translation pair deletion can't be done.\n");
		validIndex = 0; // Prevent further processing
	}

	if (validIndex == 1) // There is/are entry/ies available to display
	{
		displayAllEntries(entries, *countEntry); // Display entries before deletion

		printf("Enter the entry number to delete [1-%d]: ", *countEntry);
		scanf(" %d%c", &selectedIndex, &trash); // Prompt the user what entry number to delete
		
		while (trash != '\n' && scanf("%c", &trash) == 1);

		if (selectedIndex < 1 || selectedIndex > *countEntry) // User inputs an invalid entry number
		{
			printf("Invalid entry number! Redirecting back to Manage Data Menu.\n");
			printf("Press any key to continue...\n");
			getch(); // Waits for any key	
			validIndex = 0;	// Prevent further processing
		}
		else // Valid entry number
		{
			selectedIndex--; // Convert 1-based index to 0-based index
		}
	}

	while (validIndex == 1) // Loop until the user doesn't want to delete language-translation pair anymore or there is no pair to delete anymore
	{
		printf("Enter the pair number to delete [1-%d]: ", entries[selectedIndex].pairCount);
		scanf(" %d%c", &selectedPairIndex, &trash); // Prompt the user what language-translation pair they want to delete
		while (trash != '\n' && scanf("%c", &trash) == 1);
		
		if (selectedPairIndex < 1 || selectedPairIndex > entries[selectedIndex].pairCount) // If user inputs an invalid language-translation pair number
		{
			printf("Invalid pair number! Continue deleting pair? ");						
			choice = getChoice(); // Prompt the user if they want to still continue deleting language-translation pair
			if (choice == 'N')
			{
				validIndex = 0; // Prevent further processing
			}
		}
		else // Valid language-translation pair number
		{
			selectedPairIndex--; // Convert 1-based index to 0-based index

			for (i = selectedPairIndex; i < entries[selectedIndex].pairCount - 1; i++) // Shift subsequent pairs left to overwrite the deleted pair, only shift if it is not the last pair
			{
				entries[selectedIndex].pair[i] = entries[selectedIndex].pair[i + 1]; // Shift subsequent pairs left to overwrite the deleted pair
			}
			entries[selectedIndex].pairCount--; // Reduce the pair count of the selected entry

			entries[selectedIndex].pair[entries[selectedIndex].pairCount].lang[0] = '\0'; // Clear the last pair
    		entries[selectedIndex].pair[entries[selectedIndex].pairCount].trans[0] = '\0'; // Clear the last pair

			if (entries[selectedIndex].pairCount == 0) // If the entry's pair count is zero, shift subsequent
			{
				for (j = selectedIndex; j < *countEntry - 1; j++)
				{
					entries[j] = entries[j + 1]; // Shift subsequent entries left to overwrite the deleted entry since the entry doesn't contain any pairs anymore
				}
				(*countEntry)--; // Reduce the entry since the selected entry doesn't have any pair anymore so it was deleted
				printf("Entry has been deleted as it had no remaining pairs.\n");
				validIndex = 0; // Prevent further processing
			}
			else
			{
				printf("\nUpdated Entry:\n");
				displayUpdatedEntry(entries[selectedIndex], selectedIndex);

				printf("Continue deleting pair? ");
				choice = getChoice(); // Prompt the user if they want to still continue deleting language-translation pair	
				if (choice == 'N')
				{
					validIndex = 0; // Prevent further processing
				}
			}
		}
	}
	sortEntry(entries, *countEntry); // Sort entries after deletion
}

/*
 * Function Name: searchWord()
 * Searches for a word among the translations in the dictionary entries.
 * This function prompts the user to input a word. It then scans through all entries to find any
 * language-translation pair that matches the input word (case-insensitive). If one or more entries
 * contain the word, only those entries are displayed allowing the userto view them similarly to Display 
 * All Entries (with navigation options for next, previous, and exit).
 * If no matching word is found, a message is printed and the program returns to the Manage Data menu.
 * @param entries   - Array of entryType containing the dictionary entries.
 * @param countEntry - The total number of entries in the dictionary.
 * @ return none
 */
void searchWord(entryType *entries, int countEntry) 
{
    Str20 translationInput; // String variable to store the word to be search
	char trash, 
		 choice = ' '; // Variable char choice to store P/N/X

    int i = 0, 
		j = 0, 
		sameEntryIndex[MAX_ENTRY] = {0}, // Array to store the indeces of the entry with the same word
		sameEntryCount = 0, // Count of entries with the same word as the inputted one
		found = 0, // Variable to flag if the word is found within an entry
		waitingForKey = 1, // Flag to wait for the user to press any key 
		currentIndex = 0, // Variable to keep track of what is the current entry index being printed
		navigating = 1, // Flag to keep track whether the user is still nexting or previous-ing to the entries
		entryIndex = 0, // Variable to store the entry index of the entry
		validChoice = 0; // Variable to keep track whether the user is still making valid choices in the navigation

	inputString(translationInput, MAX_LETTER, "Enter word: ");
    // Find all matching entries
    for (i = 0; i < countEntry; i++) 
	{
        found = 0; // Flag to avoid storing duplicates
        for (j = 0; j < entries[i].pairCount; j++) 
		{
            if (strcasecmp(entries[i].pair[j].trans, translationInput) == 0 && found == 0) 
			{
                sameEntryIndex[sameEntryCount] = i; // Store the entry that has the similar searched for word
                sameEntryCount++; // Increment similar entry count since there was an entry found with the searched word
                found = 1; // Flag to avoid the duplicates within an entry
            }
        }
    }

    // If no matches found
    while (sameEntryCount == 0 && waitingForKey) 
	{
        printf("Word does not exist. Redirecting back to Manage Data menu.\n");
        printf("Press any key to continue...\n");
        getch();
        waitingForKey = 0; // Breaks the loop naturally
    }

    // PNX Navigation
    if (sameEntryCount > 0) 
	{
        printf("You are now in Search View Mode.\n");
        printf("Press 'N' for Next, 'P' for Previous, 'X' to exit.\n");

        while (navigating) // Loop if the user still wants to display entries
		{
            entryIndex = sameEntryIndex[currentIndex]; // Store the entry index of matched entries

            printf("\n  +---------------------------------------------------+\n");
            printf("  |                   Entry %-3d                       |\n", entryIndex + 1);
            printf("  +-----+----------------------+----------------------+\n");
            printf("  | No. | Language             | Translation          |\n");
            printf("  +-----+----------------------+----------------------+\n");

            // Highlight the matched words
            for (j = 0; j < entries[entryIndex].pairCount; j++) 
			{
                if (strcasecmp(entries[entryIndex].pair[j].trans, translationInput) == 0) 
				{
                    printf("  |%s%2d%s   | %s%-20.20s%s | %s%-20.20s%s |\n",
                           GREEN, j + 1, RESET, GREEN, entries[entryIndex].pair[j].lang, RESET, GREEN, entries[entryIndex].pair[j].trans, RESET);
                } 
				else 
				{
                    printf("  | %-2d  | %-20.20s | %-20.20s |\n", j + 1, entries[entryIndex].pair[j].lang, entries[entryIndex].pair[j].trans);
                }
            }
            printf("  +-----+----------------------+----------------------+\n");

            printf("\nEnter Choice [N/P/X]: "); 
            scanf(" %c%c", &choice, &trash); // Prompt the user to choose if show previous, next, or exit display function
			while (trash != '\n' && scanf("%c", &trash) == 1);

            validChoice = 0;
            while (!validChoice) // Ensures that the user inputs a valid choice
			{
                if (choice == 'N' || choice == 'n') // User chooses to display next entry
				{
                    if (currentIndex < sameEntryCount - 1) // If the user is still not in the last entry, allow to display next
					{
                        currentIndex++;
                    } 
					else // The user is already at the last entry
					{
                        printf("WARNING: Already at the last match!\n");
                    }
                    validChoice = 1;
                } 
				else if (choice == 'P' || choice == 'p') // User chooses to display previous entry 
				{
                    if (currentIndex > 0) // If the user is still not in the first entry, allow to display previous
					{
                        currentIndex--;
                    } 
					else // The user is already at the firs entry
					{
                        printf("WARNING: Already at the first match!\n");
                    }
                    validChoice = 1;
                } 
				else if (choice == 'X' || choice == 'x') // The user chooses to exit the display function
				{
                    navigating = 0; // Exit the loop
                    validChoice = 1;
                } 
				else // Invalid input handler
				{
                    printf("Invalid choice. Try again: ");
                    scanf(" %c%c", &choice, &trash); // Prompt the user for choice 
					while (trash != '\n' && scanf("%c", &trash) == 1);
                }
            }
        }
        printf("Exiting Search View Mode...\n");
    }
}

/*
 * Function Name: searchTranslation()
 * Finds entries with a specific language-translation pair.
 * Prompts the user for a language and translation, then checks all entries for a 
 * case-insensitive match. If one or more entriescontain the word, only those entries are 
 * displayed allowing the user to view them similarly to Display 
 * All Entries (with navigation options for next, previous, and exit).
 * If no language-translation pair is found, a message is printed and 
 * the program returns to the Manage Data menu.
 * otherwise, a message is shown and returns to the Manage Data menu.
 * @param entries   - Array of dictionary entries.
 * @param countEntry - Total number of entries.
 * @return none
 */
void searchTranslation(entryType *entries, int countEntry) 
{
    Str20 translationInput, // String to store the translation to be searched for
		  languageInput; // String to store the language to be searched for
	int i = 0, 
		j = 0, 
		sameEntryIndex[MAX_ENTRY] = {0}, 
		sameEntryCount = 0, // Count of entries with the same word as the inputted one
		found = 0, // Variable to flag if the word is found within an entry
		waitingForKey = 1, // Flag to wait for the user to press any key 
		currentIndex = 0, // Variable to keep track of what is the current entry index being printed
		navigating = 1, // Flag to keep track whether the user is still nexting or previous-ing to the entries
		entryIndex = 0, // Variable to store the entry index of the entry
		validChoice = 0; // Variable to keep track whether the user is still making valid choices in the navigation
    char trash,
		 choice = ' '; // Variable char choice to store P/N/X

    inputString(languageInput, MAX_LETTER, "Enter language: "); // Prompt the user for the language to be searched for
    inputString(translationInput, MAX_LETTER, "Enter translation: "); // Prompt the user for the translation to be searched for
    // Find all matching entries
    for (i = 0; i < countEntry; i++) 
	{
        found = 0; // Avoid duplicate entries
        for (j = 0; j < entries[i].pairCount; j++) 
		{
            if (strcasecmp(entries[i].pair[j].trans, translationInput) == 0 &&
                strcasecmp(entries[i].pair[j].lang, languageInput) == 0 &&
                found == 0) // If there is a language-translation pair that exists in an entry
			{
                sameEntryIndex[sameEntryCount] = i; // Store the entry that has the similar searched for word
                sameEntryCount++; // Increment similar entry count since there was an entry found with the searched word
                found = 1; // Flag to avoid the duplicates within an entry
            }
        }
    }

    // If no matches found
    while (sameEntryCount == 0 && waitingForKey) 
	{
        printf("Translation does not exist. Redirecting back to Manage Data menu.\n");
        printf("Press any key to continue...\n");
        getch();
        waitingForKey = 0; // Exit loop naturally
    }

    // PNX Navigation for matched entries
    if (sameEntryCount > 0) 
	{
        printf("You are now in Translation Search Mode.\n");
        printf("Press 'N' for Next, 'P' for Previous, 'X' to exit.\n");

        while (navigating) // Loop if the user still wants to display entries
		{
            entryIndex = sameEntryIndex[currentIndex]; // Store the entry index of matched entries

            printf("\n  +---------------------------------------------------+\n");
            printf("  |                   Entry %-3d                       |\n", entryIndex + 1);
            printf("  +-----+----------------------+----------------------+\n");
            printf("  | No. | Language             | Translation          |\n");
            printf("  +-----+----------------------+----------------------+\n");

            // Highlight the matched translation
            for (j = 0; j < entries[entryIndex].pairCount; j++) 
			{
                if (strcasecmp(entries[entryIndex].pair[j].trans, translationInput) == 0 &&
                    strcasecmp(entries[entryIndex].pair[j].lang, languageInput) == 0) 
				{
                    printf("  |%s%2d%s   | %s%-20.20s%s | %s%-20.20s%s |\n",
                           GREEN, j + 1, RESET, GREEN, entries[entryIndex].pair[j].lang, RESET, GREEN, entries[entryIndex].pair[j].trans, RESET);
                } 
				else 
				{
                    printf("  | %-2d  | %-20.20s | %-20.20s |\n", j + 1, entries[entryIndex].pair[j].lang, entries[entryIndex].pair[j].trans);
                }
            }
            printf("  +-----+----------------------+----------------------+\n");

            printf("\nEnter Choice [N/P/X]: ");
            scanf(" %c%c", &choice, &trash); // Prompt the user to choose if show previous, next, or exit display function
			while (trash != '\n' && scanf("%c", &trash) == 1);

            validChoice = 0;
            while (!validChoice) // Ensures that the user inputs a valid choice
			{
                if (choice == 'N' || choice == 'n') // User chooses to display next entry
				{
                    if (currentIndex < sameEntryCount - 1) // If the user is still not in the last entry, allow to display next
					{
                        currentIndex++;
                    } 
					else // The user is already at the last entry
					{
                        printf("WARNING: Already at the last match!\n");
                    }
                    validChoice = 1;
                } 
				else if (choice == 'P' || choice == 'p') // User chooses to display previous entry 
				{
                    if (currentIndex > 0) // If the user is still not in the first entry, allow to display previous
					{
                        currentIndex--;
                    } 
					else // The user is already at the firs entry
					{
                        printf("WARNING: Already at the first match!\n");
                    }
                    validChoice = 1;
                } 
				else if (choice == 'X' || choice == 'x') // The user chooses to exit the display function
				{
                    navigating = 0; // Exit the loop
                    validChoice = 1;
                } 
				else // Invalid input handler
				{
                    printf("Invalid choice. Try again: ");
                    scanf(" %c%c", &choice, &trash); // Prompt the user for choice 
					while (trash != '\n' && scanf("%c", &trash) == 1);
                }
            }
        }
        printf("Exiting Translation Search Mode...\n");
    }
}

/*
 * Function Name: exportFile()
 * Exports all dictionary data to a text file.
 * Prompts the user for a filename (max 30 characters) and writes all entries to that file.
 * Each entry is written as language-translation pairs in the format "Language: translation"
 * (one pair per line) with a blank line separating each entry. If the file exists, it will be overwritten.
 * @param entries    - Array of dictionary entries.
 * @param countEntry - Total number of entries.
 * @return none
 */
void exportFile(entryType *entries, int countEntry) 
{
    FILE *ptr;
    Str30 fileName;
    int i, 
		j,
		flag = 1;

    inputString(fileName, MAX_FILENAME, "Enter the filename to export data to [e.g., filename.txt]: ");

    ptr = fopen(fileName, "w");
    if (ptr == NULL) 
	{
        printf("Error opening file. Please check permissions and try again.\n");
        flag = 0;
    }

    if (flag) 
	{
        for (i = 0; i < countEntry; i++) 
		{
            for (j = 0; j < entries[i].pairCount; j++) 
			{
                fprintf(ptr, "%s: %s\n", entries[i].pair[j].lang, entries[i].pair[j].trans);
            }
            if (i < countEntry - 1) 
			{
                fprintf(ptr, "\n"); // Ensures a blank line between entries except after the last one
            }
        }
        printf("Successfully exported to %s!\n", fileName);
    }
	fclose(ptr);
}

/*
 * Function Name: importFile() 
 * Imports dictionary entries from a text file.
 * Prompts the user for a filename (max 30 characters) and opens the file for reading.
 * The file should follow the export format:
 *   - Each entry's language-translation pairs are in the format "Language: translation".
 *   - A blank line separates each entry.
 * The function performs the following steps:
 *   - Reads the filename from the user and attempts to open the file.
 *   - Uses `fgetc()` to check if the file is empty before proceeding.
 *   - If the file is empty or cannot be opened, an appropriate error message is displayed.
 *   - Reads and processes each line to extract language-translation pairs.
 *   - Detects new entries based on blank lines.
 *   - Displays each entry and prompts the user for confirmation before adding it.
 *   - Ensures that no more than MAX_PAIRS pairs are stored per entry, discarding extras.
 *   - Stops importing if the maximum number of dictionary entries (MAX_ENTRY) is reached.
 *   - Handles invalid lines by storing and displaying them before confirming the addition of an entry.
 * @param entries    - Array of entryType containing the dictionary entries.
 * @param countEntry - Pointer to the current number of entries.
 * @returns 1 if the import is successful, 0 if an error occurs.
 * Pre-condition: The file follows the specified export format; entries in the file are not assumed to be sorted.
 */
int importFile(entryType *entries, int *countEntry, char prompt[])
{
	FILE *ptr; // Variable to store the address of the file that will be opened
	Str30 fileName; // String to store the file name of the text file that will be opened 
	Str20 tempLang, // String to store the imported language from the file
		  tempTrans; // String to store the imported translation from the file
	char extraLang[MAX_PAIRS][MAX_LETTER], // 2D array to store the extra imported languages (more than the MAX_PAIRS already) from the file 
		 extraTrans[MAX_PAIRS][MAX_LETTER]; // 2D array to store the extra imported translations (more than the MAX_PAIRS already) from the file 
	char buffer[MAX_LETTER * 2], // Array of characters used to store the read lines from a file using fgets()
		 choice, 
		 invalidLines[MAX_ENTRY][MAX_CHARACTERS]; // 2D array of characters that store 150 invalid lines with the corresponding error message
	entryType tempEntry; // Temporary entry that will store the valid pairs that will be imported from the file 
	tempEntry.pairCount = 0; // Initialize the pair count of the temporary entry to avoid garbage values
	int entryFileNumber = 0, // Variable to store how many count of entry is being imported from the file
		flag = 1,
		i,
		extraPairCount = 0,	// Variable to store the count of extra pair in an imported entry from a file
		invalidCount = 0, // Variable to keep track of the count of invalid lines in the file that is being imported
		result = 0, // Variable to store if the process of importing is successful or not
		validEntryCount = 0; // Variable to keep track of the valid entry that will be imported

	inputString(fileName, MAX_FILENAME, "Please enter the text filename where the data will be \nloaded from [e.g., filename.txt]: "); // Prompt the user for the file name

	ptr = fopen(fileName, "r"); // Open the file for reading
	if (ptr == NULL) // If opening the file results in an error 
	{
		printf("Error opening file. Please check the file and try again. Redirecting back to %s.\n", prompt);
		flag = 0; // Prevents further processing
	}
	if (flag && fgetc(ptr) == EOF) // If the file is empty
	{
		printf("The file is empty. Please provide a valid file. Redirecting back to %s.\n", prompt);
		flag = 0; // Prevents further processing
	}
	if (*countEntry >= MAX_ENTRY) // If MAX_ENTRY is already reached, stop immediately
	{
		printf("Entry limit reached [%d]. Stopping import. Redirecting back to %s.\n", MAX_ENTRY, prompt);
		flag = 0; // Prevents further processing
	}
	if (flag) // If valid process, continue program
	{
		rewind(ptr); // Reset file pointer to the start of the file before reading

		while (fgets(buffer, sizeof(buffer), ptr) != NULL && *countEntry < MAX_ENTRY) // Read each line from the file until not the count of entry doesn't exceed the MAX_ENTRY
		{ // reads one line now
			// Check if the line is empty, indicating a new entry
			if (buffer[0] == '\n')
			{
				entryFileNumber++; // Increment entry count for every entry

				if (tempEntry.pairCount == 0) // If the entry has no valid pair
				{
					printf( RED "Skipping Entry #%d, it has 0 valid pairs." RESET "\n", entryFileNumber);
				}
				else if(tempEntry.pairCount + extraPairCount > MAX_PAIRS) // If the entry contains more than the MAX_PAIRS
				{
					// Display the entry in table format
					printf("\n  +---------------------------------------------------+\n");
					printf("  |                   Entry %-3d                       |\n", entryFileNumber);
					printf("  +-----+----------------------+----------------------+\n");
					printf("  | No. | Language             | Translation          |\n");
					printf("  +-----+----------------------+----------------------+\n");
					for (i = 0; i < tempEntry.pairCount; i++) // Print the first MAX_PAIRS pairs
					{
						printf("  | %-2d  | %-20s | %-20s |\n", i + 1, tempEntry.pair[i].lang, tempEntry.pair[i].trans);
					}

					for (i = 0; i < extraPairCount; i++) // Print the extra pairs
					{
						printf("  | %-2d  | %-20s | %-20s |\n", tempEntry.pairCount + i + 1, extraLang[i], extraTrans[i]);
					}
					printf("  +-----+----------------------+----------------------+\n\n");
					printf("Skipping Entry #%d, it exceeded the maximum number of pairs.\n", entryFileNumber);
				}
				else if (tempEntry.pairCount > 0) // If entry's pair count is less than or equal to MAX_PAIRS
				{
					printf("Detected an Entry. Now displaying Entry #%d from the file:\n", entryFileNumber);
					for (i = 0; i < invalidCount; i++)  // Print the invalid lines with the wrong format in the entry
					{
						printf("%s", invalidLines[i]);
					}
					// Display the valid entry using a table format
					printf("\n  +---------------------------------------------------+\n");
					printf("  |                   Entry %-3d                       |\n", entryFileNumber);
					printf("  +-----+----------------------+----------------------+\n");
					printf("  | No. | Language             | Translation          |\n");
					printf("  +-----+----------------------+----------------------+\n");
					for (i = 0; i < tempEntry.pairCount; i++) // Display all translation pairs for this entry
					{
						printf("  | %-2d  | %-20s | %-20s |\n", i + 1, tempEntry.pair[i].lang, tempEntry.pair[i].trans);
					}
					printf("  +-----+----------------------+----------------------+\n\n");
					printf("Do you want to add this entry? ");
					choice = getChoice();
					if (choice == 'Y' && *countEntry < MAX_ENTRY) // If the user chooses to add the entry to the database
					{
						entries[*countEntry] = tempEntry; // Store the imported entry in database
						(*countEntry)++; // Increment entry count
						if(*countEntry >= MAX_ENTRY)
						{
							printf("Invalid. Already exceeded maximum number of entries[%d]\n", MAX_ENTRY);
						}
						else
						{
							printf("Entry added.\n");
							validEntryCount++; // Increment the count of valid entries
						}
					}
					else // If the user chooses not to add the entry to the database
					{
						printf("Skipped entry.\n");
					}
				}
				invalidCount = 0; // Reset for the next entry
				tempEntry.pairCount = 0; // Reset for the next entry
				extraPairCount = 0;		 // Reset for the next entry
			}
			else
			{ // Process the current entry
				// Copies pair directly to the tempEntry
				// Scan everything before colon and expect the colon at this position and scan everything again before new line and store it to the temporary pair
				if(sscanf(buffer, "%[^:]: %[^\n]", tempLang, tempTrans) == 2)
				{
					if(strlen(tempLang) > 20 || strlen(tempTrans) > 20) // If the character of the language or translation exceeds 20 characters
					{
						sprintf(invalidLines[invalidCount], RED "[Entry #%d] Skipping invalid line: %s\t\t-> Language and translation must not exceed 20 characters.\n" RESET, entryFileNumber + 1, buffer);
						invalidCount++; // Increment the count of invalid line 
					}
					else if (tempEntry.pairCount < MAX_PAIRS) // If the pair count of the temporary still doesn't exceed the MAX_PAIRS
					{
						strcpy(tempEntry.pair[tempEntry.pairCount].lang, tempLang); // Store to the temp entry
						strcpy(tempEntry.pair[tempEntry.pairCount].trans, tempTrans); // Store to the temp entry
						tempEntry.pairCount++; // Increment pair count to allow further processing for the next pair
					}
					else if (extraPairCount < MAX_PAIRS) // If the temporary pair count already exceeds the MAX_PAIRS, then it allows for extra pairs (for printing only)
					{
						// copying of extra pairs
						strcpy(extraLang[extraPairCount], tempLang);
						strcpy(extraTrans[extraPairCount], tempTrans);
						extraPairCount++;
					}
				}
				else if (buffer[0] != '\n') // If there is an error in sscanf meaning the format of the line that is being imported is incorrect
				{	// Store the invalid line for printing later using sprintf
					sprintf(invalidLines[invalidCount], "[Entry #%d] Skipping invalid line: %s\t\t-> Must be of format: <language>: <translation>\n", entryFileNumber + 1, buffer);
					invalidCount++; // Increment the count of invalid lines
				}
			}
		}
		/* Process the last entry since the current algo is design to scan first to tempEntry then check if user wants to add
		 * but in the last entry case, we can't check for \n
		 */
		if (*countEntry < MAX_ENTRY && tempEntry.pairCount > 0)
		{
			entryFileNumber++; // Increment entry count for every entry

			if (tempEntry.pairCount == 0) // If the entry has no valid pair
			{
				printf("Skipping Entry #%d, it has 0 valid pairs.\n", entryFileNumber);
			}
			else if(tempEntry.pairCount + extraPairCount > MAX_PAIRS) // If the entry contains more than the MAX_PAIRS
			{
				printf("\n  +---------------------------------------------------+\n");
				printf("  |                   Entry %-3d                       |\n", entryFileNumber);
				printf("  +-----+----------------------+----------------------+\n");
				printf("  | No. | Language             | Translation          |\n");
				printf("  +-----+----------------------+----------------------+\n");
				for (i = 0; i < tempEntry.pairCount; i++) // Print the first MAX_PAIRS pairs
				{
					printf("  | %-2d  | %-20s | %-20s |\n", i + 1, tempEntry.pair[i].lang, tempEntry.pair[i].trans);
				}

				for (i = 0; i < extraPairCount; i++) // Print the extra pairs
				{
					printf("  | %-2d  | %-20s | %-20s |\n", tempEntry.pairCount + i + 1, extraLang[i], extraTrans[i]);
				}
				printf("  +-----+----------------------+----------------------+\n\n");
				printf("Skipping Entry #%d, it exceeded the maximum number of pairs.\n", entryFileNumber);
			}
			else if (tempEntry.pairCount > 0) // If entry's pair count is less than or equal to MAX_PAIRS
			{
				printf("Detected an Entry. Now displaying Entry #%d from the file:\n", entryFileNumber);
				for (i = 0; i < invalidCount; i++)  // Print the invalid lines with the wrong format in the entry
				{
					printf("%s", invalidLines[i]);
				}
				// Display the valid entry using a table format
				printf("\n  +---------------------------------------------------+\n");
				printf("  |                   Entry %-3d                       |\n", entryFileNumber);
				printf("  +-----+----------------------+----------------------+\n");
				printf("  | No. | Language             | Translation          |\n");
				printf("  +-----+----------------------+----------------------+\n");
				for (i = 0; i < tempEntry.pairCount; i++) // Display all translation pairs for this entry
				{
					printf("  | %-2d  | %-20s | %-20s |\n", i + 1, tempEntry.pair[i].lang, tempEntry.pair[i].trans);
				}
				printf("  +-----+----------------------+----------------------+\n\n");
				printf("Do you want to add this entry? ");
				choice = getChoice();
				if (choice == 'Y' && *countEntry < MAX_ENTRY) // If the user chooses to add the entry to the database
				{
					entries[*countEntry] = tempEntry; // Store the imported entry in database
					(*countEntry)++; // Increment entry count
					if(*countEntry >= MAX_ENTRY)
					{
						printf("Invalid. Already exceeded maximum number of entries[%d]\n", MAX_ENTRY);
					}
					else
					{
						printf("Entry added.\n");
						validEntryCount++; // Increment the count of valid entries
						sortEntry(entries, *countEntry);
						
					}
				}
				else // If the user chooses not to add the entry to the database
				{
					printf("Skipped entry.\n");
				}
			}
			invalidCount = 0; // Reset for the next entry
			tempEntry.pairCount = 0; // Reset for the next entry
			extraPairCount = 0;		 // Reset for the next entry
		}
	}
	if (flag && validEntryCount == entryFileNumber) // If all entries that are imported are all of valid format
	{
		printf("Import successful: All valid entries have been added.\n");
	    result = 1; 
	}
	else if(flag && validEntryCount < entryFileNumber && validEntryCount != 0) // If some of the entries are in the wrong format
	{
	    printf("Import completed, but some or all entries were invalid and skipped.\n");
	    result = 1;
	}
	else // If importing failed
	{
		printf("Import failed.\n");
		result = 0;
	}
	
	sortEntry(entries, *countEntry); // Sort entry after the importing
	fclose(ptr); // Close the file
	sortEntry(entries, *countEntry);
	return result; // Return 1 if importing process is a success, 0 if otherwise
}

/*
 * Function Name: exitFunction() 
 * Asks the user if they want to exit the Manage Data menu. This function 
 * also clears the information in the lists thus emptying the database except
 * for the file that is saved
 * @param entries    - Array of entryType containing the dictionary entries.
 * @param countEntry - Pointer to the current number of entries.
 * @returns 0 if 'Y' (exit) is chosen, or 1 if 'N' (stay) is chosen.
 */
int exitFunction(entryType *entries, int *countEntry)
{
	int entriesToDel = 0, // Variable to store how many entries will be deleted
		pairToDel = 0, // Variable that will store how many pairs to delete within an entry
		exitFlag = 1, 
		i, 
		j;
	char choice = 'N'; 
	printf("Exit this menu? ");
	choice = getChoice();

	if (choice == 'Y') // If the user wants to exit the function
	{
		if (*countEntry > 0) // Only delete when there is an entry to delete
		{
			entriesToDel = *countEntry; // Store how many entries that are going to be deleted
			for (i = 0; i < entriesToDel; i++) // Loop through all entries that to be deleted
			{
				pairToDel = entries[i].pairCount; // Store how many pairs to delete
				for (j = 0; j < pairToDel; j++) // Loop through all the pairs to be deleted
				{
					entries[i].pair[j].lang[0] = '\0'; // Delete the language within that entry
					entries[i].pair[j].trans[0] = '\0'; // Delete the translation within that entry
				}
				entries[i].pairCount = 0; // Set pair count of the entry as 0 since every pair was deleted
			}
			*countEntry = 0; // Set count of entry to zero since all entries are deleted
			printf("Clearing information in the lists. Press any key to continue...\n");
		    getch();  // Waits for any key	
		}
		exitFlag = 0; 
	}

	else if (choice == 'N') // The user chooses not to exit the function
	{
		exitFlag = 1;		
	}

	return exitFlag;
}

/*
 * Function Name: manageDataMenu() 
 * Display the manage data menu and prompt the user to choose what they want to do
 * @param none
 * @returns an integer choice containing what the user chose to do.
 */
int manageDataMenu()
{
	int choice = 0;
	char trash;
	do
	{
		printf("\n=========================================================\n");
	    printf("\n\t\t+------------------------+\n");
	    printf("\t\t|    "GREEN"MANAGE DATA MENU"RESET"    |\n");
	    printf("\t\t+------------------------+\n\n");
		printf("\t\t[1]  => Add Entry\n");
		printf("\t\t[2]  => Add Translations\n");
		printf("\t\t[3]  => Delete Entry\n");
		printf("\t\t[4]  => Delete Translation\n");
		printf("\t\t[5]  => Display All Entries\n");
		printf("\t\t[6]  => Search Word\n");
		printf("\t\t[7]  => Search Translation\n");
		printf("\t\t[8]  => Export\n");
		printf("\t\t[9]  => Import\n");
		printf("\t\t[10] => Exit\n\n");
		
		printf("\t\tEnter your choice: ");
 
		if (scanf(" %d%c", &choice, &trash) != 2) // Prompt the user for what they want to do
		{
			printf("\n=========================================================\n");
			printf("\n Invalid input! Please enter a number between 1 and 10.\n");
			choice = 0;
		}
		else if (choice < 1 || choice > 10) // User chooses an invalid option
		{
			printf("\n=========================================================\n");
			printf("\n Invalid choice! Please enter a number between 1 and 10.\n");
			choice = 0;
		}
		
		while (trash != '\n' && scanf("%c", &trash) == 1); // Ensured that the user inputs a valid choice
		
	} while (choice < 1 || choice > 10);
	printf("\n=========================================================\n");
 
    return choice; // Return what the program chooses to do
}
 
/*
 * Function Name: translateMenu() 
 * Display the translate menu and prompt the user to choose what they want to do
 * @param none
 * @returns an integer choice containing what the user chose to do.
 */
int translateMenu()
{
	int choice = 0;
	char trash;
	
	do
	{
		printf("\n=========================================================\n");
		printf("\n\t\t+------------------------+\n");
	    printf("\t\t|     "GREEN"TRANSLATE MENU"RESET"     |\n");
	    printf("\t\t+------------------------+\n\n");
		printf("\t\t[1]  => Translate Text Input\n");
		printf("\t\t[2]  => Translate Text File\n");
		printf("\t\t[3]  => Exit\n");
		printf("\t\tEnter your choice: ");
	
		if (scanf(" %d%c", &choice, &trash) != 2) // Prompt the user on what they want to do 
		{
			printf("\n=========================================================\n");
			printf("\n Invalid choice! Please enter a valid number between 1 to 3\n");
			while (trash != '\n' && scanf("%c", &trash) == 1); // Input buffer
			choice = 0; // Reset choice to zero
		}
		else if (choice < 1 || choice > 3)
		{
			printf("\n=========================================================\n");
			printf("\n Invalid choice! Please enter a valid number between 1 to 3\n");
			while (trash != '\n' && scanf("%c", &trash) == 1);
			choice = 0; // Reset choice to zero
		}
		
		while (trash != '\n' && scanf("%c", &trash) == 1); 
		
	} while (choice < 1 || choice > 3);
	printf("\n=========================================================\n");

    return choice;
}
 
/*
 * Function Name: mainMenu() 
 * Display the main menu and prompt the user to choose what they want to do
 * @param none
 * @returns an integer choice containing what the user chose to do.
 */
int mainMenu()
{		
	int choice;
	char trash;
 	do
 	{
 		printf("\n=========================================================\n");
		printf(GREEN"      _____                    _       _             \n"RESET);
		printf(GREEN"     |_   _| __ __ _ _ __  ___| | __ _| |_ ___  _ __ \n"RESET);
		printf(GREEN"       | || '__/ _` | '_ \\/ __| |/ _` | __/ _ \\| '__|\n"RESET);
		printf(GREEN"       | || | | (_| | | | \\__ \\ | (_| | || (_) | |   \n"RESET);
		printf(GREEN"       |_||_|  \\__,_|_| |_|___/_|\\__,_|\\__\\___/|_|   \n"RESET);
		printf("\n          By: Edriene Paingan & Marc Santos\n");
		printf("\n=========================================================\n");
		printf("\n\t\t[1] => Manage Data Menu\n");
		printf("\t\t[2] => Translate Menu\n");
		printf("\t\t[3] => Exit\n\n");
		printf("\t\tEnter your choice: ");
 
		if (scanf(" %d%c", &choice, &trash) != 2)
		{
	
			printf("Invalid input! Please enter a number between 1 and 3.\n");
			choice = 0;
		}
		while (trash != '\n' && scanf("%c", &trash) == 1);
		if (choice < 1 || choice > 3)
		{
			printf("Invalid input! Please enter a number between 1 and 3.\n");
			choice = 0;
		}
	}while (choice < 1 || choice > 3);
 	printf("\n=========================================================\n");
	return choice;	
}
