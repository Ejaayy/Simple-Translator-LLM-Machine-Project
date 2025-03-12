#include "MP2.h"

int main()
{
  entryType entry[MAX_ENTRY];
  int countEntry = 0;

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
