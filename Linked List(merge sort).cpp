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
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include"ArgumentManager.h"

using namespace std;

struct student {
	string id;
	string first;
	string last;
	string dob;
	string gpa;
	student* next;
};
class list {
private:
	student * head;
public:
	list() {
		head = NULL;
	}
	void readin(const char* fileNameA) {
		head = new student;
		student* temp = head;
		student* searchthis = head;
		ifstream input(fileNameA);
		string finalline, temp1, temp2, temp3, temp4;
		string datatemp[5];
		int i = 0;

		if (input.is_open()) {

			while (getline(input, temp1)) {
				//basic line

				if (temp1[0] == 'd') {
					int k = 0;
					int position;
					k = temp1.length();
					string searchfor;
					for (int l = 7; l < k; ++l) {
						char c = temp1[l];
						searchfor += c;
					}

					position = searchdelete(&searchthis, searchfor);
					if (position == 1) {
						temp = searchthis;
					}
					else if (position == 2) {
						head = searchthis;
					}
				}
				else {
					stringstream ss1(temp1);
					i = 0;
					while (getline(getline(ss1, temp2, '{'), temp3, '}')) { //line without brackets
						stringstream ss2(temp3);
						while (getline(getline(ss2, temp4, ':'), finalline, ',')) { //removes : and , then stores into a string array
							datatemp[i] = finalline;
							++i;
						}
					}
					//splits the data up to linked 
					head->id = datatemp[0];
					head->first = datatemp[1];
					head->last = datatemp[2];
					head->dob = datatemp[3];
					head->gpa = datatemp[4];
					head->next = new student;
					head = head->next;
					head->id = "0";
				}
			}
			head->next = NULL;
			head = temp;

		}

	}


	void splitter(student* head, student** a, student** b) {

		student* temp;
		temp = head;
		student* forward;
		student* back;
		if (head == NULL || head->next == NULL) {
			*a = temp;
			*b = NULL;
		}
		else {
			back = temp;
			forward = temp->next;

			while (forward != NULL) {

				forward = forward->next;
				if (forward != NULL) {
					back = back->next;
					forward = forward->next;
				}
			}
			//if list was 1 4 5 6 7 6 then
			*a = temp;// front of the list   1 4 5
			*b = back->next;//back of the list  6 7 6
			back->next = NULL;
		}
	}

	void mergeID(student** tempHead) {
		student* temhead = *tempHead;
		student* a = NULL;
		student* b = NULL;
		int i = 0;
		if (temhead == NULL || temhead->next == NULL) {
			return;
		}

		splitter(temhead, &a, &b);
		mergeID(&a);
		mergeID(&b);
		*tempHead = mergefinalID(a, b);
	}

	void mergeFirst(student** tempHead) {
		student* temhead = *tempHead;
		student* a = NULL;
		student* b = NULL;

		if (temhead == NULL || temhead->next == NULL) {
			return;
		}

		splitter(temhead, &a, &b);
		mergeFirst(&a);
		mergeFirst(&b);

		*tempHead = mergefinalFirst(a, b);
	}

	void mergeLast(student** tempHead) {
		student* temhead = *tempHead;
		student* a = NULL;
		student* b = NULL;

		if (temhead == NULL || temhead->next == NULL) {
			return;
		}

		splitter(temhead, &a, &b);
		mergeLast(&a);
		mergeLast(&b);

		*tempHead = mergefinalLast(a, b);
	}

	void mergeDOB(student** tempHead) {
		student* temhead = *tempHead;
		student* a = NULL;
		student* b = NULL;

		if (temhead == NULL || temhead->next == NULL) {
			return;
		}

		splitter(temhead, &a, &b);
		mergeDOB(&a);
		mergeDOB(&b);

		*tempHead = mergefinalDOBS(a, b);
	}

	void mergeGPA(student** tempHead) {
		student* temhead = *tempHead;
		student* a = NULL;
		student* b = NULL;

		if (temhead == NULL || temhead->next == NULL) {
			return;
		}

		splitter(temhead, &a, &b);
		mergeGPA(&a);
		mergeGPA(&b);

		*tempHead = mergefinalGPA(a, b);
	}

	student* mergefinalID(student* frontpart, student* backpart) {
		student* mergefinali = NULL;

		if (frontpart == NULL) {
			return backpart;
		}
		else if (backpart == NULL) {
			return frontpart;
		}
		if (frontpart->id <= backpart->id) {
			mergefinali = frontpart;
			mergefinali->next = mergefinalID(frontpart->next, backpart);
		}
		else {
			mergefinali = backpart;
			mergefinali->next = mergefinalID(frontpart, backpart->next);
		}
		return mergefinali;
	}

	student* mergefinalFirst(student* frontpart, student* backpart) {
		student* mergefinalf = NULL;
		string name1, tempname1, t1;
		string name2, tempname2, t2;
		string narr1[5];
		string narr2[5];
		int checkn1 = 0;
		int checkn2 = 0;
		int i = 0;
		int k = 0;
		int tell = 0;
		int length1, length2;
		int done = 0;

		if (frontpart == NULL) {
			return backpart;
		}
		else if (backpart == NULL) {
			return frontpart;
		}
		// use temp strings and .length() change the first letter to lower case
		tempname1 = frontpart->first;
		tempname1[0] = tolower(tempname1[0]);
		tempname2 = backpart->first;
		tempname2[0] = tolower(tempname2[0]);

		stringstream n1(tempname1);
		stringstream n2(tempname2);

		while (getline(n1, t1, '_')) {
			t1[0] = tolower(t1[0]);
			narr1[i] = t1;
			++i;
			checkn1 = 1;
		}
		if (checkn1 == 1) {
			name1 = narr1[0];
			for (int p = 1; p < 2; ++p) {
				name1 += narr1[p];
			}
		}
		while (getline(n2, t2, '_')) {
			t2[0] = tolower(t2[0]);
			narr2[k] = t2;
			++k;
			checkn2 = 1;
		}
		if (checkn2 == 1) {
			name2 = narr2[0];
			for (int o = 1; o < 2; ++o) {
				name2 += narr2[o];
			}
		}


		length1 = name1.length();
		length2 = name2.length();
		if (length1 == length2) {
			if (name1 == name2) {
				if (frontpart->id <= backpart->id) {
					tell = 0;
				}
				else {
					tell = 1;
				}
			}
		}
		if (name1[0] < name2[0]) {
			tell = 0;
		}
		else if (name2[0] < name1[0]) {
			tell = 1;
		}
		else if (length1 <= length2) {
			for (i = 0; i < length1; ++i) {
				while (name1[i] != name2[i]) {
					if (name1[i] < name2[i]) {
						tell = 0;
						done = 1;
					}
					else {
						tell = 1;
						done = 1;
					}
					break;
				}
				if (done == 1)
					break;
			}
		}
		else
		{
			for (int i = 0; i < length2; ++i) {
				while (name2[i] != name1[i]) {
					if (name2[i] < name1[i]) {
						tell = 1;
						done = 1;
					}
					else {
						tell = 0;
						done = 1;
					}
					break;
				}
				if (done == 1)
					break;
			}

		}



		if (tell == 0) {
			mergefinalf = frontpart;
			mergefinalf->next = mergefinalFirst(frontpart->next, backpart);
		}
		else {
			mergefinalf = backpart;
			mergefinalf->next = mergefinalFirst(frontpart, backpart->next);
		}
		return mergefinalf;



	}

	student* mergefinalLast(student* frontpart, student* backpart) {
		student* mergefinall = NULL;
		string name1, tempname1, t1;
		string name2, tempname2, t2;
		string narr1[5];
		string narr2[5];
		int checkn1 = 0;
		int checkn2 = 0;
		int i = 0;
		int k = 0;
		int tell = 0;
		int done = 0;
		int length1, length2;

		if (frontpart == NULL) {
			return backpart;
		}
		else if (backpart == NULL) {
			return frontpart;
		}
		// use temp strings and .length() change the first letter to lower case
		tempname1 = frontpart->last;
		tempname1[0] = tolower(tempname1[0]);
		tempname2 = backpart->last;
		tempname2[0] = tolower(tempname2[0]);

		stringstream n1(tempname1);
		stringstream n2(tempname2);

		while (getline(n1, t1, '_')) {
			t1[0] = tolower(t1[0]);
			narr1[i] = t1;
			++i;
			checkn1 = 1;
		}
		if (checkn1 == 1) {
			name1 = narr1[0];
			for (int p = 1; p < i; ++p) {
				name1 += narr1[p];
			}
		}
		while (getline(n2, t2, '_')) {
			t2[0] = tolower(t2[0]);
			narr2[k] = t2;
			++k;
			checkn2 = 1;
		}
		if (checkn2 == 1) {
			name2 = narr2[0];
			for (int o = 1; o < k; ++o) {
				name1 += narr1[o];
			}
		}

		length1 = name1.length();
		length2 = name2.length();
		if (length1 == length2) {
			if (name1 == name2) {
				if (frontpart->id <= backpart->id) {
					tell = 0;
				}
				else {
					tell = 1;
				}
			}
		}
		if (name1[0] < name2[0]) {
			tell = 0;
		}
		else if (name2[0] < name1[0]) {
			tell = 1;
		}
		else if (length1 <= length2) {
			for (i = 0; i < length1; ++i) {
				while (name1[i] != name2[i]) {
					if (name1[i] < name2[i]) {
						tell = 0;
						done = 1;
					}
					else {
						tell = 1;
						done = 1;
					}
					break;
				}
				if (done == 1)
					break;
			}
		}
		else
		{
			for (int i = 0; i < length2; ++i) {
				while (name2[i] != name1[i]) {
					if (name2[i] < name1[i]) {
						tell = 1;
						done = 1;
					}
					else {
						tell = 0;
						done = 1;
					}
					break;
				}
				if (done == 1)
					break;
			}

		}

		if (tell == 0) {
			mergefinall = frontpart;
			mergefinall->next = mergefinalLast(frontpart->next, backpart);
		}
		else {
			mergefinall = backpart;
			mergefinall->next = mergefinalLast(frontpart, backpart->next);
		}

		return mergefinall;
	}

	student* mergefinalDOBS(student* frontpart, student* backpart) {
		student* mergefinalD = NULL;
		string date1, year1, month1, day1;
		string date2, year2, month2, day2;
		string dobarray1[3];
		string dobarray2[3];
		int i = 0;
		int j = 0;
		int tell;

		if (frontpart == NULL) {
			return backpart;
		}
		else if (backpart == NULL) {
			return frontpart;
		}

		stringstream dob1(frontpart->dob);
		stringstream dob2(backpart->dob);

		while (getline(dob1, date1, '-')) {
			dobarray1[i] = date1;
			++i;
			while (getline(dob2, date2, '-')) {
				dobarray2[j] = date2;
				++j;
			}
		}

		year1 = dobarray1[0];
		month1 = dobarray1[1];
		day1 = dobarray1[2];

		year2 = dobarray2[0];
		month2 = dobarray2[1];
		day2 = dobarray2[2];
		if (year1 == year2) {
			if (month1 == month2) {
				if (day1 == day2) {
					if (frontpart->id < backpart->id) {
						tell = 0;
					}
					else {
						tell = 1;
					}
				}
				else if (day2 < day1) {
					tell = 1;
				}
				else {
					tell = 0;
				}
			}
			else if (month1 < month2) {
				tell = 0;
			}
			else if (month2 < month1) {
				tell = 1;
			}
		}
		else if (year1 < year2) {
			tell = 0;
		}
		else if (year2 < year1) {
			tell = 1;
		}

		if (tell == 0) {
			mergefinalD = frontpart;
			mergefinalD->next = mergefinalDOBS(frontpart->next, backpart);
		}
		else {
			mergefinalD = backpart;
			mergefinalD->next = mergefinalDOBS(frontpart, backpart->next);
		}

		return mergefinalD;

	}

	student* mergefinalGPA(student* frontpart, student* backpart) {
		student* mergefinalG = NULL;
		double f;
		double b;


		if (frontpart == NULL) {
			return backpart;
		}
		else if (backpart == NULL) {
			return frontpart;
		}
		stringstream f1(frontpart->gpa);
		stringstream b1(backpart->gpa);
		f1 >> f;
		b1 >> b;
	
		if ((f - b) < 0.001) {
			if (frontpart->id < backpart->id) {
				mergefinalG = frontpart;
				mergefinalG->next = mergefinalGPA(frontpart->next, backpart);
			}
			else {
				mergefinalG = backpart;
				mergefinalG->next = mergefinalGPA(frontpart, backpart->next);
			}
		}
		else if (f<b) {
			mergefinalG = frontpart;
			mergefinalG->next = mergefinalGPA(frontpart->next, backpart);
		}
		else {
			mergefinalG = backpart;
			mergefinalG->next = mergefinalGPA(frontpart, backpart->next);
		}
		return mergefinalG;
	}

	void sort(const char* sortFile) {
		ifstream sortby(sortFile);
		string whatToSort;
		student* th;
		th = head;
		if (head == NULL) {}
		else {
			list::mergeID(&th);
			head = th;
			list::deleteid();
			head = th;

			while (getline(sortby, whatToSort)) {
				student* tempsort;
				tempsort = head;
				if (whatToSort == "id") { //low to high merge sort
					mergeID(&tempsort);
					head = tempsort;
				}
				else if (whatToSort == "first") { //a to z
					mergeFirst(&tempsort);
					head = tempsort;
				}
				else if (whatToSort == "last") { //a to z
					mergeLast(&tempsort);
					head = tempsort;
				}
				else if (whatToSort == "DOB") {//OLD TO YOUNG merge sort
					mergeDOB(&tempsort);
					head = tempsort;
				}
				else if (whatToSort == "GPA") {//low to high merge sort
					mergeGPA(&tempsort);
					head = tempsort;
				}
			}
		}
	}

	void deleteid() {
		student* save;
		save = head;
		student* check = NULL;
		student* check1 = NULL;
		student* check2 = NULL;
		student* change;
		int place = 0;

		if (head == NULL || head->next == NULL) {
			return;
		}
		else {
			check = head;
			check1 = head;
			check2 = head->next;
			while (check2 != NULL) {
				if (check1->id == check2->id) {
					if (place == 0) {
						change = head;
						head = head->next;
						check = head;
						check1 = head;
						check2 = head->next;
						delete change;
					}
					else {
						change = check1;
						check->next = check1->next;
						check1 = check;
						delete change;
						place = 0;
					}
				}
				else {
					if (place == 0) {
						check1 = check1->next;
						check2 = check2->next;
						++place;
					}
					else {
						check = check->next;
						check1 = check1->next;
						check2 = check2->next;
						++place;
					}
				}
			}

		}
		head = save;
	}

	int searchdelete(student** thead, string lookfor) {
		student* thehead = *thead;
		student* check = NULL;
		student* check1 = NULL;
		student* change;
		if (thehead == NULL) {
			return 3;
		}
		else if (thehead->next->id == "0") {
			if (thehead->id == lookfor) {
				change = thehead;
				thehead = thehead->next;
				delete change;
				return 2;
			}
			else {
				return 0;
			}
		}

		if (thehead->id == lookfor) {
			change = thehead;
			thehead = thehead->next;
			*thead = thehead;
			delete change;
			return 1;

		}
		check = thehead;
		check1 = thehead->next;
		while (check1->id != "0") {
			if (check1->id == lookfor) {
				change = check1;
				check->next = check1->next;
				delete change;
				return 0;
			}
			else {
				check = check->next;
				check1 = check1->next;
			}
		}
		return 0;
	}

	void print(const char* outfilenameB) {
		ofstream outToFile(outfilenameB);
		head = head->next;
		if (head->id == "0") {
			outToFile << "error";
		}
		else {
			while (head != NULL) {
				outToFile << "{id:" << head->id << ",first:" << head->first << ",last:" << head->last << ",DOB:" << head->dob << ",GPA:" << head->gpa << "}" << endl;
				head = head->next;
			}
		}
	}

};

int main(int argc, char* argv[]) {

	ArgumentManager clparse(argc, argv);


	string infilenameA = clparse.get("input");
	string outfilenameB = clparse.get("output");
	string sortFile = clparse.get("sort");

	list thelist;

	thelist.readin(infilenameA.c_str());
	thelist.sort(sortFile.c_str());
	thelist.print(outfilenameB.c_str());

	return 0;

}