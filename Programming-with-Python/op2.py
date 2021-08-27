#Program to compare the heights of four persons A B C D and print their names in decreasing order of their height
name1,height1=input('Enter First Name: '), int(input('Enter First height: '))
name2,height2= input('Enter second Name: '), int(input('Enter Second height: '))
name3,height3 = input('Enter third Name: '), int(input('Enter third height: '))
name4,height4 = input('Enter Fourth Name: '), int(input('Enter fourth height: '))
if height1>height2 and height1>height3 and height1>height4:
	print(name1, ' ',height1)
	if height2>height3 and height2>height4:
		print(name2, ' ',height2)
		if height3>height4:
			print(name3, ' ',height3)
			print(name4, ' ',height4)
		else:
			print(name4 ,' ',height4)
			print(name3 ,' ',height3)
	elif height3>height2 and height3>height4:
		print(name3, ' ',height3)
		if height2>height4:
			print(name2, ' ',height2)
			print(name4, ' ',height4)
		else:
			print(name4, ' ',height4)
			print(name2, ' ',height2)
	elif height4>height2 and height4>height3:
		print(name4, ' ',height4)
		if height2>height3:
			print(name2, ' ',height2)
			print(name3, ' ',height3)
		else:
			print(name3, ' ',height3)
			print(name2, ' ',height2)
elif height2>height1 and height2>height3 and height2>height4:
	print(name2, ' ',height2)
	if height1>height3 and height1>height4:
		print(name1, ' ',height1)
		if height3>height4:
			print(name3, ' ',height3)
			print(name4, ' ',height4)
		else:
			print(name4 ,' ',height4)
			print(name3 ,' ',height3)
	elif height3>height1 and height3>height4:
		print(name3, ' ',height3)
		if height1>height4:
			print(name1, ' ',height1)
			print(name4, ' ',height4)
		else:
			print(name4, ' ',height4)
			print(name1, ' ',height1)
	elif height4>height1 and height4>height3:
		print(name4, ' ',height4)
		if height1>height3:
			print(name1, ' ',height1)
			print(name3, ' ',height3)
		else:
			print(name3, ' ',height3)
			print(name1, ' ',height1)
elif height3>height1 and height3>height2 and height3>height4:
	print(name3, ' ',height3)
	if height1>height2 and height1>height4:
		print(name1, ' ',height1)
		if height3>height4:
			print(name3, ' ',height3)
			print(name4, ' ',height4)
		else:
			print(name4 ,' ',height4)
			print(name3 ,' ',height3)
	elif height2>height1 and height2>height4:
		print(name2, ' ',height2)
		if height1>height4:
			print(name1, ' ',height1)
			print(name4, ' ',height4)
		else:
			print(name4, ' ',height4)
			print(name1, ' ',height1)
	elif height4>height1 and height4>height2:
		print(name4, ' ',height4)
		if height1>height2:
			print(name1, ' ',height1)
			print(name2, ' ',height2)
		else:
			print(name2, ' ',height2)
			print(name1, ' ',height1)
elif height4>height1 and height4>height3 and height4>height2:
	print(name4, ' ',height4)
	if height1>height3 and height1>height2:
		print(name1, ' ',height1)
		if height3>height2:
			print(name3, ' ',height3)
			print(name2, ' ',height2)
		else:
			print(name2 ,' ',height2)
			print(name3 ,' ',height3)
	elif height3>height1 and height3>height2:
		print(name3, ' ',height3)
		if height1>height2:
			print(name1, ' ',height1)
			print(name2, ' ',height2)
		else:
			print(name2, ' ',height2)
			print(name1, ' ',height1)
	elif height2>height1 and height2>height3:
		print(name2, ' ',height2)
		if height1>height3:
			print(name1, ' ',height1)
			print(name3, ' ',height3)
		else:
			print(name3, ' ',height3)
			print(name1, ' ',height1)