#!/bin/bash

PIDS=`ps -u dansv693 -A | grep httpd | cut -c 3-6`

# bash for loop
for pid in $PIDS; do
	echo $pid
        kill -9 $pid
done 
