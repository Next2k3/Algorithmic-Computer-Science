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
    printf "\nWord: ${RED}${word}${NC}\n"
    grep -w $word -r $1                     # print file and line in which word was found
done

