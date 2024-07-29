# Headless GPU Passthrough (libvirt, qemu, kvm)
- Asus Prime B450M Gaming BR
    - IOMMU enabled
    - SRVIO enabled
    - CSM disabled
    - gpu boot device = integrated
    - AMD 5600G APU
    - Nvidia GPU
      
- Headless OS
    - UEFI boot
    - Split IOMMU groups if needed with ACS
    - early-load vfio drivers
    - blacklist gpu drivers
      
- Libvirt/QEMU
    - q35
    - OVMF

### Nvidia Passtrough notes
It just works out of the box.

### AMD APU 5600G Passthrough notes
It will only work after AMD drivers are running, so configuring is best done using an emulated graphics card.

You can test if the passthrough was sucessfull checking VM's `dmesg` logs.

When ready, you must remove the emulated gpu.

### References

- https://wiki.archlinux.org/title/PCI_passthrough_via_OVMF
- https://github.com/isc30/ryzen-7000-series-proxmox
- https://www.reddit.com/r/homelab/comments/b5xpua/the_ultimate_beginners_guide_to_gpu_passthrough/
