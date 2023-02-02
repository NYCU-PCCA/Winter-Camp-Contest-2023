import csv, json, requests, string, secrets

def randstr(size = 12):
    alphabet = string.ascii_letters + string.digits
    return ''.join(secrets.choice(alphabet) for _ in range(size))

fn = lambda s: f'staff/{s}'

with open(fn('raw.csv')) as f:
    users = list(csv.DictReader(f))
    users.sort(key=lambda u: u['username'].lower())

teamid_begin = 3
# TODO: team should use different groupid
groupid = 6 # jury = =
role_type = {
    '出驗題': 'admin',
    '測題': 'team',
    '其他': 'jury',
}

teams = []
accounts = []
infos = []

for idx, user in enumerate(users):
    email = user['email']
    name = user['name']
    teamname = user['username']
    username = f"pcca-{ user['username'] }"
    teamid = teamid_begin + idx
    type = role_type[ user['role'] ]
    password = randstr()
    teams.append({
        'id': username,
        'icpc_id': username,
        'group_ids': [groupid],
        'name': teamname,
    })
    accounts.append({
        'id': username,
        'username': username,
        'password': password,
        'type': type,
        'name': teamname,
        'team_id': teamid,
    })
    infos.append({
        'email': email,
        'name': name,
        'teamname': teamname,
        'username': username,
        'password': password,
    })

with open(fn('teams.json'), 'w') as f:
    json.dump(teams, f)
with open(fn('accounts.json'), 'w') as f:
    json.dump(accounts, f)
with open(fn('infos.json'), 'w') as f:
    json.dump(infos, f)
