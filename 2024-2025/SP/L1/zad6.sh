#!/bin/bash

RED='\033[0;31m'
NC='\033[0m'

function get_all_words {
    find $1 -type f -exec cat {} \; |
    sed 's/[[:blank:]]\+/\n/g' |
    sort | 
    uniq
}

get_all_words $1 | while read word
do
    res=$(grep -re "\b${word}\b.*\b${word}\b" $1) # match lines with two occurences of given word
    if [ -n "$res" ]                              # match found -> print info
    then 
        printf "Word: ${RED}${word}${NC}\n"
        printf "${res}\n"
    fi
done

