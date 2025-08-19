#!/bin/bash

. config

./$UML_KERNEL_NAME umid=uml0 hostname=uml1 eth0=tuntap,tap0\
	rootfstype=hostfs rootflags=$(pwd)/rootfs \
	rw init=/init mem=64M console=tty0
#./linux umid=uml0 hostname=uml1 eth0=tuntap,tap0\
#	rootfstype=hostfs rootflags=$(pwd)/rootfs \
#	rw init=/bin/sh mem=64M
stty sane; echo
