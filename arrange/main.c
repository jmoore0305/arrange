#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "sort.h"

//Written by Justin Moore
//CS 317
//This program will be run as follows
//1. Use command: gcc -o arrange main.c
//2. Use command: ./arrange -i inputfile, where inputfile is the binary file you wish to have sorted
//3. This program will take the binary file called inputfile and sort the keys associated with their respective
//   records and then write the result to a text file called outputfile.txt with a readable format.
//4. Check for the outputfile.txt file in the arrange folder.


// function to swap elements
void swap(unsigned int *a, unsigned int *b) {
  unsigned int t = *a;
  *a = *b;
  *b = t;
}

// function to find the partition position
int partition(struct __rec_t recordsArray[], int low, int high) {

  // select the rightmost element as pivot
  int pivot = recordsArray[high].key;

  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {

    if (recordsArray[j].key <= pivot) {

      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;

      // swap element at i with element at j

      swap(&recordsArray[i].key, &recordsArray[j].key);
    }
  }

  // swap the pivot element with the greater element at i
  swap(&recordsArray[i + 1].key, &recordsArray[high].key);

  // return the partition point
  return (i + 1);
}

void quickSort(struct __rec_t recordsArray[], int low, int high) {
  if (low < high) {
    // find the pivot element such that
    // elements smaller than pivot are on left of pivot
    // elements greater than pivot are on right of pivot
    int pi = partition(recordsArray, low, high);

    // recursive call on the left of pivot
    quickSort(recordsArray, low, pi - 1);

    // recursive call on the right of pivot
    quickSort(recordsArray, pi + 1, high);
  }
}

void usage(char *prog)
{
    fprintf(stderr, "usage error");
    exit(1);
}

//main program
int main(int argc, char* argv[])
{
    char *inFile = "/no/such/file";
	struct __rec_t recordsArray[100];

    // input params
    int c;
    opterr = 0;
    while ((c = getopt(argc, argv, "i:")) != -1) {
        switch (c) {
        case 'i':
            inFile = strdup(optarg);
            break;
        default:
            usage(argv[0]);
        }
    }




    // open and create output file
    int fd = open(inFile, O_RDONLY);
    if (fd < 0) {
	perror("open");
	exit(1);
    }

    int count = 0;
    rec_t r;
    while (1) {
        int rc;
        rc = read(fd, &r, sizeof(rec_t));
        if (rc == 0) // 0 indicates EOF
            break;
        if (rc < 0) {
            perror("read");
            exit(1);
        }

        //store in array
        recordsArray[count] = r;
        count ++;
    }






    //call sort function here
    int n;

    n = sizeof(recordsArray) / sizeof(recordsArray[0]);

    quickSort(recordsArray, 0, n - 1);





    //write all this stuff to outputfile
    FILE *fp;

    fp = fopen("outputfile.txt", "w+");

    int q;
    int k;
    rec_t theRecord;
    for(q = 0; q < 100; q++)
    {
        theRecord = recordsArray[q];


        fprintf(fp, "Key: %i ", theRecord.key);

        fprintf(fp, "Rec: ");
        for (k = 0; k < NUMRECS; k++)
            fprintf(fp, "%i ", theRecord.record[k]);
        fprintf(fp, "\n");
    }

    //closing outputfile
    fclose(fp);
    //closing inputfile
    (void) close(fd);








    return 0;
}
