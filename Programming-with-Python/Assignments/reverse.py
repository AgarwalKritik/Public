"""
Write a program to read contents of a file and to display the contents in reverse order.
"""
import Logo

with open("file.txt", "r") as myfile:
    data = myfile.read()

data1 = data[::-1]

Logo.name()
print(data1)
