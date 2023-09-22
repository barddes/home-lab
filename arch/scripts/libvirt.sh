#!/bin/bash

pacman -Rnsdd iptables --noconfirm
pacman -S --noconfirm --needed libvirt qemu-base iptables-nft virt-manager dnsmasq dmidecode bridge-utils

echo 'unix_sock_group = "libvirt"' >>  /etc/libvirt/libvirtd.conf
echo 'unix_sock_ro_perms = "0770"' >>  /etc/libvirt/libvirtd.conf
systemctl enable libvirtd

sed -i '/amd_iommu=/! s/^\(GRUB_CMDLINE_LINUX_DEFAULT=".*\)"/\1 amd_iommu=on"/' /etc/default/grub

cat <<EOF > /etc/modprobe.d/kvm.conf
options kvm ignore_msrs=1
EOF

cat <<EOF > /etc/modprobe.d/vfio.conf
options vfio_iommu_type1 allow_unsafe_interrupts=1
options vfio-pci ids=10de:2504,10de:228e
EOF

cat <<EOF > /etc/modprobe.d/blacklist.conf
blacklist nvidia*
blacklist nouveau
EOF

cat <<'EOF' >> /etc/mkinitcpio.conf
MODULES=(vfio vfio_iommu_type1 vfio_pci ${MODULES[@]})
EOF

mkinitcpio -P
grub-mkconfig -o /boot/grub/grub.cfg
