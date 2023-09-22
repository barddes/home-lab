#!/bin/bash

pacman -Sy --noconfirm xorg xf86-video-amdgpu xorg-xinit \
	i3-wm lightdm dmenu lightdm-gtk-greeter alacritty \
	firefox i3status

echo "exec i3" > /root/.xinit
echo "exec i3" | tee /home/cesar/.xinit || true
systemctl enable lightdm
