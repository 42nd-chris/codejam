#!/usr/bin/env python

# License: Unlicense

# Google Code Jame 2009 Round 1C - A All Your Base
# Challenge url: http://code.google.com/codejam/contest/189252/dashboard#s=p0

# Passes both small and large input

# Usage: A-All_Your_Base.py input_file output_file
# 	input_file: text file, input is assumed to be valid and formatted as
# 	 	described in the challenge, all Google-provided inputs are in
# 		the folder inputs/all_your_base
# 
# 	output_file (optional): name of file to write the output to.
# 		will be overwritten if it exists
#		output will be written to stdout if the output file
# 		isn't specified or can't be written to

# Problem Description:
#	Given a string which represents a number in an unknown base,
#	print out the base 10 representation of it's smallest possible value.

# imports
from sys import argv, exit, stdout, stderr

# functions
def solve(case):
	"""Takes a string representing the challenge's input.
	   Returns a string representing the solution.
	   Each case is a string that represents a number in an
	   unknown base. The solution is the lowest possible number
	   that the string could represent.
	"""

	solution = '' # String to be returned

	# get the base of the string
	# the lowest possible base will be the number of unique
	# characters in the string, or 2, whichever is higher
	base = max(len(set(case)), 2)

	# this dictionary is used to translate the input into it's base
	digit_dict = get_digit_values(case, base)

	# get the digit value of each char in input string
	# using a list instead of a string because characters whose 
	# digit > 9 will cause problems
	translated = [digit_dict[c] for c in case]

	# translate the input string to a solution
	solution = str(to_base_10(translated, base))

	return solution

def get_digit_values(num_str, base):
	"""Returns a dictionary where the key is the char in it's input
	   form, the value is it's numerical value for it's output."""
	
	# Dictionary will be used to translate the input string to 
	# the proper solution
	digit_dict = {}
	
	# in order to get the lowest possible value, the value of the characters
	# should follow the pattern: 1, 0, 2 ... n where n == base
	values = [1, 0] + [x for x in range(2, base)]

	# loop through characters of string, assigning the lowest possible
	# value to each character the first time it is seen
	for c in num_str:
		if c in digit_dict.keys():
			continue
		digit_dict[c] = values.pop(0)
	
	return digit_dict

def to_base_10(digit_list, origin_base):
	""" Given a list of digits and the origin base, return the
	    number in base 10.
	    Example: to_base_10([1, 0, 2], 3) -> 11
	"""

	base_10 = 0 # to be returned

	# not using pythons built in int() function to convert on purpose
	# though int should work as it can convert any number base < 37 to base
	# 10

	# exp represents the power of the base that each place is
	exp = len(digit_list) - 1
	for d in digit_list:
		base_10 += d * origin_base**exp
		exp -= 1
	
	return base_10

# procedure
if __name__ == "__main__":
	try:
		input_file = open(argv[1], 'r')
	except:
		stderr.write("Could not open {} for reading".format(argv[1]))
		exit(1)
	
	if len(argv) == 3:
		try:
			output_file = open(argv[2], 'w')
		except:
			output_file = stdout
	else:
		output_file = stdout
	
	# discard the first line
	input_file.readline()

	# solve the cases
	case_num = 1
	for case in input_file:
		solution = solve(case.replace('\n', ''))
		formatted_output = "Case #{}: {}\n".format(case_num, solution)
		output_file.write(formatted_output)
		case_num += 1
