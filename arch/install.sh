#!/bin/bash

function usage() {
	echo >&2 Usage: $0 EFI_PARTITION ROOT_PARTITION
	echo >&2 
	echo >&2 EFI_PARTITION and ROOT_PARTITION must be in /dev/xxxx format
}

EFI_PARTITION="$1"
ROOT_PARTITION="$2"
[[ $# -ne 2  || ! $EFI_PARTITION =~ ^/dev/.+$ || ! $ROOT_PARTITION =~ ^/dev/.+$ ]] && usage "$@" && exit 1

# Mount dirs
mount $ROOT_PARTITION /mnt
mount --mkdir $EFI_PARTITION /mnt/boot

# Install system
pacstrap -K /mnt base linux  linux-firmware
genfstab -U /mnt >> /mnt/etc/fstab

# Bootstrap system
arch-chroot /mnt < scripts/bootstrap.sh

# Install libvirt
arch-chroot /mnt < scripts/libvirt.sh

# Install i3wm
arch-chroot /mnt < scripts/i3wm.sh

# Clean install
umount -R /mnt
reboot

