CONFIG_MK_PATH := $(if $(M),$(M),$(CURDIR))/../config.mk
include $(CONFIG_MK_PATH)


obj-m := hello.o

KDIR := $(KDIR_ROOT)

all:
	$(MAKE) -C $(KDIR) M=$(CURDIR) modules ARCH=um

clean:
	$(MAKE) -C $(KDIR) M=$(CURDIR) clean ARCH=um
