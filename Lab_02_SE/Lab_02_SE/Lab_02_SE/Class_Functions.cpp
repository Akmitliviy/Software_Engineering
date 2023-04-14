#include "Header.h"

//The SetStruct function takes in a double pointer to an SBook structure and a pointer to a string. 
//The function parses the string using strtok and assigns the values to the fields of the dynamically allocated SBook structure.
void SetStruct(SBook** pp_sbFirstBook, char* pString) {
	char* pToken = NULL;

	SBook* p_sbTempBook = new SBook;

	if (!p_sbTempBook) {
		cout << "\n\nSorry, can't allocate the memory\n\n";
	}
	else {

		pToken = strtok(pString, "\t");
		strcpy(p_sbTempBook->mAuthor, pToken);

		pToken = strtok(NULL, "\t");
		strcpy(p_sbTempBook->mBook, pToken);

		pToken = strtok(NULL, "\t");
		p_sbTempBook->mYear = atoi(pToken);

		pToken = strtok(NULL, "\t");
		p_sbTempBook->mPages = atoi(pToken);

		pToken = strtok(NULL, "\t");
		p_sbTempBook->mPrice = atoi(pToken);

		p_sbTempBook->mNext = nullptr;

		if (!*pp_sbFirstBook) {
			*pp_sbFirstBook = p_sbTempBook;
		}
		else {
			SBook* p_sbRunner = *pp_sbFirstBook;
			while (p_sbRunner->mNext) {
				p_sbRunner = p_sbRunner->mNext;
			}
			p_sbRunner->mNext = p_sbTempBook;
		}
	}
}

//--------------------------------------------------------------------------------

// This function displays a linked list of SBook structures.
void Show(SBook* p_sbFirstBook) {
	cout << "\n\n\tAuthor\t\t\tBook\t\t\t\t\tYear\tPages\tPrice\n\n\n";

	for (; p_sbFirstBook; p_sbFirstBook = p_sbFirstBook->mNext) {
		printf( "%-20s \t%-35s\t\t%d\t%d\t%d\n\n", p_sbFirstBook->mAuthor, p_sbFirstBook->mBook, p_sbFirstBook->mYear,
			p_sbFirstBook->mPages, p_sbFirstBook->mPrice);
	}
}

//--------------------------------------------------------------------------------


// This function sorts a linked list of SBook structures in descending order
// based on the price of the book and alphabetical order of book names.
void Sort(SBook** pp_sbFirstBook) {
	SBook* p_sbElement = *pp_sbFirstBook;
	SBook sbTempBook;
	SBook* p_sbBooksMinusOne = NULL;
	int nAveragePrice = 0, nCounter = 0;

	// Calculate the average price of books
	for (p_sbElement = *pp_sbFirstBook; p_sbElement->mNext; p_sbElement = p_sbElement->mNext) {
		nAveragePrice += p_sbElement->mPrice;
		nCounter++;
	}
	nAveragePrice /= nCounter;

	// Perform bubble sort on linked list
	for (int i = 0; i < nCounter - 1; i++) {
		for (int j = nCounter - 1; j > i + 1; j--) {
			p_sbElement = GetConcrete(*pp_sbFirstBook, j);
			p_sbBooksMinusOne = GetConcrete(*pp_sbFirstBook, j - 1);

			if (p_sbElement->mPrice > nAveragePrice && strcmp(p_sbElement->mBook, p_sbBooksMinusOne->mBook) < 0) {
				sbTempBook = *p_sbBooksMinusOne;
				*p_sbBooksMinusOne = *p_sbElement;
				p_sbBooksMinusOne->mNext = sbTempBook.mNext;
				sbTempBook.mNext = p_sbElement->mNext;
				*p_sbElement = sbTempBook;
			}
		}
	}
	cout << "\n\nList was successfully sorted!\n\n";
}

//--------------------------------------------------------------------------------

// This function returns a pointer to the book with index "index" in the list
// "SFirstBook" of books
SBook*	GetConcrete(SBook* sbFirstBook, int nIndex) {
	SBook* p_sbElement = NULL;
	if (nIndex > 0)
		p_sbElement = sbFirstBook;
		while (--nIndex > 0) {
			p_sbElement = p_sbElement->mNext;
		}
	return p_sbElement;
}

//--------------------------------------------------------------------------------

//Deletes an element from the linked list of SBook.
void DeleteElement(SBook** pp_sbFirstBook, int nIndex) {
	// Declare and initialize variables
	SBook* p_sbElement = *pp_sbFirstBook;
	SBook* p_sbPrevBook = p_sbElement;

	// Check if index is valid
	if (nIndex <= 0) {
		cout << "WARNING: You entered the wrong index";
		return;
	}

	// Traverse the linked list to find the element to delete
	while (--nIndex) {

		if (p_sbElement->mNext == NULL) {
			cout << "WARNING: You entered the wrong index";
			return;
		}

		p_sbPrevBook = p_sbElement;
		p_sbElement = p_sbElement->mNext;

	}

	// Delete the element
	if (p_sbElement->mNext == NULL) {
		p_sbPrevBook->mNext = NULL;
		free(p_sbElement);
		p_sbElement = NULL;
	}
	else if (p_sbElement == *pp_sbFirstBook) {
		*pp_sbFirstBook = p_sbElement->mNext;
		free(p_sbElement);
		p_sbElement = NULL;
	}
	else {
		p_sbPrevBook->mNext = p_sbElement->mNext;
		free(p_sbElement);
		p_sbElement = NULL;
	}

	cout << "\n\nElement was successfully deleted!\n\n";
}


//--------------------------------------------------------------------------------

// This function adds a new element to the linked list of SBook structs
void AddElement(SBook** pp_sbFirstBook) {
	SBook* p_sbNewElement = new SBook;
	SBook* p_sbElement = *pp_sbFirstBook;
	SBook* p_sbPrevBook = nullptr;
	int iIndex = 0;
	bool bBadIndex = false;

	getchar();
	cout << "\nPlease, enter author's name: ";
	gets_s(p_sbNewElement->mAuthor);
	cout << "\nPlease, enter book's name: ";
	gets_s(p_sbNewElement->mBook);
	cout << "\nPlease, enter book's year: ";
	cin >> p_sbNewElement->mYear;
	cout << "\nPlease, enter number of pages: ";
	cin >> p_sbNewElement->mPages;
	cout << "\nPlease, enter book's price: ";
	cin >> p_sbNewElement->mPrice;

	cout << "\nPlease, enter index where I should paste your element: ";
	cin >> iIndex;

	if (iIndex <= 0)
		bBadIndex = true;

	while (--iIndex > 0 && !bBadIndex) {
		p_sbPrevBook = p_sbElement;
		p_sbElement = p_sbElement->mNext;
	}

	if (!pp_sbFirstBook && iIndex)
		bBadIndex = true;

	if (bBadIndex) {
		cout << "WARNING: You entered the wrong index";
		return;
	}

	if (p_sbElement == nullptr) {
		*pp_sbFirstBook = p_sbNewElement;
	}
	else if (p_sbElement == *pp_sbFirstBook) {
		p_sbNewElement->mNext = p_sbElement;
		*pp_sbFirstBook = p_sbNewElement;
	}
	else {
		p_sbNewElement->mNext = p_sbElement;
		p_sbPrevBook->mNext = p_sbNewElement;
	}

	cout << "\n\nElement was successfully added!\n\n";
}


//--------------------------------------------------------------------------------

// This function deletes all the books from the linked list whose year is less than 2000 and whose book name starts with "P", "K" or "L"
void DeletePKL(SBook** p_sbFirstBook) {
	const int N_YEAR{ 2000 };

	SBook* sbElement = *p_sbFirstBook;
	SBook* sbPrevBook = *p_sbFirstBook;
	char p[3] = "P";
	char k[3] = "K";
	char l[3] = "L";

	while (sbElement) {
		
		if (sbElement->mYear < N_YEAR && !(strncmp(sbElement->mBook, p, 1) && strncmp(sbElement->mBook, k, 1) && strncmp(sbElement->mBook, l, 1))) {

			if (sbElement->mNext == NULL) {
				sbPrevBook->mNext = sbElement->mNext;
				free(sbElement);
				sbElement = NULL;
				continue;
			}
			else if (sbElement == *p_sbFirstBook) {
				*p_sbFirstBook = sbElement->mNext;
				free(sbElement);
				sbElement = *p_sbFirstBook;
				continue; 
			}
			else { 
				sbPrevBook->mNext = sbElement->mNext; 
				free(sbElement); 
				sbElement = sbPrevBook->mNext; 
				continue; 
			}
		}

		sbPrevBook = sbElement;
		sbElement = sbElement->mNext;
	}

	cout << "\n\nElements were successfully deleted!\n\n";
}


//--------------------------------------------------------------------------------

//This function returns a pointer to the last element of a singly - linked list of SBook nodes
SBook* GetLast(SBook* p_sbFirstBook) {
	SBook* p_sbElement = p_sbFirstBook;

	while (p_sbElement->mNext) {
		p_sbElement = p_sbElement->mNext;
	}

	return p_sbElement;
}


//--------------------------------------------------------------------------------

// This function is used to print the linked list of SBooks into a file with the provided path.
void Print(SBook* p_sbFirstBook) {
	char path[STR];

	cout << "\n\nEnter path: ";
	cin >> path;
	FILE* fFile = fopen(path, "w");

	for (; p_sbFirstBook; p_sbFirstBook = p_sbFirstBook->mNext) {
		fprintf(fFile, "%-20s \t%-35s\t\t%d\t%d\t%d\n\n", p_sbFirstBook->mAuthor, p_sbFirstBook->mBook, p_sbFirstBook->mYear,
			p_sbFirstBook->mPages, p_sbFirstBook->mPrice);
	}

	cout << "\n\nElement was saved successfully!\n\n";
}


//void AddToEnd(SBook** SElement, SBook** SFirstBook) {
//	SBook* SNewElement = malloc(sizeof(SBook));
//
//	while ((*SElement)->mNext) {
//		*SElement = (*SElement)->mNext;
//	}
//
//	getchar();
//
//	cout << "\nPlease, enter author's name: ");
//	gets(SNewElement->mAuthor);
//	cout << "\nPlease, enter book's name: ");
//	gets(SNewElement->mBook);
//	cout << "\nPlease, enter book's year: ");
//	cin >> "%d", &SNewElement->mYear);
//	cout << "\nPlease, enter number of pages: ");
//	cin >> "%d", &SNewElement->mPages);
//	cout << "\nPlease, enter book's price: ");
//	cin >> "%d", &SNewElement->mPrice);
//	SNewElement->mNext;
//
//	(*SElement)->mNext = SNewElement;
//}
//void GetLast(SBook** SElement) {
//	while ((*SElement)->mNext) {
//		*SElement = (*SElement)->mNext;
//	}
//}
//int deleteNetElement(SBook* pEl) {
//	int iRes = 0;
//	do {
//		if (!pEl || !pEl->mNext) {
//			break;
//		}
//		SBook* pBook = pEl;
//		pEl->mNext = pEl->mNext->mNext;
//		free(pBook);
//		iRes = 1;
//	} while (0);
//
//	return iRes;
//}
