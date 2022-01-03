# Benes network

from math import log2

N = 8
ETAJE = 2 * (int)(log2(N)) - 1

matrix = [[0] * ETAJE] * (int)(N/2)
permutation = []

def nextPerm(data_in):
    if data_in % 4 == 1:
        return data_in + 1
    if data_in % 4 == 2:
        return data_in - 1
    return data_in

def getNext(data_in, idx):
    if idx == 0:
        return permutation[data_in]
    if (idx == ETAJE - 2):
        return permutation[permutation[data_in]]
    if idx == ETAJE - 1:
        return data_in
    return nextPerm(data_in)

def solve(data_in, data_out, idx):
    if data_in == data_out and idx == ETAJE:
        return True
    if idx == ETAJE:
        return False
    
    rev = False
    if matrix[(int)(data_in/2)][idx] == 0:
        rev = True
        matrix[(int)(data_in/2)][idx] = 1
        next_data_in = getNext(data_in, idx)
        if solve(next_data_in, data_out, idx + 1) == True:
            return True
        if data_in % 2 == 0:
            data_in = data_in + 1
        else:
            data_in = data_in - 1
        matrix[(int)(data_in/2)][idx] = -1
        next_data_in = getNext(data_in, idx)
        if solve(next_data_in, data_out, idx + 1) == True:
            return True
    elif matrix[(int)(data_in/2)][idx] == 1:
        next_data_in = getNext(data_in, idx)
        if solve(next_data_in, data_out, idx + 1):
            return True
    else:
        if data_in % 2 == 0:
            data_in = data_in + 1
        else:
            data_in = data_in - 1
        next_data_in = getNext(data_in, idx)
        if solve(next_data_in, data_out, idx + 1) == True:
            return True
    
    if rev == True:
        matrix[(int)(data_in/2)][idx] = 0

    return False

def benes(data_in, data_out):
    for i in range(N):
        permutation.append((int)(i/2 + i%2 * pow(2, (int)(log2(N)) - 1)))

    solve(data_in, data_out, 0)

    for i in range((int)(N/2)):
        for j in range(ETAJE):
            print(matrix[i][j], end = " ")
        print()

if __name__ == "__main__":
    data_in = input('in: ')
    data_out = input('out: ')

    benes((int)(data_in), (int)(data_out))
