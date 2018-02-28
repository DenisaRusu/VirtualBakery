#pragma once
#include "Controller.h"

typedef struct {
	Controller* ctrl;
}UI;

UI* createUI(Controller* ctrl);
void destroyUI(UI* ui);

void startUI(UI* ui);

//Comments - TO DO
int commandValidator(UI* ui, int command);
int dateValidator(UI* ui, Date expdate);
Date readDate(UI* ui);
Material readMaterial(UI* ui);
int deleteUI(UI* ui);
int addUI(UI* ui);
int updateUI(UI* ui);
void printList(UI* ui, Repository* repo);

void sortSupplierDUI(UI* ui);
void sortSupplierAUI(UI* ui);
void sortQuantityUI(UI* ui);
void filterUI(UI* ui);
