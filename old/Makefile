.PHONY: install install-dependencies setup arch-all
install: install-dependencies setup arch-all

install-dependencies:
	pacman-key --init
	pacman -Sy --needed --noconfirm git ranger make

setup:
	parted -s /dev/nvme0n1 mklabel gpt
	parted -s /dev/nvme0n1 mkpart boot fat32 0% 1G
	parted -s /dev/nvme0n1 mkpart lvm ext4 1G 100%
	mkfs.fat -F32 /dev/nvme0n1p1
	mkfs.ext4 -F /dev/nvme0n1p2
	parted -s /dev/nvme0n1 set 1 boot on
	parted -s /dev/nvme0n1 set 2 lvm on
	pvcreate -ff -y /dev/nvme0n1p2
	vgcreate jedric /dev/nvme0n1p2
	lvcreate -L 8G jedric -n core -y
	mkfs.ext4 -F /dev/jedric/core

.PHONY: arch-all arch-mount-partitions arch-install-system arch-i3 arch-clean-install
arch-all: arch-mount-partitions arch-install-system arch-i3 arch-clean-install

arch-mount-partitions:
	mount /dev/jedric/core /mnt
	mount --mkdir /dev/nvme0n1p1 /mnt/boot

arch-install-system:
	pacstrap -K /mnt base linux  linux-firmware
	genfstab -U /mnt >> /mnt/etc/fstab
	arch-chroot /mnt < scripts/arch-bootstrap.sh

arch-i3:
	arch-chroot /mnt < scripts/arch-i3.sh

arch-clean:
	umount -R /mnt
	reboot


