#pragma once

typedef struct {
	int day;
	int mon;
	int year;
}Date;

typedef struct {
	char name[50];
	char supplier[50];
	int quantity;
	Date expdate;
}Material;

Date createDate(int day, int mon, int year);
Material createMaterial(char name[], char supplier[], int quantity, Date expdate);
char* getName(Material* m);
char* getSupplier(Material* m);
int getQuantity(Material* m);
Date getExpDate(Material* m);

void toString(Material m, char str[]);



