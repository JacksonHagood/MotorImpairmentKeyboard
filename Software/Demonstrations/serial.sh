#!/bin/bash


stty -F /dev/ttyACM0 raw
stty -F /dev/ttyACM0 -echo
while read -rs -n 4 press && [[ $c != 'q' ]]
do
    echo "$press"
done < /dev/ttyACM0