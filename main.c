/********************************************************************************************************* 
This is to certify that this project is our work, based on our personal efforts in studying and applying the concepts 
learned. We have constructed the functions and their respective algorithms and corresponding code by ourselves. The 
program was run, tested, and debugged by our own efforts. We further certify that we have not copied in part or whole or 
otherwise plagiarized the work of other students and/or persons.
																Edriene James A. Paingan, DLSU ID# 12413984
																Marc Andre M. Santos, DLSU ID# 12413844
*********************************************************************************************************/
/*
	Description: This program acts as a translator machine where it ask users whether they want to manage data, translate, and exit or shutdown the machine program.
	Programmed by: Marc Andre Santos and Edriene James Paingan, S11B
	Last modified: 03/30/2025
	Version: 1
*/

#include "simpleTranslator.h" // Include the header file to access the function prototypes and declarations and different c source files

/*  Function Name: main()
	This function serves as the entry point of the translator machine program. It lets the user manage
	the data in the program, translate words, phrases, or sentences accordingly, and shut down the program
	itself.
	Precondition: The program must be compiled and run. The user must input an integer value.
	@param none
	@return an integer value (0) to indicate that the program runs successfully.
*/
int main()
{
	entryType entry[MAX_ENTRY]; // Initialization and declaration of an array of structure of entryType with the max number of elements being 150
	int countEntry = 0,				  // Initialization and declaration of entry count
		manageDataChoice = 0,		  // Initialization and declaration of integer type of variable choices starting from this line
		mainChoice = 0,
		exitManageDataMenuChoice = 0,
		exitMainMenuChoice = 0,
		exitTransMenuChoice = 0,
		translateChoice = 0, // Until this line
		importStatus = 1,	 // Flag to check if importing a file is successful or not
		getFileStatus = 0;

	do
	{
		mainChoice = mainMenu(); // Function call to display main menu and to ask the user what they want to do
		switch (mainChoice)
		{
		case 1: // User choose to manage data
			do
			{
				manageDataChoice = manageDataMenu(); // Function call to display manage data menu and to ask the user what they want to do
				switch (manageDataChoice)
				{
				case 1:
					addEntry(entry, &countEntry); // Function call to add entry
					break;

				case 2:
					addTranslation(entry, &countEntry); // Function call to add translation to an existing entry
					break;

				case 3:
					deleteEntry(entry, &countEntry); // Function call to delete an entry
					break;

				case 4:
					deleteTranslation(entry, &countEntry); // Function call to delete a translation in an entry
					break;

				case 5:
					displayAllEntries(entry, countEntry); // Function call to display all the existing entries
					break;

				case 6:
					searchWord(entry, countEntry); // Function call to search for a word
					break;
				case 7:
					searchTranslation(entry, countEntry); // Function call to search a language-translation pair
					break;

				case 8:
					exportFile(entry, countEntry); // Function call to export all data to a text file
					break;

				case 9:
					importFile(entry, &countEntry, "Manage Data Menu"); // Function call to import data stored in the text file
					break;

				case 10:
					exitManageDataMenuChoice = exitFunction(entry, &countEntry); // Function call whether to exit manage data menu or not
					if (exitManageDataMenuChoice == 0)							 // User decide to exit the function
					{
						manageDataChoice = 10;

						printf("Exited Manage Data menu.\n");
					}
					else // User decide to not exit the function
					{
						manageDataChoice = 0;
					}
					break;

				default:
					printf("Invalid choice! Try again.\n");
				}
			} while (manageDataChoice != 10); // Ensures that the user inputs a valid integer value

			break;

		case 2:						// User choose to translate
			if (getFileStatus == 0) // FILE HAS NOT BEEN OPENED
			{
				importStatus = importFile(entry, &countEntry, "Translate Menu"); // Returns 1 if no error importing, 0 if there is an error

				if (importStatus == 0)
				{
					translateChoice = 3; // If there is an error, exit the translation menu
				}
				else
				{
					getFileStatus = 1; // FILE HAS BEEN OPENED
				}
			}

			if (importStatus == 1)
			{
				do
				{
					translateChoice = translateMenu(); // Function call to display translate menu and to ask the user what they want to do
					switch (translateChoice)
					{
					case 1:
						translateTextInput(entry, countEntry); // Function call if the user wants to translate an inputted text
						break;

					case 2:
						translateTextFile(entry, countEntry); // Function call if the user wants to translate a text file
						break;

					case 3:
						exitTransMenuChoice = exitFunction(entry, &countEntry); // Function call whether to exit translate menu or not
						if (exitTransMenuChoice == 0)							// User decided to exit the function
						{
							// resets variables for translate functions
							getFileStatus = 0;
							importStatus = 0;
							translateChoice = 3;

							printf("Exited Translate menu.\n");
						}
						else
						{ // User decided not to exit the function
							translateChoice = 0;
						}
						break;

					default:
						printf("Invalid choice! Try again.\n");
					}
				} while (translateChoice != 3); // Loop ensuring that the user inputs a valid integer value
			}
			break;

		case 3:
			exitMainMenuChoice = exitFunction(entry, &countEntry); // Function call whether to exit the program
			if (exitMainMenuChoice == 0)						   // User decide to exit the function
			{
				mainChoice = 3;
				printf("The program had been shut down.\n");
			}
			else // User decide to not exit the function
			{
				mainChoice = 0;
			}
			break;

		default:
			printf("Invalid choice! Try again.\n");
		}
	} while (mainChoice != 3); // Loop ensuring that the user inputs a valid integer value

	return 0;
}
