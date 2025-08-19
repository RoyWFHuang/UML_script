#!/bin/bash

. config

sudo apt install build-essential libncurses-dev flex bison
sudo apt install xz-utils wget ca-certificates bc
sudo apt install fakeroot

export REPO=http://dl-cdn.alpinelinux.org/alpine/v3.13/main
mkdir -p rootfs
curl $REPO/x86_64/APKINDEX.tar.gz | tar -xz -C /tmp/
export APK_TOOL=`grep -A1 apk-tools-static /tmp/APKINDEX | cut -c3- | xargs printf "%s-%s.apk"`
curl $REPO/x86_64/$APK_TOOL | fakeroot tar -xz -C rootfs
fakeroot rootfs/sbin/apk.static \
    --repository $REPO --update-cache \
    --allow-untrusted \
    --root $PWD/rootfs --initdb add alpine-base
echo $REPO > rootfs/etc/apk/repositories
echo "LABEL=ALPINE_ROOT / auto defaults 1 1" >> rootfs/etc/fstab

cp init rootfs/
wget -O rootfs/sbin/tini https://github.com/krallin/tini/releases/download/v0.19.0/tini-static
chmod +x rootfs/sbin/tini
cp $UML_KERNEL_SRC_PATH/$UML_KERNEL_NAME ./

./$UML_KERNEL_NAME umid=uml0 \
    rootfstype=hostfs rootflags=$(pwd)/rootfs \
    rw mem=64M init=/bin/busybox \
    --install -s && exit
stty sane; echo

