
#include <stdio.h>
#include <string.h>

#define MAX_LETTER 20  // Max length for words
#define MAX_PAIRS 10   // Max language-translation pairs per entry
#define MAX_ENTRY 150  // Max dictionary entries

typedef char Str20[MAX_LETTER + 1];  // String type (20 characters + null terminator)

//Structures
typedef struct translationPairTag{ //will hold the pair
    Str20 lang; //for language
    Str20 trans; //for translation
} translationPairType;

typedef struct entryTag{ //main shit where every translation pair is stored
    translationPairType pairs[MAX_PAIRS];  // Array of translation pairs
    int count;  // Number of pairs in this entry
} entryType;


//functions

//helper function ni chat gpt
int entryExists(entryType entries[], int countEntry, char *lang, char *trans) {
    for (int i = 0; i < countEntry; i++) { 
        for (int j = 0; j < entries[i].count; j++) { 
            if (strcmp(entries[i].pairs[j].lang, lang) == 0 && 
                strcmp(entries[i].pairs[j].trans, trans) == 0) {
                return i; // Found existing entry
            }
        }
    }
    return -1; // No match found
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
 * @param entries[] - Array storing all existing entries.
 * @param countEntry - Number of entries in the dictionary.
 */
 
void getEntry(entryType entries[], int *countEntry) {
    if (*countEntry >= MAX_ENTRY) {  
        printf("Cannot add more entries. Dictionary is full!\n");
        return;
    }

    char lang[MAX_LETTER + 1], trans[MAX_LETTER + 1];

    printf("Enter language: ");
    scanf("%s", lang);
    printf("Enter translation: ");
    scanf("%s", trans);

    // Check if the language-translation pair already exists
    int existingIndex = entryExists(entries, *countEntry, lang, trans);
    if (existingIndex != -1) {
        printf("This language-translation pair already exists");
        return;//potaena wala akong maisip na solution dito
    }

    // make a new entry/word
    entryType *entry = &entries[*countEntry];
    strcpy(entry->pairs[0].lang, lang);
    strcpy(entry->pairs[0].trans, trans);
    entry->count = 1;

    (*countEntry)++; // Increase total entries count
    printf("New entry added successfully!\n");
}


//void addTranslation(entryType *entry);

int displayMainMenu()
{
    int choice;
    do
    {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Put a new word\n");
        printf("2. tangina mo walang laman to\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) // Check if input is not a valid integer
        {
            while (getchar() != '\n'); // Clear input buffer
            printf("Invalid input! Please enter a number between 1 and 3.\n");
            choice = 0; // continue the loop
        }
        else if (choice < 1 || choice > 3) // Ensure valid range
        {
            printf("Invalid choice! Please enter a number between 1 and 3.\n");
        }

    } while (choice < 1 || choice > 3);

    return choice; // Return the valid choice
}


int main(){
	//initialize varibales that will hold user input
	entryType entry[MAX_ENTRY]; //language and translation entry
    int countEntry = 0; //Counts how many existing words there are, nakalimutan ko max
	int choice = 0;
/* Note: Baka makalimutan ko:
   
   - Each entry represents a word (concept) with translations in different languages, stored as an entryType.
   - entryType contains an array of translationPairType, which holds the different translations for that word.
   
   Visualization:
   
   entries[0]: ("love")
    +-- English -> love
    +-- Tagalog -> mahal
    +-- Spanish -> amor
    +-- Hiligaynon -> gugma

   entries[1]: ("expensive")
    +-- English -> expensive
    +-- Tagalog -> mahal
    +-- Kapampangan -> mal

*/
	//test
	entry[0].pairs[0] = (translationPairType){"English", "love"};
    entry[0].pairs[1] = (translationPairType){"Tagalog", "mahal"};
    entry[0].pairs[2] = (translationPairType){"Spanish", "amor"};
    entry[0].count = 3;
	
	do {
        choice = displayMainMenu();

        switch (choice) {
            case 1: 
                getEntry(&entry[countEntry], &countEntry);
                countEntry++;
                break;
            case 2:
                //wala pa
                break;
            case 3:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 3);
	
}