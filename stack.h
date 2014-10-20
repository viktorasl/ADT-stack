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

//stack elements
typedef struct stackElement {
	void* data;
	struct stackElement* next;
} stackElement;

//dynamic data structure
typedef struct stack {
	stackElement* top;
	int number;
	int elementSize;
} stack;

//stack initialization, must be used (!), stackElement size is passed
//and is set for all elements only once 
void stackInit(stack* theStack, void* userData, int size);

//adding element to top of the stack
void stackPush(stack* theStack, void* userData);

//removing one element from the top of the stack, if no element is found
//nothing happens
void stackPop(stack* theStack);

//getting only first element which passes getCriteria, if no element was found
//stackGet function returns NULL
void** stackGet(stack theStack, int (*getCriteria)(void*));

//sorting the stack by sortCriteria function which gets either true which means swapping element
//either false, which means skipping the element.
//if sortCriteria returns true elements are swapped, if false, nothing happens
void stackSort(stack* theStack, int (*sortCriteria)(void*, void*));

//stack search for multiple entries, which pass searchCriteria
//function passes entries to displayFunction one by one
//if sortCriteria returns true elements are passed, if false, nothing happens
void stackSearch(stack theStack, int (*searchCriteria)(void*), void (*displayFunction)(void**));

//stack dublication is required to get original stack and adrees to new stack
//function leaves original stack as it was and copies data entries to backupStack
//backupStack will be sorted opposite way
void stackDublicate(stack originalStack, stack* backupStack);

//function for stack destruction, removing all entries in the stack. Recommended to use (!)
void stackDestroy(stack* theStack);
