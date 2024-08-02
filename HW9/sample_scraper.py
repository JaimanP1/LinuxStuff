import requests
from bs4 import BeautifulSoup

response = requests.get("http://quotes.toscrape.com/page/1/")

print(response.status_code)

page = BeautifulSoup(response.text, "html.parser")

p_tags = page.find_all("p")

links = page.find_all("a", {"class": "link"})

highlights = page.select(".highlight")

print("\np_tags: \n")
for p_tag in p_tags:
    print(p_tag)

print("\nlinks: \n")
for link in links:
    print(link)

print("\nhighlight: \n")
for highlight in highlights:
    print(highlight)

quotes = page.find_all("div", {"class": "quote"})
txt = []
author = []
for quote in quotes:
    txt.append(quote.span.text)
    author.append(quote.find("small", {"class":"author"}).text)

print(txt)
print(author)
