"""
Write a program to extract only the digits from the tuples. 
For example: t=(10,20,30,’A’,’B’,’C’) and the resultant tuple should be result=(10,20,30)
"""

import Logo

t = (10, 20, 30, 'A', 'B', 'C')
n = len(t)
result = list([])

for i in t:
    if type(i) == int or type(i) == float:
        result.append(i)

result = tuple(result)
Logo.name()
print(
    f'Extracting Digits from t={t} ...\nExtracted Digits: result={result} ')
