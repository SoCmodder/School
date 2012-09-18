#!/usr/bin/bash

let inverted=4
until [ $inverted -gt 4 ]
do
	echo "Running sorts on level $inverted"
	for num in 10 25 50 100 1000 10000 100000 1000000
	do

		echo "Running sorts with $num items"
		./gen $inverted $num in.txt
		let x=1
		until [ $x -gt 10 ]
		do
			echo "Running sort $x"
			./sort $x in.txt out.txt
			./check out.txt
			let x=x+1
		done
	done
	let inverted=inverted+1
done
