#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//The goal of this program is to try out all Vigenere-based algorithms allowing the user to *eyeball* to find the correct answer.
//Author kahootbird a.k.a Ronnie Goodrich
FILE *fp, *fout, *fkey;
int lh = 0;
char mystring [350];
char worn[350]; //Get word or name.
char c; //used for a character in various circumstances..
char *final_string_output;
char *vigenere_string(char *dest, char *src);
int main(int argc,char *argv[])
{
	/* Handle File Input ********************/
	if (argv[1] == NULL)
	{
		printf("Format must be: inputfile outputfile keyfile\n");
		exit(1);
	}

	if (argv[2] == NULL)
	{
		printf("Format must be: inputfile outputfile keyfile\n");
		exit(1);
	}
	
	if (argv[3] == NULL)
	{
		printf("Format must be: inputfile outputfile keyfile\n");
		exit(1);
	}
	
	fp = fopen(argv[1],"r");
	if (fp == NULL)
	{
		printf("Failed to open file.\n");
		exit(1);
	}

	fout = fopen(argv[2], "w");
	if (fout == NULL)
	{
		printf("Failed to open file for writing.\n");
		fclose(fp);
		exit(1);
	}
	
	fkey = fopen(argv[3], "r");
	if (fkey == NULL)
	{
		printf("Failed to open keyfile for reading.");
		fclose(fp);
		fclose(fout);
		exit(1);
	}
	printf("File I/o Successful\n");
	//Now we need to do a series of steps. Read the inputfile. Afterward, while gettting keyfile input vigenerate them, outputting the result.

// THIS PROGRAM DOES NOT CONVERT TO LOWERCASE. it should already be done.
	fgets (worn, 100, fp);
	while (fgets (mystring, 100, fkey) != NULL)
	{	
		//printf("%s",mystring);
		final_string_output = vigenere_string(worn,mystring);
		puts(worn);		
		fprintf(fout,"%s\n",final_string_output);
		//Reset worn string		
		rewind(fp);
		fgets (worn, 100, fp);
	}

	// Close the former file input 	
	
	fclose(fp);
	fclose(fout);
	return (0);
}

//Takes two lowercase strings and vigenerates them by a keyed cipher.
//WARNING: does not datatype check to insure lowercase.
char *vigenere_string(char *dest, char *src)
{	
	int src_len = strlen(src);
	int dest_len = strlen(dest);
	int current_compare_char = 0;
	int src_compare_char = 0;	
	char achar;
	//printf("\n%s\n",src);
	//printf("%s\n",dest);
	//Here comes the algorithm work..
	while (current_compare_char != dest_len-1)
	{		
		//Ignore all whitespace
		if (!isspace(dest[current_compare_char]))
		{

		
			//Ensure the src character is reset since the destination could be longer..
			if (src_compare_char == src_len-1)
			{
				src_compare_char = 0;
			}
			dest[current_compare_char] -= (src[src_compare_char] - 96 -1);
			//Insure it doesn't go past z on the ascii chart.
			if (dest[current_compare_char] > 122)
			{
				dest[current_compare_char] -= 26;
			}		
			if (dest[current_compare_char] < 96)
			{
				dest[current_compare_char] += 26;
			}
		src_compare_char++;
		}
		current_compare_char++;	
	}
	//printf("%s\n",dest);	
	char *temp = dest;
	return dest;
	//return(dest);
	/*
	printf("*****************************");
	printf("%s",src);
	printf("%s",dest);
	printf("*****************************");
	*/
}
