#bin/bash!

make test-notify-open
clang -O2   -o test-notify-open test-notify-open.c
touch ./test.txt
./test-notify-open ./test.txt
