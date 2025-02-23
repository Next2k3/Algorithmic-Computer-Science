#!/bin/bash

URL_BASE=https://repo.cs.pwr.edu.pl/info/asciinema/

select fname in $(svn list $URL_BASE | grep '\.cast' -);
do
	# echo you picked $fname \($REPLY\)
        clear;
        svn cat $URL_BASE/$fname | asciinema play -
	break;
done


