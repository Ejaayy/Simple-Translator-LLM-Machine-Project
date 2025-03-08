#include "MP2.h"

int main()
{
  entryType entry[MAX_ENTRY];
  int countEntry = 0;
/*
// Initialize test data
// Entry 0: Translations related to "love" and "hate"
strcpy(entry[0].pair[0].lang, "english");
strcpy(entry[0].pair[0].trans, "love");
strcpy(entry[0].pair[1].lang, "tagalog");
strcpy(entry[0].pair[1].trans, "mahal");
strcpy(entry[0].pair[2].lang, "spanish");
strcpy(entry[0].pair[2].trans, "amor");
strcpy(entry[0].pair[3].lang, "english");
strcpy(entry[0].pair[3].trans, "hate");
entry[0].pairCount = 4;
countEntry++;


Alternative for manually computing for the pairCount
sizeof(entry[0].pairs) / sizeof(entry[0].pairs[0]);
printf("Total pairs in entry[0]: %d\n", pairCount);


// Entry 1: Translations for "happy"
strcpy(entry[1].pair[0].lang, "english");
strcpy(entry[1].pair[0].trans, "happy");
strcpy(entry[1].pair[1].lang, "tagalog");
strcpy(entry[1].pair[1].trans, "masaya");
strcpy(entry[1].pair[2].lang, "spanish");
strcpy(entry[1].pair[2].trans, "feliz");
strcpy(entry[1].pair[3].lang, "french");
strcpy(entry[1].pair[3].trans, "heureux");
entry[1].pairCount = 4;
countEntry++;

// Entry 2: Translations for "beautiful"
strcpy(entry[2].pair[0].lang, "english");
strcpy(entry[2].pair[0].trans, "beautiful");
strcpy(entry[2].pair[1].lang, "tagalog");
strcpy(entry[2].pair[1].trans, "maganda");
strcpy(entry[2].pair[2].lang, "spanish");
strcpy(entry[2].pair[2].trans, "hermosa");
strcpy(entry[2].pair[3].lang, "italian");
strcpy(entry[2].pair[3].trans, "bella");
entry[2].pairCount = 4;
countEntry++;

// Entry 3: Translations for "strong"
strcpy(entry[3].pair[0].lang, "english");
strcpy(entry[3].pair[0].trans, "strong");
strcpy(entry[3].pair[1].lang, "tagalog");
strcpy(entry[3].pair[1].trans, "malakas");
strcpy(entry[3].pair[2].lang, "japanese");
strcpy(entry[3].pair[2].trans, "tsuyoi");
strcpy(entry[3].pair[3].lang, "german");
strcpy(entry[3].pair[3].trans, "stark");
entry[3].pairCount = 4;
countEntry++;

// Entry 4: Translations for "fast"
strcpy(entry[4].pair[0].lang, "english");
strcpy(entry[4].pair[0].trans, "fast");
strcpy(entry[4].pair[1].lang, "tagalog");
strcpy(entry[4].pair[1].trans, "mabilis");
strcpy(entry[4].pair[2].lang, "spanish");
strcpy(entry[4].pair[2].trans, "rápido");
strcpy(entry[4].pair[3].lang, "korean");
strcpy(entry[4].pair[3].trans, "ppalli");
entry[4].pairCount = 4;
countEntry++;
/*
// Entry 5: Translations for "love"
strcpy(entry[5].pair[0].lang, "english");
strcpy(entry[5].pair[0].trans, "love");
strcpy(entry[5].pair[1].lang, "tagalog");
strcpy(entry[5].pair[1].trans, "mahal");
strcpy(entry[5].pair[2].lang, "spanish");
strcpy(entry[5].pair[2].trans, "amor");
strcpy(entry[5].pair[3].lang, "english");
strcpy(entry[5].pair[3].trans, "hate");
entry[5].pairCount = 4;
countEntry++;
*/
  int manageDataChoice;
  int mainChoice;
  int exitManageDataMenuChoice;
  int exitMainMenuChoice;
  int exitTransMenuChoice;
  int translateChoice;
  do
  {
    mainChoice = displayMainMenu();
    switch(mainChoice)
    {
	    case 1:
	    	do
	    	{
	    		manageDataChoice = displayManageDataMenu();
	      		switch(manageDataChoice)
	      		{
			      	case 1:
			      		addEntry(entry, &countEntry);
			      	break;
			      	
			      	case 2:
			      		addTranslation(entry, &countEntry);
			      	break;
			      	
			      	case 3:
			      		deleteEntry(entry, &countEntry);
			      	break;
			      	
			      	case 4:
			      		deleteTranslation(entry, &countEntry);
			      	break;
			      	
			      	case 5:
			      		displayModeAllEntries(entry, countEntry);
			      	break;
			      	
			      	case 6:
			      		searchWord(entry, countEntry);
			      	break;
			      	case 7:
			      		searchTranslation(entry, countEntry);
			      	break;
			      	
			      	case 8:
			      		exportFile(entry, countEntry);
			      	break;	      	
			      		
			      	case 9:
			      		importFile(entry, &countEntry);
			      	break;
			      	
			      	case 10:
			      		exitManageDataMenuChoice = exitFunction();
			      		if (!exitManageDataMenuChoice)
			      		{
			      			manageDataChoice = 10;
			      			printf("Exited Manage Data menu.\n");
						}
						else
							manageDataChoice = 0;
			      	break;		
			    
			    	default:
			      	printf("Invalid choice! Try again.\n");
		  		}
			} while(manageDataChoice != 10);
	      
	    break;
	    case 2:
	    	do
	    	{
		    	translateChoice = translateMenu();
		    	switch(translateChoice)
		    	{
		    		case 1:
		    			translateTextInput(entry, countEntry);
		    		break;
		    		
		    		case 2:
						translateTextFile(entry, countEntry);
		    		break;
		    		
		    		case 3:
		    			exitTransMenuChoice = exitFunction();
			      		if (!exitTransMenuChoice)
			      		{
			      			translateChoice = 3;
			      			printf("Exited Translate menu.\n");
						}
						else
							translateChoice = 0;
		    		break;
		    		default:
	    				printf("Invalid choice! Try again.\n");
				}
	    	} while(translateChoice != 3);
	    	break;
		    	exitMainMenuChoice = exitFunction();
				if (!exitMainMenuChoice)
				{
				    mainChoice = 3;
				    printf("The program had been shut down.\n");
				}
				else 
					mainChoice = 0;
	    	break;
	    	default:
	    	printf("Invalid choice! Try again.\n");
    }
  } while(mainChoice != 3);

  return 0;
}
//Change the argument to a specific struct only, not the whole struct of the MP 
