#!/bin/bash

pacman -Sy --noconfirm xorg xf86-video-amdgpu xorg-xinit i3-wm lightdm dmenu lightdm-gtk-greeter alacritty firefox i3status virt-manager

echo "exec i3" > $HOME/.xinit
systemctl enable lightdm
