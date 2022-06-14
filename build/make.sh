#!/bin/bash

qemu-img create -f qcow2 -F raw -o backing_file=/home/adam/so/so-june/image/minix.img minix.img

qemu-system-x86_64 -curses -drive file=minix.img -enable-kvm -rtc base=localtime -net user,hostfwd=tcp::10022-:22 -net nic,model=virtio -m 1024M -machine kernel_irqchip=off
