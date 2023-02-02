#!/bin/bash
source info
python sendmail-user.py staff/infos.json template.staff $@
