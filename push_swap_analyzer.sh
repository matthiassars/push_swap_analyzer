#!/usr/bin/env bash

N=256
FILENAME="data.csv"

while getopts "n:o:" flag
do
    case "${flag}" in
        n) N=${OPTARG};;
        o) FILENAME=${OPTARG};;
        \?) exit 1;;
    esac
done
shift $((OPTIND - 1))
PUSH_SWAP_PATH=$1
if [[ -z "${PUSH_SWAP_PATH}" || ! "$N" =~ ^[0-9]+$ ]]; then
    echo "Usage: $0 [-n <# points>] [-o <filename>] <push_swap path>" >&2
    exit 1
fi

make --silent

for i in $(seq 1 "$N")
do
	ARG="$(./generate_seq -m 1024 -o $FILENAME)"
	$PUSH_SWAP_PATH --simple $ARG | ./count_ps_ops -o $FILENAME $ARG
	$PUSH_SWAP_PATH --medium $ARG | ./count_ps_ops -o $FILENAME $ARG
	$PUSH_SWAP_PATH --complex $ARG | ./count_ps_ops -o $FILENAME $ARG
	$PUSH_SWAP_PATH --adaptive $ARG | ./count_ps_ops -o $FILENAME $ARG
	echo "" >> $FILENAME
done

gnuplot plot.gp
