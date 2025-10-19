#!/bin/bash
. config
ROOTFS_PATH=$(pwd)/$UML_INSTALL_DIR/rootfs
cmd=$1

cd $UML_KERNEL_SRC_PATH
case $cmd in
    clean)
        make mrproper
        # make clean
        # make distclean
        ;;
    build)
        make menuconfig ARCH=um SUBARCH=x86_64
        make ARCH=um prepare
        make linux ARCH=um SUBARCH=x86_64 -j `nproc`
        ;;
    module_build)
        make ARCH=um SUBARCH=x86_64 modules
        ;;
    module_install)
        make modules_install INSTALL_MOD_PATH=$ROOTFS_PATH ARCH=um
        ;;
    downlaod)
        git clone git@github.com:torvalds/linux.git
        ;;
    *)
        echo "Usage: $0 {start|stop|restart}"
        exit 1
        ;;
esac
