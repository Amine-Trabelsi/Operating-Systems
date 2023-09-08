mkdir ex3folder1
date
sleep 3
ls -t / > ex3folder1/root.txt
date 
sleep 3
mkdir ex3folder2
date
sleep 3
ls -t ~ > ex3folder2/home.txt
echo "*********** Content of root.txt ***********"
cat ex3folder1/root.txt
echo "*********** Content of home.txt ***********"
cat ex3folder2/home.txt
echo "*********** items in ex3folder1 ***********"
ls ex3folder1
echo "*********** items in ex3folder2 ***********"
ls ex3folder2