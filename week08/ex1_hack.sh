pid=$(</tmp/ex1.pid)

echo "$pid"
sudo gcore $pid

echo "core dumped"

xxd core.$pid > core_.hex
grep -bPo "pass:........" dec_.hex

yes | rm core.$pid


kill -9 $pid
