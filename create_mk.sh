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
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
cd "$1";
cpp_files=(`find *.cpp`);
touch "$DIR"/objects.mk;
 > "$DIR"/objects.mk;
for file in ${cpp_files[*]}; do
	echo `g++ -MM "$file"` >> "$DIR"/objects.mk;
done
cd $curr_dir;

