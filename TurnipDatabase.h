#ifndef TURNIPDATABASE_H
#define TURNIPDATABASE_H
#include "Database.h"

class TurnipDatabase: public Database
{
public:
	TurnipDatabase(const char* dbName);
	void createPriceTable();
	void createCostTable();
	void addPrice(const int& price, const char* day, const char* time);
	void addCost(const int& cost, const int& amount);
};

#endif /* TURNIPDATABASE_H */
