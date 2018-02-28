#include "Repository.h"
#include "UI.h"
#include <crtdbg.h>



int main()
{

	Repository* repo = createRepository(20);

	add(repo, createMaterial("Eggs", "OrganicEggs", 50, createDate(28, 1, 2018)));
	add(repo, createMaterial("Eggs", "TheCrackin'Egg", 25, createDate(12, 3, 2017)));
	add(repo, createMaterial("Flour", "Stone-Buhr", 100, createDate(13, 3, 2017)));
	add(repo, createMaterial("EggPasta", "Papi", 13, createDate(10, 3, 2017)));
	add(repo, createMaterial("Nuts", "Algromera", 26, createDate(25, 7, 2017)));
	add(repo, createMaterial("Milk", "Blanc", 40, createDate(20, 5, 2017)));
	add(repo, createMaterial("MilkChocolate", "Lindt", 15, createDate(5, 3, 2017)));
	add(repo, createMaterial("Milk", "Balint", 12, createDate(2, 3, 2017)));
	add(repo, createMaterial("Milk", "Papi", 12, createDate(28, 3, 2017)));
	add(repo, createMaterial("Milk", "Papi", 51, createDate(2, 3, 2017)));

	OperationsStack* undoStack = createStack(20);
	OperationsStack* redoStack = createStack(20);



	Controller* ctrl = createController(repo, undoStack, redoStack);
	UI* ui = createUI(ctrl);

	void TestRepository();

	startUI(ui);

	destroy(repo);
	destroyCtrl(ctrl);
	destroyUI(ui);


	_CrtDumpMemoryLeaks();
	return 0;


}