/* Google Code Jam 2010 - Qualification Round Africa - B Reverse Words
 * url: http://code.google.com/codejam/contest/351101/dashboard#s=p1
 *
 * Correctly solves both large and small input
 *
 * License: Unlicense
 *
 * Usage B-Reverse-Words input_file output_file
 * 	input_file: text file containing valid input for the problem
 * 		google-provided inputs are in ./inputs/reverse_words
 * 	output_file: location to write solutions to
 * 		file will be overwritten
 *
 * Problem Description:
 * 	Given a string, reverse the order of words
 * 	equivilent to python:
 * 		' '.join(str.split(' ')[::-1])
 * 	"this is a test" -> "test a is this"
 */

//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* word_list will hold the words from each case
 * words will be added to the beginning of the linked-list.*/
struct word_list {
	char word[1001];
	struct word_list *prev_word;
};

int get_int_line(FILE *in_file)
{
	/* Read a line containing a single int.
	 * return the int. */

	char line[6];

	fgets(line, sizeof line, in_file);

	return atoi(line);
}

struct word_list *get_words(char *line)
{
	char word[1001];
	int count, word_count;
	char c;
	struct word_list *last_word, *new_word;
	last_word = NULL;

	last_word = 0;
	count = 0;
	word_count = 0;

	while (1) {
		c = line[count];
		if (c == ' ' || c == '\n') {
			word[word_count] = '\0';

			new_word = malloc(sizeof(struct word_list));
			strcpy(new_word->word, word);
			new_word->prev_word = NULL;

			if (last_word == NULL) {
				last_word = new_word;
			} else {
				new_word->prev_word = last_word;
				last_word = new_word;
			}

			if (c == '\n')
				break;
			word_count = 0;
			count++;
			continue;
		}
		word[word_count] = c;
		word_count++;
		count++;
	}

	return last_word;
}

void print_words(struct word_list *words, FILE *out_file)
{
	struct word_list *next_word = words;
	while (1) {
		fprintf(out_file, "%s", next_word->word);
		if (next_word->prev_word == 0)
			break;
		fprintf(out_file, " ");
		next_word = next_word->prev_word;
	}
	return;
}

int main(int argc, char **argv)
{
	// vars
	FILE *in_file, *out_file;
	int case_count, current_case;
	struct word_list *words;
	char line[1001];

	// check the args
	if (argc != 3) {
		printf("Usage: %s in_file out_file\n", argv[0]);
		return 1;
	}

	// open input file
	in_file = fopen(argv[1], "r");
	if (in_file == NULL) {
		printf("Could not open %s for reading.\n", argv[1]);
		return 1;
	}

	// open output file
	out_file = fopen(argv[2], "w");
	if (out_file == NULL) {
		fclose(in_file);
		printf("Could not open %s for writing.\n", argv[2]);
		return 1;
	}

	case_count = get_int_line(in_file);

	current_case = 1;
	while (current_case <= case_count) {
		fgets(line, sizeof(line), in_file);
		words = (struct word_list *)malloc(sizeof(struct word_list));
		words = get_words(line);
		fprintf(out_file, "Case #%i: ", current_case);
		print_words(words, out_file);
//		print the words list (reversed)
		fprintf(out_file, "\n");
		current_case++;
	}
	// close files
	fclose(in_file);
	fclose(out_file);
	return 0;
}
