#!/bin/bash
MYPATH="/Users/molesen/Desktop/Hive/new_best_swap"
command -v $MYPATH/push_swap >/dev/null 2>&1 || { printf "\npush_swap not found!\n"; exit 1; }
command -v $MYPATH/checker >/dev/null 2>&1 || { printf "\nchecker not found!\n"; exit 1; }
LOCALPATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# nb of total valid test
nb=0

# colors
BOLD="\033[1m"
RED="\033[0;31m"
GREEN="\033[32m"
YELLOW="\033[33m"
BLUE="\033[34m"
PURPLE="\033[35m"
CYAN="\033[36m"
UNCOLOR="\033[0m"

# $1: i
function error_put()
{
	printf "EXPECTED OUTPUT: Error"
	printf "\nYOUR OUTPUT IS: "
}

function valid_put()
{
	printf "\nEXPECTED OUTPUT: "
	printf "OK"
	printf "\nYOUR OUTPUT IS:"
}

function number_put()
{
	printf "\nEXPECTED OUTPUT: "
	printf "OK"
	printf "\nYOUR OUTPUT IS:"
}

# $1: type test $2: example $3: number of test arg $4: var2 $5: 1 if var2 take i for arg, else 0 $6 fnctn error
function test()
{
	printf "\n$1 test: ${YELLOW}[$2]${UNCOLOR}\n"
	var2=$($3)
	if [ "$var2" == "Error" ]
	then
		var=$((ARG=$2; ${MYPATH}/checker $ARG) 2>&1 >/dev/null)
	else
		var=$((ARG=$2; ${MYPATH}/push_swap $ARG | ${MYPATH}/checker $ARG) 2>&-)
	fi
	if [ "$var" != "$var2" ]
	then
		printf "\n${RED}fail: ${UNCOLOR}\n"
		$4
		printf "$var\n"
	else
		printf "$var\n"
		printf "		${GREEN}ok${UNCOLOR}\n"
	fi
}

function error_test()
{
	printf "\n${PURPLE}${BOLD}Error tests${UNCOLOR}\n"

	# non numeric parameters
	printf "\n${BLUE}non numeric tests${UNCOLOR}"
	test invalid "10 one 25 2" "printf "Error"" error_put
	test invalid "hello my name is" "printf "Error"" error_put

	#duplicate parameters
	printf "\n${BLUE}duplicates tests${UNCOLOR}"
	test invalid "10 2 25 2" "printf "Error"" error_put
	test invalid "10 2 25 3 5 70 1 2 32 52 10 11" "printf "Error"" error_put
	test invalid "10 2 25 1 2 4 3" "printf "Error"" error_put

	#greater than MAXINT parameters
	printf "\n${BLUE}greater than MAXINT tests${UNCOLOR}"
	test invalid "10 2 25 -2147483649 7 -8" "printf "Error"" error_put
	test invalid "10 2 25 -2147483650 5 11" "printf "Error"" error_put
	test invalid "10 2 25 -214748365155020151 5 11" "printf "Error"" error_put
	test invalid "10 2 25 2147483648 7 800" "printf "Error"" error_put
	test invalid "10 2 25 200 2147483650 4210 45" "printf "Error"" error_put
	test invalid "10 2 25 200 21474836500005 4210 45" "printf "Error"" error_put
}

function valid_test()
{
	printf "\n${PURPLE}${BOLD}Valid tests${UNCOLOR}\n"

	#simple test
	printf "\n${BLUE}simple tests${UNCOLOR}"
	test valid "10 2 25" "printf "OK"" valid_put
	test valid "2 1 0" "printf "OK"" valid_put

	#big numbers
	printf "\n${BLUE}big number tests${UNCOLOR}"
	test valid "10 2 2147483647" "printf "OK"" valid_put
	test valid "10 -2147483648 25" "printf "OK"" valid_put
	test valid "10 2 2147483640" "printf "OK"" valid_put
	test valid "10 -2147483640 25" "printf "OK"" valid_put

}


# $1: type test $2: example $3: number of test arg $4: var2 $5: 1 if var2 take i for arg, else 0 $6 fnctn error
function op_test()
{
	printf "\n$1 test: ${YELLOW}[$2]${UNCOLOR}\n"
	var2=$($3)
	var=$((ARG=$2; ${MYPATH}/push_swap $ARG | wc -l) 2>&-)
	var3=$((ARG=$2; ${MYPATH}/push_swap $ARG | ${MYPATH}/checker $ARG) 2>&-)
	if [ "$var3" != "OK" ];
	then
		printf "\n${RED}numbers not sorted correctly${UNCOLOR}\n"
		var=$((${var2}+1))
	fi
	if (( $var > $var2 ));
	then
		printf "\n${RED}fail: ${UNCOLOR}\n"
		printf "\nEXPECTED OUTPUT: less or equal to ${var2}"
		printf "\nYOUR COUNT IS:"
		printf "$var\n"
	else
		printf "$var\n"
		printf "		${GREEN}ok${UNCOLOR}\n"
	fi
}

function operation_test()
{
	printf "\n${PURPLE}${BOLD}Operation tests${UNCOLOR}\n"

	#already sorted test
	printf "\n${BLUE}already sorted tests${UNCOLOR}"
	op_test instruction "42" "printf "0""
	op_test instruction "0 1 2 3" "printf "0""
	op_test instruction "0 1 2 3 4 5 6 7 8 9" "printf "0""
	op_test instruction "1 2 3 4 5" "printf "0""
	op_test instruction "2 4 6 8 10 12" "printf "0""

	#simple test
	printf "\n${BLUE}simple tests${UNCOLOR}"
	op_test instruction "2 1 0" "printf "3""

	#five number test
	printf "\n${BLUE}5 number tests${UNCOLOR}"
	op_test instruction "1 5 2 4 3" "printf "12""
	op_test instruction "1 2 3 5 4" "printf "12""
	op_test instruction "5 4 3 2 1" "printf "12""
	op_test instruction "5 4 3 1 2" "printf "12""
	op_test instruction "5 1 3 4 2" "printf "12""
	op_test instruction "3 4 1 2 5" "printf "12""
	op_test instruction "2 3 1 5 4" "printf "12""
	op_test instruction "4 3 1 5 2" "printf "12""
	op_test instruction "4 67 3 87 23" "printf "12""
}

function main()
{
	make re -C ${MYPATH}
	error_test
	valid_test
	operation_test
}

main
