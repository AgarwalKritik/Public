#Python Program to Print fibonacci series between 1 to 20
#Kritik Agarwal 19BBTCS067
a,b,x=0,1,0
print(f"Fibonacci Series between 1 to 20: {a}  {b}", end="  ")
for i in range(2,21):
    x=a+b
    print(x, end="  ")
    a,b=b,x


