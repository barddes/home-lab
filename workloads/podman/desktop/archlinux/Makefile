all: build run

build:
  podman build -t archlinux-desktop .

run:
  podman run -d --name archlinux-desktop --replace -e DISPLAY=:0 --volume /tmp/.X11-unix:/tmp/.X11-unix --userns=auto:gidmapping=985:985:1,gidmapping=989:989:1,gidmapping=994:994:1,gidmapping=996:996:1 archlinux-desktop