#pragma once
#include "Material.h"
#include <string.h>

/*This structure defines the operation type that contains a string representing the type of the operation
and an offer type element representing the backup of the offer that is used within the operation*/
typedef struct {
	Material materialBackup;
	char operationType[30];
}operation;

/*This function creates the operation type element.
Input: o - an offer type element representing the offer that is used within the operation
operationType - a string representing the type of the operation
Output: op - an operation type element constructed with the input values*/
operation createOperation(Material m, char operationType[]);

//Getter for the type of the operation
char* getOperationType(operation* op);

//Getter fot the backup offer of the operation
Material getMaterialBackup(operation* op);

//------------------------------------------------------------------

//This structure defines the OperationsStack type that represents the virtual stack of operations
typedef struct {
	operation* operations;
	int length;
	int capacity;
}OperationsStack;

//This function creates a new stack of operations and initializez its length with 0
OperationsStack* createStack(int capacity);

void destroyStack(OperationsStack* s);
void resizeStack(OperationsStack* s);

void push(OperationsStack* s, operation o);

operation* pop(OperationsStack* s);

int isEmpty(OperationsStack* s);

int isFull(OperationsStack* s);
