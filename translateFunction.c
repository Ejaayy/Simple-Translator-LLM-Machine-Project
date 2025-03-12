int filterWords(char *textInput, Str20 filteredWords[]) {
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

char* translateWord(entryType entries[], int countEntry, Str20 filteredWord, Str20 sourceLanguage, Str20 outputLanguage) 
{
    static Str20 translatedWord = {0}; 
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

    return translatedWord;
}

void translateTextInput(entryType *entries, int countEntry) {
	
	char sourceText[151] = {0};  // Assume text is at most 150 characters
	char choice = 'y';
	Str20 sourceLanguage;
	Str20 outputLanguage;
	Str20 filteredWords[MAX_WORDS];  // Array to store filtered words
	Str20 translatedWords[MAX_WORDS];  // Array to store filtered words
	Str20 tempTranslation;
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
		fgets(sourceText, 151, stdin);	
		
		// Filter words directly into an array
		wordCount = filterWords(sourceText, filteredWords);

		// Display filtered words for confirmation
		printf("\nWords in %s: ", sourceLanguage);
		for (i = 0; i < wordCount; i++) 
		{
			printf("%s ", filteredWords[i]);
		}
		printf("\n");
		//can use special case wherein the last word wont include an additional space anymore

		// Translation logic using filteredWords array
		for (i = 0; i < wordCount; i++) 
		{  //Translate inputted words to desired translation of the user
			tempTranslation[0] = '\0';
			strcpy(tempTranslation, translateWord(entries, countEntry, filteredWords[i], sourceLanguage, outputLanguage));
			strcpy(translatedWords[i], tempTranslation); //Stored in the translatedWords
		}

		printf("\nWords in %s: ", outputLanguage);
		for (i = 0; i < wordCount; i++) 
		{
			printf("%s ", translatedWords[i]);
		}
		printf("\n");
		//can use special case wherein the last word wont include an additional space anymore
		
		// Ask if the user wants to continue
		printf("Do you want to translate more text? (y/n): ");
		choice = getChoice(choice);

	} while (choice == 'y' || choice == 'Y');
}

// Function to translate a single sentence
void translateSentence(entryType entries[], int countEntry, char* sentence, char sourceLanguage[], char outputLanguage[], char translatedSentence[]){
    char word[MAX_LETTER] = {0};
    int wordIndex = 0, translatedIndex = 0;
    Str20 translatedWord;
    int i;
    
    translatedSentence[0] = '\0'; // Reset buffer

    for (i = 0; sentence[i] != '\0'; i++) 
	{
        if ((sentence[i] == ' ') || (sentence[i] == '.') || (sentence[i] == '?') || (sentence[i] == '!')) 
		{
            if (wordIndex > 0) //processes the word
			{
                word[wordIndex] = '\0';
                strcpy(translatedWord, translateWord(entries, countEntry, word, sourceLanguage, outputLanguage));
                if (translatedWord != NULL) 
				{
                    strcpy(translatedSentence + translatedIndex, translatedWord);
                    translatedIndex += strlen(translatedWord);
                }
                wordIndex = 0;
            }
    
            if ((sentence[i] == '.') || (sentence[i] == '?') || (sentence[i] == '!')) //processes the punctuation mark
			{
                translatedSentence[translatedIndex++] = sentence[i];
                translatedSentence[translatedIndex++] = '\n'; // Force newline
                while (sentence[i + 1] == ' ') 
					i++;
            }
            else if (translatedIndex > 0 && translatedSentence[translatedIndex - 1] != ' ') 
			{
                translatedSentence[translatedIndex++] = ' ';
            }
    	} 
		else 
		{
            word[wordIndex++] = sentence[i];
        }
    }

    // Process last word
    if (wordIndex > 0) 
	{
        word[wordIndex] = '\0';
        strcpy(translatedWord, translateWord(entries, countEntry, word, sourceLanguage, outputLanguage));
        if (translatedWord) 
		{
            strcpy(translatedSentence + translatedIndex, translatedWord);
            translatedIndex += strlen(translatedWord);
        }
    }

    // Trim trailing space/newline
    if (translatedIndex > 0) 
	{
        if (translatedSentence[translatedIndex - 1] == ' ') translatedIndex--;
        if (translatedSentence[translatedIndex - 1] == '\n') translatedIndex--;
    }
    translatedSentence[translatedIndex] = '\0';
}

// Function to process text files
void translateTextFile(entryType *entries, int countEntry) {
	int i;
    Str20 sourceFile, outputLanguage, sourceLanguage, outputFile;
    char buffer[151] = {0};
    char sentenceBuffer[10][151] = {0};
    char translated[10][151] = {0};

    printf("What is the file you are going to translate: ");
    inputWord(sourceFile);    
    printf("What language is this text file in?: ");
    inputWord(sourceLanguage);  
    printf("What language are you translating it into?: ");
    inputWord(outputLanguage);    
    printf("Where do we output this file: ");
    inputWord(outputFile);    

    FILE *ptrSourceFile = fopen(sourceFile, "r");
    FILE *ptrOutputFile = fopen(outputFile, "w");

    if (!ptrSourceFile || !ptrOutputFile) {
        printf("Error opening files!\n");
        if (ptrSourceFile) 
			fclose(ptrSourceFile);
        if (ptrOutputFile) 
			fclose(ptrOutputFile);
        return;
    }

    while (fgets(buffer, sizeof(buffer), ptrSourceFile)) {
        int sentenceNum = 0, bufferIdx = 0;

        // Split into sentences with proper trimming
        while (buffer[bufferIdx] && sentenceNum < 10) {
            // Skip leading whitespace
            while (isspace(buffer[bufferIdx])) bufferIdx++;
            
            int sentencePos = 0;
            while (buffer[bufferIdx] && sentencePos < 150) {
                char c = buffer[bufferIdx];
                if (strchr(".?!", c)) {
                    sentenceBuffer[sentenceNum][sentencePos++] = c;
                    bufferIdx++;
                    // Skip trailing spaces after punctuation
                    while (isspace(buffer[bufferIdx])) bufferIdx++;
                    break;
                }
                sentenceBuffer[sentenceNum][sentencePos++] = c;
                bufferIdx++;
            }
            
            // Trim trailing whitespace
            while (sentencePos > 0 && isspace(sentenceBuffer[sentenceNum][sentencePos - 1])) {
                sentencePos--;
            }
            sentenceBuffer[sentenceNum][sentencePos] = '\0';
            
            if (sentencePos > 0) sentenceNum++;
        }

        // Translate and write sentences
        for (i = 0; i < sentenceNum; i++) {
            if (strlen(sentenceBuffer[i]) == 0) 
				continue;
            translateSentence(entries, countEntry, sentenceBuffer[i], sourceLanguage, outputLanguage, translated[i]);
            fprintf(ptrOutputFile, "%s\n", translated[i]);
        }
    }

    fclose(ptrSourceFile);
    fclose(ptrOutputFile);
    printf("Translation complete!\n");
}
