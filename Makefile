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
lvm-setup:
	pvcreate -ff -y /dev/nvme0n1p1
	vgcreate jedric /dev/nvme0n1p1
	lvcreate -L 1G jedric -n boot -y
	lvcreate -L 8G jedric -n core -y

.PHONY: format-partitions
format-partitions:
	mkfs.ext4 /dev/jedric/core
	mkfs.fat -F32 /dev/jedric/boot

.PHONY: .arch-mount-partitions
.arch-mount-partitions:
	mount /dev/jedric/core /mnt
	mount --mkdir /dev/jedric/boot /mnt/boot

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
