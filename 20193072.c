#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include <unistd.h>

#define MAX_LEN 1000
#define max 1000
#define _CRT_SECURE_NO_WARNINGS

int startAddress = 0;
int endAddress = 0;

char buf[MAX_LEN];	
char code[10][10], code1[4][3] = { "33","44","53","57" };
char mnemonic1[4][5] = { "LDA","STA","LDCH","STCH" };

const char filePath[500];		//sprintf �̿��Ͽ� -i ���� �޾ƿ� ������ ����￹�� 
FILE* fp;	//�޾ƿ� ���� 

void string2hexString(char* input, char* output)		//16���� ���ڿ� ����� 
{
    int loop = 0;
    int i = 0;
    
    while(input[loop] != '\0')		
    {
        sprintf((char*)(output+i),"%02X", input[loop]);
        loop+=1;
        i+=2;
    }
    output[i++] = '\0';		     //insert NULL at the end of the output string
}


struct astable{					//table for code
    char label[10];
    char opcode[10];
    char operand[10];
};
										
struct astable file_op_code[MAX_LEN];		//saved by file		
int file_op_code_len = 0;
int before_last = 0;

struct linked{			//�ּҿ� ������ �� ���Ḯ��Ʈ 
    char address[6];
    char datas[6];
    struct linked *sameAddressNext;
    struct linked *next;
};

struct linked *root;	

void txtfileAllRead(){
    printf("The contents of Input file:\n\n");
   
    char buffer[max] = {0, };
    fread(buffer, 1, max, fp);
    printf("%s", buffer);
    fclose(fp);						//�Է¹��� ���� ��ü�� ��� 
    
    //to opcode
    fp = fopen(buf, "r");
    file_op_code_len = 0;
    while(EOF!=fscanf(fp, "%s %s %s", file_op_code[file_op_code_len].label, file_op_code[file_op_code_len].opcode, file_op_code[file_op_code_len].operand)){	//������ �� �ѹ��� ���ͼ� EOF ��� 
        file_op_code_len++;
    }
    fclose(fp);
}								//label opcde operand ������ ���� 

void symtable(){
    printf("The contents of Symbol Table :\n\n");
    char str[20];
    char targets[4][6] = { "RESW","WORD","RESB","BYTE"};
    int i;
    int startAddress = 0;
    int currentAddress = 0;
    int check = 0;					//�ߺ��Ǹ� �ּҰ� ���̻� �ȿö󰡰� ���� but �������� 
    for(i=0;i<file_op_code_len;i++){
        if(strcmp(file_op_code[i].opcode,"END") != 0){
            before_last = currentAddress - startAddress;		//T^�����ּ�^before_last 
        }
        for(int j=0;j<4;j++){									//2���������� ��� 
            if(strcmp(file_op_code[i].opcode, targets[j]) == 0){
                printf("%s %d\n",file_op_code[i].label, currentAddress);
            }
        }
        if(strcmp(file_op_code[i].opcode, "START") == 0){
            strcpy(str,file_op_code[i].operand);
            startAddress = atoi(str);
            currentAddress = startAddress;
        }else if(strcmp(file_op_code[i].opcode, "BYTE") == 0){
            currentAddress += 1;
        }else if(strcmp(file_op_code[i].opcode, "RESB") == 0){
            currentAddress += 1* atoi(file_op_code[i].operand);
        }else if(strcmp(file_op_code[i].opcode, "RESW") == 0){
            currentAddress += 3* atoi(file_op_code[i].operand);
        }else if(strcmp(file_op_code[i].opcode, "LDCH") == 0){
            if(check == 0){
                currentAddress += 3;
            }
        }else if(strcmp(file_op_code[i].opcode, "STCH") == 0){
            if(check == 0){
                currentAddress += 3;
            }
            
        }else{
            currentAddress += 3;
        }
    }
}


void programlength(){			//���α׷� ���� ��� 
    int i;
    char str[20];
    int check = 0;				//�������� 
    for(i=0;i<file_op_code_len;i++){
        if(strcmp(file_op_code[i].opcode, "START") == 0){
            strcpy(str,file_op_code[i].operand);		//str�� opcode�� start�� operand�� ���� 
            startAddress = atoi(str);					//int������ ��ȯ�ؼ� ���� 
            endAddress = startAddress;					//��� ������ų ���̱� ������ 
        }
        else if(strcmp(file_op_code[i].opcode, "WORD") == 0)
            endAddress += 3;
        else if(strcmp(file_op_code[i].opcode, "BYTE") == 0)
            endAddress += 1;
        else if(strcmp(file_op_code[i].opcode, "RESW") == 0)
            endAddress += 3 *atoi(file_op_code[i].operand);
        else if(strcmp(file_op_code[i].opcode, "RESB") == 0)
            endAddress += 1 *atoi(file_op_code[i].operand) ;
        else if(strcmp(file_op_code[i].opcode, "LDCH") == 0){
            if(check == 0){
                endAddress += 3;
            }
        }else if(strcmp(file_op_code[i].opcode, "STCH") == 0){
            if(check == 0){
                endAddress += 3;
            }
        }else if(strcmp(file_op_code[i].opcode, "END") != 0){
            endAddress += 3;
        }
    }
    printf("\n\nLength of the input program is %d.\n\n", endAddress-startAddress);		//���� ��� 
}

void intermedFile(){
    printf("\n\nThe contents of Intermed File :\n\n");
    char str[20];
    int i;
    int startAddress = 0;
    int currentAddress = 0;
    int check = 0;
    for(i=0;i<file_op_code_len;i++){
        if(strcmp(file_op_code[i].opcode, "START") == 0){
            strcpy(str,file_op_code[i].operand);
            startAddress = atoi(str);
            currentAddress = startAddress;
            printf("%s %s %s\n",file_op_code[i].label, file_op_code[i].opcode,file_op_code[i].operand);	//ù �� ����ϰ� 
        }else if(strcmp(file_op_code[i].opcode, "BYTE") == 0){
            printf("%d %s %s %s\n", currentAddress, file_op_code[i].label, file_op_code[i].opcode,file_op_code[i].operand);
            currentAddress += 1;
        }else if(strcmp(file_op_code[i].opcode, "RESB") == 0){
            printf("%d %s %s %s\n", currentAddress, file_op_code[i].label, file_op_code[i].opcode,file_op_code[i].operand);
            currentAddress += 1* atoi(file_op_code[i].operand);
        }else if(strcmp(file_op_code[i].opcode, "RESW") == 0){
            printf("%d %s %s %s\n", currentAddress, file_op_code[i].label, file_op_code[i].opcode,file_op_code[i].operand);
            currentAddress += 3 * atoi(file_op_code[i].operand);
        }else if(strcmp(file_op_code[i].opcode, "LDCH") == 0){
            printf("%d %s %s %s\n", currentAddress, file_op_code[i].label, file_op_code[i].opcode,file_op_code[i].operand);
            if(check == 0){
                currentAddress += 3;
            }
        }else if(strcmp(file_op_code[i].opcode, "STCH") == 0){
            printf("%d %s %s %s\n", currentAddress, file_op_code[i].label, file_op_code[i].opcode,file_op_code[i].operand);
            if(check == 0){
                currentAddress += 3;
            }
        }else{
            printf("%d %s %s %s\n", currentAddress, file_op_code[i].label, file_op_code[i].opcode,file_op_code[i].operand);
            currentAddress += 3;
        }
    }
    printf("\n");
}

void charIntToAddress(char * output, int currentAddress, int size){	//������Ʈ ��¸��� �� ���. ������ ���ڸ� int�� �ּҷ� ��ȯ 
    char start[100];
    int address = currentAddress;		//���� �ּҸ� address�� ���� 
    for(int i=0;i<size;i++){		//���� ������, �ڸ��� 
        start[i] = '0';
    }
    int current = size - 1;		//�ڸ��� ���߱� ���� 
    while(address > 0){ 
        start[current--] = address % 10 + '0';	//���ڸ��� �������� ������ �ᱹ 0�̵Ǿ� ��� 
        address = address / 10;
    }
    start[size] = '\0';
    sprintf(output, "%s", start);
}

void objectFile(){
    printf("Object Program has been generated.\n\n");
    printf("Object Program:\n\n");
    char left[100];
    charIntToAddress(left, startAddress, 6);			//H^ ����ϱ����� 
    char right[100];
    charIntToAddress(right, endAddress, 6);
    int isFirst = 0;	//befor_last �� ��� ������ ���� ��� 
    
    printf("H^%s^%s^%s\n",file_op_code[0].label,left,right);	//�����ּҺ��� �������ּұ��� 
    char mnemonic[4][6] = { "LDA","WORD","RESW","BYTE"};
    printf("T^00");		//�����ּҸ� 4�ڸ��� �޾ұ� ������ �տ� 00���� 
    int cA = startAddress;
    for(int j=0;j<4;j++){
        cA = startAddress;
        int check = 0; 
        for(int i=0;i<file_op_code_len;i++){
            if(strcmp(file_op_code[i].opcode, "START") == 0){
                continue;
            }
            if(strcmp(file_op_code[i].opcode, mnemonic[j]) == 0){
                char temp[100];
                if(isFirst == 0){
                    charIntToAddress(temp, startAddress, 4);	//T^00�����ּ�(4�ڸ�) 
                    isFirst = 1;	//��߹��� 
                    printf("%s^%d^%s",temp, before_last, code1[j]);
                }else{
                    charIntToAddress(temp, cA, 4);
                    printf("%s^%s",temp, code1[j]);
                }
            }
        
            if(strcmp(file_op_code[i].opcode, "BYTE") == 0){
                cA += 1;
            }else if(strcmp(file_op_code[i].opcode, "RESB") == 0){
                cA += 1* atoi(file_op_code[i].operand);
            }else if(strcmp(file_op_code[i].opcode, "RESW") == 0){
                cA += 3 * atoi(file_op_code[i].operand);
            }else if(strcmp(file_op_code[i].opcode, "LDCH") == 0){
                if(check == 0){
                    cA += 3;
                }
            }else if(strcmp(file_op_code[i].opcode, "STCH") == 0){
                if(check == 0){
                    cA += 3;
                }
            }else{
                cA += 3;
            }
        }
    }
    
    cA = startAddress;		//�缱�� 
    int save = 0;
    struct linked *temp = NULL;
    struct linked *current = NULL;
    int check = 0;
    int loc = 0;
    for(int i=0;i<file_op_code_len;i++){
        if(strcmp(file_op_code[i].opcode, "START") == 0){
            continue;
        }
        if(strcmp(file_op_code[i].opcode, "BYTE") == 0){		//CHAR BYTE C'EOF'
            int t = 0;	//16���� ��¿� ��� 
            temp = malloc(sizeof(struct linked));
            if(root == NULL){
                root = temp;
                current = root;
            }else{
                current = root;
                current->sameAddressNext = temp;
                current = temp;
            }
            temp->next = NULL;
            temp->sameAddressNext = NULL;
            char buf[6];
            for(int x=2;x<6;x++){	//CHARZ �κ� ��� 
                if(file_op_code[i].operand[x]!='\''){
                    buf[t++] =file_op_code[i].operand[x];
                }else{
                    buf[t++] ='\0';	//����� 
                }
            }
            string2hexString(buf,current->datas);	//���� ������ �� 
            cA += 1;
        }else if(strcmp(file_op_code[i].opcode, "RESB") == 0){
            char t[100];
            charIntToAddress(t, cA, 4);
            printf("%s^%s",t, "00");
            charIntToAddress(temp->address, loc, 4);
            cA += 1* atoi(file_op_code[i].operand);			//����Ʈ�� 1������ 
        }else if(strcmp(file_op_code[i].opcode, "RESW") == 0){
            cA += 3 * atoi(file_op_code[i].operand);	//word�� 3 * ����ŭ , ���ڷ� ����Ǿ��ֱ� ������ atoi��� 
        }else if(strcmp(file_op_code[i].opcode, "WORD") == 0){
            loc = atoi(file_op_code[i].operand);
            cA += 3;
        }else if(strcmp(file_op_code[i].opcode, "LDCH") == 0){
            cA += 3;  
        }else if(strcmp(file_op_code[i].opcode, "STCH") == 0){
            cA += 3;
        }else{
            cA += 3;
        }
    }
    current = root;			//CHAR BYTE C'EOF' -> 16������ ��� 
    while(current!=NULL){
        printf("%s",current->address);
        struct linked * sameAddress = current;
        while(sameAddress!=NULL){
            printf("^%s",sameAddress->datas);
            sameAddress = sameAddress->sameAddressNext;
        }
        current = current->next;
    }
    printf("\nE^%s\n",left);	//�����ּ� 
    /**/
}
int main(int argc, char ** argv)
{
    char code[3][10];
    int opt = 0;
    sprintf(buf,"%s",filePath);
    fp = fopen(buf,"r");
    while((opt=getopt(argc,argv,"i:"))!=-1){
        switch(opt)
        {
            case 'i':
                sprintf(buf,"%s",optarg);
                fp = fopen(optarg,"r");
                break;
            default : printf("error\n"); break;
            
        }
    }
    
    txtfileAllRead();
    programlength();
    symtable();
    intermedFile();
    objectFile();
}

