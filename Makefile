.PHONY: set-permissions
set-permissions:
	chmod +x scripts/*/*.sh

.PHONY: network
network:
	iwctl station wlan0 connect FUNDAO

.PHONY: partition-disk
partition-disk:
	parted -s /dev/nvme0n1 mklabel gpt
	parted -s /dev/nvme0n1 mkpart lvm ext4 0% 100%
	parted -s /dev/nvme0n1 set 1 lvm on

.PHONY: lvm-setup
lvm-setup: partition-disk
	pvcreate -ff -y /dev/nvme0n1p1
	vgcreate jedric /dev/nvme0n1p1
	lvcreate -L 8G jedric -n host

