#include <iostream>
#include <stdio.h>
#include <ctime>
#include <map>
#include <stdlib.h>
#include <cstring>
using namespace std;

int main(int argc, char** argv)
{
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

	bool debug = false;

	if(argc == 2)
	{
		if(strcmp(argv[1], "-d") == 0)
		{
			debug = true;
		}
	}


	if(system(nullptr))
	{
		if(day == 0)
		{
			int command = system("git pull && cd Python && ./cost && cd ../C++ && ./turnip && cd .. && git add C++/*.db && git add Python/*.db && git commit -m \"Added new cost data\" && git push");

			if(debug)
			{
				cout<<command<<endl;
			}
		}

		else
		{
			const char* weekday = weekdays[day];
			const char* time = (hour >= 12) ? "afternoon" : "morning";

			char values[175];
			sprintf(values, "git pull && cd Python && ./price && cd ../C++ && ./turnip && cd .. && git add C++/*.db && git add Python/*.db && git commit -m \"Added %s %s price\" && git push", weekday, time);

			int command = system(values);

			if(debug)
			{
				cout<<command<<endl;
			}
		}
	}

	else
	{
		cout<<"ERROR!"<<endl;
	}

	return 0;
}
