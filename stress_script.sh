#!/usr/bin/env bash
cmake CMakeLists.txt
make
mkdir stress 2> /dev/null
for ((i = 1; i < 100; i++)); do
    ./bin/GeneratorMain > ./stress/graph.txt
    ./bin/CorrectMain < ./stress/graph.txt > ./stress/correct.txt
    time ./bin/TLSMain < ./stress/graph.txt > ./stress/tls.txt
    cat ./stress/graph.txt ./stress/correct.txt ./stress/tls.txt > ./stress/checker.txt
    ./bin/Checker < ./stress/checker.txt || break
    echo "Test $i: OK"
done

