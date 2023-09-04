	#define _CRT_SECURE_NO_WARNINGS
	#include<stdio.h>
	#include<stdlib.h>
	#include<string.h>
	#define LINE_LENGTH 20	/* �ڵ� �� �ٴ� �ִ� ���� */
	#define SYMBOL_LENGTH 10	/* �ɺ� �̸��� �ִ� ���� */
	#define CONSTANT_LENGTH 10	/* ��� �̸��� �ִ� ���� */

	/* �ڷᱸ�� ����ü ���� */
	typedef struct lineList {	/* lineList ���� */
		char command[LINE_LENGTH];
		int adress;
		struct lineList* next;
	}lineList;
	typedef struct symbolList {	/* symbolList ���� */
		char name[SYMBOL_LENGTH];
		int adress;
		struct symbolList* next;
	}symbolList;
	typedef struct opcodeList {	/* opcodeList ���� */
		int opcode;
		char operandName[SYMBOL_LENGTH];
		int operandAdress;
		struct opcodeList* next;
	}opcodeList;
	typedef struct constantList {	/* sconstant_list ���� */
		char constant[CONSTANT_LENGTH];
		struct constantList* next;
	}constantList;

	/* �� �ڷᱸ���� head�� tail ���� */
	lineList* lineList_head = NULL;
	lineList* lineList_tail = NULL;
	symbolList* symbolList_head = NULL;
	symbolList* symbolList_tail = NULL;
	opcodeList* opcodeList_head = NULL;
	opcodeList* opcodeList_tail = NULL;
	constantList* constantList_head = NULL;
	constantList* constantList_tail = NULL;

	/* �� �ڷᱸ���� �޸� �Ҵ� �Լ� */
	lineList* line_alloc() { return (lineList*)malloc(sizeof(lineList)); }
	symbolList* symbol_alloc() { return (symbolList*)malloc(sizeof(symbolList)); }
	opcodeList* opcode_alloc() { return (opcodeList*)malloc(sizeof(opcodeList)); }
	constantList* constant_alloc() { return (constantList*)malloc(sizeof(constantList)); }

	/* �� �ڷᱸ���� ��� ���� �Լ� */

	/* lineList ���� �Լ� */
	void line_insert(char* newLine, int locctr) {
		lineList* newNode = line_alloc();

		/* ����� �޸� �Ҵ� ���н� �Լ� ���� */
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
	/* symbolList ���� �Լ� */
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
	/* opcodeList ���� �Լ� */
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
	/* Symbol�� �ּҸ� opcodeList�� operandAdress�� �����ϴ� �Լ� */
	void opcodeAdress_insert(char* symbolName, int symbolAdress) {
		opcodeList* curr = opcodeList_head;

		/* opcodeList���� symbol�� ���� operand�� �̸��� Ž���� �� symbol�� �ּҸ� ���� */
		while (curr != NULL) {
			if (strcmp(curr->operandName, symbolName) == 0) {
				curr->operandAdress = symbolAdress;
				return;
			}
			curr = curr->next;
		}
	}
	/* ����� 16������ ��ȯ�ϴ� �Լ� */
	char* constantToHex(char* constant) {
		char* constant_ptr = strtok(constant, " '");
		char hex[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
		static char hexConstant[] = "000000";
		int resultLength = strlen(hexConstant) - 1;

		/* ����� ���ڿ��� �� */
		if (strcmp(constant_ptr, "C") == 0) {	/* 'C'�� ������ ��� ���ڿ��� ���� */
			constant_ptr = strtok(NULL, "'\n");
			for (int i = strlen(constant_ptr) - 1; i >= 0; i--) {
				int c = (int)constant_ptr[i];	/* �� ���ھ� ASCII�ڵ�� ��ȯ */
				while (c >= 16) {
					int x = c % 16;
					c /= 16;
					hexConstant[resultLength--] = hex[x];
				}
				hexConstant[resultLength--] = hex[c];
			}
		}
		/* ����� ������ �� */
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
	/* constantList ���� �Լ� */
	void constant_insert(char* newConstant) {
		constantList* newNode = constant_alloc();
		char* hexConstant = constantToHex(newConstant);	/* ����� 16������ ��ȯ */
		if (newNode == NULL) {
			printf("Constant Node Allocation Failed.\n");
			return;
		}
		strcpy(newNode->constant, hexConstant);	/* 16������ ��ȯ�� ����� ���� */
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
	/* ��� �Լ� ���� */

	/* �ڵ� ��ü ��� */
	void printCode() {
		lineList* curr = lineList_head;

		printf("The contents of input file:\n\n");

		while (curr != NULL) {	
			printf("%s", curr->command);	/* lineList�� command�κи� ��� */
			curr = curr->next;
		}
		printf("\n\n");
	}
	/* �ڵ��� ���� ��� */
	void printLength(int codeLength) {
		printf("Length of the input program is %d.\n\n", codeLength);
	}
	/* Symbol Table ��� */
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
	/* Intermed File ��� */
	void printIntermedFile() {
		lineList* curr = lineList_head;

		printf("The contents of Intermed File:\n\n");

		while (curr != NULL) {
			if (curr->adress == -1) {	/* �ڵ��� ù��° ���� �ּҸ� ������� ���� */
				printf("%s", curr->command);
			}
			else {	/* lineList�� adress�� command�� �Բ� ��� */
				printf("%d", curr->adress);
				printf(" %s", curr->command);
			}
			curr = curr->next;
		}
		printf("\n\n");
	}
	/* Object File�� Header Record ��� �Լ� */
	void printHeaderRecord(char* codeName, int startAdress, int endAdress) {
		printf("H^%s^%06d^%06d\n", codeName, startAdress, endAdress);
	}
	/* Object File�� Text Record ��� �Լ� */
	void printTextRecord(int codeLength) {
		opcodeList* opcodeCurr = opcodeList_head;
		constantList* constantCurr = constantList_head;

		printf("T^%d", codeLength - 1);	/* **END**�� ������ �ڵ��� ���� ��� */

		/* opcodeList�κ��� ��ɾ�� Symbol�� �ּҽ��� ��� */
		while (opcodeCurr != NULL) {
			printf("^%d%d", opcodeCurr->opcode, opcodeCurr->operandAdress);
			opcodeCurr = opcodeCurr->next;
		}

		/* constantList�κ��� 16������ ��ȯ�� ����� ��� */
		while (constantCurr != NULL) {
			printf("^%s", constantCurr->constant);
			constantCurr = constantCurr->next;
		}
		printf("\n");
	}
	/* Object File�� End Record ��� �Լ� */
	void printEndRecord(int startAdress) {
		printf("E^%06d\n", startAdress);
	}
	/* Object Code ��� */
	void printObjectCode(char* codeName, int startAdress, int endAdress) {
		int codeLength = endAdress - startAdress;

		printf("Object Program has been generated.\n\n");
		printf("Object Program:\n\n");

		printHeaderRecord(codeName, startAdress, endAdress);	/* Header Record ��� */
		printTextRecord(codeLength);	/* Text Record ��� */
		printEndRecord(startAdress);	/* End Record ��� */
	}
	int main() {
		char opcode[10], operand[10], symbol[10];
		char code1[4][3] = { "33","44","53","57" };
		char mnemonic[6][6] = { "START","LDA","STA","LDCH","STCH","END" };
		char mnemonic1[4][5] = { "LDA","STA","LDCH","STCH" };
		char codeName[10];
		int codeLength, locctr = -1, lineCount = 1;

		FILE* fp = fopen("INPUT01.DAT", "r");

		/* ������ �о���µ� �����ϸ� ���α׷� ����. */
		if (fp == NULL) {
			printf("File Open Failed\n");
			return 0;
		}

		/* �ڵ� ��ü ��ĵ ���� */
		while (feof(fp) == 0) {
			char line[LINE_LENGTH];
			fgets(line, LINE_LENGTH, fp);
			line_insert(line, locctr);

			if (lineCount == 1) {	/* ù��° ���� ��� */
				char* startLine_ptr = strtok(line, " ");

				strcpy(codeName, startLine_ptr);	/* �ڵ��� �̸� ���� */

				startLine_ptr = strtok(NULL, " ");
				startLine_ptr = strtok(NULL, " ");

				locctr = atoi(startLine_ptr);	/* �ڵ��� ���� �ּ� ���� */

				lineCount++;
			}
			else {
				char* line_ptr = strtok(line, " \n");

				/* "**"�� ������ ��� */
				if ((strcmp(line_ptr, "**") == 0)) {
					char* instruction_ptr = line_ptr;
					instruction_ptr = strtok(NULL, " ");

					/* "**"�� �����ϵ�, �ڵ��� ������ ���� ��� */
					if (strcmp(instruction_ptr, mnemonic[5]) == 0) {}
					/* ���� ������ ��ɾ��� ��� */
					else {
						strcpy(opcode, instruction_ptr);
						instruction_ptr = strtok(NULL, " \n");
						strcpy(operand, instruction_ptr);

						locctr += 3;	/* ��ɾ��̹Ƿ� locctr�� 3BYTE �߰� */

						/* opcodeList�� ���� */
						if (strcmp(opcode, mnemonic1[0]) == 0) opcode_insert(atoi(code1[0]), operand, 0);
						else if (strcmp(opcode, mnemonic1[1]) == 0) opcode_insert(atoi(code1[1]), operand, 0);
						else if (strcmp(opcode, mnemonic1[2]) == 0) opcode_insert(atoi(code1[2]), operand, 0);
						else if (strcmp(opcode, mnemonic1[3]) == 0) opcode_insert(atoi(code1[3]), operand, 0);
					}
				}
				/* �ڵ尡 Symbol�� �����ϴ� ��� */
				else {
					strcpy(symbol, line_ptr);

					symbol_insert(symbol, locctr);	/* symbol�� �̸��� �ּҸ� symbolList�� ���� */
					opcodeAdress_insert(symbol, locctr);	/* symbol�� �ּڰ��� opcodeList�� ���� */

					char* storage_ptr = line_ptr;
					storage_ptr = strtok(NULL, " ");

					/* storage�� RESB�� ��� */
					if (strcmp(storage_ptr, "RESB") == 0) {
						storage_ptr = strtok(NULL, " ");
						int reserved_value = atoi(storage_ptr);

						locctr += reserved_value;	/* n���� BYTE ���� �� ���� �ּҿ� +n ���� */
					}
					/* storage�� RESW�� ��� */
					else if (strcmp(storage_ptr, "RESW") == 0) {
						storage_ptr = strtok(NULL, " ");
						int reserved_value = atoi(storage_ptr);

						locctr += 3 * reserved_value;	/* n���� WORD ���� �� ���� �ּҿ� 3*n ���� */
					}
					/* storage�� BYTE�� ��� */
					else if (strcmp(storage_ptr, "BYTE") == 0) {
						char* constant_ptr = storage_ptr;
						constant_ptr = strtok(NULL, " ");

						constant_insert(constant_ptr);	/* constantList�� ���� */

						locctr++;	/* 1BYTE ���� */
					}
					/* storage�� WORD�� ��� */
					else if (strcmp(storage_ptr, "WORD") == 0) {
						char* constant_ptr = storage_ptr;
						constant_ptr = strtok(NULL, " ");

						constant_insert(constant_ptr);	/* constantList�� ���� */

						locctr += 3;	/* 1WORD ����*/
					}
					/* ��ȿ���� ���� storage �Է� �� ���α׷� ���� */
					else {
						printf("Invalid Storage Name\n");
						return 0;
					}
				}
				lineCount++;	/* ���� ī��Ʈ ���� */
			}
		}
			
		/* ��� ��� �Լ��� */
		printCode();
		printLength(lineList_tail->adress - lineList_head->next->adress);
		printSymbolTable();
		printIntermedFile();
		printObjectCode(codeName, lineList_head->next->adress, lineList_tail->adress);

		return 0;
	}
