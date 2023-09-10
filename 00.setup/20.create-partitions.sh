#!/bin/bash

echo parted -s $DISK mklabel gpt
echo parted -s $DISK mkpart boot fat32 0% 1G
echo parted -s $DISK mkpart lvm ext4 1G 100%
echo parted -s $DISK set 1 boot on
echo parted -s $DISK set 2 lvm on

export SERVER_PARTITION=${DISK}p2 
return 0

