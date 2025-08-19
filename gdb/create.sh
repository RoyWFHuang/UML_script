#!/bin/bash
. config
. ../config

cd $UML_ROOT_PATH/$UML_KERNEL_SRC_PATH
echo "CONFIG_GDB_SCRIPTS=y" > .config-fragment
ARCH=um scripts/kconfig/merge_config.sh .config .config-fragment
make ARCH=um scripts_gdb

echo "test gdb"

gdb -ex "add-auto-load-safe-path scripts/gdb/vmlinux-gdb.py" \
      -ex "file vmlinux" \
      -ex "lx-version" -q
