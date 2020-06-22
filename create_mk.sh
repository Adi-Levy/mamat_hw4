#!/bin/bash

##############################################################
# function name: create_mk
#
# description: creates makefile rules for all .cpp files in 
#		the given directory 
#
# parameters: 1 - a directory that holds .cpp files
#
# return value: N/A. the function creates an objects.mk file 
#		for the makefile rules 
##############################################################

curr_dir="$PWD";
cd "$1";
cpp_files=(`find *.cpp`);
touch objects.mk;
 > objects.mk;
for file in ${cpp_files[*]}; do
	echo `g++ -MM "$file"` >> objects.mk;
done
if [[ "$1" != "$curr_dir" ]]; then
	mv "objects.mk" "$curr_dir";
fi
cd $curr_dir;

