import json

number = 144
possible = []

for i in range(1, number):
    if number % i == 0:
        possible.append({
            "pixel/section" : i,
            "sections" : number // i
        })
print(json.dumps(possible, indent=3), len(possible))