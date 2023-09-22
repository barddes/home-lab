ln -sf /usr/share/zoneinfo/America/Sao_Paulo /etc/localtime
hwclock --systohc

sed -i -E 's/#(en_US.UTF-8 UTF-8)/\1/' /etc/locale.gen
sed -i -E 's/#(pt_BR.UTF-8 UTF-8)/\1/' /etc/locale.gen
locale-gen

echo "LANG=en_US.UTF-8" > /etc/locale.conf
echo "jedric" > /etc/hostname

pacman -Sy --noconfirm --needed grub efibootmgr os-prober ranger vim \
	git curl wget iw iwd wireless_tools man-db man-pages texinfo \
	dhcpcd amd-ucode lvm2 vi sudo bluez bluez-utils blueman \
	pulseaudio-bluetooth pulseaudio-alsa pavucontrol 

sed -i 's/^\(HOOKS=.*\)block filesystems/\1block lvm2 filesystems/' /etc/mkinitcpio.conf
mkinitcpio -P

echo 'root:root' | chpasswd

grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=grub
grub-mkconfig -o /boot/grub/grub.cfg

systemctl enable iwd
systemctl enable dhcpcd

groupadd sudo
groupadd libvirt
useradd -m cesar
usermod -a -G sudo cesar
usermod -a -G libvirt cesar
echo 'cesar:cesar' | chpasswd

