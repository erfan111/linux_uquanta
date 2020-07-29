#!/bin/bash

UTIL_DIR=/mnt/data/linux_uquanta/scripts/sched_setsched
PERIOD=50
RUNTIME=40
INTERVAL=0.1 #100 ms
EXPERIMENT_DURATION=40

killall stress-ng &>/dev/null
killall nr_running_reader.sh &>/dev/null

# echo "Running MQ experiment ..."
# stress-ng -c 400 &

# sleep 10

# $UTIL_DIR/set_microq_params.out $PERIOD $RUNTIME `pgrep stress-ng` > /dev/null

# sleep 1

# taskset -c 39 timeout $(($EXPERIMENT_DURATION + 20 )) $UTIL_DIR/nr_running_reader_mq.sh "mq" $INTERVAL &
# nr_running_pid=$!
# sleep 10

# for pid in $(pgrep -w stress-ng) 
# do
# 	echo $pid
# 	taskset -cp 0-38 $pid > /dev/null
# done

# sleep $EXPERIMENT_DURATION

# killall stress-ng &>/dev/null
# while kill -0 $nr_running_pid 2> /dev/null; do
# 	sleep 0.1
# done
# echo "Microquanta experiment finished."

################
# sleep 5
echo "Running CFS experiment ..."
taskset -c 0-38 /mnt/data/stress-ng/stress-ng --pthread 10 &
sleep 5
taskset -c 39 timeout $(($EXPERIMENT_DURATION + 10 )) $UTIL_DIR/placement_reader.sh "mq" $INTERVAL &
nr_running_pid=$!


sleep $EXPERIMENT_DURATION

killall stress-ng &>/dev/null
while kill -0 $nr_running_pid 2> /dev/null; do
	sleep 0.1
done
echo "CFS experiment finished."
