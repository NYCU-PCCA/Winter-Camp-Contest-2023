#!/bin/bash
source info
python sendmail-team.py team/name.json template.team-name $@
