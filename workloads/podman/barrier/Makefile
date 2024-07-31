all: build run

build:
	podman build -t barrier .

run:
	podman run -d --name barrier --hostname X11 --network main --replace -e DISPLAY=:0 --volume /tmp/.X11-unix:/tmp/.X11-unix --userns=auto:gidmapping=985:985:1,gidmapping=989:989:1,gidmapping=994:994:1,gidmapping=996:996:1 barrier