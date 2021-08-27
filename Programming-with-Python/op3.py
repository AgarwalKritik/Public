a,b=map(int, input("Enter two elements(use \",\" to separate the elements): ").split(","))
if a==b:
    print("EQUAL")
elif a<b:
    print(f"{a} < {b}")
elif b<a:
    print(f"{b} > {a}")