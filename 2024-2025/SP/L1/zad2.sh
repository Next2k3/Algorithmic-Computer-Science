#!/bin/bash

find $1 -type f -exec cat {} \; |   # output content of all files
sed 's/[[:blank:]]\+/\n/g' |        # remove string of tabs and spaces with new line
sort |                                              
uniq -c

