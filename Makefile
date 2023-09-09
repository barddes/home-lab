.PHONY: all
all: arch-post-install

.PHONY: arch-post-install
arch-post-install:
	chmod +x scripts/*.sh
	./scripts/install-i3.sh

.PHONY: format-all
format-all: lvm-setup format-partitions .arch-all

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
	parted -s /dev/nvme0n1 mkpart boot fat32 0% 1G
	parted -s /dev/nvme0n1 mkpart lvm ext4 1G 100%
	mkfs.fat -F32 /dev/nvme0n1p1
	mkfs.ext4 -F /dev/nvme0n1p2
	parted -s /dev/nvme0n1 set 1 boot on
	parted -s /dev/nvme0n1 set 2 lvm on

.PHONY: lvm-setup
lvm-setup: partition-disk
	pvcreate -ff -y /dev/nvme0n1p2
	vgcreate jedric /dev/nvme0n1p2
	lvcreate -L 8G jedric -n core -y

.PHONY: format-partitions
format-partitions:
	mkfs.fat -F32 /dev/nvme0n1p1
	mkfs.ext4 -F /dev/jedric/core

.PHONY: .arch-all
.arch-all: .arch-mount-partitions .arch-install-system .arch-bootstrap .arch-clean

.PHONY: .arch-mount-partitions
.arch-mount-partitions:
	mount /dev/jedric/core /mnt
	mount --mkdir /dev/nvme0n1p1 /mnt/boot

.PHONY: .arch-install-system
.arch-install-system:
	pacstrap -K /mnt base linux  linux-firmware
	genfstab -U /mnt >> /mnt/etc/fstab

.PHONY: .arch-bootstrap
.arch-bootstrap:
	arch-chroot /mnt < scripts/arch-bootstrap.sh

.PHONY: .arch-clean
.arch-clean:
	umount -R /mnt
