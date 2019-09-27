import time 
import os
import yfinance as yf 
import json


class BidNetwork():
    def __init__(self):
        
        # Large list containing everything there is to know about stocks
        self.stock_list = [] 
        # List containing just basic information on stocks.
        self.stock_name_price_count = []
        
    # Add's stocks to our database. 
    def add_stock(self, stock_name, share_count):
        try: 
            self.stock_list.append(yf.Ticker(stock_name))
            print("Stock:", self.stock_list[len(self.stock_list) -1 ].info["shortName"], "was successfully added")
            self.stock_list[len(self.stock_list) -1 ].info["share_count"] = share_count
        
        except:
            print("Stock was unsuccessfully added to the market")
        
        stock_dict = {
            'stockName': stock_name, 
            'stockFullName': self.stock_list[len(self.stock_list) -1 ].info["shortName"],
            'stockPrice': self.stock_list[len(self.stock_list) -1 ].info["bid"],
            'stockShare': share_count, 
            'totalCash':  (self.stock_list[len(self.stock_list) -1 ].info["bid"]) * share_count}
        
        # Adding relevant data to 2D array
        self.stock_name_price_count.append(stock_dict)
    
    # Goes through and updates our database of stock. 
    def spin(self):
        current_stock = 0
        for stock in self.stock_name_price_count:
            stock['stockPrice'] =  self.stock_list[current_stock].info["bid"]
            stock['totalCash'] = stock['stockPrice'] * stock['stockShare']
            current_stock = current_stock + 1
    
    
# TESTING BEGINS HERE 

bid_network = BidNetwork()
    
def testing_functionality():
    global bid_network
    
    while(1):
        stock_str = str(input("Enter a Stock you want to add to our database: "))
        if(len(stock_str) > 4) or len(stock_str) == 0:
            break
        
        stock_count = int(input("Enter a how many shares you have: "))
        bid_network.add_stock(stock_str, stock_count)
        bid_network.spin()
        print(bid_network.stock_name_price_count)
    
    while(1):
        bid_network.spin()
        for stock in bid_network.stock_name_price_count:
            print(stock)
            time.sleep(1)
    
    
testing_functionality()
    

# TESTING ENDS HERE 
