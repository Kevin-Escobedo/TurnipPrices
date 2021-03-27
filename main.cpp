#include "TurnipDatabase.h"

int main(int argc, char** argv)
{
	TurnipDatabase td("turnips.db");

	time_t t = time(nullptr);
	tm* now = localtime(&t);
	int day = now->tm_wday;

	if(day == 0)
	{
		td.createCostTable();
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
		td.createPriceTable();
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

		td.addPrice(price);
	}

	return 0;
}
