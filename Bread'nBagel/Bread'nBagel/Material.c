
#include "Material.h"
#include <string.h>
#include <stdio.h>

Date createDate(int day, int mon, int year)
{
	Date d;
	d.day = day;
	d.mon = mon;
	d.year = year;
	return d;
}

Material createMaterial(char name[], char supplier[], int quantity, Date expdate)
{
	Material m;
	strcpy(m.name, name);
	strcpy(m.supplier, supplier);
	m.quantity = quantity;
	m.expdate.day = expdate.day;
	m.expdate.mon = expdate.mon;
	m.expdate.year = expdate.year;

	return m;
}

char * getName(Material * m)
{
	return m->name;
}

char * getSupplier(Material * m)
{
	return m->supplier;
}

int getQuantity(Material * m)
{
	return m->quantity;
}

Date getExpDate(Material * m)
{
	return m->expdate;
}

void toString(Material m, char str[])
{
	sprintf(str, "The material %s, provided by %s, has a current quantity of: %d and the expiration date: %d/%d/%d.", m.name, m.supplier, m.quantity, m.expdate.day, m.expdate.mon, m.expdate.year);
}

