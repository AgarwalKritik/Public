#Python Program to ask user to enter marks and print the corresponding grade.
print(" Welcome to XYZ School! ")
name=input("Enter Student Name: ")
print("Enter marks out of 100: ")
a,b,c,d,e=int(input("1. Mathematics: ")), int(input("2. Science: ")), int(input("3. History: ")), int(input("4. Geography: ")), int(input("5. Computer Science: "))
m=(a+b+c+d+e)/5
if m>80:
    print(f"{name} has secured grade \"A\"")
elif m>=60 and m<=80:
    print(f"{name} has secured grade \"B\"")
elif m>=50 and m<60:
    print(f"{name} has secured grade \"C\"")
elif m>=45 and m<50:
    print(f"{name} has secured grade \"D\"")
elif m>=25 and m<45:
    print(f"{name} has secured grade \"E\"")
else:
    print(f"{name} has secured grade \"F\"")

