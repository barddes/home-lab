#!/bin/bash

set -e

read -p 'Password for root: ' _ && echo $_ | passwd --stdin root
read -p 'Timezone: ' _ && ln -sf /usr/share/zoneinfo/$_ /etc/localtime || echo >&2 "Timezone not set"
read -p 'Hostname: ' _ && echo $_hostname > /etc/hostname
read -p 'Locale [en_US.UTF-8]:' _ && echo ${_:-en_US.UTF-8} >> /etc/locale.gen && locale-gen || echo >&2 "Locale not set"
read -p 'Keymap: ' _ && echo KEYMAP=$_ >> /etc/vconsole.conf || echo >&2 "Keymap not set"

read -p 'Main user: ' username
[ -z $username ] && echo >&2 "Username is required" && exit 1

useradd -m $username
usermod -a -G libvirt,sudo,kvm,wheel $username

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

# Update initram and grub
mkinitcpio -P
grub-mkconfig -o /boot/grub/grub.cfg

# systemctl enable \
#     NetworkManager \
#     libvirt \
#     cockpit \
#     sshd \
#     podman.socket \
#     pmcd pmlogger pmie