#Take input of age of 3 people by user and determine oldest and youngest among them
a,b,c=input("Age of 3 people separated by comma(','): ").split(",")
if a<b and a<c:
    if b<c:
        print(f"{c} is oldest,{a} is youngest.")
    else:
        print(f"{b} is oldest,{a} is youngest.")
elif b<a and b<c:
    if a<c:
        print(f"{c} is oldest,{b} is youngest.")
    else:
        print(f"{a} is oldest,{b} is youngest.")
elif c<a and c<b:
    if a<b:
        print(f"{b} is oldest,{c} is youngest.")
    else:
        print(f"{a} is oldest,{c} is youngest.")
else:
    print("All are equal.")
