.PHONY: install-dependencies
install-dependencies:
	pacman-key --init
	pacman -Sy --noconfirm git ranger make

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
	lvcreate -L 1G jedric -n boot -y
	lvcreate -L 8G jedric -n core -y

.PHONY: format-partitions
format-partitions:
	mkfs.ext4 /dev/jedric/core
	mkfs.fat -F32 /dev/jedric/boot

