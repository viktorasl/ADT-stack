/*
 * Example program to show stack.h module capabilities:
 * stack initialization, data insertion to the top, data erasure from the top,
 * entries obtainment, data sorting, data search for both single oand multiple entries,
 * data destruction.
 *
 * I have integrated Garardas Butkevicius module (linear list) and make an example showcase
 * program of football clubs.
 *
 * Author: Viktoras Laukevicius
 * Course: Informatics 2 group
 *
 * v1.0
 * Fixes: none
 *
 * v2.0
 * Fixes: Gerardas module fix: usage of two mode functions
 * pfindElement for getting pointer to element and fprintList for writing data to file
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "viktoro/stack.h"
#include "gerardo/module_list.h"

#define TOP_COUNTRIES 50

//Viktoras module demonstation functions and variables
typedef struct countries {
	char* name;
	char* code;
	int count;
} countries;

int all(void* country){
	return 1;
}

void display(void** country){
	countries* data = *country;
	printf("\t%s [%s] %d\n", data->name, data->code, data->count);
}

int getLithuania(void* country){
	countries* data = country;
	return (data->name == "Lithuania");
}

int highToLow(void* countryData_1, void* countryData_2){
	countries* country_1 = countryData_1;
	countries* country_2 = countryData_2;
	return (country_1->count > country_2->count);
}

int topCountries(void* country){
	countries* data = country;
	return (data->count >= TOP_COUNTRIES);
}

//Gerardas module demonstation functions and variables
typedef struct club {
	char* name;
	char* country;
	int titles;
} club;

void printFootballClubs(void* clubData){
	club* data = clubData;
	printf("%s from %s, CL titles: %d\n", data->name, data->country, data->titles);
}

int sortByWonTitles(void* clubOne, void* clubTwo){
	club* dataOne = clubOne;
	club* dataTwo = clubTwo;
	return (dataOne->titles > dataTwo->titles);
}

int findBayern(void* data){
	club* bayern = data;
	return (bayern->name == "Bayern Munich");
}

void standartPrint(void* clubData, FILE *fp){
	if (fp != NULL){
		club* data = clubData;
		fprintf(fp, "%s from %s, CL titles: %d\n", data->name, data->country, data->titles);
	}
}

int main(){
	
	//required for the begining
	stack collection;
	
	countries country;
	
	//stack initialization
	country.name = "Lithuania";
	country.code = "LT";
	country.count = 305;
	stackInit(&collection, &country, sizeof(country));
	
	//data insert
	country.name = "Argentina";
	country.code = "AR";
	country.count = 53;
	stackPush(&collection, &country);
	
	country.name = "Hungary";
	country.code = "HU";
	country.count = 17;
	stackPush(&collection, &country);
	
	country.name = "Netherlands";
	country.code = "NL";
	country.count = 41;
	stackPush(&collection, &country);
	
	country.name = "Poland";
	country.code = "PL";
	country.count = 231;
	stackPush(&collection, &country);
	
	country.name = "Uruguay";
	country.code = "UY";
	country.count = 3;
	stackPush(&collection, &country);
	
	//display all data
	printf("Trade list in 2002-05-01:\n");
	stackSearch(collection, all, display);
	
	//data delete
	printf("3 collectable items from Uruguay were sent.\n");
	stackPop(&collection);
	
	//display all data
	printf("Trade list in 2003-01-08:\n");
	stackSearch(collection, all, display);
	
	//get and change lithuanian data
	countries** countryData = malloc(sizeof(country));
	countryData = (countries**)stackGet(collection, getLithuania);
	if (*countryData){
		printf("%s trade stock increased by 19\n", (*countryData)->name);
		(*countryData)->count += 19;
	}
	
	//display all data
	printf("Trade list in 2004-08-18:\n");
	stackSearch(collection, all, display);
	
	//data sort from highest to lowest
	stackSort(&collection, highToLow);
	
	//display countries which items count > TOP_COUNTRIES
	printf("Top countries sorted from lowest to highest count of items (count >= %d):\n", TOP_COUNTRIES);
	stackSearch(collection, topCountries, display);
	
	//backuping data
	stack backup;
	stackDublicate(collection, &backup);

	countryData = (countries**)stackGet(collection, getLithuania);
	if (*countryData){
		printf("%s trade stock increased by 78\n", (*countryData)->name);
		(*countryData)->count += 78;
	}
	
	//printing all backup data
	printf("Backup data (all):\n");
	stackSearch(backup, all, display);
	//printing all collection data
	printf("Collection data (all):\n");
	stackSearch(collection, all, display);
	
	stackDestroy(&collection);
	stackDestroy(&backup);
	
	//Gerardas module integration
	printf("\n\nGerardas module integration\n");
	printf("Football clubs DB: \n\n");
	
	struct list* clubs = NULL;
	struct list* backupClubs = NULL;
	club cl;
	
	cl.name = "FC Barcelona";
	cl.country = "Spain";
	cl.titles = 4;
	addElement(&clubs, &cl, 1, sizeof(club));
	
	cl.name = "AC Milan";
	cl.country = "Italy";
	cl.titles = 7;
	addElement(&clubs, &cl, 2, sizeof(club));
	
	cl.name = "FC Liverpool";
	cl.country = "England";
	cl.titles = 5;
	addElement(&clubs, &cl, 3, sizeof(club));
	
	cl.name = "Real Madrid CF";
	cl.country = "Spain";
	cl.titles = 9;
	addElement(&clubs, &cl, 1, sizeof(club));
	
	cl.name = "Bayern Munich";
	cl.country = "Germany";
	cl.titles = 4;
	addElement(&clubs, &cl, 5, sizeof(club));
	
	cl.name = "Ekranas Panevezys";
	cl.country = "Lithuania";
	cl.titles = 0;
	addElement(&clubs, &cl, 5, sizeof(club));
	
	//Printing football clubs
	printf("All entered clubs:\n");
	printList(clubs, printFootballClubs);
	
	//Deleting "Panevezys Ekranas"
	deleteElement(&clubs, 5);
	
	//Printing football clubs
	printf("\nAll %d clubs which won at least one title:\n", countElements(clubs));
	if (!checkIfEmptyList(clubs)){
		printList(clubs, printFootballClubs);
	}
	dublicate(clubs, &backupClubs, sizeof(club));
	
	//Sortring by titles
	sortElements(backupClubs, sortByWonTitles);
	sortElements(clubs, sortByWonTitles);
	
	//Printing football clubs
	printf("\nAll entered clubs sorted by won titles:\n");
	printList(clubs, printFootballClubs);
	
	int bayernID = findElement(clubs, findBayern);
	printf("\nBayern Munich is number %d!\n", bayernID);
	
	//making a mistake in country
	cl.name = "Bayern Munich";
	cl.country = "Germanys";
	cl.titles = 5;
	
	printf("\nBayern Munich have won another title!\n");
	changeElement(&clubs, bayernID, &cl, sizeof(club));
	
	//correction of mistake
	club* bayernClub = malloc(sizeof(club));
	bayernClub = (club*)pfindElement(clubs, findBayern);
	if (bayernClub != NULL){
		bayernClub->country = "Germany";
	}
	
	//Sortring by titles
	sortElements(clubs, sortByWonTitles);
	printf("\nAll entered clubs sorted by won titles (latest data):\n");
	fprintList(clubs, stdout, standartPrint);
	
	destroy(&clubs);
	destroy(&backupClubs);
	
	system("PAUSE");
	return 0;
}
