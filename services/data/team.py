import csv, json, requests, string, secrets

def randstr(size = 12):
    alphabet = string.ascii_letters + string.digits
    return ''.join(secrets.choice(alphabet) for _ in range(size))

fn = lambda s: f'team/{s}'

with open(fn('raw.csv')) as f:
    raw = list(csv.DictReader(f))

teamid_begin = 22
groupid = 3

teams = []
accounts = []
infos = []

for idx, user in enumerate(raw):
    email = user['email']
    name = user['teamname']
    username = f"team{idx + 101}"
    teamid = teamid_begin + idx
    type = 'team'
    password = randstr()
    teams.append({
        'id': username,
        'icpc_id': username,
        'group_ids': [groupid],
        'name': name,
    })
    accounts.append({
        'id': username,
        'username': username,
        'password': password,
        'type': type,
        'name': name,
        'team_id': teamid,
    })
    infos.append({
        'email': email,
        'name': name,
        'username': username,
        'password': password,
    })

with open(fn('teams.json'), 'w') as f:
    json.dump(teams, f)
with open(fn('accounts.json'), 'w') as f:
    json.dump(accounts, f)
with open(fn('infos.json'), 'w') as f:
    json.dump(infos, f)
