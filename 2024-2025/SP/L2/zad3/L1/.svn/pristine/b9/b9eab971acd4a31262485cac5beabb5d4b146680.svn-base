#!/bin/bash

function get_all_words {
    find $1 -type f -exec cat {} \; |
    sed 's/[[:blank:]]\+/\n/g' |
    sort | 
    uniq
}

get_all_words $1 | while read word                  # loop at all words in all subdirs
do
    no_of_files=$(grep -lwr $word $1 | wc -l)       # count number of files with occurence of word in all files recursively
    printf "${no_of_files}\t${word}\n"
done

