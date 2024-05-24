//Christopher Deluigi
//Dr. Steinberg
//COP3223C Section 1
//Small Program 8

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LIMIT 50

typedef struct{
    char * fname; //first name
	char * lname; //last name
	char * show; //favorite show
}record_t;

record_t * createArray(int maxsize);
record_t * insert(record_t *myarray, int *maxsize, int *currentsize); 
void display(record_t *myarray, int currentsize);
record_t *doubleIt(record_t *arr, int size); 
int removeRecord(record_t *arr, int size, int index); 
void freeRecords(record_t *arr, int size); 

int main(void)
{
	int maxsize;

	printf("Enter a size for the dynamic array: ");
	scanf("%d", &maxsize);


	record_t *myarray = createArray(maxsize);
	
	int currentsize = 0;
	int option = -1;

	while(option != 0)
    {
        printf("What would you like to do?\n");
        printf("1: Insert a record\n");
        printf("2: Display records\n");
        printf("3: Remove record\n");
        printf("4: Exit\n");
        printf("Enter an option: ");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
                printf("Insert was selected...\n");
                myarray = insert(myarray, &maxsize, &currentsize);
                break;

            case 2:
                printf("Display was selected...\n");
                display(myarray, currentsize);
                break;

            case 3:
                printf("Remove was selected...\n");
                printf("Select an index of record to remove...\n");
                int index;
                scanf("%d", &index);
                currentsize = removeRecord(myarray,currentsize,index);
                break;

            case 4:
                printf("Exiting...\n");
                option = 0;
				break;

            default:
                printf("Invalid Selection...\n");

        }

    }
	
	freeRecords(myarray, currentsize);
	free(myarray);

	myarray = NULL;

	return 0;
}

record_t * createArray(int maxsize)
{
	record_t * arr = (record_t *) malloc(maxsize * sizeof(record_t));
	
	if(arr == NULL)
	{
		printf("malloc error in createArray...program exiting\n");
		exit(1);
	}
	
	return arr;
}



void display(record_t *myarray, int currentsize)
{
	printf("---------------------------------\n");

	for(int x = 0; x < currentsize; ++x)
	{
	    printf("myarray[%d].fname = %s\n", x, (x + myarray)->fname); //try it with myarray[x].name
		printf("myarray[%d].lname = %s\n", x, (x + myarray)->lname); //try it with myarray[x].name
		printf("myarray[%d].show = %s\n", x, (x + myarray)->show); //try it with myarray[x].show
	}

	printf("---------------------------------\n");
}

record_t *insert(record_t *myarray, int *maxsize, int *currectsize) ////function to insert a record
{
    if(*currectsize == *maxsize) //calls doubleit to get more space
    {
        printf("Array is full...Need to doubleIt...\n");
        
        int size = *maxsize;
        myarray = doubleIt(myarray, size);
        *maxsize = *maxsize * 2;
    }

    myarray[*currectsize].fname = (char *) malloc(sizeof(char) * LIMIT); //finds memory in the heap for each sting.
    myarray[*currectsize].lname = (char *) malloc(sizeof(char) * LIMIT);
    myarray[*currectsize].show = (char *) malloc(sizeof(char) * LIMIT);

    printf("Enter the first name: ");
    scanf("%s", myarray[*currectsize].fname); //takes in user input for first name

    printf("Enter the last name: ");
    scanf("%s", myarray[*currectsize].lname);//takes in user input for last name

    getc(stdin);

    printf("Enter favorite show: ");
    fgets(myarray[*currectsize].show, LIMIT,stdin);

    *currectsize = *currectsize + 1; //adds new value to *currentsize
    return myarray;
}

record_t *doubleIt(record_t *arr, int size)
{
    record_t *tempo = (record_t*) malloc(2 * size * sizeof(record_t)); //doubles the size of the array
    if(tempo == NULL) //checks to see if no memory was allocated
    {
        printf("malloc error in createArray...program exiting\n"); //prints fail statement
        exit(1);
    }
    for(int i=0; i<size; ++i) // copies old array to place of new array
        tempo[i] = arr[i]; 

    free(arr); //freeing the old array.

    return tempo;
}

int removeRecord(record_t *arr, int size, int index)
{                               //clears out what the user wants to be deleted, that current space so it may shift over correctly
    if(index<0 || index > size)
        printf("Invalid Index...\n");

    else
    {
        free(arr[index].fname);
        free(arr[index].lname);
        free(arr[index].show);
    

        for(index; index < size; index++) //shifts over and copies everything to the left
            arr[index] = arr[index +1];

        size = size -1;
    }
    return size;
}

void freeRecords(record_t *arr, int size) //clears out the last elements in the array
{
    for(int i=0; i<size; ++i)
    {
        free(arr[i].fname);
        free(arr[i].lname);
        free(arr[i].show);
    }
}