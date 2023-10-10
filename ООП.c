#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 200

typedef struct Candy {
	char *name;
	/*char *producer;*/
	struct Fabric* linkFabric;
	int production;
	int year;
	float price;
	float weight;
	int* parameters;
	struct Candy* prev;
	struct Candy* next;
};

typedef struct Fabric {
	char* name;
	struct Fabric* prev;
	struct Fabric* next;
};

int getLenString(char* str) {
	int i = 0;
	while (str[i]) {
		i++;
	}
	i--;
	return(i);
}

int getCountSeparator(char* str) {
	int i;
	int	separatorCount = 0;
	for (i = 0; i < getLenString(str); i++) {
		if (str[i] == ';') {
			separatorCount++;
		}
	}
	return separatorCount;
}

struct Fabric* setNewFabricElement(char** text, struct Fabric* head) {
    struct Fabric* temp;
	if (head == NULL) {
		struct Fabric* temp;
		temp = (struct Fabric*)malloc(sizeof(struct Fabric));
		/*pFabric->name = (char*)malloc(getLenString(text[1]) * sizeof(char));*/
		temp->name = text[1];
		temp->next = NULL;
		temp->prev = NULL;
		head = temp;
		return head;
	}
	else {
		struct Fabric* p = head;
		while (p->next != NULL) {
			if (!strcmp(text[1], p->name)) {
				return head;
			}
			p = p->next;
		}

		temp = (struct Fabric*)malloc(sizeof(struct Fabric));
		temp->name = text[1];
		temp->next = NULL;
		p->next = temp;
		temp->prev = p;
		return head;
	}
}

char** setMemoryForWords(char* str) {
	int i;
	int	separatorCount = getCountSeparator(str);
	char** words = (char**)malloc((separatorCount) * sizeof(char*));
	if (words != NULL) {
		for (i = 0; i < separatorCount; ++i) {
			words[i] = (char*)malloc(getLenString(str) * sizeof(char));
		}
	}
	else {
		puts("Memory allocation error");
	}
	return words;
}

char** split(char* str) {
	int i;
	int laterNumber = 0;
	int wordNumber = 0;
	int lenStr = getLenString(str);
	char** words = setMemoryForWords(str);

	for (i = 0; i < lenStr; i++) {
		if (str[i] != ';') {
			words[wordNumber][laterNumber] = str[i];
			laterNumber++;
		}
		else {
			words[wordNumber][laterNumber] = '\0';
			wordNumber++;
			laterNumber = 0;
		}
	}
	return words;
}

struct Fabric* getDataFabric() {
    char** text;
	struct Fabric* head = NULL;
	FILE* file;
	char str[MAX_LEN];
	file = fopen("dataa.csv", "r");


	if (file != NULL) {
		while (fgets(str, MAX_LEN, file) != NULL) {
			text = split(str);
			head = setNewFabricElement(text, head);
		}
	}
	else {
		puts("File no open");
	}
	return head;
}

struct Fabric* getLink(char** text, struct Fabric* pFabric) {

	struct Candy* p = NULL;
	p = (struct Candy*)malloc(sizeof(struct Candy));
	while (pFabric != NULL) {

		if (!strcmp(text[1], pFabric->name)) {
			p->linkFabric = pFabric;
			break;
		}
		pFabric = pFabric->next;
	}
	return p->linkFabric;
}

struct Candy* setCandy(char** text, struct Fabric* headFabric) {
	struct Fabric* pFabric = headFabric;
	struct Candy* p = NULL;

	p = (struct Candy*)malloc(sizeof(struct Candy));
	p->parameters = (int*)malloc(4 * sizeof(int));
	p->name = text[0];
	p->linkFabric = getLink(text, pFabric);
	p->production = atoi(text[2]);
	p->year = atoi(text[3]);
	p->price = atof(text[4]);
	p->weight = atof(text[5]);
	p->parameters[0] = atoi(text[6]);
	p->parameters[1] = atoi(text[7]);
	p->parameters[2] = atoi(text[8]);
	p->parameters[3] = atoi(text[9]);

	return p;
}

struct Candy* setNewCandyElement(char** text, struct Candy* head, struct Fabric* headFabric) {
    struct Candy* temp;
	if (head == NULL) {
		struct Candy* temp;
		temp = (struct Candy*)malloc(sizeof(struct Candy));
		/*pFabric->name = (char*)malloc(getLenString(text[1]) * sizeof(char));*/
		temp = setCandy(text, headFabric);
		temp->next = NULL;
		temp->prev = NULL;
		head = temp;
		return head;
	}
	else {
		struct Candy* p = head;
		while (p->next != NULL) {
			p = p->next;
		}

		temp = (struct Candy*)malloc(sizeof(struct Candy));
		temp = setCandy(text, headFabric);
		temp->next = NULL;
		p->next = temp;
		temp->prev = p;
		return head;
	}
}

struct Candy *getDataCandy(struct Fabric *headFabric) {
	char** text;
	struct Candy *head = NULL;
	FILE* file;
	char str[MAX_LEN];
	file = fopen("dataa.csv", "r");


	if (file != NULL) {
		while (fgets(str, MAX_LEN, file) != NULL) {
			text = split(str);
			head = setNewCandyElement(text, head, headFabric);
		}
	}
	else {
		puts("File no open");
	}
	return head;
}

struct Candy* getLastCandy(struct Candy* head) {
	struct Candy* p = NULL;
	p = head;
	while (p->next != NULL) {
			p = p->next;
	}
	return p;
}

struct Fabric* getLastFabric(struct Fabric* head) {
	struct Fabric* p = NULL;
	p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p;
}

struct Fabric* deleteFabricFirst(struct Fabric* headFabric) {

	struct Fabric* p = headFabric;
	headFabric = headFabric->next;
	headFabric->prev = NULL;
	free(p);
	return headFabric;
}

struct Fabric* deleteFabricLast(struct Fabric* lastFabric) {
	struct Fabric* p = lastFabric;
	lastFabric = lastFabric->prev;
	lastFabric->next = NULL;
	free(p);
	return lastFabric;
}

void deleteFabricMiddle(struct Fabric* pFabric) {
	struct Fabric* pNext = pFabric->next;
	struct Fabric* pPrev = pFabric->prev;
	pNext->prev = pFabric->prev;
	pPrev->next = pFabric->next;
	free(pFabric);
}

struct Fabric* deleteFabric(struct Fabric* headFabric, struct Fabric* lastFabric) {
	struct Fabric* pFabric = headFabric;
	char str[MAX_LEN];

	printf("Write Fabric name for delete: ");
	fgets(str, MAX_LEN, stdin);
	str[strlen(str) - 1] = '\0';
	while (pFabric != NULL) {
		if (!strcmp(pFabric->name, str)) {
			if (pFabric == headFabric) {
				headFabric = deleteFabricFirst(headFabric);

				return headFabric;
			}
			if (pFabric == lastFabric) {
				lastFabric = deleteFabricLast(lastFabric);

				return headFabric;
			}
			deleteFabricMiddle(pFabric);
			return headFabric;
		}
		pFabric = pFabric->next;
	}
	return headFabric;
}

struct Candy* deleteCandyFirst(struct Candy* headCandy) {

	struct Candy* p = headCandy;
	headCandy = headCandy->next;
	headCandy->prev = NULL;
	free(p);
	return headCandy;
}

struct Candy* deleteCandyLast(struct Candy* lastCandy) {
	struct Candy* p = lastCandy;
	lastCandy = lastCandy->prev;
	lastCandy->next = NULL;
	free(p);
	return lastCandy;
}

void deleteCandyMiddle(struct Candy* pCandy) {
	struct Candy* p = pCandy;
	struct Candy* pNext = pCandy->next;
	struct Candy* pPrev = pCandy->prev;
	pNext->prev = pCandy->prev;
	pPrev->next = pCandy->next;
	free(p);
}

struct Candy* deleteCandy(struct Candy* headCandy, struct Candy* lastCandy) {
	struct Candy* pCandy = headCandy;
	struct Candy* pTemp;



	while (pCandy != NULL) {


		if (strstr(pCandy->linkFabric->name, "0") && (pCandy == headCandy)) {

			pCandy = pCandy->next;
			headCandy = deleteCandyFirst(headCandy);
			continue;
		}
		if (strstr(pCandy->linkFabric->name, "0") && (pCandy == lastCandy)) {

			lastCandy = deleteCandyLast(lastCandy);
			pCandy = NULL;
			continue;
		}
		if (strstr(pCandy->linkFabric->name, "0")) {

			pTemp = pCandy->next;
			deleteCandyMiddle(pCandy);
			pCandy = pTemp;
			continue;
		}
		pCandy = pCandy->next;

	}
	return headCandy;
}

void viewCandyReverse(struct Candy* head) {
	struct Candy* p = head;


	printf("\n\n| %16s | %16s | %16s | %16s | %16s | %16s | %s\n", "name", "producer", "production", "year", "price", "weight", "parameters");
	printf("| %16s | %16s | %16s | %16s | %16s | %16s | %s\n", "________________", "________________", "________________",
		"________________", "________________", "________________", "________________");


	while (p != NULL) {
		printf("| %16s | %16s | %16d | %16d | %16.3f | %16.3f | %4d %4d %4d %4d \n",
			p->name, p->linkFabric->name, p->production, p->year,
			p->price, p->weight, p->parameters[0],
			p->parameters[1], p->parameters[2], p->parameters[3]);
		p = p->prev;
	}
}

void viewCandy(struct Candy* head) {
	struct Candy* p = head;


	printf("| %16s | %16s | %16s | %16s | %16s | %16s | %s\n", "name", "producer", "production", "year", "price", "weight", "parameters");
	printf("| %16s | %16s | %16s | %16s | %16s | %16s | %s\n", "________________", "________________", "________________",
		"________________", "________________", "________________", "________________");


	while (p != NULL) {
		printf("| %16s | %16s | %16d | %16d | %16.3f | %16.3f | %4d %4d %4d %4d \n",
			p->name, p->linkFabric->name, p->production, p->year,
			p->price, p->weight, p->parameters[0],
			p->parameters[1], p->parameters[2], p->parameters[3]);
		p = p->next;
	}
}

int main() {

	struct Fabric* headFabric = NULL, * lastFabric = NULL;
	struct Candy *headCandy = NULL, * lastCandy = NULL;

	headFabric = getDataFabric();
	lastFabric = getLastFabric(headFabric);

	headCandy = getDataCandy(headFabric);
	lastCandy = getLastCandy(headCandy);

	viewCandy(headCandy);
	viewCandyReverse(lastCandy);

	headFabric = deleteFabric(headFabric, lastFabric);
	lastFabric = getLastFabric(headFabric);

	headCandy = deleteCandy(headCandy, lastCandy);
	lastCandy = getLastCandy(headCandy);

    viewCandy(headCandy);
	viewCandyReverse(lastCandy);

	getchar();
	return 0;
}
