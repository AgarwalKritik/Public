#Python Program to check whether a given number is odd or even
a='y'
while a=='y' or a=='Y':
    n=int(input("Enter a number: "))
    if n%2==0:
        print(f"\"{n}\" is an even number.")
    else:
        print(f"\"{n}\" is an odd number")
    a=input("Do you want to check for another number? (y/n): ")