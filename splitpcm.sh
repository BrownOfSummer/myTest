#!bin/bash

pcm=$1
start=$2

size=$[ ($start+10)*16000 ]
head -c $size $pcm > tmp
tail -c 160000 tmp > ${pcm%.pcm}_$start.pcm

rm tmp
