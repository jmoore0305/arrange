# arrange
Summary:
Objective is to build a program called ``arrange'' that takes in a file
called inputfile and arranges it based on the 4-byte key in increasing
order (the remainder of the record should of course be kept with the
same key). Analysis of the algorithm used for sorting is in report.pdf.

Dependencies:
You will need a binary file labeled inputfile with 100 records, where
each record is divided up into two segments. The first segment is the
key which is the first 4 bytes of the record. The second segment is the
data tied to that key which is 96 bytes.

Instructions:
1. Use command: gcc -o arrange main.c
2. Use command: ./arrange -i inputfile, where inputfile is the binary file
you wish to have sorted
3. This program will take the binary file called inputfile and sort the
keys associated with their respective records and then write the result
to a text file called outputfile.txt with a readable format.
4. Check for the outputfile.txt file in the arrange folder to view
