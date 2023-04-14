#include "Header.h"

int main() {

	char cSymbol;
	char sPath[STR];
	char sTempStr[STR];
	SBook* p_sbFirstBook = NULL;
	SBook* p_sbFree = NULL;

	cout << "Enter path of file with list: ";
	cin >> sPath;

	FILE* fFile = fopen(sPath, "r");

	while (!feof(fFile)) {
		fgets(sTempStr, STR, fFile);
		SetStruct(&p_sbFirstBook, sTempStr);
	}
	fclose(fFile);


	int nElementIndex = 0;
	int bIsOngoing = 1;
	getchar();
	while (bIsOngoing) {
		cout << "\n\nKeys: q - Quit, s - Show, o - Sort, a - Add, d - Delete, x - Delete books which names start with П К or Л\n\nPlease, choose option: ";
		cSymbol = getchar();

		switch (cSymbol){
		case 'o':
			Sort(&p_sbFirstBook);
			break;
		case 's':
			Show(p_sbFirstBook);
			break;
		case 'a':
			AddElement(&p_sbFirstBook);
			break;
		case 'd':
			cout << "\nEnter number of element: ";
			cin >> nElementIndex;
			DeleteElement(&p_sbFirstBook, nElementIndex);
			break;
		case 'x':
			DeletePKL(&p_sbFirstBook);
			break;
		case 'p':
			Print(p_sbFirstBook);
			break;
		case 'q':
			bIsOngoing = 0;
			if (p_sbFirstBook) {
				SBook* p_sbElement = p_sbFirstBook;
				while (p_sbElement) {
					p_sbFree = p_sbElement;
					p_sbElement = p_sbElement->mNext;
					free(p_sbFree);

				}
				p_sbFree = NULL;
				p_sbFirstBook = NULL;
			}
			break;
		default:
			cout << "Wrong character!";
			break;
		}

		getchar();
	}

	return 0;
}