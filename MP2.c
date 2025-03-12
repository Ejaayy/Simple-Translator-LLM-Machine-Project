char getChoice(char choice) {
    int validChoice = 0;
    char temp;

    while (!validChoice) 
	{
        printf("Please enter 'y' or 'n': ");

        if (scanf(" %c", &choice) == 1) 
		{ // Read character input
            while ((temp = getchar()) != '\n' && temp != EOF);  // Clear input buffer

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
		else
			while ((temp = getchar()) != '\n' && temp != EOF);  
    }
    return choice;
}

void updateLanguageTranslationPair(entryType *entry, Str20 language, Str20 translation)
{
  strcpy(entry->pair[entry->pairCount].lang, language);
  strcpy(entry->pair[entry->pairCount].trans, translation);
  entry->pairCount++;
}

void showMatchedEntries(entryType entries[], int matchedIndexes[], int matchCount)
{
  int i, j;
  for (i = 0; i < matchCount; i++) // loops for all match count (same entry)
  {
    entryType *entry = &entries[matchedIndexes[i]]; // prints all the matched index
    printf("Entry %d:\n", matchedIndexes[i] + 1);

    for (j = 0; j < entry->pairCount; j++) // prints members of that entry
    {
      printf("%d.Language: %-15s Translation: %s\n", j+1,entry->pair[j].lang, entry->pair[j].trans);
    }
  }
}
//made it multifunctional
int isDuplicate(entryType entries[], int countEntry, Str20 language, Str20 translate, int matchedIndexes[], int currentEntryIndex) 
{
    int matchPairCount = 0;
    int found, i, j;

    // Determine the range of entries to check
    int startIndex, endIndex;

    if (currentEntryIndex == -1) {
        startIndex = 0;         // Check all entries
        endIndex = countEntry;
    } 
    else {
        startIndex = currentEntryIndex; // Check only the current entry
        endIndex = currentEntryIndex + 1;
    }

    // Search for duplicates within the specified range
    for (i = startIndex; i < endIndex; i++) 
    {
        found = 0; // Reset flag for each entry
        for (j = 0; j < entries[i].pairCount; j++) 
        {
            if (!strcmp(entries[i].pair[j].lang, language) && 
                !strcmp(entries[i].pair[j].trans, translate)) 
            {
                if (!found) 
                {
                    matchedIndexes[matchPairCount++] = i;
                    found = 1; // Prevent counting this entry twice
                }
            }
        }
    }
    return matchPairCount;
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
        if(ch == '\n'){
        	printf("Invalid input. Must contain at least one character.\n");
		}
        ch = getchar();  // Read the next character

    } while (i < MAX_LETTER && ch != '\n'); // Stop condition
    
    sentence[i] = '\0'; // Null-terminate the string
}

void inputFileName(char sentence[]) 
{
    int i = 0;
    char ch;

    // Skip any leading newline or spaces left in the input buffer
    while ((ch = getchar()) == '\n' || ch == ' ');

    do {
        sentence[i] = ch;  // Store the character in the array
        i++;
        if(ch == '\n'){
        	printf("Invalid input. Must contain at least one character.\n");
		}
        ch = getchar();  // Read the next character

    } while (i < MAX_FILENAME && ch != '\n'); // Stop condition
    
    sentence[i] = '\0'; // Null-terminate the string
}

// Function to get language-translation pair
void getLanguageTranslation(char language[], char translation[])
{
    printf("Input for language-translation pair:\n");
    printf("Language: ");
    inputWord(language);  // Get language input
    toLowerString(language) ;
    printf("Translation: ");
    inputWord(translation);  // Get translation input
	toLowerString(translation);
}

int countEntryIsZero(int countEntry)
{
	int validIndex = 1;
	if (countEntry == 0) 
    	validIndex = 0; // Prevent further processing
    return validIndex; 
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
    Str20 language, translation;

    if (*countEntry >= MAX_ENTRY)
    {
        printf("Cannot add more entries. Dictionary is full!\n");
        entryFlag = 0;
    }
    else
    {
        while (choice == 'y' && entryFlag)
        {
            getLanguageTranslation(language, translation);
            
            // Check for duplicates across all entries
            matchCount = isDuplicate(entries, *countEntry, language, translation, matchedIndexes, -1); //Try to change -1 to a flag that it is only one single entry there is to check

            if (matchCount > 0)
            {
                showMatchedEntries(entries, matchedIndexes, matchCount);
                printf("This language-translation pair already exists!\n");
                printf("Is this a new entry? (y/n): ");
                choice = getChoice(choice);

                if (choice == 'n')
                {
                    entryFlag = 0;
                }
                else if (choice == 'y')
                {
                    entries[*countEntry].pairCount = 0;
                    updateLanguageTranslationPair(&entries[*countEntry], language, translation);
                    printf("New entry has been added successfully!\n");

                    // Adding extra pairs within the same entry
                    while (choice == 'y')
                    {
                        printf("Add another language-translation pair to the current entry? (y/n): ");
                        choice = getChoice(choice);

                        if (choice == 'y')
                        {
                            getLanguageTranslation(language, translation);

                            // Check for duplicates **within the current entry**
                            matchCount = isDuplicate(entries, *countEntry, language, translation, matchedIndexes, *countEntry);

                            if (matchCount > 0)
                            {
                                printf("This pair already exists within the current entry! Skipping...\n");
                            }
                            else
                            {
                                updateLanguageTranslationPair(&entries[*countEntry], language, translation);
                                printf("New language-translation pair has been added successfully!\n");
                            }
                        }
                    }
                    (*countEntry)++;
                }
            }
            else
            {
                printf("This language-translation pair does not exist!\nIs this a new entry? (y/n): ");
                choice = getChoice(choice);

                if (choice == 'n')
                {
                    entryFlag = 0;
                }
                else if (choice == 'y')
                {
                    entries[*countEntry].pairCount = 0;
                    updateLanguageTranslationPair(&entries[*countEntry], language, translation);
                    printf("New entry has been added successfully!\n");

                    // Adding extra pairs within the same entry
                    while (choice == 'y')
                    {
                        printf("Add another language-translation pair to the current entry? (y/n): ");
                        choice = getChoice(choice);

                        if (choice == 'y')
                        {
                            getLanguageTranslation(language, translation);

                            // Check for duplicates wihtin current entry
                            matchCount = isDuplicate(entries, *countEntry, language, translation, matchedIndexes, *countEntry);

                            if (matchCount > 0)
                            {
                                printf("This pair already exists within the current entry! Skipping...\n");
                            }
                            else
                            {
                                updateLanguageTranslationPair(&entries[*countEntry], language, translation);
                                printf("New language-translation pair has been added successfully!\n");
                            }
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

    matchCount = isDuplicate(entries, *countEntry, language, translation, matchedIndexes, -1); // Check if an entry exists with the given language and translation pair
                                                                                           // Store matching entry indexes in matchedIndexes and count in matchCount

    if (matchCount <= 0)                                                                   // If no matching entry is found
    {
        printf("The entry doesn't exist. Would you like to add a new entry? (y/n): ");                            // Inform the user that no entry exists
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
        showMatchedEntries(entries, matchedIndexes, matchCount);                                  // Show all matched entries

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

                printf("Add another language-translation pair? (y/n): ");                 // Ask the user if they want to add another pair
                choice = getChoice(choice);                                                 // Get the user's choice
            } while (choice == 'y' && entries[selectedIndex].pairCount < MAX_PAIRS);        // Loop to add more translations, but prevent adding if the max count is reached
        }
    }
}

void sortEntry(entryType *entry, int countEntry)
{
    int englishIndex[MAX_ENTRY] = {0};
    int notEnglishIndex[MAX_ENTRY] = {0};
    int englishPairIndex[MAX_ENTRY] = {0}; // Store index of the English pair for each entry
	Str20 temp;
	entryType tempEntry[countEntry];
	
    int englishCount = 0;
    int notEnglishCount = 0;
    int i, j,k;
    int found;
    
    int idx1, idx2, pairIdx1, pairIdx2;
    
    // Separate entries into those with and without English
	for (i = 0; i < countEntry; i++) {
	    found = 0; // Reset flag for each entry
	    for (j = 0; j < entry[i].pairCount; j++) {
	        if (strcmp("english", entry[i].pair[j].lang) == 0 && found == 0) {
	            found = 1; // Mark that English was found
	            englishIndex[englishCount] = i;       // Store entry index
	            englishPairIndex[englishCount++] = j;   // Store the English pair index
	        }
	    }
	    if (found == 0) { // If no English translation was found
	        notEnglishIndex[notEnglishCount++] = i; // Store entry index without English
	    }
	}

    // INTER-ENTRY: Bubble Sort the englishIndex array based on the English translation
    for (i = 0; i < englishCount - 1; i++) {
        for (j = 0; j < englishCount - i - 1; j++) {
            idx1 = englishIndex[j];
            idx2 = englishIndex[j + 1];
            pairIdx1 = englishPairIndex[j];
            pairIdx2 = englishPairIndex[j + 1];

            if (strcmp(entry[idx1].pair[pairIdx1].trans, entry[idx2].pair[pairIdx2].trans) > 0) {
                // Swap the indices
                int swapTemp = englishIndex[j];
                englishIndex[j] = englishIndex[j + 1];
                englishIndex[j + 1] = swapTemp;

                // Swap the corresponding englishPairIndex values
                swapTemp = englishPairIndex[j];
                englishPairIndex[j] = englishPairIndex[j + 1];
                englishPairIndex[j + 1] = swapTemp;
            }
        }
    }

	//APPEND EVERYTHING TO THE ORIGINAL ENTRY
    int newIndex = 0;
    for (i = 0; i < englishCount; i++) {
        tempEntry[newIndex++] = entry[englishIndex[i]];
    }
    for (i = 0; i < notEnglishCount; i++) {
        tempEntry[newIndex++] = entry[notEnglishIndex[i]];
    }

    // Copy back the sorted entries to the original array
    for (i = 0; i < countEntry; i++) {
        entry[i] = tempEntry[i];
    }
   
	// INTRA-ENTRY: Bubble sort the language-translation pairs for each entry
	for (i = 0; i < countEntry; i++) { // for each entry
	    for (j = 0; j < entry[i].pairCount - 1; j++) {
	        for (k = 0; k < entry[i].pairCount - j - 1; k++) {
	            if (strcmp(entry[i].pair[k].lang, entry[i].pair[k + 1].lang) > 0) {
	                translationPairType tempPair = entry[i].pair[k];
	                entry[i].pair[k] = entry[i].pair[k + 1];
	                entry[i].pair[k + 1] = tempPair;
	            }
	        }
	    }
	}
}

void displayAllEntries(entryType *entry, int countEntry)
{
	if(!countEntryIsZero(countEntry))
		printf("No entries available to display.\n");
	
	else
	{
		int i,j;
		sortEntry(entry, countEntry); 
	
		for(i=0;i<countEntry;i++)
		{
			printf("\nEntry %d:\n", i + 1);
			for(j=0;j<entry[i].pairCount;j++)
			{
				printf("%d.Language: %-15s Translation: %s\n", j+1, entry[i].pair[j].lang, entry[i].pair[j].trans);
			}
		}	
	}
}

void displayModeAllEntries(entryType entry[], int countEntry)
{
	int j;
	if(!countEntryIsZero(countEntry))
		printf("No entries available to display.\n");
	
	else
	{
		int i = 0; // Current index
	    char choice, temp;
	    sortEntry(entry, countEntry); // Sort everything
	
	    printf("You are now in Display View Mode.\n");
	    printf("Press 'N' to go to the Next entry.\n");
	    printf("Press 'P' to go to the Previous entry.\n");
	    printf("Press 'X' to exit Display View.\n");
		
		do
		{
			printf("Select which entry to Display (1-%d): ", countEntry);
			scanf("%d", &i);
			if(i<1 || i > countEntry)
			{
				printf("Invalid Entry Number! Please try again.\n");
			}
		}while(i<1 || i > countEntry);
		
		i--; //index
		
	    do 
		{
	        // Print the current entry
	        printf("\nEntry %d:\n", i + 1);
	        for (j = 0; j < entry[i].pairCount; j++) 
			{
	            printf("%d.Language: %-15s Translation: %s\n", j+1, entry[i].pair[j].lang, entry[i].pair[j].trans);
	        }
	
	        // Ask for user input
	        printf("\nEnter Choice (N/P/X): ");
	        scanf(" %c", &choice); // Added a space before %c to handle previous newlines
	        while ((temp = getchar()) != '\n' && temp != EOF);
	
	        // Handle navigation
	        if (choice == 'N' || choice == 'n') 
			{
	            if (i >= countEntry - 1) 
				{
	                printf("WARNING: Already at the last entry!\n");
	            } 
				else 
				{
	                i++;
	            }
	        } 
			else if (choice == 'P' || choice == 'p') 
			{
	            if (i <= 0) 
				{
	                printf("WARNING: Already at the first entry!\n");
	            } 
				else 
				{
	                i--;
	            }
	        }
	    }while (choice != 'X' && choice != 'x');
	    printf("Exiting Display View Mode...\n");
	}
}

void deleteEntry(entryType entries[], int *countEntry)
{
	if(!countEntryIsZero(*countEntry))
		printf("No entries available to display.\n");
	
	else
	{
	    int selectedIndex;
	    int validIndex = 1;
	    int i, j;
	    int transLen = 0;
	    int langLen = 0;
		
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
		    
		    for (i = 0; i < entries[*countEntry - 1].pairCount; i++) 
			{
			    // Get the length of the string in lang and trans
			    langLen = strlen(entries[*countEntry - 1].pair[i].lang);
			    transLen = strlen(entries[*countEntry - 1].pair[i].trans);
			
			    // Clear all characters in the lang string
			    for (j = 0; j < langLen; j++) 
				{
			        entries[*countEntry - 1].pair[i].lang[j] = '\0';  // Clear language field
			    }
			
			    // Clear all characters in the trans string
			    for (j = 0; j < transLen; j++) 
				{
			        entries[*countEntry - 1].pair[i].trans[j] = '\0'; // Clear translation field
			    }
			}
		    
		    entries[*countEntry - 1].pairCount = 0;
		    
		    // Reduce the entry count
		    (*countEntry)--;
		
		    printf("Entry deleted successfully!\n");
	    }
	}
}

void deleteTranslation(entryType *entries, int *countEntry)
{
	if(!countEntryIsZero(*countEntry))
		printf("No entries available to display.\n");
	
	else
	{
		// Display all current entries before asking which one to delete
		int selectedIndex = 0;
		int selectedPairIndex = 0; 
		int validIndex = 1;
		int validPairIndex = 1;
		char choice = 'y';
		int i, j;
		
		if (*countEntry == 0) 
		{
	        printf("No entries available to delete.\n");
	        validIndex = 0; // Prevent further processing
	    }
		
		if (validIndex)
		{
			displayAllEntries(entries, *countEntry);
		
		    printf("Enter the entry number to delete (1-%d): ", *countEntry);
			scanf("%d", &selectedIndex);    
			
			if (selectedIndex < 1 || selectedIndex > *countEntry)
			{
			    printf("Invalid entry number! Redirecting back to Manage Data Menu.\n");
			    validIndex = 0; 
			}
			else
			{
				selectedIndex--;
			} 
		    
		    // Convert 1-based index to 0-based index
		}
		    
		while (validIndex)
		{
			printf("Enter the pair number to delete (1-%d): ", entries[selectedIndex].pairCount);
			scanf("%d", &selectedPairIndex);    
				
			if (selectedPairIndex < 1 || selectedPairIndex > entries[selectedIndex].pairCount)
			{
				printf("Invalid pair number! Continue deleting pair? ");
				choice = getChoice(choice);
				    if (choice == 'n')
					{
		                validIndex = 0;
		        	}
			}
			else
			{
				selectedPairIndex--;
				        
				for (i = selectedPairIndex; i < entries[selectedIndex].pairCount - 1; i++)
				{
						entries[selectedIndex].pair[i] = entries[selectedIndex].pair[i + 1]; // Overwrite current entry with the next entry
				}
				entries[selectedIndex].pairCount--;
				
				printf("Continue deleting pair? ");
				choice = getChoice(choice);
				    if (choice == 'n')
					{
		                validIndex = 0;
		        	}
			
				if (entries[selectedIndex].pairCount == 0) 
				{
	                for (j = selectedIndex; j < *countEntry - 1; j++) 
					{
	                    entries[j] = entries[j + 1]; // Shift entries left
	                }
	                (*countEntry)--;
	                printf("Entry has been deleted as it had no remaining pairs.\n");
	                validIndex = 0;
	        	}
			}
		} 	
	}
}

void searchWord(entryType *entries, int countEntry){
	Str20 translationInput;
	printf("Enter word: ");
	inputWord(translationInput);
	
	//display entries that have matching
	int i,j;
	
	int sameEntryIndex[MAX_ENTRY] = {0};
	int sameEntryCount = 0;
	
	for (i = 0; i < countEntry; i++) {
	    for (j = 0; j < entries[i].pairCount; j++) {
	    	if(strcmp(entries[i].pair[j].trans,translationInput)==0){
	    		sameEntryIndex[sameEntryCount++] = i;
			} 
		}
	}
	
	if(sameEntryCount == 0){
		printf("Word does not exist. Redirecting back to Menu...\n");
	}
	else{
		showMatchedEntries(entries, sameEntryIndex, sameEntryCount);		
	}
}

void searchTranslation(entryType *entries, int countEntry)
{
	int matchedIndexes[MAX_ENTRY] = {0};
    int matchCount = 0;
	Str20 language, translation;
	
	printf("Input pair to look for: \n");
	getLanguageTranslation(language, translation);
	matchCount = isDuplicate(entries, countEntry, language, translation, matchedIndexes, -1);
	
	if (!matchCount)
	{
		printf("The pair does not exist! Redirecting back to Manage Data menu.\n");
	}
	
	else 
	{
		showMatchedEntries(entries, matchedIndexes, matchCount);
	}
}

void exportFile(entryType *entries, int countEntry)
{
	FILE *ptr;
	Str30 fileName;
	int i,j;
	int flag = 1;
	
	printf("Please enter the filename of the text file you want to import (e.g., filename.txt): ");
	inputFileName(fileName);
    
	ptr = fopen(fileName,"w");
	if (ptr == NULL) 
	{
        printf("Error opening file. Please check the file and try again.\n");
        flag = 0;
    }
    if (flag)
	{
		sortEntry(entries,countEntry);
		for(i = 0; i < countEntry; i++)
		{
		    for (j = 0; j < entries[i].pairCount; j++) 
			{
	             fprintf(ptr, "%s: %s\n", entries[i].pair[j].lang, entries[i].pair[j].trans);
	        }
			fprintf(ptr,"\n");
		}
		fclose(ptr);
	}
	
	printf("Successfully exported to %s! Redirecting back to Manage Data menu.\n", fileName);
}

void importFile(entryType *entries, int *countEntry) 
{
    FILE *ptr;
    Str30 fileName;
    Str20 tempLang, tempTrans, extraLang[MAX_PAIRS], extraTrans[MAX_PAIRS];
    char buffer[MAX_LETTER * 2];
    entryType tempEntry;
    int entryFileNumber = 0;
    char choice;
    int flag = 1;
    int i;
    int extraPairCount = 0;
    int stopProcessing = 0;
    
    // Ask the user for the filename
    printf("Please enter the filename of the text file you want to import (e.g., filename.txt): ");
    inputFileName(fileName);

    // Open the file for reading
    ptr = fopen(fileName, "r");
    if (ptr == NULL) 
	{
        printf("Error opening file. Please check the file and try again.\n");
        flag = 0;
    }
    if (flag && fgetc(ptr) == EOF) 
	{
	    printf("The file is empty. Please provide a valid file. Redirecting back to Manage Data menu.\n");
	    flag = 0;
	}
	
	// If MAX_ENTRY is already reached, stop immediately
    if (*countEntry >= MAX_ENTRY) 
    {
        printf("Entry limit reached (%d). Stopping import. Redirecting back to Manage Data menu.\n", MAX_ENTRY);
        flag = 0;
    }
	if (flag)
	{
		rewind(ptr);  //Reset file pointer before reading
		
	    // Read each line from the file
	    while (fgets(buffer, sizeof(buffer), ptr) != NULL) 
		{ //reads one line now
		
			if (*countEntry >= MAX_ENTRY) 
            {
                printf("Entry limit reached (%d). Stopping import. Redirecting back to Manage Data menu.\n", MAX_ENTRY);
                stopProcessing = 1; // Set flag to stop further processing
            }
            
            if (!stopProcessing)
            {
	            // Check if the line is empty, indicating a new entry
		        if (buffer[0] == '\n') 
				{
		            entryFileNumber++; // Increment entry count
		            printf("Detected an Entry. Now displaying Entry #%d from the file:\n", entryFileNumber);
		            
		            // Display all translation pairs for this entry
		            for (i = 0; i < tempEntry.pairCount; i++) 
					{
		            	printf("%d.Language: %-15s Translation: %s\n", i+1, tempEntry.pair[i].lang, tempEntry.pair[i].trans);
		            }
		            
		            for (i = 0; i < extraPairCount; i++)
		            {
		            	printf("%d.Language: %-15s Translation: %s\n", tempEntry.pairCount + 1 + i, extraLang[i], extraTrans[i]);
					}
		            
		            // Ask the user whether to add this entry
		            if (tempEntry.pairCount < MAX_PAIRS)
		            {
		            	printf("Do you want to add this entry? (y/n): ");
		            	choice = getChoice(choice);
		            	if (choice == 'y') 
						{
		                	entries[*countEntry] = tempEntry; // Store entry in database
		                	(*countEntry)++; // Increment entry count
		            	}
					}
					else
			        {
			            printf("Skipping this entry because it exceeded the maximum number of pairs (%d).\n", MAX_PAIRS);
			        }
		            tempEntry.pairCount = 0; // Reset for the next entry
		            extraPairCount = 0; // Reset for the next entry
		        } 
		        else 
				{ //process the current entry
		        	//copies pair directly to the tempEntry
		        	// %[^\n] means it will scan everything after space until new line
		        	sscanf(buffer, "%[^:]: %[^\n]", tempLang, tempTrans);
		        	if (tempEntry.pairCount < MAX_PAIRS)
			        {
			        	strcpy(tempEntry.pair[tempEntry.pairCount].lang, tempLang);
			        	strcpy(tempEntry.pair[tempEntry.pairCount].trans, tempTrans);
			            tempEntry.pairCount++; // Increment pair count
			        }
			        else if (extraPairCount < MAX_PAIRS) //limit to 10 extra pairs
			        {
			            // copying of extra pairs
			            strcpy(extraLang[extraPairCount], tempLang);
			            strcpy(extraTrans[extraPairCount], tempTrans);
			            extraPairCount++;
			        }
		        }
			}
	    }
	    // Process the last entry since the current algo is design to scan first to tempEntry then check if user wants to add
	    //but in the last entry case, we cant check for \n
	    
	    if(!stopProcessing && *countEntry < MAX_ENTRY)
	    {
		    entryFileNumber++; // Increment entry count
            printf("Detected an Entry. Now displaying Entry #%d from the file:\n", entryFileNumber);
            
            // Display all translation pairs for this entry
            for (i = 0; i < tempEntry.pairCount; i++) 
			{
            	printf("%d.Language: %-15s Translation: %s\n", i+1, tempEntry.pair[i].lang, tempEntry.pair[i].trans);
            }
            
            for (i = 0; i < extraPairCount; i++)
            {
            	printf("%d.Language: %-15s Translation: %s\n", tempEntry.pairCount + 1 + i, extraLang[i], extraTrans[i]);
			}
            
            // Ask the user whether to add this entry
            if (tempEntry.pairCount < MAX_PAIRS)
            {
            	printf("Do you want to add this entry? (y/n): ");
            	choice = getChoice(choice);
            	if (choice == 'y' && *countEntry < MAX_ENTRY) 
				{
                	entries[*countEntry] = tempEntry; // Store entry in database
                	(*countEntry)++; // Increment entry count
            	}
			}
			else
	        {
	            printf("Skipping this entry because it exceeded the maximum number of pairs (%d).\n", MAX_PAIRS);
	        }
		}
	}
	// Close the file after reading	
	fclose(ptr);
}

int exitFunction()
{
	char choice = 'n';
	int exitFlag = 1;
	printf("Exit this menu? ");
	choice = getChoice(choice);
	if (choice == 'y')
		exitFlag = 0;
		
	else if (choice == 'n')
		exitFlag = 1;
		
	return exitFlag;
}

int displayManageDataMenu()
{
    int choice;
    do
    {
        printf("\n===== MANAGE DATA MENU =====\n");
        printf("1. Add Entry\n");
        printf("2. Add Translations\n");
        printf("3. Delete Entry\n");
        printf("4. Delete Translation\n");
        printf("5. Display All Entries\n");
        printf("6. Search Word\n");
        printf("7. Search Translation\n");
        printf("8. Export\n");
        printf("9. Import\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n'); // Clear input buffer
            printf("Invalid input! Please enter a number between 1 and 10.\n");
            choice = 0;
        }
        else if (choice < 1 || choice > 10)
        {
            printf("Invalid choice! Please enter a number between 1 and 10.\n");
        }

    } while (choice < 1 || choice > 10);

    return choice;
}

int translateMenu()
{
    int choice;
    do
    {
        printf("\n===== TRANSLATE MENU =====\n");
        printf("1. Translate Text Input\n");
        printf("2. Translate Text File\n");
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

int displayMainMenu()
{		
	int choice;
	do
	{
	    printf("\n===== TRANSLATOR NI ALING NENA =====\n");
	    printf("1. Manage Data Menu\n");
	    printf("2. Translate Menu\n");
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
	}while (choice < 1 || choice > 3);
	return choice;	
}
