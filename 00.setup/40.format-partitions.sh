#!/bin/bash

echo mkfs.fat -F32 /dev/nvme0n1p1
echo mkfs.ext4 -F /dev/jedric/server

return 0

