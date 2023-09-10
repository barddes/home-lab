#!/bin/bash

echo pvcreate -ff -y /dev/nvme0n1p2
echo vgcreate jedric /dev/nvme0n1p2
echo lvcreate -L 20G jedric -n server -y

return 0

