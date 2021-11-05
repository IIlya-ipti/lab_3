#include <iostream>
using namespace std;

struct List {
	List* next = NULL;
	int number;
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

void Add_to_Map(Map* s, char* sur, int number) {
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

int main()
{
	char o[6] = "abcdr";
	char a[10][10]{
		"aaaaaaafa",
		"aaaaaaaea",
		"aaaaaaada",
		"aaaaaaaca",
		"aaaaaaaba",
		"aaaaaaaaa",
		"aaaaaaaae",
		"aaaaaaaad",
		"aaaaaaaac",
		"aaaaaaaab"
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
	Map* map = InitialMap();
	for (int i = 0; i < 10; i++) {
		Add_to_Map(map, a[i], 200 + i);
	}
	PrintMap(map);
	for (int i = 0; i < 10; i++) {
		Add_to_Map(map, b[i], 210 + i);
	}
	Add_to_Map(map, o, 345);
	PrintMap(map);
	SearchMap(map, b[9]);
	PrintMap(map);
	DeleteNode(map, a[1]);
	PrintMap(map);

	return 0;
}


