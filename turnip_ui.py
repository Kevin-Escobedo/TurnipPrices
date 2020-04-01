#Author:Kevin C. Escobedo
#Email: escobedo001@gmail.com
import turnip_database as td
import datetime
from time import strptime, strftime

months = {1: "January", 2: "February", 3: "March", 4: "April", 5: "May",
          6: "June", 7: "July", 8: "August", 9: "September", 10: "October",
          11: "November", 12: "December"}

def get_price():
    '''Reads input for the price'''
    while True:
        try:
            price = int(input("Enter Price: "))
            return price
        except ValueError:
            print("Invalid input for price")

def get_day():
    '''Reads input for the day'''
    week = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]
    while True:
        try:
            day = input("Enter Day: ")
            if day not in week:
                raise ValueError
            return day
        except ValueError:
            print("Invalid input for day")

def get_time():
    '''Reads input for time'''
    times = ["Morning", "Afternoon"]
    while True:
        try:
            time = input("Enter Time: ")
            if time not in times:
                raise ValueError
            return time
        except ValueError:
            print("Invalid input for time")


if __name__ == "__main__":
    now = datetime.datetime.now()
    date = "{} {}, {}".format(months[now.month], now.day, now.year)
    weekday = strftime("%A", strptime(date, "%B %d, %Y"))
    if now.hour < 12:
        time = "Morning"
    elif now.hour >= 12:
        time = "Afternoon"
    else:
        time = "NULL"
    tp = td.TurnipDatabase()
    price = get_price()
    tp.insert_price(price, weekday, time)
    tp.close()
