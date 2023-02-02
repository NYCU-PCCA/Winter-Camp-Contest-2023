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

filename = argv[1]
template = argv[2]
REAL_RUN = len(argv) >= 4 and argv[3] == 'Y'

server = getvar('SERVER')

sender = getvar('SENDER')
if REAL_RUN:
    smtpserver = getvar('SMTPSERVER')
    smtpport = getvar('SMTPPORT', '465')
    username = getvar('USER')
    password = getvar('PASS', getpass)

with open(filename) as f:
    users = json.load(f)
with open(template) as f:
    subject = f.readline()
    template = Template(f.read())

if REAL_RUN:
    conn = SMTP(smtpserver, int(smtpport), 'PCCA')
    conn.set_debuglevel(True)
    conn.login(username, password)

for user in users:
    content = template.render(**user, server=server)
    msg = MIMEText(content, 'plain')
    msg['Subject'] = subject
    msg['From'] = sender
    msg['To'] = user['email']
    msg['CC'] = sender
    print(msg)
    print(content)
    if REAL_RUN:
        conn.sendmail(sender, [user['email'], sender], msg.as_string())
