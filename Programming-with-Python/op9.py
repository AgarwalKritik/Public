#Program to implement membership operators
a=10
b=25
list = [10,20,30,40,50]

if a in list:
    print(f"{a} is a member of the list.")
else:
    print(f"{a} is not a member of the list.")
if b not in list:
    print(f"{b} is not a member of the list.")
else:
    print(f"{b} is a member of the list.")