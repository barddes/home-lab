ln -sf /usr/share/zoneinfo/America/Sao_Paulo /etc/localtime
hwclock --systohc
sed -i -E 's/#(en_US.UTF-8 UTF-8)/\1/' /etc/locale.gen
sed -i -E 's/#(pt_BR.UTF-8 UTF-8)/\1/' /etc/locale.gen
locale-gen
echo "LANG=en_US.UTF-8" > /etc/locale.conf
echo "jedric" > /etc/hostname
mkinitcpio -P
echo 'root:root' | chpasswd
pacman -Sy --noconfirm grub efibootmgr os-prober ranger vim git curl wget iw iwd wireless_tools man-db man-pages texinfo dhcpcd amd-ucode
grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=grub
grub-mkconfigo -o /boot/grub/grub.cfg