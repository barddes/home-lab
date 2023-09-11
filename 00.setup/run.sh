#!/bin/bash -e

source 00.config.sh

$0/../utils/ensure-parameters.sh DISK

for step in $(find . -regex ".*/[0-9]+\..*\.sh" -not -name '*.config.sh' | sort); do
	echo "==> Running $step..."
	source $step
done
