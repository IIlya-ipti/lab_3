#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

struct List {
	List* next = NULL;
	long long number;
	char* fam;
		
};

List* Search(List* s, char* fam) {
	// Search element in map
	List* p1 = s,*p2=s->next;
	while (p2 != NULL) {
		if (!strcmp(fam,p2->fam)) {
			break;
		}
		p1 = p2;
		p2 = p2->next;
	}
	if (p2 != NULL) {
		p1->next = p2->next;
		p2->next = s->next;
		s->next = p2;
	}
	return p2;
}
void Add(List* s, List* b) {
	// add element to list
	List* p = s;
	while (p->next != NULL){
		p = p->next;
		if (!strcmp(p->fam, b->fam)) {
			p->number = b->number;
			delete b;
			return;
		}
	}
	p->next = b;
}
struct Map {
	List* s = NULL;
};

Map* InitialMap() {
	// Initialization map
	Map* s = new Map[26];
	for (int i = 0; i < 26; i++) {
		s[i].s = new List;
	}
	return s;
}
void Add_to_Map(Map*s, List* d) {
	// add element to map
	Add(s[d->fam[0] - 97].s, d);
}

void Add_to_Map(Map* s, char* sur, long long number) {
	// add element to map
	List* new_node = new List;
	new_node->fam = sur;
	new_node->number = number;
	Add_to_Map(s, new_node);
}


void PrintList(List*s) {
	// Print list
	List* pl = s->next;
	while (pl != NULL) {
		cout << pl->number << ' ' << pl->fam << ' ';
		pl = pl->next;
	}
	cout << endl;
}

void PrintMap(Map* map) {
	//Print Map
	for (int i = 0; i < 26; i++) {
		cout << i << " --- " << endl;
		PrintList(map[i].s);
	}

}
List* SearchMap(Map* map, char* fam) {
	// search element in map
	return Search(map[fam[0] - 97].s, fam);
}


bool DeleteNode(List*s,char* fum) {
	// delete element in list
	List* p1 = s->next, *p2 = s;
	while (p1 != NULL) {
		if (!strcmp(p1->fam, fum)) {
			p2->next = p1->next;
			delete p1;
			return true;
		}
		p2 = p1;
		p1 = p1->next;
	}
	return false;
}
bool DeleteNode(Map*map,char* fum) {
	// delete element in map
	return DeleteNode(map[fum[0] - 97].s, fum);
}

void swap_(List* a, List* b) {
	char* c = a->fam;
	long long nm = a->number;
	a->fam = b->fam;
	a->number = b->number;
	b->fam = c;
	b->number = nm;
}
void Sort(List* s) {
	//sort list
	List* p1 = s->next;
	List* p2;
	while (p1 != NULL) {
		p2 = p1->next;
		while (p2 != NULL) {
			if (strcmp(p2->fam,p1->fam) < 0) {
				swap_(p2, p1);
			}
			p2 = p2->next;
		}
		p1 = p1->next;
	}
	
}
char BUFFER[100];
void read_file(Map* map, FILE* f) {
	long long num;
	char* word;
	while (!feof(f)) {
		fscanf(f, "%s", &BUFFER);
		fscanf(f, "%lld", &num);
		word = new char[strlen(BUFFER) + 1];
		strcpy(word, BUFFER);
		Add_to_Map(map, word, num);
	}
}
void write_file(List* s, FILE* f) {
	List* p = s->next;
	while (p != NULL) {
		fwrite(p->fam, sizeof(char), strlen(p->fam), f);
		fprintf(f, "%c", ' ');
		fprintf(f, "%lld", p->number);
		fprintf(f, "%c", '\n');
		p = p->next;
		
	}
}
void write_file(Map* map, FILE* f) {
	for (int i = 0; i < 26; i++) {
		write_file(map[i].s, f);
	}
}
void Sort(Map* map) {
	 // sort all lists
	for (int i = 0; i < 26; i++) {
		Sort(map[i].s);
	}
}
int main()
{
	char a[10][10]{
		"abaaaaafa",
		"acaaaaaea",
		"adaaaaada",
		"aeaaaaaca",
		"afaaaaaba",
		"agaaaaaaa",
		"ahaaaaaae",
		"aiaaaaaad",
		"ajaaaaaac",
		"akaaaaaab"
	};
	char b[10][10]{
		"baaaaaafa",
		"baaaaaaea",
		"baaaaaada",
		"baaaaaaca",
		"baaaaaaba",
		"baaaaaaaa",
		"baaaaaaae",
		"baaaaaaad",
		"baaaaaaac",
		"baaaaaaab"
	};
	// create book
	Map* map = InitialMap();

	// add to book (point of book,string,number phone)
	for (int i = 0; i < 10; i++) {
		Add_to_Map(map, a[i], i);
	}
	for (int i = 0; i < 10; i++) {
		Add_to_Map(map, b[i], i);
	}

	// Print a book
	PrintMap(map);

	//Search in book surname
	SearchMap(map, b[9]);

	PrintMap(map);

	//delete info by pointer
	DeleteNode(map, a[1]);
	PrintMap(map);

	//Sort book
	Sort(map);
	PrintMap(map);

	//read book by file(txt)
	FILE* f;
	f = fopen("TextFile1.txt", "r");
	if (f != NULL) {
		read_file(map, f);
		fclose(f);
	}
	else {
		printf("Not read file \n");
	}

	PrintMap(map);

	//write book to file

	f = fopen("text.txt", "w");
	if (f != NULL) {
		write_file(map, f);
	}
	else {
		cout << "NOT WRITE FILE";
	}
	fclose(f);

	f = fopen("text.txt", "r");
	
	read_file(map, f);
	PrintMap(map);

	return 0;
}


