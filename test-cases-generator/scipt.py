import os

tc = input('Enter number of testcases : ')

for t in range(tc):

    #creating input files
    os.system('g++ gen.cpp')
    os.system('./a.out > input{}.txt'.format(t))

    #creating corresponding output files
    os.system('g++ sol.cpp')
    os.system('./a.out < input{}.txt > output{}.txt'.format(t,t))

    print('Successfully generated testcase no {}'.format(t + 1))
