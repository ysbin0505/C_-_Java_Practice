	#define _CRT_SECURE_NO_WARNINGS
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#define LINE_LENGTH 20	/* 코드 한 줄당 최대 길이 */
	#define SYMBOL_LENGTH 10	/* 심볼 이름의 최대 길이 */
	#define CONSTANT_LENGTH 10	/* 상수 이름의 최대 길이 */

	/* 자료구조 구조체 정의 */
	typedef struct lineList {	/* lineList 정의 */
		char command[LINE_LENGTH];
		int adress;
		struct lineList* next;
	}lineList;
	typedef struct symbolList {	/* symbolList 정의 */
		char name[SYMBOL_LENGTH];
		int adress;
		struct symbolList* next;
	}symbolList;
	typedef struct opcodeList {	/* opcodeList 정의 */
		int opcode;
		char operandName[SYMBOL_LENGTH];
		int operandAdress;
		struct opcodeList* next;
	}opcodeList;
	typedef struct constantList {	/* sconstant_list 정의 */
		char constant[CONSTANT_LENGTH];
		struct constantList* next;
	}constantList;

	/* 각 자료구조의 head나 tail 정의 */
	lineList* lineList_head = NULL;
	lineList* lineList_tail = NULL;
	symbolList* symbolList_head = NULL;
	symbolList* symbolList_tail = NULL;
	opcodeList* opcodeList_head = NULL;
	opcodeList* opcodeList_tail = NULL;
	constantList* constantList_head = NULL;
	constantList* constantList_tail = NULL;

	/* 각 자료구조의 메모리 할당 함수 */
	lineList* line_alloc() { return (lineList*)malloc(sizeof(lineList)); }
	symbolList* symbol_alloc() { return (symbolList*)malloc(sizeof(symbolList)); }
	opcodeList* opcode_alloc() { return (opcodeList*)malloc(sizeof(opcodeList)); }
	constantList* constant_alloc() { return (constantList*)malloc(sizeof(constantList)); }

	/* 각 자료구조의 노드 삽입 함수 */

	/* lineList 삽입 함수 */
	void line_insert(char* newLine, int locctr) {
		lineList* newNode = line_alloc();

		/* 노드의 메모리 할당 실패시 함수 종료 */
		if (newNode == NULL) {
			printf("Line Node Allocation Failed.\n");
			return;
		}
		strcpy(newNode->command, newLine);
		newNode->adress = locctr;
		newNode->next = NULL;
		if (lineList_head == NULL) {
			lineList_head = newNode;
			lineList_tail = newNode;
		}
		else {
			lineList_tail->next = newNode;
			lineList_tail = newNode;
		}
	}
	/* symbolList 삽입 함수 */
	void symbol_insert(char* newSymbolName, int newSymbolAdress) {
		symbolList* newNode = symbol_alloc();
		if (newNode == NULL) {
			printf("Symbol Node Allocation Failed.\n");
			return;
		}
		strcpy(newNode->name, newSymbolName);
		newNode->adress = newSymbolAdress;
		newNode->next = NULL;
		if (symbolList_head == NULL) {
			symbolList_head = newNode;
			symbolList_tail = newNode;
		}
		else {
			symbolList_tail->next = newNode;
			symbolList_tail = newNode;
		}
	}
	/* opcodeList 삽입 함수 */
	void opcode_insert(int newOpcode, char* newOperand, int newOperandAdress) {
		opcodeList* newNode = opcode_alloc();
		if (newNode == NULL) {
			printf("Opcode Node Allocation Failed.\n");
			return;
		}
		newNode->opcode = newOpcode;
		strcpy(newNode->operandName, newOperand);
		newNode->operandAdress = newOperandAdress;
		newNode->next = NULL;
		if (opcodeList_head == NULL) {
			opcodeList_head = newNode;
			opcodeList_tail = newNode;
		}
		else {
			opcodeList_tail->next = newNode;
			opcodeList_tail = newNode;
		}
	}
	/* Symbol의 주소를 opcodeList의 operandAdress에 대입하는 함수 */
	void opcodeAdress_insert(char* symbolName, int symbolAdress) {
		opcodeList* curr = opcodeList_head;

		/* opcodeList에서 symbol와 같은 operand의 이름을 탐색한 후 symbol의 주소를 삽입 */
		while (curr != NULL) {
			if (strcmp(curr->operandName, symbolName) == 0) {
				curr->operandAdress = symbolAdress;
				return;
			}
			curr = curr->next;
		}
	}
	/* 상수를 16진수로 변환하는 함수 */
	char* constantToHex(char* constant) {
		char* constant_ptr = strtok(constant, " '");
		char hex[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
		static char hexConstant[] = "000000";
		int resultLength = strlen(hexConstant) - 1;

		/* 상수가 문자열일 때 */
		if (strcmp(constant_ptr, "C") == 0) {	/* 'C'로 시작할 경우 문자열로 간주 */
			constant_ptr = strtok(NULL, "'\n");
			for (int i = strlen(constant_ptr) - 1; i >= 0; i--) {
				int c = (int)constant_ptr[i];	/* 한 문자씩 ASCII코드로 변환 */
				while (c >= 16) {
					int x = c % 16;
					c /= 16;
					hexConstant[resultLength--] = hex[x];
				}
				hexConstant[resultLength--] = hex[c];
			}
		}
		/* 상수가 정수일 때 */
		else {
			int intConstant = atoi(constant_ptr);
			while (intConstant >= 16) {
				int x = intConstant % 16;
				intConstant /= 16;
				hexConstant[resultLength--] = hex[x];
			}
			hexConstant[resultLength--] = hex[intConstant];
		}
		return hexConstant;
	}
	/* constantList 삽입 함수 */
	void constant_insert(char* newConstant) {
		constantList* newNode = constant_alloc();
		char* hexConstant = constantToHex(newConstant);	/* 상수를 16진수로 변환 */
		if (newNode == NULL) {
			printf("Constant Node Allocation Failed.\n");
			return;
		}
		strcpy(newNode->constant, hexConstant);	/* 16진수로 변환된 상수를 삽입 */
		newNode->next = NULL;
		if (constantList_head == NULL) {
			constantList_head = newNode;
			constantList_tail = newNode;
		}
		else {
			constantList_tail->next = newNode;
			constantList_tail = newNode;
		}
	}
	/* 출력 함수 정의 */

	/* 코드 전체 출력 */
	void printCode() {
		lineList* curr = lineList_head;

		printf("The contents of input file:\n\n");

		while (curr != NULL) {	
			printf("%s", curr->command);	/* lineList의 command부분만 출력 */
			curr = curr->next;
		}
		printf("\n\n");
	}
	/* 코드의 길이 출력 */
	void printLength(int codeLength) {
		printf("Length of the input program is %d.\n\n", codeLength);
	}
	/* Symbol Table 출력 */
	void printSymbolTable() {
		symbolList* curr = symbolList_head;

		printf("The contests of Symbol Table:\n\n");

		while (curr != NULL) {
			printf("%s", curr->name);
			printf("\t%d\n", curr->adress);
			curr = curr->next;
		}
		printf("\n");
	}
	/* Intermed File 출력 */
	void printIntermedFile() {
		lineList* curr = lineList_head;

		printf("The contents of Intermed File:\n\n");

		while (curr != NULL) {
			if (curr->adress == -1) {	/* 코드의 첫번째 줄은 주소를 출력하지 않음 */
				printf("%s", curr->command);
			}
			else {	/* lineList의 adress와 command를 함께 출력 */
				printf("%d", curr->adress);
				printf(" %s", curr->command);
			}
			curr = curr->next;
		}
		printf("\n\n");
	}
	/* Object File의 Header Record 출력 함수 */
	void printHeaderRecord(char* codeName, int startAdress, int endAdress) {
		printf("H^%s^%06d^%06d\n", codeName, startAdress, endAdress);
	}
	/* Object File의 Text Record 출력 함수 */
	void printTextRecord(int codeLength) {
		opcodeList* opcodeCurr = opcodeList_head;
		constantList* constantCurr = constantList_head;

		printf("T^%d", codeLength - 1);	/* **END**를 제외한 코드의 길이 출력 */

		/* opcodeList로부터 명령어와 Symbol의 주소쌍을 출력 */
		while (opcodeCurr != NULL) {
			printf("^%d%d", opcodeCurr->opcode, opcodeCurr->operandAdress);
			opcodeCurr = opcodeCurr->next;
		}

		/* constantList로부터 16진수로 변환된 상수를 출력 */
		while (constantCurr != NULL) {
			printf("^%s", constantCurr->constant);
			constantCurr = constantCurr->next;
		}
		printf("\n");
	}
	/* Object File의 End Record 출력 함수 */
	void printEndRecord(int startAdress) {
		printf("E^%06d\n", startAdress);
	}
	/* Object Code 출력 */
	void printObjectCode(char* codeName, int startAdress, int endAdress) {
		int codeLength = endAdress - startAdress;

		printf("Object Program has been generated.\n\n");
		printf("Object Program:\n\n");

		printHeaderRecord(codeName, startAdress, endAdress);	/* Header Record 출력 */
		printTextRecord(codeLength);	/* Text Record 출력 */
		printEndRecord(startAdress);	/* End Record 출력 */
	}
	int main() {
		char opcode[10], operand[10], symbol[10];
		char code1[4][3] = { "33","44","53","57" };
		char mnemonic[6][6] = { "START","LDA","STA","LDCH","STCH","END" };
		char mnemonic1[4][5] = { "LDA","STA","LDCH","STCH" };
		char codeName[10];
		int codeLength, locctr = -1, lineCount = 1;

		FILE* fp = fopen("INPUT01.DAT", "r");

		/* 파일을 읽어오는데 실패하면 프로그램 종료. */
		if (fp == NULL) {
			printf("File Open Failed\n");
			return 0;
		}

		/* 코드 전체 스캔 시작 */
		while (feof(fp) == 0) {
			char line[LINE_LENGTH];
			fgets(line, LINE_LENGTH, fp);
			line_insert(line, locctr);

			if (lineCount == 1) {	/* 첫번째 줄일 경우 */
				char* startLine_ptr = strtok(line, " ");

				strcpy(codeName, startLine_ptr);	/* 코드의 이름 추출 */

				startLine_ptr = strtok(NULL, " ");
				startLine_ptr = strtok(NULL, " ");

				locctr = atoi(startLine_ptr);	/* 코드의 시작 주소 추출 */

				lineCount++;
			}
			else {
				char* line_ptr = strtok(line, " \n");

				/* "**"로 시작할 경우 */
				if ((strcmp(line_ptr, "**") == 0)) {
					char* instruction_ptr = line_ptr;
					instruction_ptr = strtok(NULL, " ");

					/* "**"로 시작하되, 코드의 마지막 줄일 경우 */
					if (strcmp(instruction_ptr, mnemonic[5]) == 0) {}
					/* 현재 라인이 명령어일 경우 */
					else {
						strcpy(opcode, instruction_ptr);
						instruction_ptr = strtok(NULL, " \n");
						strcpy(operand, instruction_ptr);

						locctr += 3;	/* 명령어이므로 locctr에 3BYTE 추가 */

						/* opcodeList에 삽입 */
						if (strcmp(opcode, mnemonic1[0]) == 0) opcode_insert(atoi(code1[0]), operand, 0);
						else if (strcmp(opcode, mnemonic1[1]) == 0) opcode_insert(atoi(code1[1]), operand, 0);
						else if (strcmp(opcode, mnemonic1[2]) == 0) opcode_insert(atoi(code1[2]), operand, 0);
						else if (strcmp(opcode, mnemonic1[3]) == 0) opcode_insert(atoi(code1[3]), operand, 0);
					}
				}
				/* 코드가 Symbol로 시작하는 경우 */
				else {
					strcpy(symbol, line_ptr);

					symbol_insert(symbol, locctr);	/* symbol의 이름과 주소를 symbolList에 삽입 */
					opcodeAdress_insert(symbol, locctr);	/* symbol의 주솟값을 opcodeList에 대입 */

					char* storage_ptr = line_ptr;
					storage_ptr = strtok(NULL, " ");

					/* storage가 RESB인 경우 */
					if (strcmp(storage_ptr, "RESB") == 0) {
						storage_ptr = strtok(NULL, " ");
						int reserved_value = atoi(storage_ptr);

						locctr += reserved_value;	/* n개의 BYTE 예약 시 현재 주소에 +n 더함 */
					}
					/* storage가 RESW인 경우 */
					else if (strcmp(storage_ptr, "RESW") == 0) {
						storage_ptr = strtok(NULL, " ");
						int reserved_value = atoi(storage_ptr);

						locctr += 3 * reserved_value;	/* n개의 WORD 예약 시 현재 주소에 3*n 더함 */
					}
					/* storage가 BYTE인 경우 */
					else if (strcmp(storage_ptr, "BYTE") == 0) {
						char* constant_ptr = storage_ptr;
						constant_ptr = strtok(NULL, " ");

						constant_insert(constant_ptr);	/* constantList에 삽입 */

						locctr++;	/* 1BYTE 증가 */
					}
					/* storage가 WORD인 경우 */
					else if (strcmp(storage_ptr, "WORD") == 0) {
						char* constant_ptr = storage_ptr;
						constant_ptr = strtok(NULL, " ");

						constant_insert(constant_ptr);	/* constantList에 삽입 */

						locctr += 3;	/* 1WORD 증가*/
					}
					/* 유효하지 않은 storage 입력 시 프로그램 종료 */
					else {
						printf("Invalid Storage Name\n");
						return 0;
					}
				}
				lineCount++;	/* 라인 카운트 증가 */
			}
		}
			
		/* 결과 출력 함수들 */
		printCode();
		printLength(lineList_tail->adress - lineList_head->next->adress);
		printSymbolTable();
		printIntermedFile();
		printObjectCode(codeName, lineList_head->next->adress, lineList_tail->adress);

		return 0;
	}
