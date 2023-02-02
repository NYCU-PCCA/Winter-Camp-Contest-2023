#!/bin/bash
rv () {
    echo -n "$1 : " >&2
    read -r x
    echo "$x"
}
url=$(rv url)
pass=$(rv pass)
set -x
# python staff.py
curl -k -u "admin:$pass" "$url/api/users/accounts" -F 'tsv=@empty.tsv'
curl -k -u "admin:$pass" "$url/api/users/teams" -F 'json=@staff/teams.json'
curl -k -u "admin:$pass" "$url/api/users/accounts" -F 'json=@staff/accounts.json'
