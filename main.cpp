#include "TurnipDatabase.h"
#include <ctime>
#include <map>

int main(int argc, char** argv)
{
	TurnipDatabase td("turnips.db");
	td.createPriceTable();
	td.createCostTable();

	time_t t = time(nullptr);
	tm* now = localtime(&t);
	int hour = now->tm_hour;
	int day = now->tm_wday;

	std::map<int, const char*> weekdays;

	weekdays[0] = "Sunday";
	weekdays[1] = "Monday";
	weekdays[2] = "Tuesday";
	weekdays[3] = "Wednesday";
	weekdays[4] = "Thursday";
	weekdays[5] = "Friday";
	weekdays[6] = "Saturday";

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
			std::cout<<"Enter Cost: ";
			std::cin>>cost;

			std::cout<<"Enter Amount: ";
			std::cin>>amount;
		}

		td.addCost(cost, amount);
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
			std::cout<<"Enter Price: ";
			std::cin>>price;
		}

		td.addPrice(price, weekday, time);
	}

	return 0;
}
