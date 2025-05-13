/********************************************************************************************************* 
This is to certify that this project is our work, based on our personal efforts in studying and applying the concepts 
learned. We have constructed the functions and their respective algorithms and corresponding code by ourselves. The 
program was run, tested, and debugged by our own efforts. We further certify that we have not copied in part or whole or 
otherwise plagiarized the work of other students and/or persons.
																Edriene James A. Paingan, DLSU ID# 12413984
																Marc Andre M. Santos, DLSU ID# 12413844
*********************************************************************************************************/
/*
	Description: This program allows the user to translate a text input, translate a text file, and exit the function.
	Programmed by: Marc Andre Santos and Edriene James Paingan, S11B
	Last modified: 03/30/2025
	Version: 1
*/

/*
 * Function Name: filterWords()
 * Extracts individual words from a given text input and stores them in an array.
 * @param textInput - the input string containing words.
 * @param filteredWords - an array to store extracted words.
 * @return int - the total number of words stored in filteredWords.
 * Pre-condition: textInput is a valid null-terminated string.
 * Post-condition: Words are extracted and stored in filteredWords, up to MAX_WORDS limit.
 */
int filterWords(char *textInput, Str20 filteredWords[])
{
	int wordCount = 0,
		letterIndex = 0,
		i;
	Str20 word = {0};
	// Loop through each character in the textInput
	for (i = 0; textInput[i] != '\0'; i++)
	{
		// Store the inputted text to word as long as it's a letter in the alphabet (small case or capital case)
		if (((textInput[i] >= 'A' && textInput[i] <= 'Z') || (textInput[i] >= 'a' && textInput[i] <= 'z')) && letterIndex < sizeof(Str20) - 1)
		{
			word[letterIndex++] = textInput[i]; // Increment letterIndex to allow for storing of the next letter
		}

		else if (textInput[i] == ' ' || textInput[i] == '\n') // Space or \n means end of a word
		{
			word[letterIndex] = '\0'; // Null char the word to mark its end

			if (wordCount < MAX_WORDS) // Store the word in the filteredWords array if there's still space
			{
				strcpy(filteredWords[wordCount++], word); // Copy the cutted word into the array of filtered words
			}

			letterIndex = 0; // Reset letter index to zero to allow for the copying of the next word
		}
	}
	// Handle the last word
	// checks if there is still a word that is needed to be put into filtered words
	if (letterIndex > 0 && wordCount < MAX_WORDS)
	{
		word[letterIndex] = '\0';				  // Null the final letter
		strcpy(filteredWords[wordCount++], word); // Store it in the array
	}

	return wordCount; // Return the total number of words filtered
}

/*
 * Function Name: printFilteredWords()
 * Prints the list of filtered words.
 * @param filteredWords - an array containing the extracted words.
 * @param wordCount - the number of words in the filteredWords array.
 * @return none
 * Pre-condition: filteredWords contains wordCount valid words.
 * Post-condition: All words in filteredWords are printed to the console.
 */
void printFilteredWords(Str20 filteredWords[], int wordCount)
{
	int i;
	printf("Filtered words:\n");
	for (i = 0; i < wordCount; i++) // Prints all the filtered words
	{
		printf("%s\n", filteredWords[i]);
	}
}

/*
 * Function Name: translateWord()
 * Finds and retrieves the translation of a given word from the entries.
 * @param entries - an array of entryType structures containing translation pairs.
 * @param countEntry - the number of entries in the entries array.
 * @param filteredWord - the word to be translated.
 * @param sourceLanguage - the language of the filteredWord.
 * @param outputLanguage - the target language for translation.
 * @param translatedWord - stores the translated word if found; otherwise, remains as filteredWord.
 * @return none
 * Pre-condition: entries contain valid translation pairs, and sourceLanguage and outputLanguage exist.
 * Post-condition: If a translation exists, translatedWord is updated; otherwise, it remains unchanged.
 */
void translateWord(entryType entries[], int countEntry, Str20 filteredWord, Str20 sourceLanguage, Str20 outputLanguage, Str20 translatedWord)
{
	int matchedIndexes[MAX_WORDS] = {0}, // Array containing the indeces of the entry that contains similar pair with the sourceLanguage and filteredWord
		matchPairCount = 0,	// Count of the matched entry/ies
		i,
		j,
		foundIndex = -1, // Variable to store the index of the correct pair 
		checkAll = -1, // Variable to check all the entry/ies in the file to look for a duplicate for the sourceLanguage and the filteredWord
		found = 0;

	// Default to original word (if no translation is found)
	strcpy(translatedWord, filteredWord);

	// Call isDuplicate to find matching entries (same source language and translation )
	matchPairCount = isDuplicate(entries, countEntry, sourceLanguage, filteredWord, matchedIndexes, checkAll);

	if (matchPairCount > 0) // If a matched entry is found
	{
		for (i = 0; i < matchPairCount && found == 0; i++) // Loop through all matched entries
		{
			for (j = 0; j < entries[matchedIndexes[i]].pairCount && found == 0; j++) // Checks that pairs in the entry
			{
				if (strcasecmp(entries[matchedIndexes[i]].pair[j].lang, outputLanguage) == 0) // Checks if the language user wants to output exists
				{
					foundIndex = j; // Store index of the correct pair
					found = 1;		// Set flag to stop further searching since the first encountered in the array is the one to be used
				}
			}
		}

		if (found == 1) // If the output language exist
		{
			strcpy(translatedWord, entries[matchedIndexes[i - 1]].pair[foundIndex].trans); // Copy the translation to the translated word after it has been found
		}
	}
}

/*
 * Function Name: translateTextInput()
 * Processes user input for text translation by filtering and translating words individually.
 * @param entries - pointer to an array of entryType structures containing translation data.
 * @param countEntry - the number of entries in the translation dictionary.
 * @return none
 * Pre-condition: entries must be initialized with valid translation pairs.
 * Post-condition: Prompts the user for source and target languages, tokenizes the input text,
 * removes punctuation, and translates words individually. Displays translated text while
 * preserving untranslatable words. Allows repeated translations until the user exits.
 */
void translateTextInput(entryType *entries, int countEntry)
{
	char sourceText[MAX_CHARACTERS + 1] = {0}, // Assume text is at most 150 characters
		 choice = 'Y';
	Str20 sourceLanguage,			// String to store what is the source language of the word that the user intends to translate
		  outputLanguage,				// String to store what output the user wants to translate to
		  filteredWords[MAX_WORDS],	// Array of strings to store filtered words
		  translatedWords[MAX_WORDS], // Array of strings to store translated words
		  tempTranslation;			// Temporary string to store the translation
	int wordCount = 0,				// Tracks number of filtered words
		i;

	do
	{
		// Ask for Source and Output Language (ONLY if first time or user wants to change it)
		inputString(sourceLanguage, MAX_LETTER, "Enter the source language: ");
		inputString(outputLanguage, MAX_LETTER, "Enter the language to translate into: ");

		do
		{
			// Ask for Text to Translate
			inputString(sourceText, MAX_CHARACTERS, "Enter the text to be translated (max 150 characters): ");
			sourceText[strcspn(sourceText, "\n")] = '\0'; // Remove newline if present

			// Process and Translate
			wordCount = filterWords(sourceText, filteredWords);
			for (i = 0; i < wordCount; i++)
			{
				tempTranslation[0] = '\0'; // Initialize to zero to avoid garbage value or residue data
				translateWord(entries, countEntry, filteredWords[i], sourceLanguage, outputLanguage, tempTranslation);
				strcpy(translatedWords[i], tempTranslation); // Copy the translation to the translated words array
			}

			// Display Result
			printf("\nTranslated words in %s: ", outputLanguage);
			for (i = 0; i < wordCount; i++)
			{
				if (translatedWords[i][0] != '\0')
				{ // Check if the word is not empty
					printf("%s", translatedWords[i]);

					// Print space only if it's not the last non-empty word
					if (i < wordCount - 1)
					{
						printf(" ");
					}
				}
			}
			printf("\n");

			// Ask if user wants to translate more text (same languages)
			printf("\nDo you want to translate more text with the same languages?\n");
			choice = getChoice();

		} while (choice == 'Y' || choice == 'y'); // Only repeat if user wants to translate more text with SAME languages

		// Ask if user wants to restart with new source & output language
		printf("\nDo you want to change the source and output languages? \n(Y/N): ");
		choice = getChoice();

	} while (choice == 'Y' || choice == 'y'); // Restart with new language settings if user says YES
}
/*
 * Function Name: translateSentence() 
 * Translates a given sentence, word by word while preserving punctuation.  
 * @param entries - array of entryType structures containing translation data.  
 * @param countEntry - number of entries in the translation dictionary.  
 * @param sentence - the input sentence to be translated.  
 * @param sourceLanguage - the language of the input sentence.  
 * @param outputLanguage - the target language for translation.  
 * @param translatedSentence - buffer to store the translated sentence.  
 * @return none  
 * Pre-condition: entries must be initialized with valid translation pairs.  
 * Post-condition: translatedSentence contains the translated version of sentence with punctuation preserved.  
 */
void translateSentence(entryType entries[], int countEntry, char *sentence,
					   char sourceLanguage[], char outputLanguage[], char *translatedSentence)
{
	char word[MAX_LETTER] = {0}, // Contains the word to be translated
		 tempTranslation[MAX_LETTER + 1] = {0}, // String temp to store the translation
		 punctuation = '\0';  // Store punctuation
	int wordIndex = 0, // To store the letter index of the word
		translatedIndex = 0, // To store how many letters of the word have been translated
		spaceFlag = 0, // Variable to track whether to put a space or not
		i;

	for (i = 0; sentence[i] != '\0'; i++) // Store as long as the string doesn't reach the null byte yet
	{
		if (sentence[i] == '.' || sentence[i] == '?' || sentence[i] == '!') // Detection of sentence ender punctuation
		{
			punctuation = sentence[i]; // Store punctuation separately to restore later
			word[wordIndex] = '\0'; // Null-terminate the string if detected a punctuation
		
			if (wordIndex > 0) // Translate only if there is/are letter/s in the word
			{
				tempTranslation[0] = '\0'; // Initalize to zero the temporary string for translation to avoid garbage values
				translateWord(entries, countEntry, word, sourceLanguage, outputLanguage, tempTranslation); // Translate the word

				strcpy(translatedSentence + translatedIndex, tempTranslation); // Append/copy translated word to the sentence
				translatedIndex += strlen(tempTranslation); // Increment the length of the translated index since new translated word was added to the sentence

				if (punctuation != '\0') // Restore punctuation after translation (only if there is a punctuation that exists in the word before translation)
				{
					translatedSentence[translatedIndex++] = punctuation; // Store the punctuation to the translated sentence
					punctuation = '\0'; // Reset after use
					wordIndex = 0; // Reset for the next word
				}
			}
			spaceFlag = 0; // Stop space after punctuation
		}
		else if (sentence[i] == ' ') // If the specific index of a sentence detects a space, process that
		{
			word[wordIndex] = '\0'; // Null-terminate the string if detected a punctuation

			if (wordIndex > 0) // Translate only if there is/are letter/s in the word
			{
				translateWord(entries, countEntry, word, sourceLanguage, outputLanguage, tempTranslation); // Translate the word

				strcpy(translatedSentence + translatedIndex, tempTranslation); // Append/copy translated word to the sentence
				translatedIndex += strlen(tempTranslation); // Increment the length of the translated index since new translated word was added to the sentence

				wordIndex = 0; // Reset for the next word
				spaceFlag = 1; // Flag to put a space 
			}
		}
		else if (ispunct(sentence[i]) && sentence[i] != '.' && sentence[i] != '?' && sentence[i] != '!')
		{
			punctuation = sentence[i]; // Store the punctuation separately
			word[wordIndex] = '\0';    // Null-terminate the word

			if (wordIndex > 0) // If there's a word before the punctuation, translate it
			{
				translateWord(entries, countEntry, word, sourceLanguage, outputLanguage, tempTranslation); // Translate word
				strcpy(translatedSentence + translatedIndex, tempTranslation); // Append translated word
				translatedIndex += strlen(tempTranslation); // Update index

				if (punctuation != '\0') // Restore punctuation after translation
				{
					translatedSentence[translatedIndex++] = punctuation; // Append punctuation

					// Set spaceFlag if punctuation is not a linking punctuation
					if (punctuation != '\'' && punctuation != '-')
					{
						spaceFlag = 1; // Flag to put a space
					}
					else
					{
						spaceFlag = 0; // Flag not to put a space
					}

					punctuation = '\0'; // Reset punctuation after processing
					wordIndex = 0;      // Reset word index for next word
				}
			}
		}
		else // Store the characters in the sentence to word as long as it's not the punctuation given in the specs
		{
			if(spaceFlag == 1) // Put a space 
			{
				translatedSentence[translatedIndex++] = ' '; // Store the space to the translated sentence
				spaceFlag = 0; // Reset for next
			}
			word[wordIndex++] = sentence[i]; // Increment wordIndex each time a letter is stored to allow for the collection for the succeeding letters
		}
	}
	if (wordIndex > 0) // Handle the last word (if there is no trailing punctuation)
	{
		word[wordIndex] = '\0'; // Null-terminate the word
		tempTranslation[0] = '\0'; // Null-terminate the string if detected a punctuation
		translateWord(entries, countEntry, word, sourceLanguage, outputLanguage, tempTranslation); // Translate the word

		strcpy(translatedSentence + translatedIndex, tempTranslation); // Append/copy translated word to the sentence
		translatedIndex += strlen(tempTranslation); // Increment the length of the translated index since new translated word was added to the sentence
	}
	translatedSentence[translatedIndex] = '\0'; // Properly null-terminate the translated sentence
}

/*
 * Function Name: translateTextFile() 
 * translates a text file sentence by sentence and writes the translated output to another file.
 * @param entries - pointer to an array of entryType structures containing translation data.
 * @param countEntry - the number of entries in the translation dictionary.
 * @return none
 * Pre-condition: The source file must exist and contain properly formatted sentences.  
 * Post-condition: Reads the input file, translates each sentence while handling punctuation, and writes the translated text to the output file.  
 * Sentences are displayed on screen and saved in the output file, with each sentence separated by a newline.
 */
void translateTextFile(entryType *entries, int countEntry)
{
	Str30 sourceFile, // String to store the name of the source file
		  outputFile; // String to store the name of the output file
	Str20 sourceLanguage, // String to store the source language
		  outputLanguage; // String to store the output language
	FILE *ptrSourceFile, // File pointer for the source file
		 *ptrOutputFile; // File pointer for the output file 
	int sentenceLen = 0, // Flag to keep track if continue on processing the code
		validFlag = 1,
		i,
		ch, // Variable for the flag if the consuming of skipped lines is successful or not
		tempIndex = 0; // Variable to store the index of the letter of the word in the temporary sentence
	char bufferSentence[MAX_CHARACTERS + 1], // Array of characters to store the scanned lines inside the file and the ones needed to be translated
		 tempSentence[MAX_CHARACTERS + 1], // Temporary array of characters to avoid unwanted changes to the bufferSentence
		 translatedSentence[MAX_CHARACTERS + 1]; // Array of character to store the translated sentences

	inputString(sourceLanguage, MAX_LETTER, "What language is the text file in?: "); // Prompt for the language of what the text file in
	
	inputString(sourceFile, MAX_FILENAME, "What is the name of the file you are going to translate: "); // Prompt for the file to be translated

	inputString(outputLanguage, MAX_LETTER, "What language are you translating it into?: "); // Prompt for the target language to be translated to

	inputString(outputFile, MAX_FILENAME, "Where do we output this file: "); // Prompt for the file where the result will be saved

	ptrSourceFile = fopen(sourceFile, "r"); // Open the source file for reading
	ptrOutputFile = fopen(outputFile, "w"); // Open the text file for writing 

	if (ptrSourceFile != NULL && ptrOutputFile != NULL) // If successful opening of file
	{
		while (fgets(bufferSentence, MAX_CHARACTERS + 2, ptrSourceFile) != NULL) // Keep reading lines until EOF is reached and read at most MAX_CHARACTERS + 2
		{
			sentenceLen = strlen(bufferSentence); // Get the length of the read line from the file
			
			if (sentenceLen > 0 && bufferSentence[sentenceLen - 1] == '\n') // Ensures that the string is not empty and null terminate the new line
			{
				bufferSentence[sentenceLen - 1] = '\0';
				sentenceLen--; // Reduce the length of the string since '\n' was deleted/removed
			}
			if (sentenceLen == 0) // If the read line doesn't contatin anything
			{
				printf("Skipped a line. The line doesn't contain anything.\n");
			}
			else if (sentenceLen > MAX_CHARACTERS) // If the scanned line is more than the MAX_CHARACTERS
			{
				printf("Skipped a line. Exceeded %d characters.\n", MAX_CHARACTERS); 
				while ((ch = fgetc(ptrSourceFile)) != '\n' && ch != EOF); // Flush the values starting at the file cursor until newline of the skipped line or EOF
			}
			if (validFlag == 1) // If the line is valid
			{
				tempIndex = 0; // Initialize the variable to avoid garbage value or residue data
	            for (i = 0; bufferSentence[i] != '\0'; i++) // Loop until not the end of the sentence
	            {
	                tempSentence[tempIndex++] = bufferSentence[i]; // Store everything to the temporary sentence for modification
	                
	                if (bufferSentence[i] == '.' || bufferSentence[i] == '?' || bufferSentence[i] == '!') // Detects punctuation marks to end a sentence
	                {
	                    tempSentence[tempIndex] = '\0'; // End current sentence
	                    
	                    translatedSentence[0] = '\0'; // Initialize to zero to avoid garbage value or residue data
	                    translateSentence(entries, countEntry, tempSentence, sourceLanguage, outputLanguage, translatedSentence); // Translate the sentence
	                    printf("Translated sentence: %s\n", translatedSentence); // Print the translated sentence/s
	                    fprintf(ptrOutputFile, "%s\n", translatedSentence); // Print to the file the translated sentence/s
	                    
	                    tempIndex = 0; // Reset for next sentence
					}
				}
			}
		}
	}
	else // If error in opening the file
	{
		printf("Error opening file.\n");
	}
	fclose(ptrSourceFile); // Close the source file
	fclose(ptrOutputFile); // Close the output/result file
}
