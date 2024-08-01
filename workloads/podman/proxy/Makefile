name := nginx

all: build run

build:
	podman build -t $(name) .

run:
	podman run -d --name $(name) --hostname $(name) --network main --replace $(name)
