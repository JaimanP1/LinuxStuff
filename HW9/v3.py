import requests
from bs4 import BeautifulSoup
from pymongo import MongoClient

url = 'https://finance.yahoo.com/most-active'

response = requests.get(url)

print(response.status_code)

soup = BeautifulSoup(response.text, "html.parser")
table = soup.find('table')
data = []

rows = table.find_all('tr')
for row in rows[1:]:
    cols = row.find_all('td')
    if len(cols) >= 7:
        data.append({
            'Symbol': cols[0].text.strip(),
            'Name': cols[1].text.strip(),
            'Price (Introday)': cols[2].text.strip(),
            'Change': cols[3].text.strip(),
            'Volume': cols[6].text.strip()
            })

#print(data)

client = MongoClient()
client.drop_database('stocks') #erasing previous data
db = client['stocks']
collection = db['volume']

collection.insert_many(data)
