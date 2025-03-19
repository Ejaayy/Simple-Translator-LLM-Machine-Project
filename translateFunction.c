int filterWords(char *textInput, Str20 filteredWords[]) 
{
    int wordCount = 0;       
    Str20 word = {0};        
    int letterIndex = 0;      
    int i;
    
    // Loop through each character in the textInput
    for (i = 0; textInput[i] != '\0'; i++) 
	{
        
		if (((textInput[i] >= 'A' && textInput[i] <= 'Z') || (textInput[i] >= 'a' && textInput[i] <= 'z')) && letterIndex < sizeof(Str20) - 1) //instead of isalpha()
		{
		    word[letterIndex++] = textInput[i];
		}
        
        else if (textInput[i] == ' ' || textInput[i] == '\n') 
		{ // space or \n means end of a word
            
            word[letterIndex] = '\0';  // Null char the word to mark its end
                
            if (wordCount < MAX_WORDS) 
			{ // Store the word in the filteredWords array if there's still space
                strcpy(filteredWords[wordCount++], word);
            }
            
            letterIndex = 0; 
        }
    }

    // Handle the last word
    //checks if ther is still a word thats needed to be put into filtered words
    if (letterIndex > 0 && wordCount < MAX_WORDS) 
	{
        word[letterIndex] = '\0';       // Null the final word
        strcpy(filteredWords[wordCount++], word);  // Store it in the array
    }

    return wordCount;  // Return the total number of words filtered
}

void printFilteredWords(Str20 filteredWords[], int wordCount) 
{
	int i;
    printf("Filtered words:\n");
    for (i = 0; i < wordCount; i++) {
        printf("%s\n", filteredWords[i]);
    }
}

void translateWord(entryType entries[], int countEntry, Str20 filteredWord, Str20 sourceLanguage, Str20 outputLanguage, Str20 translatedWord) 
{ 
    int matchedIndexes[MAX_WORDS];        
    int matchPairCount;
    int i, j;
    int foundIndex = -1;               
    int found = 0;      
	Str20 tempTranslation;              

    // Default to original word (if no translation is found)
    strcpy(translatedWord, filteredWord);

    // Call isDuplicate to find matching entries (same source language and translation )
    matchPairCount = isDuplicate(entries, countEntry, sourceLanguage, filteredWord, matchedIndexes, -1);

    if (matchPairCount > 0) //if a matyched entry is found
    {
        for (i = 0; i < matchPairCount && !found; i++) 
        {
        	found = 0;
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
}

void translateTextInput(entryType *entries, int countEntry) {
	
    char sourceText[MAX_CHARACTERS + 1] = {0};  // Assume text is at most 150 characters
    char choice = 'y';
    Str20 sourceLanguage;
    Str20 outputLanguage;
    Str20 filteredWords[MAX_WORDS];  // Array to store filtered words
    Str20 translatedWords[MAX_WORDS];  // Array to store translated words
    Str20 tempTranslation;
    int wordCount = 0;  // Tracks number of filtered words
    int i;
    int validInput;

    do {
        // Ask for source language
        printf("Enter the source language: ");
        inputWord(sourceLanguage);
        
        // Get valid input that is at most 150 characters
        do {
            validInput = 1; // Assume input is valid
            printf("Enter the text to be translated (max 150 characters): ");
            
            // 
            fgets(sourceText, MAX_CHARACTERS + 1, stdin);

            // check if input exceeds 150 characters
            if (strlen(sourceText) > MAX_CHARACTERS) {
                printf("Error: Text exceeds 150 characters. Please enter a shorter sentence.\n");
                validInput = 0; // mark input as invalid
                while (getchar() != '\n'); // clear excess input from buffer
            }
        } while (!validInput);

        // remove newline character if present to prevent formatting issues
        sourceText[strcspn(sourceText, "\n")] = '\0';	
        
        // Ask for target language
        printf("Enter the language to translate into: ");
        inputWord(outputLanguage);
        
        // Confirm input details
        printf("\nYou are translating from %s to %s.\n", sourceLanguage, outputLanguage);

        // Tokenization: filter words from input
        wordCount = filterWords(sourceText, filteredWords);

        // Display filtered words for confirmation
        printf("\nWords in %s: ", sourceLanguage);
        for (i = 0; i < wordCount; i++) {
            printf("%s ", filteredWords[i]);
        }
        printf("\n");

        // Translation logic using filteredWords array
        for (i = 0; i < wordCount; i++) {  
            tempTranslation[0] = '\0';
            translateWord(entries, countEntry, filteredWords[i], sourceLanguage, outputLanguage, tempTranslation);
            strcpy(translatedWords[i], tempTranslation); // Store in translatedWords array
        }

        // Display translated words
        printf("\nTranslated words in %s: ", outputLanguage);
        for (i = 0; i < wordCount; i++) {
            printf("%s", translatedWords[i]);
            if (i < wordCount - 1) {
                printf(" ");  // Avoid extra space at the end
            }
        }
        printf("\n");

        // Ask if the user wants to continue
        printf("\nDo you want to translate more text? (y/n): ");
        choice = getChoice(choice);

    } while (choice == 'y' || choice == 'Y');
}

// Function to translate a single sentence
void translateSentence(entryType entries[], int countEntry, char* sentence, 
                       char sourceLanguage[], char outputLanguage[], char* translatedSentence) {
    char word[MAX_LETTER] = {0};  
    char tempTranslation[MAX_LETTER] = {0}; 
    int wordIndex = 0, translatedIndex = 0;
    char punctuation = '\0'; // Store punctuation
    int i;

    for (i = 0; sentence[i] != '\0'; i++) { 
        // Detect punctuation (excluding spaces)
        if (sentence[i] == ',' || sentence[i] == '.' || sentence[i] == '?' || sentence[i] == '!') {
            punctuation = sentence[i]; // Store punctuation separately
        } 
        
        // Word separator (space or punctuation)
        if (sentence[i] == ' ' || punctuation != '\0') {  
            if (wordIndex > 0) {
                word[wordIndex] = '\0';  // Null-terminate the word
                translateWord(entries, countEntry, word, sourceLanguage, outputLanguage, tempTranslation);

                // Append translated word to the sentence
                strcpy(translatedSentence + translatedIndex, tempTranslation);
                translatedIndex += strlen(tempTranslation);

                // Restore punctuation after translation
                if (punctuation != '\0') {
                    translatedSentence[translatedIndex++] = punctuation;
                    punctuation = '\0'; // Reset after use
                    
                    // ? Ensure a space is added after punctuation
                    if (sentence[i + 1] != ' ' && sentence[i + 1] != '\0') { 
                        translatedSentence[translatedIndex++] = ' ';
                    }
                }
            }

            // ? Ensure space is added only if it’s not right after punctuation
            if (sentence[i] == ' ' && translatedSentence[translatedIndex - 1] != ' ') {
                translatedSentence[translatedIndex++] = ' ';
            }

            wordIndex = 0; // Reset for the next word
        } 
        // Store normal characters in `word[]`
        else {
            word[wordIndex++] = sentence[i];
        }
    }
    translatedSentence[translatedIndex] = '\0'; // Null-terminate the final translation
}

void translateTextFile(entryType *entries, int countEntry) {
    Str20 sourceFile, outputLanguage, sourceLanguage, outputFile;
    int flag = 1;
    
    // Get file names
    printf("What language is the text file in?: ");
    inputWord(sourceLanguage);  
    
    printf("What is the name of the file you are going to translate: ");
    inputWord(sourceFile);    
    
    printf("What language are you translating it into?: ");
    inputWord(outputLanguage);    
    
    printf("Where do we output this file: ");
    inputWord(outputFile);    

    FILE *ptrSourceFile = fopen(sourceFile, "r");
    FILE *ptrOutputFile = fopen(outputFile, "w");

    if (!ptrSourceFile || !ptrOutputFile) {
        printf("Error opening file.\n");
        flag = 0;
    }

    if (flag) {
        char bufferSentence[MAX_CHARACTERS + 1] = {0};  
        int sentenceIndex = 0;
        char word[MAX_LETTER];
        int i;
        char lastChar = '\0'; // track last added character
        int skipSentence = 0; // flag to skip processing

        // read words from file
        while (fscanf(ptrSourceFile, "%s", word) != EOF) {
            int spaceFlag = 0;

            for (i = 0; word[i] != '\0'; i++) {
                // if sentence is too long
                if (sentenceIndex >= MAX_CHARACTERS) {
                    printf("Error: Sentence exceeds 150 characters. Skipping: %s...\n", bufferSentence);
                    skipSentence = 1;  // set flag to skip
                }

                // only store if sentence is within limits
                if (!skipSentence) {
                    bufferSentence[sentenceIndex++] = word[i];
                    lastChar = word[i];
                }

                // check if it's the end of a sentence
                if (word[i] == '.' || word[i] == '?' || word[i] == '!') {
                    bufferSentence[sentenceIndex] = '\0';

                    // only translate if sentence is valid
                    if (!skipSentence) {
                        char translatedSentence[MAX_CHARACTERS + 1] = {0};
                        translateSentence(entries, countEntry, bufferSentence, sourceLanguage, outputLanguage, translatedSentence);
                        printf("Translated sentence: %s\n", translatedSentence);
                        fprintf(ptrOutputFile, "%s\n", translatedSentence);
                    }

                    // reset for next sentence
                    sentenceIndex = 0;
                    lastChar = '\0';
                    skipSentence = 0;  // reset skip flag
                }
            }

            // ensure spaces are only added between words, not after punctuation
            if (!skipSentence && spaceFlag == 0 && sentenceIndex < MAX_CHARACTERS) {
                if (lastChar != ',' && lastChar != '.' && lastChar != '?' && lastChar != '!' && lastChar != ' ') { 
                    bufferSentence[sentenceIndex++] = ' ';
                    lastChar = ' ';
                }
            }
        }

        // process the last sentence if it didn't end with punctuation
        if (sentenceIndex > 0 && !skipSentence) {
            bufferSentence[sentenceIndex] = '\0';

            char translatedSentence[MAX_CHARACTERS + 1] = {0};
            translateSentence(entries, countEntry, bufferSentence, sourceLanguage, outputLanguage, translatedSentence);
            printf("Translated sentence: %s\n", translatedSentence);
            fprintf(ptrOutputFile, "%s\n", translatedSentence);
        }

        fclose(ptrSourceFile);
        fclose(ptrOutputFile);
    }
}
