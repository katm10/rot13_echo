cmd_/home/kmohr/rot13_echo/instrumentation/kernel_asm_helper.o := gcc -Wp,-MMD,/home/kmohr/rot13_echo/instrumentation/.kernel_asm_helper.o.d -nostdinc -isystem /usr/lib/gcc/x86_64-linux-gnu/11/include -I./arch/x86/include -I./arch/x86/include/generated  -I./include -I./arch/x86/include/uapi -I./arch/x86/include/generated/uapi -I./include/uapi -I./include/generated/uapi -include ./include/linux/compiler-version.h -include ./include/linux/kconfig.h -I./ubuntu/include -D__KERNEL__ -fmacro-prefix-map=./= -D__ASSEMBLY__ -fno-PIE -m64 -DCONFIG_X86_X32_ABI -Wa,-gdwarf-2 -gdwarf-5 -DCC_USING_FENTRY  -DMODULE  -c -o /home/kmohr/rot13_echo/instrumentation/kernel_asm_helper.o /home/kmohr/rot13_echo/instrumentation/kernel_asm_helper.S

source_/home/kmohr/rot13_echo/instrumentation/kernel_asm_helper.o := /home/kmohr/rot13_echo/instrumentation/kernel_asm_helper.S

deps_/home/kmohr/rot13_echo/instrumentation/kernel_asm_helper.o := \
  include/linux/compiler-version.h \
    $(wildcard include/config/CC_VERSION_TEXT) \
  include/linux/kconfig.h \
    $(wildcard include/config/CPU_BIG_ENDIAN) \
    $(wildcard include/config/BOOGER) \
    $(wildcard include/config/FOO) \

/home/kmohr/rot13_echo/instrumentation/kernel_asm_helper.o: $(deps_/home/kmohr/rot13_echo/instrumentation/kernel_asm_helper.o)

$(deps_/home/kmohr/rot13_echo/instrumentation/kernel_asm_helper.o):
