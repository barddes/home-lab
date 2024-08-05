#!/bin/bash

set -e

mkdir -p /etc/rancher/k3s
internal_ip=$(ip addr | grep 192.168 | head -n 1 | sed -E 's|.+(192\.168\..+)/.+|\1|')
cat <<EOF >/etc/rancher/k3s/config.yaml
write-kubeconfig-mode: "0644"
tls-san:
  - "$internal_ip"
EOF
