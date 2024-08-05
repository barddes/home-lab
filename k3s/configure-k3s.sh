#!/bin/bash

set -e

mkdir -p /etc/rancher/k3s
cat <<EOF >/etc/rancher/k3s/config.yaml
write-kubeconfig-mode: "0644"
tls-san:
  - "192.168.3.104"
EOF
