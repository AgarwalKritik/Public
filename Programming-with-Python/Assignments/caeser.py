"""
A Caesar cypher is a weak form of encryption that involves “rotating” each letter by a fixed number of places. 
To rotate a letter means to shift it through the alphabet, wrap‐ ping around to the beginning if necessary, so ‘A’ rotated by 3 is ‘D’ and ‘Z’ rotated by 1 is ‘A’.
To rotate a word, rotate each letter by the same amount. For example, “cheer” rotated by 7 is “jolly” and “melon” rotated by -10 is “cubed”. 
In the movie 2001: A Space Odys‐ sey, the ship computer is called HAL, which is IBM rotated by -1.

Write a function called rotate_word that takes a string and an integer as
parameters, and returns a new string that contains the letters from the original
string rotated by the given amount.

"""

from __future__ import print_function, division
import Logo


def rotate_letter(letter, n):
    if letter.isupper():
        start = ord('A')
    elif letter.islower():
        start = ord('a')
    else:
        return letter

    c = ord(letter) - start
    i = (c + n) % 26 + start
    return chr(i)


def rotate_word(word, n):
    res = ''
    for letter in word:
        res += rotate_letter(letter, n)
    return res


if __name__ == '__main__':
    Logo.name()
    print(rotate_word('cheer', 7))
    print(rotate_word('melon', -10))
    print(rotate_word('CMRU', 19))
    print(rotate_word('IBM', -1))
