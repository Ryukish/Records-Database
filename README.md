# Linked-List-Merge-sort

/*
Read in to linked list
The input has a fixed order

One record per Line (end with \n)

{id:1234567,first:Mary,last:Green,DOB:1996-10-03,GPA:4.0}
{id:1234568,first:Peter,last:White,DOB:1997-05-22,GPA:3.8}
{id:1654238,first:Nick,last:Park,DOB:1995-08-18,GPA:4.0}
{id:1234587,first:Katy,last:Green,DOB:1995-08-18,GPA:4.0}

ignore : { : ,
or
you can reuse them when you print out to file

struct student{
int id;
string first;
string last;
string DOB
double gpa;
}

use this to grab each line to the end of file
while (getline, str)
same ID = duplicated record
update with the latter one (update with the later one)
if somebody's name has more than one word, the separator would be underline "_"
No empty values will be given in the columns
no other character or space will be given(no need for me to check)

----------------------------------------------------------------------------------------

Adding record (use the information of that record)
deleting record (delete id)

----------------------------------------------------------------------------------------

sort
types of sorts
ID
FIRST name
LAST name
DOB (yyyy-mm-dd)
GPA (double)
(all case sensitive)

If two or more records by passing all commands have same order, the one
with lower id value should be outputted first.

----------------------------------------------------------------------------------------

output to file
Output should be based on the sequence of commands
commands top -> bottom (sort from the previous sort)
output line end with \n


*/
