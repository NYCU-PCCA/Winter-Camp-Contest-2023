#!/bin/bash
source info
python sendmail-team.py team/infos.json template.team-info $@
