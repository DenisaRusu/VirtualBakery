#include "Operationstack.h"
#include <assert.h>


operation createOperation(Material o, char operationType[]) {
	operation op;
	op.materialBackup = o;
	strcpy(op.operationType, operationType);

	return op;
}

char* getOperationType(operation* op) {
	return op->operationType;
}

Material getMaterialBackup(operation* op) {
	return op->materialBackup;
}

//---------------------------------------------------

OperationsStack* createStack(int capacity) {
	OperationsStack* s = (OperationsStack*)malloc(sizeof(OperationsStack));
	s->capacity = capacity;
	s->length = 0;
	s->operations = (operation*)malloc(capacity*sizeof(operation));
	return s;
}

void destroyStack(OperationsStack* s) {
	free(s->operations);
	free(s);
}

void resizeStack(OperationsStack* s) {
	s->capacity *= 2;
	s->operations = (operation*)realloc(s->operations, s->capacity*sizeof(operation));
}

void push(OperationsStack* s, operation o) {
	if (isFull(s))
		return;

	s->operations[s->length] = o;
	s->length++;
}

operation* pop(OperationsStack* s) {
	if (isEmpty(s))
		return;
	s->length--;
	return &(s->operations[s->length]);
}

int isEmpty(OperationsStack* s) {
	return (s->length == 0);
}

int isFull(OperationsStack* s) {
	return s->length == 100;
}





