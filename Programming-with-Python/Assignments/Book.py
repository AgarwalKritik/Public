"""
Suppose the cover price of a book is $24.95, but bookstores get a 40% discount. 
Shipping costs $3 for the first copy and 75 cents for each additional copy. 
What is the total wholesale cost for 60 copies?

"""

import Logo  # For My Name Watermark

CoverBookCP = 24.95
Quantity = 60
ShippingFirstCopy = 3
ShippingAdditionalCopy = 0.75
Discount = CoverBookCP - (CoverBookCP*(40/100))
TotalWholesaleCP = (Discount*Quantity) + ShippingFirstCopy + \
    ((Quantity-1)*ShippingAdditionalCopy)
Logo.name()  # For My Name Watermark
print(f'The total wholesale cost for {Quantity} copies: ${TotalWholesaleCP}')
