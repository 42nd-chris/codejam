/* Google Code Jam 2010 - Qualification Round Africa - C T9 Spelling
 * url: http://code.google.com/codejam/contest/351101/dashboard#s=p2
 *
 * passes both large and small input
 *
 * License: Unlicense
 *
 * usage C-T9-Spelling in_file out_file
 * 	in_file: text file containing valid input for the challenge
 * 		google-provided input in ./intput/t9_spelling/
 * 	out_file: file that results will be written to
 * 		will be overwritten
 *
 * Problem Description:
 * 	Given a string, print out the key presses needed to spell it on a
 * 	mobile phone. A space indicates the required pause when two consecutive
 * 	characters are on the same key.
 *
 * 	Example: "hi" -> "44 444"
 */

//includes
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

void write_keys(char c, FILE *out_file)
{
	//255 being used instead of NULL as
	// NULL was giving warning:
	// initialization makes int from pointer without a cast
	static int last_press = 255;
	int this_press;
	int num_presses;

	// clear last_press in between cases
	if (c == '\n') {
		last_press = 255;
		return;
	}

	// determine which key to press
	switch (c) {
		case 'a':
		case 'b':
		case 'c':
			this_press = 2;
			break;
		case 'd':
		case 'e':
		case 'f':
			this_press = 3;
			break;
		case 'g':
		case 'h':
		case 'i':
			this_press = 4;
			break;
		case 'j':
		case 'k':
		case 'l':
			this_press = 5;
			break;
		case 'm':
		case 'n':
		case 'o':
			this_press = 6;
			break;
		case 'p':
		case 'q':
		case 'r':
		case 's':
			this_press = 7;
			break;
		case 't':
		case 'u':
		case 'v':
			this_press = 8;
			break;
		case 'w':
		case 'x':
		case 'y':
		case 'z':
			this_press = 9;
			break;
		case ' ':
			this_press = 0;
			break;
		default:
			fprintf(stderr, "Which keys defaulted with: %c\n", c);
			break;
	}
	
	// add the required pause between
	// pressing the same key for different
	// characters
	if (last_press == this_press)
		fprintf(out_file, " ");
	
	// get the number of presses
	switch (c) {
		case 'a':
		case 'd':
		case 'g':
		case 'j':
		case 'm':
		case 'p':
		case 't':
		case 'w':
		case ' ':
			num_presses = 1;
			break;
		case 'b':
		case 'e':
		case 'h':
		case 'k':
		case 'n':
		case 'q':
		case 'u':
		case 'x':
			num_presses = 2;
			break;
		case 'c':
		case 'f':
		case 'i':
		case 'l':
		case 'o':
		case 'r':
		case 'v':
		case 'y':
			num_presses = 3;
			break;
		case 's':
		case 'z':
			num_presses = 4;
			break;
		default:
			fprintf(stderr, "Number of presses defaulted with: %c\n", c);
			break;
	}

	int i;
	for (i = 0; i < num_presses; i++)
	{
		fprintf(out_file, "%i", this_press);
	}

	last_press = this_press;
	
	return;
}

int main(int argc, char **argv)
{
	//vars
	FILE *in_file, *out_file;
	int case_count, current_case;

	//check args
	if (argc != 3) {
		printf("Usage: %s in_file out_file\n", argv[0]);
		return 1;
	}

	// open input
	in_file = fopen(argv[1], "r");
	if (in_file == NULL) {
		printf("Could not open %s for reading.\n", argv[1]);
		return 1;
	}

	// open output
	out_file = fopen(argv[2], "w");
	if (out_file == NULL) {
		printf("Could not open %s for writing.\n", argv[2]);
		fclose(in_file);
		return 1;
	}

	case_count = get_int_line(in_file);

	current_case = 1;
	
	while (current_case <= case_count) {
	
		fprintf(out_file, "Case #%i: ", current_case);
		char c;
		while(1) {
			c = fgetc(in_file);
			if (c == '\n' || c == '\0') {
				write_keys('\n', out_file);
				break;
			}
			write_keys(c, out_file);
		}
		fprintf(out_file, "\n");
		current_case++;
	}

	//close files
	fclose(in_file);
	fclose(out_file);
	return 0;
}
