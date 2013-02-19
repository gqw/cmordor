#!/bin/bash

rm ./cscope.*
rm ./TAGS

find /usr/include -regex ".*\.\(h\|cpp\)$" >> cscope.files
find /usr/include/boost/ -regex ".*\.\(h\|cpp\)$" >> cscope.files
find /usr/lib/gcc/x86_64-linux-gnu/4.4/include -regex ".*\.\(h\|cpp\)$" >> cscope.files
find /usr/local/include -regex ".*\.\(h\|cpp\)$" >> cscope.files
find ./ -regex ".*\.\(h\|cpp\)$" >> cscope.files
find ./ -regex ".*\.\(h\|cpp\)$" | xargs etags

cscope -bvkq