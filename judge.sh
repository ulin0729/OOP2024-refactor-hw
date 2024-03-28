#! /usr/bin/env bash

file_name=$1
correct=0

if [[ ! -f $file_name ]]; then
    echo "File not exist!"
    exit 1
fi

if [[ $file_name == *.cpp ]]; then
    g++ -std=c++23 $file_name -o a.out
    if [[ $? -ne 0 ]]; then
        echo "Compile Error!"
        exit 1
    fi
elif [[ $file_name == *.c ]]; then
    gcc $file_name -o a.out
    if [[ $? -ne 0 ]]; then
        echo "Compile Error!"
        exit 1
    fi
else
    echo "File type not supported!"
    exit 1
fi

for i in {0..10}
do
    ./a.out < ./testdata/$i.in > ./output.txt

    if diff -b output.txt ./testdata/$i.out >/dev/null; then
        echo "Test $i Passed"
        correct=$((correct+1))
    else
        echo "Test $i Failed"
    fi

    rm output.txt
done

if [[ $correct -eq 11 ]]; then
    echo "AC"
else
    echo "WA"
fi

rm a.out