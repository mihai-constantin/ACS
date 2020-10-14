import requests

def get_method():
    r = requests.get('https://en.wikipedia.org/wiki/Cat')
    print(r.status_code)
    print(r.headers['Content-Type'])
    print(r.text)

# Save an image from an URL
def save_image():
    image = requests.get('https://imgs.xkcd.com/comics/making_progress.png')
    with open('/Users/mihai/Desktop/Semestrul 1/SPRC/l4-sprc-lab/lab01/image.png', 'wb') as f:
        f.write(image.content)

# Passing Argument in the request
def get_arg():
    ploads = {'things': 2, 'total': 25}
    r = requests.get('https://httpbin.org/get', params = ploads)
    print(r.text)
    print(r.url)

def post_method():
    pload = {'username': 'Olivia', 'password': '123'}
    r = requests.post('https://httpbin.org/post', data = pload)
    # print(r.url)
    print(r.text)
    print(r.json())

if __name__ == "__main__":
    #  get_method()
    #  save_image()
    # get_arg()
    post_method()
