TARGET=rot13_module
obj-m += $(TARGET).o
$(TARGET)-objs := sample_kernel_driver.o \
fast_table.o \
globals.o \
kernel_helper.o \
lakeplacid_kernel.o \
wrappers.o \
kernel_asm_helper.o \
specialized/ASSEMBLE/server.o 

all: install

build: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

install: build
	- sudo rmmod rot13_module.ko
	sudo insmod rot13_module.ko
	sudo chmod 666 /dev/rot13_driver

uninstall:
	sudo rmmod $(TARGET).ko

user: 
	cc -o  /home/kmohr/rot13_echo/instrumentation/fallback_exe /home/kmohr/rot13_echo/instrumentation/sample_user_driver.c \
  /home/kmohr/rot13_echo/instrumentation/fallback/ASSEMBLE/server.o \
  /home/kmohr/rot13_echo/instrumentation/slow_table.c \
  /home/kmohr/rot13_echo/instrumentation/globals_user.c \
  /home/kmohr/rot13_echo/instrumentation/globals.c \
  /home/kmohr/rot13_echo/instrumentation/lakeplacid_user.c \
  /home/kmohr/rot13_echo/instrumentation/user_asm_helper.S \
  /home/kmohr/rot13_echo/instrumentation/user_helper.c