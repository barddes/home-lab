.PHONY: set-permissions network partition-disk
set-permissions:
	chmod +x scripts/*/*.sh

network:
	iwctl station wlan0 connect FUNDAO

partition-disk:
	echo To be implemented...
	./scripts/disk/lvm-on-nvme.sh /dev/nvme0n1
