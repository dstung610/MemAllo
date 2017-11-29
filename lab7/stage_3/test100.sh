#!/bin/bash
for i in {1..100}
do
./stress_test.run -n 4 -k 100 -s
echo $i
done
