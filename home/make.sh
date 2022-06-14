#bin/bash!

cd /usr/src && make includes
cd /usr/src/minix/servers/vfs/ && make clean && make && make install
cd /usr/src/releasetools && make do-hdboot
reboot
