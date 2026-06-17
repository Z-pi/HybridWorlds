import sqlite3

con = sqlite3.connect("Data.db")
cursor = con.cursor()

def assign_city(list_of_numbers):
    for number in list_of_numbers:
        city = cursor.execute("""
            SELECT id, safety_classification, health_care_classification, cost_of_living_classification, pollution_classification
            FROM quality_of_life
            WHERE id = ?
                AND year = 2026;
            """, (number,)).fetchone()
        city_stats = {"id": city[0], "safety": city[1], "health": city[2], "cost": city[3], "pollution": city[4],}
        return city_stats