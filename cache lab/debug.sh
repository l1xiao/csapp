#!/bin/bash

./csim-ref -v -s 2 -E 2 -b 3 -t traces/test.txt > csim-ref.txt
./csim -v -s 2 -E 2 -b 3 -t traces/test.txt > csim.txt

