#!/bin/bash

mkdir -p results
timestamp=$(date +%y%m%d-%H%M%S)
FILENAME="results/running-$1-$timestamp.csv"

# pathstr="cat /proc/{"
# pids=`pgrep -w cpptools-srv | sed ':a;N;$!ba;s/\n/,/g'`
# pathstr+=$pids
# pathstr+="}/task/*/stat"
echo $pathstr
while true
do
cat /proc/sched_debug | grep -A1 "cpu#" | grep ".nr_running" | awk '{print $3}' | sed ':a;N;$!ba;s/\n/ /g' >> $FILENAME
sleep $2

done