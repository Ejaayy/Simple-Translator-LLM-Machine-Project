

int filterWords(char *textInput, Str20 filteredWords[]) {
    int wordCount = 0;       
    Str20 word = {0};        
    int wordIndex = 0;      
    int i;
    
    // Loop through each character in the textInput
    for (i = 0; textInput[i] != '\0'; i++) {
        
		if (isalpha(textInput[i]) && wordIndex < sizeof(Str20) - 1) {
		    word[wordIndex++] = textInput[i];
		}
        
        else if (textInput[i] == ' ' || textInput[i] == '\n') { // space or \n means end of a word
            
            word[wordIndex] = '\0';  // Null char the word to mark its end
                
            if (wordCount < MAX_WORDS) { // Store the word in the filteredWords array if there's still space
                strcpy(filteredWords[wordCount++], word);
            }

            wordIndex = 0; 

        }
    }

    // Handle the last word
    //checks if ther is still a word thats needed to be put into filtered words
    if (wordIndex > 0 && wordCount < MAX_WORDS) {
        word[wordIndex] = '\0';       // Null the final word
        strcpy(filteredWords[wordCount++], word);  // Store it in the array
    }

    return wordCount;  // Return the total number of words filtered
}

void printFilteredWords(Str20 filteredWords[], int wordCount) {
    printf("Filtered words:\n");
    for (int i = 0; i < wordCount; i++) {
        printf("%s\n", filteredWords[i]);
    }
}

char* translateWord(entryType entries[], int countEntry, Str20 filteredWord, Str20 sourceLanguage, Str20 outputLanguage) 
{
    static Str20 translatedWord = {0}; 
    int matchedIndexes[MAX_WORDS];        
    int matchPairCount;
    int i, j;
    int foundIndex = -1;               
    int found = 0;                    

    // Default to original word (if no translation is found)
    strcpy(translatedWord, filteredWord);

    // Call isDuplicate to find matching entries (same source language and translation )
    matchPairCount = isDuplicate(entries, countEntry, sourceLanguage, filteredWord, matchedIndexes, -1);

    if (matchPairCount > 0) //if a matyched entry is found
    {
        for (i = 0; i < matchPairCount && !found; i++) 
        {
            for (j = 0; j < entries[matchedIndexes[i]].pairCount && !found; j++) //checks that entry
            {
                if (strcmp(entries[matchedIndexes[i]].pair[j].lang, outputLanguage) == 0) //checks if the language user wants to output exists
                {
                    foundIndex = j; // Store index of the correct pair
                    found = 1;      // Set flag to stop further searching
                }
            }
        }

        if (found) 
        {
            strcpy(translatedWord, entries[matchedIndexes[i - 1]].pair[foundIndex].trans);
        }
    }

    return translatedWord;
}

void translateTextInput(entryType *entries, int countEntry) {
	
	char sourceText[151] = {0};  // Assume text is at most 150 characters
	char choice = 'y';
	Str20 sourceLanguage;
	Str20 outputLanguage;
	Str20 filteredWords[MAX_WORDS];  // Array to store filtered words
	Str20 translatedWords[MAX_WORDS];  // Array to store filtered words
	int wordCount = 0;  // Tracks number of filtered words
	int i;

	do {
		// Ask for source language
		printf("What language is the source text you're going to input you bitch?: ");
		inputWord(sourceLanguage);
		
		// Ask for target language
		printf("What language are you translating it into you bitch?: ");
		inputWord(outputLanguage);
		
		// Ask for text input
		printf("You are going to translate from %s to %s.\n", sourceLanguage, outputLanguage);
		printf("Input text to be translated: ");
		fgets(sourceText, 150, stdin);	
		
		// Filter words directly into an array
		wordCount = filterWords(sourceText, filteredWords);

		// Display filtered words for confirmation
		printf("\nWords in %s: ", sourceLanguage);
		for (i = 0; i < wordCount; i++) {
			printf("%s ", filteredWords[i]);
		}
		printf("\n");

		// Translation logic using filteredWords array
		for (i = 0; i < wordCount; i++) {
			Str20 tempTranslation;  // Temporary storage for clarity
			strcpy(tempTranslation, translateWord(entries, countEntry, filteredWords[i], sourceLanguage, outputLanguage));
			strcpy(translatedWords[i], tempTranslation);
		}

		printf("\nWords in %s: ", outputLanguage);
		for (i = 0; i < wordCount; i++) {
			printf("%s ", translatedWords[i]);
		}
		printf("\n");
		
		// Ask if the user wants to continue
		printf("Do you want to translate more text? (y/n): ");
		choice = getChoice(choice);

	} while (choice == 'y' || choice == 'Y');
}

