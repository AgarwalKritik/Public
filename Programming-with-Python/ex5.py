#A company decided to give bonus of 5% to employee if his/her year of service is more than 5 years.
#Program to ask user for their salary and year of service and print the net bonus amount.
print('''
                                 WELCOME TO AGARWAL'S PVT. LTD.
                                     !!!ANNOUNCEMENT!!!
We have decided to give a bonus of 5% to the employees whose year of service is more than 5 years.\n''')
a,b=int(input("Enter your current salary amount: ")), int(input("Enter service year: "))
if b>5:
    c=input("Enter your name: ")
    print(f"Dear {c}, thanks for your {b} years of service.\nNet bonus amount on your salary of Rs.{a} is Rs.{a*(5/100)}.")
else:
    print("Sorry, You are ineligible for the bonus.")





