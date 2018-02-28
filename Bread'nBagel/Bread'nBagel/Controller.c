#include "Controller.h"
#include <string.h>

Controller* createController(Repository * repo, OperationsStack* undoStack, OperationsStack* redoStack)
{
	Controller* ctrl = (Controller*)malloc(sizeof(Controller));
	ctrl->repo = repo;
	ctrl->undoStack = undoStack;
	ctrl->redoStack = redoStack;
	return ctrl;
}

void destroyCtrl(Controller* ctrl) {
	free(ctrl);

}

Repository * getRepository(Controller * ctrl)
{
	return ctrl->repo;
}

int addCtrl(Controller * ctrl, Material m)
{
	int check = add(ctrl->repo, m);
	if (check == 1) {
		operation op = createOperation(m, "add");
		if (ctrl->undoStack->length == ctrl->undoStack->capacity)
			resizeStack(ctrl->undoStack);
		if (ctrl->redoStack->length == ctrl->redoStack->capacity)
			resizeStack(ctrl->redoStack);
		push(ctrl->undoStack, op);
		push(ctrl->redoStack, op);
	}
	return check;
}

int updateCtrl(Controller * ctrl, char name[], char supplier[], Date expdate, int newQuantity)
{
	int pos = find(ctrl->repo, name, supplier, expdate);
	Material old = getMaterialOnPos(ctrl->repo, pos);
	int check = update(ctrl->repo, name, supplier, expdate, newQuantity);
	Material new = getMaterialOnPos(ctrl->repo, pos);
	if (check == 1) {

		operation oUndo = createOperation(old, "update");
		operation oRedo = createOperation(new, "update");
		if (ctrl->undoStack->length == ctrl->undoStack->capacity)
			resizeStack(ctrl->undoStack);
		if (ctrl->redoStack->length == ctrl->redoStack->capacity)
			resizeStack(ctrl->redoStack);
		push(ctrl->undoStack, oUndo);
		push(ctrl->redoStack, oRedo);
	}
	return check;
}

int deleteCtrl(Controller * ctrl, char name[], char supplier[], Date expdate)
{
	int pos = find(ctrl->repo, name, supplier, expdate);
	Material m = getMaterialOnPos(ctrl->repo, pos);
	int check = delete(ctrl->repo, name, supplier, expdate);
	if (check == 1) {
		operation op = createOperation(m, "delete");
		if (ctrl->undoStack->length == ctrl->undoStack->capacity)
			resizeStack(ctrl->undoStack);
		if (ctrl->redoStack->length == ctrl->redoStack->capacity)
			resizeStack(ctrl->redoStack);
		push(ctrl->undoStack, op);
		push(ctrl->redoStack, op);
	}
	return check;
}

Repository* filterByName(Controller* ctrl, Repository* result, char name[]) {

	if (strcmp(name, "*") == 0)
		return ctrl->repo;

	for (int i = 0; i < getLength(ctrl->repo); i++)
	{
		Material m = getMaterialOnPos(ctrl->repo, i);
		if (strstr(m.name, name) != NULL)
			add(result, m);
	}
	return result;

}

Repository* filterBySupplier(Controller* ctrl, Repository* result, char supplier[]) {

	if (strcmp(supplier, "*") == 0)
		return ctrl->repo;

	for (int i = 0; i < getLength(ctrl->repo); i++)
	{
		Material m = getMaterialOnPos(ctrl->repo, i);
		if (strstr(m.supplier, supplier) != NULL)
			add(result, m);
	}
	return result;

}

void sortBySupplierA(Repository* repo) {

	Material aux;
	for (int i = 0; i < repo->length - 1; i++)
	{
		for (int j = 0; j<repo->length - 1 - i; j++)
			if (strcmp(repo->materials[j].supplier, repo->materials[j + 1].supplier) > 0) {
				aux = repo->materials[j];
				repo->materials[j] = repo->materials[j + 1];
				repo->materials[j + 1] = aux;
			}

	}

}
void sortBySupplierD(Repository* repo) {

	Material aux;
	for (int i = 0; i < repo->length - 1; i++)
	{
		for (int j = 0; j<repo->length - 1 - i; j++)
			if (strcmp(repo->materials[j].supplier, repo->materials[j + 1].supplier) < 0) {
				aux = repo->materials[j];
				repo->materials[j] = repo->materials[j + 1];
				repo->materials[j + 1] = aux;
			}

	}

}

void sortByQuantity(Repository* repo) {
	Material aux;
	for (int i = 0; i < repo->length - 1; i++)
	{
		for (int j = 0; j<repo->length - 1 - i; j++)
			if (repo->materials[j].quantity>repo->materials[j + 1].quantity) {
				aux = repo->materials[j];
				repo->materials[j] = repo->materials[j + 1];
				repo->materials[j + 1] = aux;
			}
	}

}

int undo(Controller * ctrl) {
	operation* op = pop(ctrl->undoStack);
	char* type = getOperationType(op);
	if (strcmp(type, "add") == 0) {
		Material toDelete = getMaterialBackup(op);
		int check = delete(ctrl->repo, toDelete.name, toDelete.supplier, toDelete.expdate);
		//if check==1 => undo succesful
		return check;
	}
	else if (strcmp(type, "delete") == 0) {
		Material toAdd = getMaterialBackup(op);
		int check = add(ctrl->repo, toAdd);
		//if check==1 => undo succesful
		return check;
	}
	else if (strcmp(type, "update") == 0) {
		Material oldMaterial = getMaterialBackup(op);
		int check = update(ctrl->repo, oldMaterial.name, oldMaterial.supplier, oldMaterial.expdate, oldMaterial.quantity);
		//if check==1 => undo succesful
		return check;
	}
	return 0;
}

int redo(Controller * ctrl) {
	operation* op = pop(ctrl->redoStack);
	char* type = getOperationType(op);
	if (strcmp(type, "add") == 0) {
		Material toAdd = getMaterialBackup(op);
		int check = add(ctrl->repo, toAdd);
		//if check==1 => redo succesful
		return check;
	}
	else if (strcmp(type, "delete") == 0) {
		Material toDelete = getMaterialBackup(op);
		int check = delete(ctrl->repo, toDelete.name, toDelete.supplier, toDelete.expdate);
		//if check==1 => redo succesful
		return check;
	}
	else if (strcmp(type, "update") == 0) {
		Material newMaterial = getMaterialBackup(op);
		int check = update(ctrl->repo, newMaterial.name, newMaterial.supplier, newMaterial.expdate, newMaterial.quantity);
		//if check==1 => redo succesful
		return check;
	}
	return 0;
}

