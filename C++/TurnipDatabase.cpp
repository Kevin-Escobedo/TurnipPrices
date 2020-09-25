#ifndef TURNIPDATABASE_CPP
#define TURNIPDATABASE_CPP

#include "TurnipDatabase.h"

TurnipDatabase::TurnipDatabase()
:db(), rc(), sql(), priceSize(), costSize()
{
	rc = sqlite3_open("turnips.db", &db);
	if(rc)
	{
		fprintf(stderr, "Can't open database");
	}

	else
	{
		priceSize = length("PRICES");
		costSize = length("COSTS");
	}
}

TurnipDatabase::TurnipDatabase(const TurnipDatabase& td)
:db(td.db), rc(td.rc), sql(td.sql), priceSize(td.priceSize), costSize(td.costSize)
{

}

TurnipDatabase::~TurnipDatabase()
{
	sqlite3_close(db);
}

TurnipDatabase& TurnipDatabase::operator =(const TurnipDatabase& td)
{
	db = td.db;
	rc = td.rc;
	sql = td.sql;
	priceSize = td.priceSize;
	costSize = td.costSize;
	return *this;
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
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void TurnipDatabase::createCostTable()
{
	const char* command = "CREATE TABLE IF NOT EXISTS COSTS(" \
			       "WEEK INT PRIMARY KEY NOT NULL, "\
			       "COST INT NOT NULL, "\
			       "AMOUNT INT NOT NULL, "\
			       "TOTAL INT NOT NULL );";
	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
}

void TurnipDatabase::insertPrice(int price, const char* day, const char* time)
{
	char values[100];
	sprintf(values, "VALUES(%d, %d, '%s', '%s');", priceSize, price, day, time);
	string dataValues(values);
	string sqlCommand = "INSERT INTO PRICES(NUM, PRICE, DAY, TIME) ";
	string tempCommand = sqlCommand + dataValues;
	const char* command = tempCommand.c_str();

	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	else
	{
		priceSize++;
	}

}

void TurnipDatabase::insertCost(int cost, int amount)
{
	char values[100];
	sprintf(values, "VALUES(%d, %d, %d, %d);", costSize, cost, amount, cost * amount);
	string dataValues(values);
	string sqlCommand = "INSERT INTO COSTS(WEEK, COST, AMOUNT, TOTAL) ";
	string tempCommand = sqlCommand + dataValues;
	const char* command = tempCommand.c_str();

	rc = sqlite3_exec(db, command, callback, nullptr, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	else
	{
		costSize++;
	}
}

void TurnipDatabase::close()
{
	sqlite3_close(db);
}

int TurnipDatabase::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	int* c = (int*)NotUsed;
	*c = atoi(argv[0]);

	bool debug = false;

	if(debug)
	{
		for(int i = 0; i < argc; i++)
		{
			printf("%s = %s\n", azColName[i], argv[1] ? argv[i] : "NULL");
		}

		printf("\n");
	}

	return 0;
}

int TurnipDatabase::length(const char* tableName)
{
	int count = 0;
	bool isPrices = (strcmp(tableName, "PRICES") == 0);
	const char* command = isPrices ? "SELECT COUNT(*) FROM PRICES" : "SELECT COUNT(*) FROM COSTS";

	rc = sqlite3_exec(db, command, callback, &count, &zErrMsg);

	if(rc != SQLITE_OK)
	{
		bool noPrice = strcmp(zErrMsg, "no such table: PRICES") == 0;
		bool noCost = strcmp(zErrMsg, "no such table: COSTS") == 0;

		if(!noPrice && !noCost)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			return -1;
		}

		sqlite3_free(zErrMsg);
		return 0;
	}

	else
	{
		return count;
	}
}

#endif /* TURNIPDATABASE_CPP */
