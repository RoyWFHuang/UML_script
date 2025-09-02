obj-m += Kasan.o

PWD := $(shell pwd)
KDIR := $(PWD)/../../linux/
# i/home/roy/src_code/00.project/linux/app/.. M=/home/roy/src_code/00.project/linux/app

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules ARCH=um

all: default
	gcc Asan.c -fsanitize=address -fsanitize-recover=address -o Asan_test
	gcc Asan.c -fsanitize=address -fsanitize-recover=address -g -o Asan_test_debug
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean ARCH=um

asan:
	LSAN_OPTIONS=verbosity=1 ASAN_OPTIONS=detect_leaks=1:halt_on_error=0:detect_stack_use_after_return=1 ./Asan_test