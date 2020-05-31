#Author: Kevin C. Escobedo
#Email: escobedo001@gmail.com
import turnip_database as td

def get_amount():
    '''Reads input for the amount purchased'''
    while True:
        try:
            amount = int(input("Enter Amount: "))
            return amount
        except ValueError:
            print("Invalid input for amount")

def get_cost():
    '''Reads input for the cost of turnips'''
    while True:
        try:
            cost = int(input("Enter Cost: "))
            return cost
        except ValueError:
            print("Invalid input for cost")

if __name__ == "__main__":
    cost = get_cost()
    amount = get_amount()
    tp = td.TurnipDatabase()
    tp.insert_cost(cost, amount)
    tp.close()
