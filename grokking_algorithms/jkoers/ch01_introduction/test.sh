#!/bin/bash
FIND="dpkjlhmnodjzhriynmorbpqstirtbj"

if [ ! -f random.out ]; then
	echo "generating random.out..."
	# cat /dev/urandom | tr -dc '[:alpha:]' | fold -w ${1:-20} | head -n 100000 > random.out
	node generateInput.js
	echo $FIND >> random.out
fi

echo "cpp"
echo "------------------------------"
cd cpp
make
./a.out ../random.out $FIND

echo
echo
echo "ts"
echo "------------------------------"
cd ..
cd ts
ts-node main.ts ../random.out $FIND
