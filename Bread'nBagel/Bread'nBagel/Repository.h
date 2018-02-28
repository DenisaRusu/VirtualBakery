#pragma once
#include "Material.h"

typedef struct {

	Material* materials;
	int capacity;
	int length;

}Repository;

//Creates the repository
Repository* createRepository(int capacity);
void destroy(Repository* repo);
void resize(Repository* repo);


int getLength(Repository* repo);

/*Verifies if 2 dates are equal.
Input: d1,d2 - 2 date type elements
Output: 1 if the 2 dates are equal, 0 otherwise*/
int equalDates(Date d1, Date d2);

/*Verifies if a date is greater that another date.
Input: d1,d2 - 2 date type elements
Output: 1 if d1 > d2, 0 otherwise*/
int greaterDate(Date d1, Date d2);

/*Verifies is a material is "empty".
Input: m - a Material type element
Output: 1 if the material is "empty", 0 otherwise.*/
int isEmptyM(Material m);


/*Finds the material uniquely identified by its name, supplier and expiration date.
Input: repo - a pointer to the repository
name - a char type element representing the name of the material
supplier - a char type element representing the supplier of the material
date - a date type element representing the expiration date of the material
Output: pos - the position on which the material is situated in the repository,
-1 if the material could not be found*/
int find(Repository* repo, char name[], char supplier[], Date expdate);

/*Returns the material on the given position in the repository
Input: repo - a pointer to the repository
pos - an integer representing the position
Output: the material on the given position, or an "empty" material.*/
Material getMaterialOnPos(Repository* repo, int pos);

/*Adds a material to the repository
Input: repo - a pointer to the repository
m - a material
Output: 1 if the material was added, 0 if it was already in the repository (its quantity was updated)*/
int add(Repository* repo, Material m);

/*Updates the quantity of a material from the repository
Input:  repo - a pointer to the repository
name - a char type element representing the name of the material
supplier - a char type element representing the supplier of the material
date - a date type element representing the expiration date of the material
newQuantity - an integer representing the new quantity value
Output: 1 if the update was successful, 0 otherwise */
int update(Repository* repo, char name[], char supplier[], Date expdate, int newQuantity);

/*Deletes material from the repository
Input:  repo - a pointer to the repository
name - a char type element representing the name of the material
supplier - a char type element representing the supplier of the material
date - a date type element representing the expiration date of the material
Output: 1 if the delete was successful, 0 otherwise */
int delete(Repository* repo, char name[], char supplier[], Date expdate);


void TestRepository();