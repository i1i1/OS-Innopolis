#!/bin/sh

test_copy() {
    if [ ! -z "$sync" ]; then
       gcc -DSYNC -DBUF_SIZE=$1 ./copy.c -o out
    else
       gcc        -DBUF_SIZE=$1 ./copy.c -o out
    fi
    time ./out infile outfile
}


buf_sizes="500 1000 5000 10000 20000 40000 80000"

dd if=/dev/zero of=infile bs=1M count=4

echo -e "\e[31mTesting without sync\e[0m"

sync=
for b in $buf_sizes; do
    echo buf-size $b
    test_copy $b
done

echo -e "\e[31mTesting with sync\e[0m"
sync=y
for b in $buf_sizes; do
    echo buf-size $b
    test_copy $b
done

