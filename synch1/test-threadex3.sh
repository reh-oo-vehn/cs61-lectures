#! /bin/sh

while true; do
	./threadex3 > out.txt
	x="`cat out.txt | tr '\n' ' '`"
	if [ "$x" != "Hello from thread 1 Hello from thread 2 " -a "$x" != "Hello from thread 2 Hello from thread 1 " ]; then
		cat out.txt
		exit 1
	fi
done
