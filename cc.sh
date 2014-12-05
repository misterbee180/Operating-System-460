echo compiling ....
bcc -c sh2.c
bcc -c -ansi syscall.c
bcc -c crt0.c
as86 -o us.o  us.s

echo linking .......
ld86 -o sh2 us.o syscall.o sh2.o crt0.o mtxlib /usr/lib/bcc/libc.a

sudo mount -o loop mtximage b
sudo cp ./sh2 b/bin/sh
sudo umount b
rm us.o syscall.o crt0.o sh2.o sh2
