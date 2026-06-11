#!/usr/bin/env bash

N_POINTS=256
FILENAME="data.csv"

while getopts "p:o:" flag
do
    case "${flag}" in
        p) N_POINTS=${OPTARG};;
        o) FILENAME=${OPTARG};;
        \?) exit 1;;
    esac
done
shift $((OPTIND - 1))
PUSH_SWAP_PATH=$1
if [[ -z "${PUSH_SWAP_PATH}" || ! "$N_POINTS" =~ ^[0-9]+$ ]]; then
    echo "Usage: $0 [-p <# points>] [-o <filename>] <push_swap path>" >&2
    exit 1
fi

make --silent

for i in $(seq 1 "$N_POINTS")
do
	ARG="$(./generate_seq -m 1024 -o $FILENAME)"
    echo -n "," >> $FILENAME
	$PUSH_SWAP_PATH --simple $ARG | ./count_ps_ops -o $FILENAME $ARG
	echo -n "," >> $FILENAME
	$PUSH_SWAP_PATH --medium $ARG | ./count_ps_ops -o $FILENAME $ARG
	echo -n "," >> $FILENAME
	$PUSH_SWAP_PATH --complex $ARG | ./count_ps_ops -o $FILENAME $ARG
	echo -n "," >> $FILENAME
	$PUSH_SWAP_PATH --adaptive $ARG | ./count_ps_ops -o $FILENAME $ARG
	echo "" >> $FILENAME
done

gnuplot plot.gp
