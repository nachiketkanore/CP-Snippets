
echo 'Compiling files'

g++ -O2 -std=c++17 -o a sol.cpp
g++ -O2 -std=c++17 -o brute brute.cpp
g++ -O2 -std=c++17 -o gen gen.cpp

echo 'Compilation done'

for((i = 1; i <= 100; ++i)); do
    echo TEST: $i
    # below line gives command line args to gen.cpp
    ./gen $i > input
    # cat input     # to check input generator

    # ./a < input > out1
    # ./brute < input > out2
    # diff -w out1 out2 || break
    
    diff -w <(time ./a < input) <(./brute < input) || break
    echo $'\n'
done
