from smtplib import SMTP_SSL as SMTP
from os import getenv
from sys import argv
from email.mime.text import MIMEText
from jinja2 import Template
from getpass import getpass
import json

print(argv)
assert len(argv) >= 3

def getvar(name, func = input):
    val = getenv(name)
    if not val:
        if type(func) == str:
            val = func
        else:
            val = func(f'{name} > ').strip()
    return val

teamjson = argv[1]
template = argv[2]
REAL_RUN = len(argv) >= 4 and argv[3] == 'Y'
TEST_RUN = len(argv) >= 4 and argv[3] == 'T'
RUN = REAL_RUN or TEST_RUN

sender = getvar('SENDER')
CC = getvar('CC').split(',') + [ sender ]
if RUN:
    smtpserver = getvar('SMTPSERVER')
    smtpport = getvar('SMTPPORT', '465')
    username = getvar('USER')
    password = getvar('PASS', getpass)

with open(teamjson) as f:
    teams = json.load(f)
with open(template) as f:
    subject = f.readline()
    template = Template(f.read())

if TEST_RUN:
    subject = '[TEST] ' + subject
if RUN:
    conn = SMTP(smtpserver, int(smtpport), 'PCCA')
    conn.set_debuglevel(True)
    conn.login(username, password)

for team in teams:
    if type(team['email']) != list:
        team['email'] = [ team['email'] ]
    content = template.render(**team)
    msg = MIMEText(content, 'plain')
    msg['Subject'] = subject
    msg['From'] = sender
    msg['To'] = ', '.join(team['email'])
    msg['CC'] = ', '.join(CC)
    to = team['email'] + CC
    if TEST_RUN:
        to = [sender]
    print(to)
    print(msg)
    print(content)
    if RUN:
        conn.sendmail(sender, to, msg.as_string())
    if TEST_RUN:
        break
