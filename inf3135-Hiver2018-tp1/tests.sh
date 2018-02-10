#!/bin/bash
#
# Copyright 2017 Alexandre Terrasa <alexandre@moz-code.org>.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

tests_dir=tests
out_dir=tests_out

# Prepare output directory
rm -rf $out_dir
mkdir $out_dir

# test_00: Compile using makefile
make -B bin/pandemic > $out_dir/test_00.err 2>&1

if [ $? -gt 0 ]; then
	echo -ne "[\033[31mERR\033g[0m] "
	echo -ne "\033[1mtest_00: make bin/pandemic\e[0m "
	echo -e "(cat $out_dir/test_00.err)"
	exit 1
else
	echo -ne "[\033[32mOK\e[0m] "
	echo -e "\033[1mtest_00: make bin/pandemic\e[0m"
fi

# Run tests
for test in `ls tests/*.in`; do
	test_basename=$(basename "$test")
	test_name="${test_basename%.*}"

	test_in="$tests_dir/$test_name.in"
	test_args="$tests_dir/$test_name.args"
	test_res="$tests_dir/$test_name.res"
	test_out="$out_dir/$test_name.out"
	test_diff="$out_dir/$test_name.diff"

	# Check arg file
	if [ ! -f $test_args ]; then
		echo -ne "[ARG] "
		echo -ne "\033[1m$test_name\e[0m "
		echo -e "(no arg file for test $test_name)"
		continue
	fi

	# Check res file
	if [ ! -f $test_res ]; then
		echo -ne "[RES] "
		echo -ne "\033[1m$test_name\e[0m "
		echo -e "(no res file for test $test_name)"
		continue
	fi

	# Run the test
	bin/pandemic `cat $test_args` < $test_in > $test_out 2>&1

	# Check empty output
	if [ ! -f $tests_out ]; then
		echo -ne "[\033[31mERR\e[0m] "
		echo -ne "\033[1m$test_name\e[0m "
		echo -e "(no output)"
		continue
	fi

	# Check diff
	diff --ignore-all-space $test_res $test_out > $test_diff
	if [ -s $test_diff ]; then
		echo -ne "[\033[31mKO\e[0m] "
		echo -ne "\033[1m$test_name\e[0m "
		echo -e "(diff $test_res $test_out)"
	else
		echo -ne "[\033[32mOK\e[0m] "
		echo -e "\033[1m$test_name\e[0m"
	fi
done
