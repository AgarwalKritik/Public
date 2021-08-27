#A student will not be allowed to sit in exam if his/her attendence is less than 75%.
#But will be allowed to sit if he/she has medical cause. Ask user if he/she has medical cause or not ( 'Y' or 'N' ) and print accordingly.
print(" Welcome to XYZ Institute.")
name=input("Enter Name of Student: ")
a,b=float(input("Number of classes held? :")), float(input("Number of classes attended? :"))
p=(b/a)*100
if p>=75:
    print(f"Your attendance percentage is {p}%. Hence, you are allowed to sit in the exam.")
else:
    c=input("Do you have a valid medical cause for less than 75% attendance?('Y' or 'N'): ")
    if c=='y' or c=='Y':
        print("You are allowed to sit in the exam.")
    else:
        print("Your attendance percentage is below 75% and you don't have a valid medical cause too.\nHence, you are not allowed to sit in the exam.")