#include "TurnipDatabase.h"

TurnipDatabase::TurnipDatabase(const char* dbName) : Database(dbName)
{

}

void TurnipDatabase::createPriceTable()
{
	const char* command = "CREATE TABLE IF NOT EXISTS PRICES(" \
				"TIME TIMESTAMP PRIMARY KEY NOT NULL, "\
				"PRICE INT NOT NULL );";

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
				"TIME TIMESTAMP PRIMARY KEY NOT NULL, "\
				"COST INT NOT NULL, "\
				"AMOUNT INT NOT NULL );";

	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void TurnipDatabase::addPrice(const int price)
{
	const char* now = currentTime();
	char values[64];
	sprintf(values, "VALUES('%s', %d);", now, price);
	std::string dataValues(values);
	std::string sqlCommand = "INSERT INTO PRICES(TIME, PRICE) ";
	std::string tempCommand = sqlCommand + dataValues;
	const char* command = tempCommand.c_str();

	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	delete[] now;
}

void TurnipDatabase::addCost(const int cost, const int amount)
{
	const char* now = currentTime();
	char values[64];
	sprintf(values, "VALUES('%s', %d, %d);", now, cost, amount);
	std::string dataValues(values);
	std::string sqlCommand = "INSERT INTO COSTS(TIME, COST, AMOUNT) ";
	std::string tempCommand = sqlCommand + dataValues;
	const char* command = tempCommand.c_str();

	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL Error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	delete[] now;
}
