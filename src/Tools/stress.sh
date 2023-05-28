g++ gen.cpp -o gen -std=c++17 -Wall -O2
g++ ans.cpp -o ans -std=c++17 -Wall -O2
g++ usr.cpp -o ans -std=c++17 -Wall -O2
while true; do
    ./gen > 1
    ./ans < 1 > 2
    ./usr < 1 > 3
    diff 2 3
    if [ $? -ne 0 ] ; then break; fi
done
