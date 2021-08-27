"""
The brilliant mathematician Srinivasa Ramanujan found an infinite series that can be used to generate a numerical approximation of pi:

![Ramanujan](https://wikimedia.org/api/rest_v1/media/math/render/svg/49a59057b013e0f53abf350f5db0a6d7917eba56)

Write a function called estimate_pi that uses this formula to compute and return an estimate of pi. It should use a while loop to compute terms of 
the summation until the last term is smaller than 1e-15 (which is Python notation for 10^−15 ). You can check the result by comparing it to math.pi.

"""

import math
import Logo


def factorial(n):
    if n == 0:
        return 1
    else:
        return n*factorial(n-1)


def estimate_pi():
    total = 0
    k = 0
    factor = 2 * math.sqrt(2) / 9801
    while True:
        num = factorial(4*k) * (1103 + 26390*k)
        den = factorial(k)**4 * 396**(4*k)
        term = factor * num / den
        total += term
        if abs(term) < 1e-15:
            break
        k += 1
    return 1 / total


Logo.name()
print(f'Result of estimate_pi: {estimate_pi()}')
print(f'Result of math.pi: {math.pi}')
