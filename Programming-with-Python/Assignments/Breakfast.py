"""
If I leave my house at 6:52 am and run 1 mile at an easy pace (8:15 per mile), 
then 3 miles at tempo (7:12 per mile) and 1 mile at an easy pace again, 
what time do I get home for breakfast?

"""

import Logo

start_time = (6*60 + 52)*60
easy_time = (8*60 + 15)*2
tempo_time = (7*60 + 12)*3

breakfast_hour = (start_time + easy_time + tempo_time)/(60*60)
bh = int(breakfast_hour)
breakfast_minute = int((breakfast_hour - bh)*60)
Logo.name()
print(f'''If You leave my house at 6:52 am and Run 1 mile at an easy pace (8:15 per mile),then 3 miles at tempo (7:12 per mile) and 1 mile at an easy pace again, 
Then,
You will get home for breakfast at {bh}:{breakfast_minute} am''')
