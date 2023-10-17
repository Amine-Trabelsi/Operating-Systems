gcc -pthread worker.c -o worker
gcc -pthread scheduler_sjf.c -o scheduler_sjf

./scheduler_sjf data.txt