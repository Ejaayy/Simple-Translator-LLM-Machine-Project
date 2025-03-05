#include "MP2.h"

int main()
{
  entryType entry[MAX_ENTRY];
  int countEntry = 0;

  // Initialize test data
  // Entry 0: Translations related to "love" and "hate"
  strcpy(entry[0].pair[0].lang, "English");
  strcpy(entry[0].pair[0].trans, "love");
  strcpy(entry[0].pair[1].lang, "Tagalog");
  strcpy(entry[0].pair[1].trans, "mahal");
  strcpy(entry[0].pair[2].lang, "Spanish");
  strcpy(entry[0].pair[2].trans, "amor");
  strcpy(entry[0].pair[3].lang, "English");
  strcpy(entry[0].pair[3].trans, "hate");
  entry[0].pairCount = 4;
  countEntry++;
  /*
  Alternative for manually computing for the pairCount
  sizeof(entry[0].pairs) / sizeof(entry[0].pairs[0]);
  printf("Total pairs in entry[0]: %d\n", pairCount);
  */

  // Entry 1: Translations for "happy"
  strcpy(entry[1].pair[0].lang, "English");
  strcpy(entry[1].pair[0].trans, "happy");
  strcpy(entry[1].pair[1].lang, "Tagalog");
  strcpy(entry[1].pair[1].trans, "masaya");
  strcpy(entry[1].pair[2].lang, "Spanish");
  strcpy(entry[1].pair[2].trans, "feliz");
  strcpy(entry[1].pair[3].lang, "French");
  strcpy(entry[1].pair[3].trans, "heureux");
  entry[1].pairCount = 4;
  countEntry++;
  // Entry 2: Translations for "beautiful"
  strcpy(entry[2].pair[0].lang, "English");
  strcpy(entry[2].pair[0].trans, "beautiful");
  strcpy(entry[2].pair[1].lang, "Tagalog");
  strcpy(entry[2].pair[1].trans, "maganda");
  strcpy(entry[2].pair[2].lang, "Spanish");
  strcpy(entry[2].pair[2].trans, "hermosa");
  strcpy(entry[2].pair[3].lang, "Italian");
  strcpy(entry[2].pair[3].trans, "bella");
  entry[2].pairCount = 4;
  countEntry++;
  // Entry 3: Translations for "strong"
  strcpy(entry[3].pair[0].lang, "English");
  strcpy(entry[3].pair[0].trans, "strong");
  strcpy(entry[3].pair[1].lang, "Tagalog");
  strcpy(entry[3].pair[1].trans, "malakas");
  strcpy(entry[3].pair[2].lang, "Japanese");
  strcpy(entry[3].pair[2].trans, "tsuyoi");
  strcpy(entry[3].pair[3].lang, "German");
  strcpy(entry[3].pair[3].trans, "stark");
  entry[3].pairCount = 4;
  countEntry++;
  // Entry 4: Translations for "fast"
  strcpy(entry[4].pair[0].lang, "English");
  strcpy(entry[4].pair[0].trans, "fast");
  strcpy(entry[4].pair[1].lang, "Tagalog");
  strcpy(entry[4].pair[1].trans, "mabilis");
  strcpy(entry[4].pair[2].lang, "Spanish");
  strcpy(entry[4].pair[2].trans, "rápido");
  strcpy(entry[4].pair[3].lang, "Korean");
  strcpy(entry[4].pair[3].trans, "ppalli");
  entry[4].pairCount = 4;
  countEntry++;
  // Entry 5: Translations for "love"
  strcpy(entry[5].pair[0].lang, "English");
  strcpy(entry[5].pair[0].trans, "love");
  strcpy(entry[5].pair[1].lang, "Tagalog");
  strcpy(entry[5].pair[1].trans, "mahal");
  strcpy(entry[5].pair[2].lang, "Spanish");
  strcpy(entry[5].pair[2].trans, "amor");
  strcpy(entry[5].pair[3].lang, "English");
  strcpy(entry[5].pair[3].trans, "hate");
  entry[5].pairCount = 4;
  countEntry++;

  int choice;
  do
  {
    choice = displayMainMenu();
    switch (choice)
    {
    case 1:
      printf("Add a new entry to the DataBase\n");
      addEntry(entry, &countEntry);
      break;
    case 2:
      printf("Add a new entry to the DataBase\n");
      addTranslation(entry, &countEntry);
      break;
    case 3:
      printf("Exiting program...\n");
      break;
    default:
      printf("Invalid choice! Try again.\n");
    }
  } while (choice != 3);

  return 0;
}
//Change the argument to a specific struct only, not the whole struct of the MP 
