#include "TurnipDatabase.h"
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <map>

int main(int argc, char** argv)
{
	TurnipDatabase td;
	td.createPriceTable();
	td.createCostTable();

	time_t t = time(nullptr);
	tm* now = localtime(&t);
	int hour = now->tm_hour;

	time_t timeTemp = mktime(now);
	const tm* timeOut = localtime(&timeTemp);

	int day = timeOut->tm_wday;

	map<int, const char*> weekdays;

	weekdays[0] = "Sunday";
	weekdays[1] = "Monday";
	weekdays[2] = "Tuesday";
	weekdays[3] = "Wednesday";
	weekdays[4] = "Thursday";
	weekdays[5] = "Friday";
	weekdays[6] = "Saturday";

	const bool debug = false;

	if(day == 0)
	{
		int cost = -1;
		int amount = -1;
		if(argc == 3)
		{
			cost = atoi(argv[1]);
			amount = atoi(argv[2]);
		}

		else
		{
			cout<<"Enter Cost: ";
			cin >> cost;

			cout<<"Enter Amount: ";
			cin >> amount;
		}

		if(system(nullptr))
		{
			int command = system("ls");
			if(debug)
			{
				cout<<command<<endl;
			}
		}

		td.insertCost(cost, amount);
		td.close();

		if(system(nullptr))
		{
			int command = system("git add *.db && git commit -m \"Added new cost datapoint\" && git push");
			if(debug)
			{
				cout<<command<<endl;
			}
		}
	}

	else
	{
		const char* weekday = weekdays[day];
		const char* time = (hour >= 12) ? "Afternoon" : "Morning";

		int price = -1;
		if(argc == 2)
		{
			price = atoi(argv[1]);
		}

		else
		{
			cout<<"Enter Price: ";
			cin >> price;
		}

		td.insertPrice(price, weekday, time);
		td.close();

		if(system(nullptr))
		{
			char values[100];
			sprintf(values, "git add *.db && git commit -m \"Added %s %s price && git push", weekday, time);
			int command = system(values);

			if(debug)
			{
				cout<<command<<endl;
			}
		}
	}
	
	return 0;
}
