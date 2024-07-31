FROM archlinux:base

# Update arch
RUN pacman -Sy

RUN pacman -S --noconfirm i3-wm dmenu vim ranger nemo firefox i3status xss-lock
RUN pacman -S --noconfirm networkmanager network-manager-applet
RUN pacman -S --noconfirm alacritty
# RUN mkdir -p /root/.config/i3
# RUN cp /etc/i3/config /root/.config/i3/config
CMD i3