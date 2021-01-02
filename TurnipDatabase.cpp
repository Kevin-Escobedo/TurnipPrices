#include "TurnipDatabase.h"

TurnipDatabase::TurnipDatabase(const char* dbName) : Database(dbName)
{

}

void TurnipDatabase::createPriceTable()
{
	const char* command = "CREATE TABLE IF NOT EXISTS PRICES(" \
				"NUM INT PRIMARY KEY NOT NULL, "\
				"PRICE INT NOT NULL, "\
				"DAY TEXT NOT NULL, "\
				"TIME TEXT NOT NULL );";

	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void TurnipDatabase::createCostTable()
{
	const char* command = "CREATE TABLE IF NOT EXISTS COSTS("\
				"WEEK INT PRIMARY KEY NOT NULL, "\
				"COST INT NOT NULL, "\
				"AMOUNT INT NOT NULL, "\
				"TOTAL INT NOT NULL );";

	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void TurnipDatabase::addPrice(const int& price, const char* day, const char* time)
{
	char values[128];
	sprintf(values, "VALUES(%d, %d, '%s', '%s');", length("PRICES"), price, day, time);
	std::string dataValues(values);
	std::string sqlCommand = "INSERT INTO PRICES(NUM, PRICE, DAY, TIME) ";
	std::string tempCommand = sqlCommand + dataValues;
	const char* command = tempCommand.c_str();

	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void TurnipDatabase::addCost(const int& cost, const int& amount)
{
	char values[128];
	sprintf(values, "VALUES(%d, %d, %d, %d);", length("COSTS"), cost, amount, cost * amount);
	std::string dataValues(values);
	std::string sqlCommand = "INSERT INTO COSTS(WEEK, COST, AMOUNT, TOTAL) ";
	std::string tempCommand = sqlCommand + dataValues;
	const char* command = tempCommand.c_str();

	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}
