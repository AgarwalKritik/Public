# Write a program that displays which Letters are in the Two Strings but not in both (Hint: use Set data structure)

import Logo

Logo.name()
S1 = input("Enter 1st string: ")
S2 = input("Enter 2nd string: ")
A = list(set(S1) ^ set(S2))
print("The letters are:")

for i in A:
    print(i, end="   ")
