sudo chown $USER:$USER lofsdisk

cd lofsdisk
echo "Fedor" > file1
echo "Ivanov" > file2

# copy executables
cp --parents /usr/bin/{bash,cat,echo,ls} ./
# copy dependencies
cp --parents /lib/x86_64-linux-gnu/{libtinfo.so.6,libdl.so.2,libc.so.6,libselinux.so.1,libpcre2-8.so.0,libpthread.so.0} ./
cp --parents /lib64/ld-linux-x86-64.so.2 ./
cd ..

gcc ex02.c -o ./lofsdisk/ex02.out -static -g -Wall -fsanitize=undefined -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow
sudo chroot ./lofsdisk ./ex02.out > ex02.txt
./lofsdisk/ex02.out >> ex02.txt

