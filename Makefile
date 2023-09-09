.PHONY: set-permissions
set-permissions:
	chmod +x scripts/*/*.sh

.PHONY: network
network:
	iwctl station wlan0 connect FUNDAO

.PHONY: partition-disk
partition-disk:
	echo To be implemented...
	./scripts/disk/lvm-on-nvme.sh /dev/nvme0n1
