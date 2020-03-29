#Author: Kevin C. Escobedo
#Email: escobedo001@gmail.com
import sqlite3

class TurnipDatabase:
    def __init__(self):
        self.db = sqlite3.connect("turnips.db")
        self.cursor = self.db.cursor()
        self.price_num = self.get_price_num()
        self.week = self.get_week()

    def create_price_table(self) -> None:
        '''Creates a table to track prices in the database'''
        self.cursor.execute("""
        CREATE TABLE IF NOT EXISTS prices (num INTEGER PRIMARY KEY, price INTEGER, day TEXT, time TEXT)""")

        self.db.commit()

    def create_cost_table(self) -> None:
        '''Creats a table to track costs in the database'''
        self.cursor.execute("""
        CREATE TABLE IF NOT EXISTS costs(week INTEGER PRIMARY KEY, price INTEGER, amount INTEGER, total INTEGER)""")

        self.db.commit()
