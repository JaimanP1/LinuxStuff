import requests
from bs4 import BeautifulSoup
from pymongo import MongoClient

url = "https://finance.yahoo.com/most-active"

response = requests.get(url)

print(response.status_code)

page = BeautifulSoup(response.text, "html.parser")

ticker = page.find_all("a", {"data-test":"quoteLink"})
price = page.find("fin-streamer", {"class data-symbol":"NVDA"})
print(price)

query = []
for i in ticker:
    query.append({"ticker":i.string})
    #price = page.find("fin-streamer", {"class data-symbol":i.string})
    #print(price)

print(query)

client = MongoClient()
client.drop_database('stocks') #erasing previous data
db = client['stocks']
collection = db['volume']

collection.insert_many(query)

