import requests

r = requests.get('http://www.google.com/images/ branding/googlelogo/1x/googlelogo_white_background_color_272x92dp.png')

print(r.status_code)

fd=open('./googlelogo.png', 'wb')

fd.write(r.content)

fd.close()
