/*
 * Abstract dynamic structure Stack
 *
 * Before using stack, the type should be declared
 * Example: stack newStack;
 *
 * After the work, the stack should be destroyed
 * by calling stackDestroy function and sending the address to stack
 * Example: stackDestroy(&newStack);
 *
 * Author: Viktoras Laukevicius
 * Course: Informatics 2 group
 *
 * v1.0
 * Fixes: 
 ** stack destructor deleting elements one by one (no memory leak).
 ** poping stack element, the data is deleted also (no memory leak).
 ** stacks dublication works properly now. Making copies of both element and
 * its data
 *
 * v2.0
 * Fixes: none
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

//#define DEBUG 1

//initializing stack
void stackInit(stack* theStack, void* userData, int size){
	
	#ifdef DEBUG
	printf("\nDEBUG (%d): ****stackInit****", __LINE__);
	#endif
	
	//new stack element
	stackElement* temp;
	temp = malloc(sizeof(stackElement));
	temp->data = malloc(size);
	memcpy(temp->data, userData, size);
	temp->next = NULL;
	
	//initializing the stack
	theStack->top = malloc(sizeof(stackElement));
	memcpy(theStack->top, temp, sizeof(stackElement));
	theStack->number = 1;
	theStack->elementSize = size;
	
	#ifdef DEBUG
	printf("\nDEBUG (%d): size = %d", __LINE__, size);
	printf("\nDEBUG (%d): theStack->number = %d", __LINE__, theStack->number);
	#endif
	
	free(temp);
	
}

//adding element to stack
void stackPush(stack* theStack, void* userData){
	
	#ifdef DEBUG
	printf("\nDEBUG (%d): ****PUSH****", __LINE__);
	#endif
	
	//new stack element
	stackElement* temp;
	temp = (stackElement*)malloc(sizeof(stackElement));
	temp->data = malloc(theStack->elementSize);
	memcpy(temp->data, userData, theStack->elementSize);
	temp->next = theStack->top;
	
	//push to stack
	theStack->top = malloc(sizeof(stackElement));
	memcpy(theStack->top, temp, sizeof(stackElement));
	theStack->number++;
	
	#ifdef DEBUG
	printf("\nDEBUG (%d): theStack->elementSize = %d", __LINE__, theStack->elementSize);
	printf("\nDEBUG (%d): theStack->number = %d", __LINE__, theStack->number);
	#endif
	
	free(temp);

}

//removing element from stack
void stackPop(stack* theStack){
	
	#ifdef DEBUG
	printf("\nDEBUG (%d): ****POP****", __LINE__);
	#endif
	
	//temporary stackElement to go though stack
	stackElement* temp;
	temp = malloc(sizeof(stackElement));
	
	if (theStack->top && theStack->top->next){
		memcpy(temp, theStack->top->next, sizeof(stackElement));
		
		#ifdef DEBUG
		printf("\nDEBUG (%d): sizeof(stackElement) = %d", __LINE__, sizeof(stackElement));
		#endif
		
		//pop the element from stack
		free(theStack->top->data);
		free(theStack->top);
		theStack->top = malloc(sizeof(stackElement));
		memcpy(theStack->top, temp, sizeof(stackElement));
		theStack->number--;
		
		#ifdef DEBUG
		printf("\nDEBUG (%d): theStack->number = %d", __LINE__, theStack->number);
		#endif
	}else if (theStack->top){
		#ifdef DEBUG
		printf("\nDEBUG (%d): last element free(theStack->top)", __LINE__);
		#endif
		free(theStack->top);
		theStack->top = NULL;
	}
	
	free(temp);
}

//getting all element by search criteria
//sending them one by one to display function
void stackSearch(stack theStack, int (*searchCriteria)(void*), void (*displayFunction)(void**)){
	
	#ifdef DEBUG
	printf("\nDEBUG (%d): ****stackSearch****", __LINE__);
	#endif
	
	//temporary stack element to go through stack
	stackElement* temp = theStack.top;
	
	while (temp){
		//1 if search criteria is passed, 0 if not
		if ((*searchCriteria)(temp->data)){
			#ifdef DEBUG
			printf("\nDEBUG (%d): if searchCriteria is passed", __LINE__);
			#endif
			(*displayFunction)(&temp->data);
		}
		temp = temp->next;
	}
	
	free(temp);
	
}

//getting only one (first) stack element according to getCriteria
void** stackGet(stack theStack, int (*getCriteria)(void*)){

	#ifdef DEBUG
	printf("\nDEBUG (%d): ****stackGet****", __LINE__);
	#endif
	
	//temporary stackElement to go through stack
	stackElement* temp = theStack.top;
	
	while (temp){
		if ((*getCriteria)(temp->data)){
			#ifdef DEBUG
			printf("\nDEBUG (%d): if getCriteria is passed", __LINE__);
			#endif
			return &temp->data;
		}
		temp = temp->next;
	}
	
	return NULL;
}

//sorting the stack by sortCriteria function
void stackSort(stack* theStack, int (*sortCriteria)(void*, void*)){
	
	#ifdef DEBUG
	printf("\nDEBUG (%d): ****stackSort****", __LINE__);
	#endif
	
	//counter one
	stackElement* i = theStack->top;

	while (1){
		if (i == NULL){
			break;
		}
		//counter two
		stackElement* j = i->next;
		//variable for comparing
		stackElement* compare = i;
		if (j == NULL){
			break;
		}
		while (1){
			if (j == NULL){
				break;
			}
			//if sort criteria is passed
			if ((*sortCriteria)(j->data, compare->data)){
				#ifdef DEBUG
				printf("\nDEBUG (%d): sort swap", __LINE__);
				#endif
				compare = j;
			}
			j = j->next;
		}
	
		//data swap
		void* tempData = malloc(theStack->elementSize);
		memcpy(tempData, i->data, theStack->elementSize); 
		memcpy(i->data, compare->data, theStack->elementSize);
		memcpy(compare->data, tempData, theStack->elementSize);
		free(tempData);
		
		i = i->next;
	}
}

//stack duplicate, leaving originalStack as it was and copying
//data entires to backupStack
//backupStack will be sorted opposite way
void stackDublicate(stack originalStack, stack* backupStack){

	#ifdef DEBUG
	printf("\nDEBUG (%d): ****dublicateStack****", __LINE__);
	#endif
	
	backupStack->number = originalStack.number;
	backupStack->elementSize = originalStack.elementSize;
	backupStack->top = NULL;
	
	stackElement* temp = originalStack.top;
	while (temp != NULL){
		#ifdef DEBUG
		printf("\nDEBUG (%d): entries are copied", __LINE__);
		#endif
		stackPush(backupStack, temp->data);
		temp = temp->next;
	}
	
}

//stack destructor
void stackDestroy(stack* theStack){

	#ifdef DEBUG
	printf("\nDEBUG (%d): ****stackDestroy****", __LINE__);
	#endif
	
	stackElement* temp;
	//deleting elements one by one
	while (theStack->top != NULL){
		temp = theStack->top->next;
		free(theStack->top->data);
		free(theStack->top);
		#ifdef DEBUG
		printf("\nDEBUG (%d): ****delete Element****", __LINE__);
		#endif
		theStack->top = temp;
	}
	
	free(theStack->top);
	theStack->top = NULL;
	
}
