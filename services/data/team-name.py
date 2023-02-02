import csv, json, requests, string, secrets

fn = lambda s: f'team/{s}'

with open(fn('name.csv')) as f:
    users = list(csv.DictReader(f))

mxid = max(int(user['teamid']) for user in users)
teams = [{} for _ in range(mxid+1)]
for user in users:
    team = teams[int(user['teamid'])]
    for k in user:
        if k == 'teamid':
            continue
        if k not in team:
            team[k] = []
        team[k].append(user[k])

print(teams[0])

with open(fn('name.json'), 'w') as f:
    json.dump(teams, f)
