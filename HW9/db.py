import requests
from pymongo import MongoClient
from bs4 import BeautifulSoup

url = "https://quotes.toscrape.com/"

response = requests.get(url)

soup = BeautifulSoup(response.text, "html.parser")

quotes = soup.find_all("div", {"class":"quote"})

query = []

for i in quotes:
    text = i.find("span", {"class":"text"}).string
    author = i.find("small", {"class":"author"}).string

    query.append({"quote":text, "author":author})

print(query)

client = MongoClient()
db = client['data']
collection = db['quotes']

collection.insert_many(query)
