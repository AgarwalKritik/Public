#Iterate over a given list l = [2,3,5,1,10,25,115,160] and print the number which is divisible by 5 and stop the iteration if a number greater than 150 is found.
#Kritik Agarwal 19BBTCS067
l=[2,3,5,1,10,25,115,160]
for i in l:
    if i>150:
        break
    elif i%5==0:
        print(i, end="  ")

