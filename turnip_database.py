#Author: Kevin C. Escobedo
#Email: escobedo001@gmail.com
import sqlite3

class TurnipDatabase:
    def __init__(self):
        self.db = sqlite3.connect("turnips.db")
        self.cursor = self.db.cursor()
        self.price_point = self.get_num("prices")
        self.week = self.get_num("costs")

    def create_price_table(self) -> None:
        '''Creates a table to track prices in the database'''
        self.cursor.execute("""
        CREATE TABLE IF NOT EXISTS prices(num INTEGER PRIMARY KEY, price INTEGER, day TEXT, time TEXT)""")

        self.db.commit()

    def create_cost_table(self) -> None:
        '''Creats a table to track costs in the database'''
        self.cursor.execute("""
        CREATE TABLE IF NOT EXISTS costs(week INTEGER PRIMARY KEY, price INTEGER, amount INTEGER, total INTEGER)""")

        self.db.commit()

    def get_num(self, table_name:str) -> int:
        '''Gets the current length of the specified database'''
        try:
            self.cursor.execute("SELECT * FROM {}".format(table_name))
            return len(self.cursor.fetchall())
        except sqlite3.OperationalError:
            return 0

    def insert_price(self, price:int, day:str, time:str) -> None:
        '''Adds a new price point into the database'''
        try:
            self.price_point += 1
            self.cursor.execute("""INSERT INTO prices(num, price, day, time) VALUES(?, ?, ?, ?)""", (self.price_point, price, day, time))

        except sqlite3.IntegrityError:
            self.price_point += 1
            self.cursor.execute("""INSERT INTO prices(num, price, day, time) VALUES(?, ?, ?, ?)""", (self.price_point, price, day, time))

    def insert_cost(self, price:int, amount:int) -> None:
        '''Adds a new cost point into the database'''
        try:
            self.week += 1
            self.cursor.execute("""INSERT INTO costs(week, price, amount, total) VALUES(?, ?, ?, ?)""", (self.week, price, amount, price * amount))

        except sqlite3.IntegrityError:
            self.week += 1
            self.cursor.execute("""INSERT INTO costs(week, price, amount, total) VALUES(?, ?, ?, ?)""", (self.week, price, amount, total))

    def delete_last_entry(self, table_name:str) -> None:
        '''Removes the last entry in the table'''
        if table_name == "prices":
            command = "DELETE FROM prices WHERE num=?"
        elif table_name == "costs":
            command = "DELETE FROM costs WHERE week=?"
        self.cursor.execute(command, (self.get_num(table_name),))
        self.db.commit()

    def close(self) -> None:
        '''Closes the connection to the database'''
        self.db.commit()
        self.db.close()

if __name__ == "__main__":
    tp = TurnipDatabase()
    tp.insert_cost(100, 300)
    #tp.delete_last_entry("prices")
    #tp.insert_cost(103, 150)
    #tp.insert_cost(98, 250)
    tp.close()
