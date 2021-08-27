#Program to find largest of three numbers entered by user using logical operators
a,b,c=int(input("Enter 1st Number : ")),int(input("Enter 2nd Number : ")),int(input("Enter 3rd Number : "))
if a>b and a>c:
    print(f"\n{a} is largest.")
elif b>c:
    print(f"\n{b} is largest.")
else:
    printf(f"\n{c} is largest.")