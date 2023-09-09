#!/bin/bash

pacman -S --noconfirm --needed libvirt qemu-base iptables-nft 
systemctl enable libvirtd
