/*
 * Google Code Jam 2010 - Qualification Round Africa - A Store Credit
 * url: http://code.google.com/codejam/contest/351101/dashboard#s=p0
 *
 * Solves both small and large data sets correctly.
 *
 * License: Unlicense
 *
 * Usage: A-Store-Credit input_file output_file
 * 	input_file: text file containing valid input for the problem
 * 		all google-provided input is in ./inputs/store_credit
 * 	output_file: results will be written to this file; it will be
 * 		overwritten if it already exists
 *
 * Problem description: Given an amount of store credit, and a list of prices
 * 	find the two items whose prices add up to the credit amount. No item may
 * 	be purchased twice. No items have a price of 0. All cases have exactly
 * 	one correct answer.
 */

// includes
#include <stdio.h>
#include <stdlib.h>

int get_int_line(FILE *in_file)
{
	/* Read a line containing a single int.
	 * return the int. */

	char line[6];

	fgets(line, sizeof line, in_file);

	return atoi(line);
}

void get_item_prices(int prices[2001], FILE *in_file)
{
	/* Reads the line containing the list of item prices.
	 * Puts the int representation of each price in prices array.*/
	char c;
	int count;
	int price_count;
	char line[6];

	count = 0;
	price_count = 0;
	while (1) {
		c = fgetc(in_file);
		if (c == '\0' || c == '\n') {
			line[count] = '\0';
			prices[price_count] = atoi(line);
			break;
		}
		if (c == ' ') {
			line[count] = '\0';
			prices[price_count] = atoi(line);
			price_count++;
			count = 0;
		}
		line[count] = c;
		count++;
	}

	return;
}

void solve(int credit_amount, int items[2001], int num_items, int solution[2])
{
	// solve the case; no item can be used twice; no price will be 0
	// add the answers to the solution array
	int i, j;
	int credit_remaining;

	i = 0;
	while (i < num_items) {
		if (items[i] >= credit_amount) {
			i++;
			continue;
		}
		credit_remaining = credit_amount - items[i];
		j = 0;
		while (j < num_items) {
			if (j == i) {
				j++;
				continue;
			}
			if (items[j] == credit_remaining) {
				solution[0] = i + 1;
				solution[1] = j + 1;
				return;
			}
			j++;
		}
		i++;
	}

	// The only way this is executed is if there is a bug
	// or invalid input
	printf("COULDN'T FIND SOLUTION\n");
	return;
}

int main(int argc, char **argv)
{
 	// vars
 	FILE *in_file, *out_file;
	int case_count; // total number of cases
	int current_case; // used for tracking the loop and printing results
	int credit_amount; // amount of credit for each case
	int num_items; // the number of items for each case
	int items[2001]; // the prices, large dataset can have 2000 items
	int solution[2]; // holds the two items that add up to the credit amount

 	// check args
 	if (argc != 3) {
 		printf("Usage: A-Store-Credit input_file output_file\n");
 		return 1;
 	}
 
 	// open input file
 	in_file = fopen(argv[1], "r");
 	if (in_file == NULL) {
 		printf("Could not read from %s\n", argv[1]);
 		return 1;
 	}
 
 	// open output file
 	out_file = fopen(argv[2], "w");
 	if (out_file == NULL) {
 		printf("Could not write to %s\n", argv[2]);
 		fclose(in_file);
 		return 1;
 	}

	// get the number of cases
	case_count = get_int_line(in_file);

	current_case = 1;

	// loop over the cases
	while (current_case <= case_count) {
		credit_amount = get_int_line(in_file);
		
		// get number of items
		num_items = get_int_line(in_file);
		
		// get items list
		get_item_prices(items, in_file);
	
		// solve problem
		solve(credit_amount, items, num_items, solution);

		// write solution to out_file
		fprintf(out_file, "Case #%i: %i %i\n", current_case, solution[0], solution[1]);
		current_case++;
	}
 
 
 	// close the files
 	fclose(in_file);
 	fclose(out_file);
 
	return 0;
}
