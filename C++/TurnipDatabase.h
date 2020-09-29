#ifndef TURNIPDATABASE_H
#define TURNIPDATABASE_H

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
using namespace std;

class TurnipDatabase
{
private:
	sqlite3* db;
	char* zErrMsg = nullptr;
	int rc;
	char* sql;
	int priceSize;
	int costSize;
	bool isOpen = false;
public:
	TurnipDatabase();
	TurnipDatabase(const TurnipDatabase& td);
	~TurnipDatabase();
	TurnipDatabase& operator =(const TurnipDatabase& td);
	void createPriceTable();
	void createCostTable();
	void insertPrice(int price, const char* day, const char* time);
	void insertCost(int cost, int amount);
	void close();
private:
	static int callback(void* NotUsed, int argc, char** argv, char** azColName);
	int length(const char* tableName);
};

#endif /* TURNIPDATABASE_H */
