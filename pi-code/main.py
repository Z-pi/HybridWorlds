from createPlayers import *
from publishData import start, publishStat, stop

# Create the players with their statistics
players = createPlayers()
orangeCity = assign_city(players[0])
purpleCity = assign_city(players[1])
print(orangeCity)
print(purpleCity)

# Publish statistic per topic
start()
try:
    publishStat(orangeCity)
    publishStat(purpleCity)
finally:
    stop()