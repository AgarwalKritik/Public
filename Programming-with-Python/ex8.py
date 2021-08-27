#A student will not be allowed to sit in exam if his/her attendence is less than 75%.
#Take inputs from user and print if the student is allowed to sit in exam or not.
print(" Welcome to XYZ Institute.")
name=input("Enter Name of Student: ")
a,b=float(input("Number of classes held? :")), float(input("Number of classes attended? :"))
p=(b/a)*100
if p>=75:
    print(f"Your attendance percentage is {p}%. Hence, you are allowed to sit in the exam.")
else:
    print("Your attendance percentage is below 75%. Hence, you are not allowed to sit in the exam.")
