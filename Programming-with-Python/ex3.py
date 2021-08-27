#Python program which accepts the user's first and last name and print them in reverse order with a space between them
a,b=input("Enter First Name: "), input("Enter Last Name: ")
c=a[::-1]
d=b[::-1]
print(f"Complete Reverse: {d.upper()} {c.upper()}")
print(f"In Reverse Order: {b.upper()} {a.upper()}")
