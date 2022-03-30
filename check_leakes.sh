#!/bin/bash

usage() {
	echo -e \
"
${BOLD}Usage${NOCOLOR}: ${BOLD}$(basename "${BASH_SOURCE[0]}")${NOCOLOR} ${BOLD}arg1${NOCOLOR} [${BOLD}arg2...${NOCOLOR}]
	${BOLD}arg1${NOCOLOR} - ${DIMM}executable file for the check valgring${NOCOLOR}
	${BOLD}arg2${NOCOLOR} - ${DIMM}arguments executable file${NOCOLOR}\
"
	exit 0
}

set_colors() {
	RED="\033[31m"
	GREEN="\033[32m"
	YELLOW="\033[33m"
	BOLD="\033[1m"
	DIMM="\033[2m"
	NOCOLOR="\033[0m"
}

set_env() {
	if [ ! -n "$1" ]; then
		echo -e "${RED}Error${NOCOLOR}"
		exit 1
	fi
	argv=""
	if [ "$#" -gt 1 ]; then
		argv="${@:2}"
	fi
	make > /dev/null
	valgrind --leak-check=full --leak-resolution=high --log-file=leaks.log -s $1 $argv > /dev/null 2> error
	if [ -s "error" ]; then
		echo -e "${RED}Error:${NOCOLOR}"
		cat error
		rm -f error
		exit 1
	else
		if [ -f "error" ]; then
			rm -f error
		fi
	fi
	if [ -s "leaks.log" ]; then
		awk '{$1=""; print $0}' leaks.log > new_leaks.log
		rm -f leaks.log
		heap_allocs=$(cat new_leaks.log | grep "total heap usage" | awk '{print($4)}')
		heap_frees=$(cat new_leaks.log | grep "total heap usage" | awk '{print($6)}')
		leaks=$(cat new_leaks.log | grep "LEAK SUMMARY")
		errors=$(cat new_leaks.log | grep "ERROR SUMMARY" | awk '{print($3)}')
		errors_context=$(cat new_leaks.log | grep "ERROR SUMMARY" | awk '{print($6)}')
	fi
	if [ -s "new_leaks.log" ]; then
		if [ "${heap_allocs}" == "${heap_frees}" ]; then
			heap_result="${GREEN}OK${NOCOLOR}"
		else
			heap_result="${RED}KO\n$(cat new_leaks.log | grep "total heap usage")${NOCOLOR}"
		fi

		if [ -z "${leaks}" ]; then
			leaks_result="${GREEN}OK${NOCOLOR}"
		else
			line_start=$(cat new_leaks.log | grep -n "LEAK SUMMARY" | grep -Eo '^[^:]+')
			(( line_start++ ))
			line_end="$(( line_start + 4 ))"
			leaks_result="${RED}KO\n$(sed -n "${line_start},${line_end}p" new_leaks.log)${NOCOLOR}"
		fi

		if [ "${errors}" == "${errors_context}" ]; then
			errors_result="${GREEN}OK${NOCOLOR}"
		else
			errors_result="${RED}KO\n$(cat new_leaks.log | grep "ERROR SUMMARY" | sort | uniq )${NOCOLOR}"
		fi
		rm -f new_leaks.log
	fi
}

output() {
	echo -e \
	"${YELLOW}Heap${NOCOLOR}: $heap_result\
	\n${YELLOW}LEAK SUMMARY${NOCOLOR}: $leaks_result\
	\n${YELLOW}ERROR SUMMARY${NOCOLOR}: $errors_result\
	"
}

set_colors
if [ $# -lt 1 ]; then
	usage
fi
set_env $@
output