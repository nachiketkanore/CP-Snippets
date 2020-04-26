#	Removing residue input and output files
	rm -rf input
	rm -rf output

#	Creating Directory and temporary files for input and output files
	mkdir input
	mkdir output
	touch temp.txt

#	Read number of test case 
	read -p"How many Test Cases to Generate : " mx

#	sol.cpp :	Solution Generator
	g++ -std=c++11 -O2  1.cpp -o sol

#	gen.cpp	:	Test Case Generator
	g++ -std=c++11 -O2  gen.cpp -o gen

i=0
while [ $i -lt $mx ]
do
#	Generating name of input and output file
	if [ $i -le 9 ]
	then
		in="input0$i.txt"
		out="output0$i.txt"
	else
		in="input$i.txt"
		out="output$i.txt"
	fi

	echo $i > temp.txt
	echo "#$i"

# 	Generating Test Case
	./gen < temp.txt > "input/$in"

# 	Generating solutions
	./sol < "input/$in" > "output/$out"

	i=$((i+1))
done

#	Removing residue files
rm sol
rm gen
rm temp.txt
