# Write a program to find the sum of all values in a dictionary

import Logo


def dictSum(myDict):
    sum = 0
    for i in myDict:
        sum += myDict[i]
    return sum


Logo.name()
dict = {'a': 250, 'b': 198, 'c': 130}
print(f"Sum of {dict['a']}+{dict['b']}+{dict['c']} =", dictSum(dict))
