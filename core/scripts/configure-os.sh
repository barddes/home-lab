#!/bin/bash

set -e

read -p 'Main user: ' username
[ -z $username ] && echo >&2 "Username is required" && exit 1

useradd -m $username
usermod -a -G libvirt,sudo,kvm,wheel

echo "Password for user $username"
passwd $username

# Add grub flags
grub_flags="iommu=pt initcall_blacklist=sysfb_init pcie_acs_override=downstream,multifunction"
sed -i -E 's/^GRUB_CMDLINE_LINUX_DEFAULT="(.+)"/GRUB_CMDLINE_LINUX_DEFAULT="\1 '"$grub_flags"' /' /etc/default/grub \
    || echo >&2 "Error while trying to update grub config" && exit 1

# Blacklist gpu drivers
cat <<EOF >> /etc/modprobe.d/blacklist.conf
blacklist nouveau
blacklist nvidia*
EOF

# Early load vfio drivers
echo "MODULES+=(vfio_pci vfio vfio_iommu_type1)" >> /etc/mkinitcpio.conf
cat <<EOF >> /etc/modprobe.d/vfio.conf
# options vfio-pci ids=1002:1638,1002:1637,10de:2504,10de:228e disable_vga=1
options vfio-pci ids=10de:2504,10de:228e
softdep nouveau pre: vfio-pci
softdep nvidia pre: vfio-pci
# softdep amdgpu pre: vfio-pci
# softdep radeon pre: vfio-pci
# softdep snd_hda_intel pre: vfio-pci
# softdep vfio-pci pre: vendor-reset
EOF

mkinitcpio -P
grub-mkconfig -o /boot/grub/grub.cfg
