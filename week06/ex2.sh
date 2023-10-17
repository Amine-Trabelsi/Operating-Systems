gcc -pthread worker.c -o worker
gcc -pthread scheduler.c -o scheduler

./scheduler data.txt