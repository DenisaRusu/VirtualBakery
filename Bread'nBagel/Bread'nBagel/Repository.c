#include "Repository.h"
#include<assert.h>
#include <stdlib.h>
#include <string.h>

Repository* createRepository(int capacity)
{
	Repository* repo = (Repository*)malloc(sizeof(Repository));
	if (repo == NULL)
		return NULL;
	repo->capacity = capacity;
	repo->length = 0;
	repo->materials = (Material*)malloc(capacity*sizeof(Material));
	if (repo->materials == NULL)
		return NULL;
	return repo;
}

void destroy(Repository* repo) {
	//free the space allocated for offers
	free(repo->materials);
	//free the space allocated for the whole dynamic structure of the repository
	free(repo);
}
void resize(Repository* repo) {
	repo->capacity *= 2;
	repo->materials = (Material*)realloc(repo->materials, repo->capacity*sizeof(Material));
}

int getLength(Repository* repo)
{
	return repo->length;
}

int equalDates(Date d1, Date d2)
{
	if (d1.day == d2.day && d1.mon == d2.mon && d1.year == d2.year)
		return 1;
	return 0;
}

int greaterDate(Date d1, Date d2)
{
	if (d1.year == d2.year && d1.mon == d2.mon && d1.day >= d2.day)
		return 1;
	if (d1.year == d2.year && d1.mon > d2.mon)
		return 1;
	if (d1.year > d2.year)
		return 1;
	return 0;
}

int isEmptyM(Material m)
{
	Date d = createDate(-1, -1, -1);
	if (strcmp(m.name, "") == 0 && strcmp(m.supplier, "") == 0 && m.quantity == -1 && equalDates(m.expdate, d))
		return 1;
	return 0;
}

int find(Repository * repo, char name[], char supplier[], Date expdate)
{
	Material* m = NULL;

	for (int i = 0; i < repo->length; i++)
		if (strcmp(repo->materials[i].name, name) == 0 && strcmp(repo->materials[i].supplier, supplier) == 0 && equalDates(repo->materials[i].expdate, expdate))
			return i;
	return -1;
}

Material getMaterialOnPos(Repository * repo, int pos)
{
	if (pos<0 || pos>repo->length)
		return createMaterial("", "", -1, createDate(-1, -1, -1));
	return repo->materials[pos];

}

int add(Repository * repo, Material m)
{
	if (repo->length == repo->capacity)
		resize(repo);
	Material found;
	int pos = find(repo, m.name, m.supplier, m.expdate);
	if (pos != -1) {
		found = getMaterialOnPos(repo, pos);
		repo->materials[pos].quantity += m.quantity;
		return 0;
	}
	repo->materials[repo->length] = m;
	repo->length++;

	return 1;

}

int update(Repository * repo, char name[], char supplier[], Date expdate, int newQuantity)
{
	int pos = find(repo, name, supplier, expdate);
	if (pos == -1)
		return 0;
	repo->materials[pos].quantity = newQuantity;
	return 1;

}

int delete(Repository * repo, char name[], char supplier[], Date expdate)
{
	int pos = find(repo, name, supplier, expdate);
	if (pos == -1)
		return 0;

	for (int i = pos; i < repo->length; i++)
		repo->materials[i] = repo->materials[i + 1];
	repo->length--;
	return 1;
}
//------------------------------------------

void TestRepository() {
	Repository* repo = createRepository(3);
	Material m = createMaterial("Eggs", "OrganicEggs", 50, createDate(28, 1, 2018));
	Material ma = createMaterial("Eggs", "OrganicEggs", 120, createDate(28, 1, 2018));
	assert(add(&repo, m), 1);
	assert(delete(&repo, "Milk", "Napolact", createDate(1, 1, 1)), 0);
	assert(delete(&repo, "Eggs", "OrganicEggs", createDate(28, 1, 2018)), 1);
	assert(repo->length, 0);
	assert(add(&repo, m), 1);
	assert(add(&repo, ma), 1);
	assert(repo->length, 1);
	assert(repo->materials[0].quantity, 120);
	assert(update(&repo, "Eggs", "OrganicEggs", createDate(28, 1, 2018), 333), 1);
	assert(repo->materials[0].quantity, 333);

}











