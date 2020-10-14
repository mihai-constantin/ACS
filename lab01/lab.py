import requests
import json

def task1():
    print('===== Exercise 1 =====')
    # create args for requests
    params = 'nume=Constantin Mihai&grupa=341C1'
    data = {'secret': 'SPRCisNice'}
    headers = {'secret2': 'SPRCisBest'}
    
    # post request at url
    url = 'https://sprc.dfilip.xyz/lab1/task1'
    requests.post(url, params = params, data = data, headers = headers)
    
    # post request at url_check
    url_check = 'https://sprc.dfilip.xyz/lab1/task1/check' 
    response = requests.post(url_check, params = params, data = data, headers = headers)

    return response.json()

def task2():
    print('===== Exercise 2 =====')
    url = 'https://sprc.dfilip.xyz/lab1/task2'
    payload = {
        'username': 'sprc',
        'password': 'admin',
        'nume': 'Constantin Mihai'
    }

    response = requests.post(url, json = payload)
    return response.json()

def task3():
    print('===== Exercise 3 =====')

    # create session
    session = requests.Session()

    # login
    url = 'https://sprc.dfilip.xyz/lab1/task3/login'
    payload = {
        'username': 'sprc',
        'password': 'admin',
        'nume': 'Constantin Mihai'
    }
    session.post(url, json = payload)

    # check
    url_check = 'https://sprc.dfilip.xyz/lab1/task3/check'
    return session.get(url_check).json()

if __name__ == "__main__":
    print(json.dumps(task1(), indent = 4))
    print(json.dumps(task2(), indent = 4))
    print(json.dumps(task3(), indent = 4))
