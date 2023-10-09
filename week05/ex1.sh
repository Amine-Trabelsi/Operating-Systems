gcc publisher.c -o publisher 
gcc subscriber.c -o subscriber

gnome-terminal -- ./publisher "$1"
for((x=0; x<$1; x++))
do
	gnome-terminal -- ./subscriber $x
done