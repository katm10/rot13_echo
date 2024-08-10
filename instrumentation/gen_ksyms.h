sudo cat /proc/kallsyms > syms.txt


fsym() {
        echo \#define $2 \(0x$(cat syms.txt | grep " $1$" | cut -d" " -f1)ULL\)
}



echo \#ifndef KSYMS_H
echo \#define KSYMS_H

fsym __sys_sendto SYS_SENDTO_ADDR
fsym __sys_recvfrom SYS_RECVFROM_ADDR

echo \#endif