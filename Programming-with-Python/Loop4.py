#Python Program to Print multiplication table of a given number
#Kritik Agarwal 19BBTCS067
n=int(input("Enter a number: "))
print("-"*30)
print(f" Multiplication Table of {n}")
print("-"*30)
for i in range(1,11):
    print(f"{n} x {i:2} = {n*i}")