"""
Write a function called middle that takes a list and returns a new list that
contains all but the first and last elements. For example:
>>> t = [1, 2, 3, 4]
>>> middle(t)
[2, 3]

"""

import Logo


def middle(n):
    return n[1:-1]


t = [1, 2, 3, 4]
listm = middle(t)

Logo.name()
print(f'>>> t = {t}')  # stays unmodified
print(f'>>> middle(t) = {listm}')
