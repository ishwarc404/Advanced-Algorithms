import numpy as np
import pandas as pd
import time
from random import randrange

numbers = [i for i in range(50,80)]
iterations = [i for i in range(400,410)]

numbers = [i for i in range(2352,24532)]
iterations = [i for i in range(1000,1100)]

init_primes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,37,41,43,47,53,59,61,67
,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173]


def miller_rabin(n, a):
    if n < 2: return False
    for p in init_primes:
        if n < p * p: return True
        if n % p == 0: return False
    r, s = 0, n - 1
    while s % 2 == 0:
        r += 1
        s //= 2
    for _ in range(a):
        a = randrange(2, n - 1)
        x = pow(a, s, n)
        if x == 1 or x == n - 1:
            continue
        for _ in range(r - 1):
            x = pow(x, 2, n)
            if x == n - 1:
                break
        else:
            return False
    return True

df = pd.DataFrame(columns = iterations)
df["Numbers"] = numbers
for i in iterations:
    result = []
    for num in numbers:
        start_time = time.time()
        (miller_rabin(num,i))
        result.append((time.time() - start_time))
    df[i] = result


df.to_csv("Results.csv")