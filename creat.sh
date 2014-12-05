
echo compiling ....
bcc -c init.c
bcc -c -ansi syscall.c
bcc -c crt0.c
as86 -o us.o  us.s

echo linking .......
ld86 -o init us.o syscall.o crt0.o init.o mtxlib /usr/lib/bcc/libc.a

rm init.o us.o syscall.o crt0.o

echo compiling ....
bcc -c login.c
bcc -c sh2.c
bcc -c grep.c
bcc -c -ansi  syscall.c
bcc -c crt0.c
bcc -c cat.c
bcc -c more.c
bcc -c cp.c
as86 -o us.o  us.s

echo linking .......
#ld86 -o login us.o syscall.o crt0.o login.o mtxlib /usr/lib/bcc/libc.a
ld86 -o ./sh us.o syscall.o crt0.o sh2.o mtxlib /usr/lib/bcc/libc.a
ld86 -o ./cat us.o syscall.o crt0.o cat.o mtxlib /usr/lib/bcc/libc.a
ld86 -o ./grep us.o syscall.o crt0.o grep.o mtxlib /usr/lib/bcc/libc.a
#ld86 -o ./more us.o syscall.o crt0.o more.o mtxlib /usr/lib/bcc/libc.a
#ld86 -o ./cp us.o syscall.o crt0.o cp.o mtxlib /usr/lib/bcc/libc.a

sudo mount -o loop mtximage b
#sudo cp login b/bin/login
#sudo cp init b/bin/init
sudo cp ./sh b/bin/sh
sudo cp ./cat b/bin/cat
sudo cp ./grep b/bin/grep
#sudo cp ./more b/bin/more
#sudo cp ./cp b/bin/cp
sudo umount b

rm cat.o sh2.o login.o us.o syscall.o crt0.o grep.o more.o cp.o
