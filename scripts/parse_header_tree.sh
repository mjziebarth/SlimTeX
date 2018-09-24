#!/bin/bash
#
# parse_header_tree.sh
# Shell script to parse the header dependencies of a source file
# and select those that are part of SlimTeX.
#
# Copyright (C) 2018 Malte Ziebarth
#
# This file is part of SlimTeX.
#
# SlimTeX is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# SlimTeX is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with SlimTeX. If not, see <https://www.gnu.org/licenses/>.

# Obtain a list of all project headers:
all=($(ls include))

# Function to check whether a string is in the list of all
# headers of the project:
function is_project_header {
	for h in ${all[*]}; do
		if [ $1 == $h ]; then
			isheader=1
			return
		fi
	done
	isheader=0
}

# Recursively parse headers:
function obtain_headers_l1 {
	# Obtain list of all headers in current file:
	selected=($(cat $1 | grep "#include <"))
	# Cutting:
	# (iterate over this)
	for f in ${selected[*]}; do
		if [ $f != "#include" ]; then
			var=$(echo $f | cut -d "<" -f2 | cut -d ">" -f1)
			is_project_header $var
			if [ $isheader -eq 1 ]; then
				echo "$var"
				obtain_headers_l1 include/$var
			fi
		fi
	done
}

# Recursion start:
function obtain_headers_l0 {
	# Iterate over all input parameters (each of which is supposed to
	# contain a source file):
	for file in "$@"; do
	#	echo $file
		echo $(obtain_headers_l1 $file)
	done
}

function obtain_headers {
	headers=$(obtain_headers_l0 $@)
	for h in $headers; do
		echo "include/$h"
	done
}

# Collect all headers:
headers=$(echo $(obtain_headers $@) | tr '\n' ' ')
objname=$(echo $@ | cut -d "/" -f2 | cut -d "." -f1)
echo -e "build/$objname.tmp.dep: $headers;"
