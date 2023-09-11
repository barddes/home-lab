#!/bin/bash -e

EXIT=0

function missing() {
	echo >&2 Parameter $1 is missing
	EXIT=1
}

while [ $# -gt 0 ]; do
	[ ! -z "${!1}" ] || missing $1
	shift
done

exit $EXIT
