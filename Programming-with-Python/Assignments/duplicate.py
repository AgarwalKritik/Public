"""
Write a function called has_duplicates that takes a list and returns True if there is any element that appears more than once. 
It should not modify the original list.
"""

import Logo


def has_duplicates(n):
    if len(n) == 0:
        return 'List is empty.'
    elif len(n) == 1:
        return 'List contains only one element.'
    previous_elem = n[0]
    for elem in sorted(n):
        if previous_elem == elem:
            return True
        previous_elem = elem
    return False


Logo.name()
a = [1, 2, 3, 4, 5, 3]
print(has_duplicates(a))
print(has_duplicates(['c', 'm', 'r', 'u']))
print(has_duplicates([]))
print(has_duplicates(['']))
print(has_duplicates([5, 7, 6, 9, 4, 2, 8, ]))
