FROM archlinux:base

# Update arch
RUN pacman -Sy

RUN pacman -S --noconfirm barrier xorg-fonts-100dpi
COPY config /etc/barrier/config

CMD /usr/bin/barriers -f --no-tray --debug DEBUG --name X11 --disable-crypto --disable-client-cert-checking -c /etc/barrier/config --address :24800
