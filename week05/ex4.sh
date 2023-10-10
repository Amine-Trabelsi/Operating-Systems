gcc -pthread ex4.c -o run
for x in {1,2,4,10,100}
do
	echo "Using m= $x ##########################"
	start=`date +%s.%N`
	./run 10000000 $x
	end=`date +%s.%N`
	runtime=$( echo "$end - $start" | bc -l )
	echo "DONE in $runtime seconds"
	echo
done

