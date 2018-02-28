#pragma once
#include "Repository.h"
#include "OperationStack.h"

typedef struct {

	Repository* repo;
	OperationsStack* undoStack;
	OperationsStack* redoStack;

}Controller;

Controller* createController(Repository* repo, OperationsStack* undoStack, OperationsStack* redoStack);
void destroyCtrl(Controller* ctrl);

Repository* getRepository(Controller* ctrl);

int addCtrl(Controller* ctrl, Material m);

int updateCtrl(Controller* ctrl, char name[], char supplier[], Date expdate, int newQuantity);

int deleteCtrl(Controller* ctrl, char name[], char supplier[], Date expdate);

Repository* filterByName(Controller* ctrl, Repository* result, char name[]);

Repository* filterBySupplier(Controller* ctrl, Repository* result, char supplier[]);

void sortBySupplierA(Repository* repo);


void sortBySupplierD(Repository* repo);

void sortByQuantity(Repository* repo);

int undo(Controller * ctrl);
int redo(Controller * ctrl);

