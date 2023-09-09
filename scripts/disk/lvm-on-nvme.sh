#!/bin/sh

DISK=${1}

parted -s $DISK mklabel gpt
parted -s $DISK mkpart lvm ext4 0% 100%
parted -s $DISK set 1 lvm on

