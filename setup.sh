#!/bin/bash

. config
sudo apt install curl
sudo apt install build-essential libncurses-dev flex bison
sudo apt install xz-utils wget ca-certificates bc
sudo apt install fakeroot

export REPO=http://dl-cdn.alpinelinux.org/alpine/v3.13/main
mkdir -p $UML_INSTALL_DIR/rootfs
curl $REPO/x86_64/APKINDEX.tar.gz | tar -xz -C /tmp/
export APK_TOOL=`grep -A1 apk-tools-static /tmp/APKINDEX | cut -c3- | xargs printf "%s-%s.apk"`
curl $REPO/x86_64/$APK_TOOL | fakeroot tar -xz -C $UML_INSTALL_DIR/rootfs
fakeroot $UML_INSTALL_DIR/rootfs/sbin/apk.static \
    --repository $REPO --update-cache \
    --allow-untrusted \
    --root $PWD/$UML_INSTALL_DIR/rootfs --initdb add alpine-base
echo $REPO > $UML_INSTALL_DIR/rootfs/etc/apk/repositories
echo "LABEL=ALPINE_ROOT / auto defaults 1 1" >> $UML_INSTALL_DIR/rootfs/etc/fstab

cp init $UML_INSTALL_DIR/rootfs/
wget -O $UML_INSTALL_DIR/rootfs/sbin/tini https://github.com/krallin/tini/releases/download/v0.19.0/tini-static
sudo chmod +x $UML_INSTALL_DIR/rootfs/sbin/tini
cp $UML_KERNEL_SRC_PATH/$UML_KERNEL_NAME ./$UML_INSTALL_DIR/

./$UML_INSTALL_DIR/$UML_KERNEL_NAME umid=uml0 \
    rootfstype=hostfs rootflags=$(pwd)/$UML_INSTALL_DIR/rootfs \
    rw mem=128M init=/bin/busybox \
    --install -s && exit
stty sane; echo

