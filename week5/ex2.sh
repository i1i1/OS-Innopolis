#!/bin/sh

cd $(dirname $0)
file=./ex2.txt
lockfile=$file.lock

add_num() {
    while true; do
        if ln $file $lockfile 2>/dev/null; then
            break
        else
            sleep 0.0001
        fi
    done

    n=$(tail -1 <$file)
    n=$((n+1))
    echo $n >>$file

    rm $lockfile
}

while true; do
    add_num
done

