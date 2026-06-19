from receiveCity import *
from publishData import start, publishStat, stop

test_city = 7 

city_stats = assign_city([test_city])

start()
try:
    publishStat(city_stats)
finally:
    stop()
