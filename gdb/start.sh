#!/bin/bash
. config
. ../config

GDB_ENV=$(pwd)

echo "current = $GDB_ENV"
cp gdbinit.config gdbinit
cd $UML_ROOT_PATH

# set rootfs
sed -i 's|FULLPATH|'"$PWD"'|' $GDB_ENV/gdbinit
cd $UML_KERNEL_SRC_PATH/
gdb -q -x $GDB_ENV/gdbinit
