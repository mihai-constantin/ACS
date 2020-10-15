import requests
import json

def get_args():
    nume = input('Nume: ') 
    grupa = input('Grupa: ')
    return [nume, grupa]

def task1(nume, grupa):
    print('===== Exercise 1 =====')
    # create args for requests
    params = {'nume': nume, 'grupa': grupa}
    data = {'secret': 'SPRCisNice'}
    headers = {'secret2': 'SPRCisBest'}
    
    # post request at url
    url = 'https://sprc.dfilip.xyz/lab1/task1'
    requests.post(url, params = params, data = data, headers = headers)
    
    # post request at url_check
    url_check = 'https://sprc.dfilip.xyz/lab1/task1/check' 
    response = requests.post(url_check, params = params, data = data, headers = headers)

    return response.json()

def task2(nume):
    print('===== Exercise 2 =====')
    url = 'https://sprc.dfilip.xyz/lab1/task2'
    payload = {
        'username': 'sprc',
        'password': 'admin',
        'nume': nume
    }

    response = requests.post(url, json = payload)
    return response.json()

def task3(nume):
    print('===== Exercise 3 =====')
    # create session
    session = requests.Session()

    # login
    url = 'https://sprc.dfilip.xyz/lab1/task3/login'
    payload = {
        'username': 'sprc',
        'password': 'admin',
        'nume': nume
    }
    session.post(url, json = payload)

    # check
    url_check = 'https://sprc.dfilip.xyz/lab1/task3/check'
    return session.get(url_check).json()

if __name__ == "__main__":
    [nume, grupa] = get_args()
    print(json.dumps(task1(nume, grupa), indent = 4))
    print(json.dumps(task2(nume), indent = 4))
    print(json.dumps(task3(nume), indent = 4))
