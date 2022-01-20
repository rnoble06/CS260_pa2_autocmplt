#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 256
#define INITIAL_SIZE 2
#define MAX_SIZE 10

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

  return newList;
}

/*----------------------------------------------------------------*/
/*----------------------------------------------------------------*/

void insertToHead(List *namedList, char *word, int weight)
{
  Entry *newEntry = initEntry(word,weight);
  if (namedList->size==0)
  {
    namedList->data[namedList->size] = newEntry;
    namedList->size=namedList->size+1;
  }
  
  else
  {
    if (((namedList->size)+1)<=(namedList->capacity))
    {
      //shiftPosition(namedList, 0);
      
      namedList->data[0] = newEntry;
      namedList->size=namedList->size+1;
    }

    else if (((namedList->size)+1)>(namedList->capacity))
    {
      //shiftPosition(namedList, 0);

      namedList->data[0] = newEntry;
      namedList->size=namedList->size+1;
    }
  }
  
}
void insertToTail(List *namedList, char *word,int weight)
{
  Entry *newEntry = initEntry(word,weight);
  if (((namedList->size)+1)<=(namedList->capacity))
  {
    namedList->data[namedList->size] = newEntry;
    namedList->size=namedList->size+1;
  }
  else if (((namedList->size)+1)>(namedList->capacity))
  {
    //doubleCapacity(namedList);
    
    namedList->data[namedList->size] = newEntry;
    namedList->size=namedList->size+1;
  }
  else fprintf(stderr,"Invalid Insert!\n");
}

void printList(List *namedList)
{
  int i=0;
  if (namedList->data[0] != NULL)
  {
    while ((namedList->data[i] != NULL)&&(i<MAX_SIZE))
    {
      fprintf(stderr,"%s,%d\n",namedList->data[i]->word, namedList->data[i]->weight);
      i++;
    }
  }
  else fprintf(stderr,"List is empty!!\n");
}

void InsertionSort(List *namedList)
{
  int j=1;
  int k=j;
  Entry *temp;
  while(j<namedList->size)
  {
    k=j;
    while ((k>0) && (strcmp(namedList->data[k-1]->word,namedList->data[k]->word))>0)
    {
      temp=namedList->data[k-1];
      namedList->data[k-1]=namedList->data[k];
      namedList->data[k]=temp;
      
      k=k-1;
      temp=NULL;
      free(temp);
    }
    j=j+1;
  } 
}

void InsertionSortWeight(List *namedList)
{
  int j=1;
  int k=j;
  Entry *temp;
  while(j<namedList->size)
  {
    k=j;
    while ((k>0) && ((namedList->data[k-1]->weight)<(namedList->data[k]->weight)))
    {
      temp=namedList->data[k-1];
      namedList->data[k-1]=namedList->data[k];
      namedList->data[k]=temp;
      
      k=k-1;
      temp=NULL;
      free(temp);
    }
    j=j+1;
  } 
}

int find(List *namedList, char *queryWord, int qWlen)
{
  int i=0;
  
  for (i=0;i<namedList->size;i++)
  {
    if(strncmp(namedList->data[i]->word,queryWord,qWlen)==0)
    {
      return 1;
    }
  }
  return 0;
}

int findFirst(List *namedList, char *queryWord, int qWlen)
{
  int firstP=0;

  while((strncmp(namedList->data[firstP]->word,queryWord,qWlen)!=0)&&(namedList->data[firstP]!=NULL))
  {
    firstP=firstP+1;
  }
  return firstP;
}

int findLast(List *namedList, char *queryWord, int qWlen)
{
  int lastP=namedList->size-1;
  while((strncmp(namedList->data[lastP]->word,queryWord,qWlen)!=0)&&(namedList->data[lastP]!=NULL))
  {
    lastP=lastP-1;
  }
  return lastP;
}

/*----------------------------------------------------------------*/
/*----------------------------------------------------------------*/


int main(int argc, char **argv) {
  char *inputFilePath = argv[1]; //this keeps the path to input file
  char *queryWord = argv[2]; // this keeps the query word
  int lineCount=0; //this variable will tell us how much memory to allocate
  int firstPos=0;
  int lastPos=0;
  int qWlen=strlen(queryWord);
  int qMatches=0;
  int inList=0;
  
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

  /*---Allocate memory for structure. Review function from prj 1 ---*/
  List *origList;
  origList = initList(lineCount);
  /*----------------------------------------------------------------*/

  //Read the file once more, this time to fill in the data into memory
  fseek(fp, 0, SEEK_SET);// rewind to the beginning of the file, before reading it line by line.
  char word[BUFSIZE]; //to be used for reading lines in the loop below
  int weight;
  for(int i = 0; i < lineCount; i++)
  {
    fscanf(fp, "%s %d\n",word,&weight);

    /*----------------------------------------------------------------*/
    /*---Fill list---*/
    if (i==0)
    {
      insertToHead(origList,word,weight);
    }
    else
    {
      insertToTail(origList,word,weight);
    }

  }
  /*----------------------------------------------------------------*/
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
  /*---Sort list---*/
  InsertionSort(origList);

  /*---Get new list matching user input given in *queryWord---*/
  /*---Create new list---*/

  if ((inList=find(origList, queryWord, qWlen)) == 1)
  {
    firstPos=findFirst(origList,queryWord,qWlen);
    lastPos=findLast(origList,queryWord,qWlen);

    qMatches=(lastPos-firstPos)+1;
    List *autoList;
    autoList = initList(qMatches);

    for(int i = firstPos, j=0; i < (lastPos+1); i++,j++)
    {
      /*---Fill autoList---*/
      if (j==0)
      {
        insertToHead(autoList,origList->data[i]->word,origList->data[i]->weight);
      }
      else
      {
        insertToTail(autoList,origList->data[i]->word,origList->data[i]->weight);
      }

    }
    InsertionSortWeight(autoList);
    printList(autoList);
    free(autoList);
  }
  else
  {
    fprintf(stderr,"No suggestion!\n");
  }
  /*----------------------------------------------------------------*/
  /*----------------------------------------------------------------*/

  free(origList);
  
  /*----------------------------------------------------------------*/

  return 0;
}
