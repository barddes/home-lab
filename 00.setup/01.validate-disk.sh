#!/bin/bash

[[ ! $DISK =~ ^/dev/nvme.*$ ]] && (
	echo >&2 DISK=$DISK not valid, must be nvme
	exit -1
)

return 0
