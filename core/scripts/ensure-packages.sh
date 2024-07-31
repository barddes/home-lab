#!/bin/bash
packages=(
    # Base system
    base
    linux
    linux-firmware
    linux-headers

    # boot and network
    amd-ucode
    grub
    efibootmgr
    networkmanager
    
    # GPU driver and Xorg server
    xf86-video-amdgpu mesa amdvlk
    xorg-server

    # libvirt
    iptables-nft
    libvirt
    libvirt-storage-iscsi-direct
    dmidecode
    dnsmasq
    openbsd-netcat
    swtpm
    virt-install
    podman podman-compose

    # QEMU packages (i'm not worried about those now)
    qemu-audio-alsa qemu-audio-dbus qemu-audio-jack qemu-audio-oss qemu-audio-pa qemu-audio-pipewire 
    qemu-audio-sdl qemu-audio-spice qemu-base qemu-block-curl qemu-block-iscsi qemu-block-nfs qemu-block-ssh 
    qemu-chardev-baum qemu-chardev-spice qemu-docs qemu-hw-display-qxl qemu-hw-display-virtio-gpu
    qemu-hw-display-virtio-gpu-gl qemu-hw-display-virtio-gpu-pci qemu-hw-display-virtio-gpu-pci-gl
    qemu-hw-display-virtio-vga qemu-hw-display-virtio-vga-gl qemu-hw-s390x-virtio-gpu-ccw qemu-hw-usb-host
    qemu-hw-usb-redirect qemu-hw-usb-smartcard qemu-pr-helper qemu-tests qemu-tools qemu-ui-curses
    qemu-ui-dbus qemu-ui-egl-headless qemu-ui-gtk qemu-ui-opengl qemu-ui-sdl qemu-ui-spice-app
    qemu-ui-spice-core qemu-user qemu-user-static qemu-vhost-user-gpu

    # Management and utilities
    openssh ranger sudo texinfo unzip vi vim wget zip xorg-xclock make man-db man-pages barrier git jq yq
    firewalld cockpit cockpit-machines cockpit-packagekit cockpit-pcp cockpit-podman cockpit-storaged
)

pacman -Syy --needed ${packages[@]}