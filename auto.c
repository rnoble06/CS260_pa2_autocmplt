#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256
#define INITIAL_SIZE 2

typedef struct entry
{
	char *word;
	int weight;
} Entry;

Entry *initEntry(char *word, int weight)
{
  Entry *newEntry = malloc(sizeof(Entry));

  newEntry->word = malloc(sizeof(char)*(strlen(word)+1));
  strcpy(newEntry->word,word);

  newEntry->weight = weight;

  return newEntry;
}

typedef struct arrayList 
{
	int capacity;     //max possible
	int size;         //number of entries
	Entry **data;
} List;

List *initList(int lineCount)
{
  List *newList = malloc(sizeof(List));
  newList->size = 0;
  newList->capacity = lineCount;
  newList->data = malloc(sizeof(Entry *)*newList->capacity);

  printf("%d\n",newList->capacity);

  return newList;
}




int main(int argc, char **argv) {
    char *inputFilePath = argv[1]; //this keeps the path to input file
    char *queryWord = argv[2]; // this keeps the query word
    int lineCount=0; //this variable will tell us how much memory to allocate
    
    //read input file
    FILE *fp = fopen(inputFilePath, "r");
    char *line = NULL; //variable to be used for line counting
    size_t lineBuffSize = 0; //variable to be used for line counting
    ssize_t lineSize; //variable to be used for line counting
    
    //check if the file is accessible, just to make sure...
    if(fp == NULL){
        fprintf(stderr, "Error opening file\n");
        return -1;
    }

    //First, let's count number of lines. This will help us know how much memory to allocate
    while((lineSize = getline(&line,&lineBuffSize,fp)) !=-1)
    {
        lineCount++;
    }
    
    //Printing line count for debugging purposes. You can remove this part from your submission.
    printf("%d\n",lineCount);
    
    
    //This might be a good place to allocate memory for your data structure, by the size of "lineCount"


    /*-------  Allocate memory for structure. Review function from prj 1  -------*/

    List *sortedList;
	  sortedList = initList(lineCount);

    /*----------------------------------------------------------------*/

    //Read the file once more, this time to fill in the data into memory
    fseek(fp, 0, SEEK_SET);// rewind to the beginning of the file, before reading it line by line.
    char word[BUFSIZE]; //to be used for reading lines in the loop below
    int weight;
    for(int i = 0; i < lineCount; i++)
    {
        fscanf(fp, "%s %d\n",word,&weight);
        //Let's print them to the screen to make sure we can read input, for debugging purposes. You can remove this part from your submission.
        //printf("%s %d\n",word,weight);
    }
    //close the input file
    fclose(fp);
    
    //Now it is your turn to do the magic!!!
    //do search/sort/print, whatever you think you need to do to satisfy the requirements of the assignment!
    //don't forget to free the memory before you quit the program!
    
    //OUTPUT SPECS:
    // use the following if no word to suggest: printf("No suggestion!\n");
    // use the following to print a single line of outputs (assuming that the word and weight are stored in variables named word and weight, respectively): printf("%s %d\n",word,weight);
    // if there are more than 10 outputs to print, you should print top weighted 10 outputs.
    
    /*----------------------------------------------------------------*/
    free(sortedList);

    return 0;
}
