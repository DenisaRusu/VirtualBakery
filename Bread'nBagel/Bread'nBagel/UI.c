#include "UI.h"

#include <stdio.h>

UI* createUI(Controller* ctrl)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->ctrl = ctrl;

	return ui;
}
void destroyUI(UI* ui) {
	free(ui);
}
//----------------------------------Prints

void printMenu() {
	printf("\n\t\t\tWelcome to Bread'n Bagel!\n");
	printf("\tManaging the materials:\n");
	printf("1. Add a material.\n");
	printf("2. Update a material.\n");
	printf("3. Remove a material.\n");
	printf("4. Show all expired materials containing a given string.\n");
	printf("5. Show all the available materials containing a given string sorted by their suppliers descending.\n");
	printf("6. Show all the available materials containing a given string sorted by their suppliers ascending.\n");
	printf("7. Show all materials given by a supplier which are in short supply sorted by their quantities.\n");
	printf("8. Undo.\n");
	printf("9. Redo.\n");
	printf("0. Stop.\n");
}

void printAllMaterials(UI* ui) {
	Repository* repo = getRepository(ui->ctrl);
	int length = getLength(repo);

	if (length == 0)
		printf("There are no materials stored!\n");

	for (int i = 0; i < length; i++)
	{
		char str[200];
		toString(getMaterialOnPos(repo, i), str);
		printf("%s\n", str);
	}
}

void printList(UI* ui, Repository* list) {
	for (int i = 0; i < list->length; i++)
	{
		char str[200];
		toString(getMaterialOnPos(list, i), str);
		printf("%s\n", str);
	}

}

//----------------------------------Validators

int commandValidator(UI* ui, int command) {
	if (command >= 0 && command <= 9)
		return 1;
	return 0;
}

int dateValidator(UI* ui, Date expdate) {
	if (expdate.year >= 2000) {
		if (expdate.mon == 1 || expdate.mon == 3 || expdate.mon == 5 || expdate.mon == 7 || expdate.mon == 8 || expdate.mon == 10 || expdate.mon == 12) {
			if (expdate.day >= 1 && expdate.day <= 31)
				return 1;
			else
				return 0;
		}
		else if (expdate.mon == 4 || expdate.mon == 6 || expdate.mon == 9 || expdate.mon == 11) {
			if (expdate.day >= 1 && expdate.day <= 30)
				return 1;
			else
				return 0;
		}
		else if (expdate.mon == 2) {
			if (expdate.day >= 1 && expdate.day <= 28)
				return 1;
			else
				return 0;
		}
	}
	else
		return 0;
}

//----------------------------------Reads

Date readDate(UI* ui) {
	int day, month, year, check = 0;
	Date newDate;
	while (check == 0) {
		printf("\nEnter the day: ");
		scanf("%d", &day);
		printf("\nEnter the month: ");
		scanf("%d", &month);
		printf("\nEnter year: ");
		scanf("%d", &year);
		newDate = createDate(day, month, year);
		if (dateValidator(ui, newDate))
			check = 1;
		else
			printf("\nInvalid date! Try again.");
	}
	return newDate;
}

Material readMaterial(UI* ui) {
	char name[50];
	char supplier[50];
	int quantity;
	Date expdate;

	printf("Reading a material.\n");
	printf("\nEnter the name: ");
	scanf("%s", name);
	printf("\nEnter the supplier: ");
	scanf("%s", supplier);
	printf("\nEnter the quantity: ");
	scanf("%d", &quantity);
	printf("\nEnter the expiration date.\n");
	expdate = readDate(ui);

	return createMaterial(name, supplier, quantity, expdate);
}

//----------------------------------Functionalities

int addUI(UI* ui) {
	Material m = readMaterial(ui);
	return addCtrl(ui->ctrl, m);
}


int updateUI(UI* ui)
{
	char name[50];
	char supplier[50];
	Date expdate;
	int newquantity;

	printf("To identify the material you want to update please enter the following.\n");
	printf("\nEnter the name: ");
	scanf("%s", name);
	printf("\nEnter the supplier: ");
	scanf("%s", supplier);
	printf("Enter the expiration date.\n");
	expdate = readDate(ui);
	printf("\nNow enter the new quantity: ");
	scanf("%d", &newquantity);

	return updateCtrl(ui->ctrl, name, supplier, expdate, newquantity);
}

int deleteUI(UI* ui)
{
	char name[50];
	char supplier[50];
	Date expdate;

	printf("To identify the material you want to remove please enter the following.\n");
	printf("\nEnter the name: ");
	scanf("%s", name);
	printf("\nEnter the supplier: ");
	scanf("%s", supplier);
	printf("Enter the expiration date.\n");
	expdate = readDate(ui);

	return deleteCtrl(ui->ctrl, name, supplier, expdate);
}

void filterUI(UI* ui) {
	char name[30];
	Date cdate;

	printf("To filter the materials please enter the following.\n");
	printf("\nEnter the name [ * for all of them] : ");
	scanf("%s", name);
	printf("Enter the current date.\n");
	cdate = readDate(ui);
	Repository* filter = createRepository(20);
	filter = filterByName(ui->ctrl, filter, name);

	printf("\n The expired materials containing the given string in their name are:\n");
	for (int i = 0; i < filter->length; i++)
	{
		Material aux = getMaterialOnPos(filter, i);
		if (greaterDate(cdate, aux.expdate))
		{
			char str[200];
			toString(aux, str);
			printf("%s\n", str);

		}
	}

}

void sortSupplierDUI(UI* ui) {
	char name[30];

	printf("To filter the materials please enter the following.\n");
	printf("\nEnter the name [ * for all of them] : ");
	scanf("%s", name);

	Repository* sorted = createRepository(20);
	sorted = filterByName(ui->ctrl, sorted, name);
	sortBySupplierD(sorted);

	printf("\n The materials containing the given string in their name and sorted by supplier descending are:\n");
	for (int i = 0; i < sorted->length; i++) {
		Material aux = getMaterialOnPos(sorted, i);
		char str[200];
		toString(aux, str);
		printf("%s\n", str);
	}


}

void sortSupplierAUI(UI* ui) {
	char name[30];

	printf("To filter the materials please enter the following.\n");
	printf("\nEnter the name [ * for all of them] : ");
	scanf("%s", name);

	Repository* sorted = createRepository(20);
	sorted = filterByName(ui->ctrl, sorted, name);
	sortBySupplierA(sorted);

	printf("\n The materials containing the given string in their name and sorted by supplier ascending are:\n");
	for (int i = 0; i < sorted->length; i++) {
		Material aux = getMaterialOnPos(sorted, i);
		char str[200];
		toString(aux, str);
		printf("%s\n", str);
	}


}

void sortQuantityUI(UI* ui) {
	char supplier[30];
	int quantity;
	printf("To filter the materials please enter the following.\n");
	printf("\nEnter the supplier [ * for all of them]: ");
	scanf("%s", supplier);
	printf("\nEnter quantity criteria: ");
	scanf("%d", &quantity);

	Repository* result = createRepository(20);
	result = filterBySupplier(ui->ctrl, result, supplier);
	sortByQuantity(result);

	printf("\n The materials given by a supplier which are in short supply sorted by their quantities are:\n");
	for (int i = 0; i < result->length; i++) {
		Material aux = getMaterialOnPos(result, i);
		if (aux.quantity<quantity) {
			char str[200];
			toString(aux, str);
			printf("%s\n", str);

		}
	}






}



//----------------------------------------------------------

void startUI(UI* ui) {
	int stop = 0;
	while (!stop) {
		printf("\nMaterials:\n");
		printAllMaterials(ui);
		printMenu();
		int command;
		printf("\nEnter command:");
		scanf("%d", &command);
		if (commandValidator(ui, command)) {
			if (command == 1)
			{
				printf("\nYou selected the first command.\n");
				if (addUI(ui) == 0)
					printf("The material already existed! Its quantity was updated.");
				else
					printf("\nThe material was added!");
			}

			else if (command == 2)
			{
				printf("\nYou selected the second command.\n");
				if (updateUI(ui) == 0)
					printf("The material doesn't exist! Therefore, there's nothing to update.");
				else
					printf("\nThe material was updated!");

			}
			else if (command == 3)
			{
				printf("\nYou selected the third command.\n");
				if (deleteUI(ui) == 0)
					printf("The material doesn't exist! Therefore, there's nothing to remove.");
				else
					printf("\nThe material was removed!");

			}

			else if (command == 4)
				filterUI(ui);

			else if (command == 5)
				sortSupplierDUI(ui);

			else if (command == 6)
				sortSupplierAUI(ui);

			else if (command == 7)
				sortQuantityUI(ui);
			else if (command == 8) {
				if (undo(ui->ctrl) == 0)
					printf("Undo not successful!");
				printf("Successful undo!");
			}
			else if (command == 9) {
				if (redo(ui->ctrl) == 0)
					printf("Redo not successful!");
				printf("Successful redo!");
			}


			else if (command == 0) {
				printf("\nProgram is ending...\n");
				stop = 1;
			}
		}
		else
			printf("\nInvalid command!");

	}
}
