# UML
## Prepare env:
1. build UML linux kernel
```
$ make mrproper
# use default config
$ make defconfig ARCH=um SUBARCH=x86_64
or
# Add config setting
$ make menuconfig ARCH=um SUBARCH=x86_64 
$ make linux ARCH=um SUBARCH=x86_64 -j `nproc`
```
then you will get a linux elf file

2. Move this "==linux==" file into target UML directory

3. execute setup.sh
This will create the rootfs and setup the busybox
## start the UML
execute UML_start.sh



