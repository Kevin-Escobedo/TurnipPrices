#Author: Kevin C. Escobedo
#Email: escobedo001@gmail.com
import sqlite3

class TurnipDatabase:
    def __init__(self):
        self.db = sqlite3.connect("turnip_prices.db")
        self.cursor = self.db.cursor()
        self.datapoint = self.get_datapoint_num()

    def create_table(self, table_name:str) -> None:
        '''Creates a new table in the database'''
        self.cursor.execute("""
        CREATE TABLE IF NOT EXISTS {} (num INTEGER PRIMARY KEY, price INTEGER, day TEXT, time TEXT)""".format(table_name))

        self.db.commit()

    def insert_price(self, price:int, day:str, time:str) -> None:
        '''Adds a new price into the database'''
        try:
            self.cursor.execute("""INSERT INTO turnip_prices(num, price, day, time) VALUES(?, ?, ?, ?)""", (self.datapoint, price, day, time))
            self.datapoint += 1

        except sqlite3.IntegrityError:
            self.datapoint += 1
            self.cursor.execute("""INSERT INTO turnip_prices(num, price, day, time) VALUES(?, ?, ?, ?)""", (self.datapoint, price, day, time))

    def get_datapoint_num(self) -> int:
        '''Gets the current length of the database'''
        try:
            self.cursor.execute("SELECT * FROM turnip_prices")
            return len(self.cursor.fetchall())
        except sqlite3.OperationalError:
            return 0

    def delete_last_entry(self) -> None:
        '''Removes the last entry in the database'''
        command = "DELETE FROM turnip_prices WHERE num=?"
        self.cursor.execute(command, (self.get_datapoint_num(),))
        self.db.commit()

    def close(self):
        '''Closes the connection to the database'''
        self.db.commit()
        self.db.close()

if __name__ == "__main__":
    tp = TurnipDatabase()
    tp.create_table("turnip_prices")
    tp.close()
