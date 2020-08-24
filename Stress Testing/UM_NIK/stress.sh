#!/bin/bash

g++ -O2 -std=c++17 -o sol sol.cpp
g++ -O2 -std=c++17 -o brute brute.cpp
g++ -O2 -std=c++17 -o gen gen.cpp

for((i=0; i<1000;++i))
do
  ./gen > testcase
  ./brute < testcase > ans1
  ./sol < testcase > ans2
  
  if diff -w ans1 ans2
  then
      echo $i OK
  else
      echo $i WA
      exit
  fi
done
