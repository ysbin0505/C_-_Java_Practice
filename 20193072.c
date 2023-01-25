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

const char filePath[500];		//sprintf 이용하여 -i 에서 받아온 것으로 덮어씌울예정 
FILE* fp;	//받아온 파일 

void string2hexString(char* input, char* output)		//16진수 문자열 만들기 
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

struct linked{			//주소와 데이터 값 연결리스트 
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
    fclose(fp);						//입력받은 파일 전체를 출력 
    
    //to opcode
    fp = fopen(buf, "r");
    file_op_code_len = 0;
    while(EOF!=fscanf(fp, "%s %s %s", file_op_code[file_op_code_len].label, file_op_code[file_op_code_len].opcode, file_op_code[file_op_code_len].operand)){	//마지막 값 한번더 나와서 EOF 사용 
        file_op_code_len++;
    }
    fclose(fp);
}								//label opcde operand 나눠서 저장 

void symtable(){
    printf("The contents of Symbol Table :\n\n");
    char str[20];
    char targets[4][6] = { "RESW","WORD","RESB","BYTE"};
    int i;
    int startAddress = 0;
    int currentAddress = 0;
    int check = 0;					//중복되면 주소값 더이상 안올라가게 설정 but 오류였다 
    for(i=0;i<file_op_code_len;i++){
        if(strcmp(file_op_code[i].opcode,"END") != 0){
            before_last = currentAddress - startAddress;		//T^시작주소^before_last 
        }
        for(int j=0;j<4;j++){									//2중포문으로 출력 
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


void programlength(){			//프로그램 길이 출력 
    int i;
    char str[20];
    int check = 0;				//마찬가지 
    for(i=0;i<file_op_code_len;i++){
        if(strcmp(file_op_code[i].opcode, "START") == 0){
            strcpy(str,file_op_code[i].operand);		//str에 opcode가 start인 operand값 저장 
            startAddress = atoi(str);					//int형으로 변환해서 저장 
            endAddress = startAddress;					//계속 증가시킬 것이기 때문에 
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
    printf("\n\nLength of the input program is %d.\n\n", endAddress-startAddress);		//길이 출력 
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
            printf("%s %s %s\n",file_op_code[i].label, file_op_code[i].opcode,file_op_code[i].operand);	//첫 줄 출력하고 
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

void charIntToAddress(char * output, int currentAddress, int size){	//오브젝트 출력만들 때 사용. 문자형 숫자를 int형 주소로 변환 
    char start[100];
    int address = currentAddress;		//받은 주소를 address에 저장 
    for(int i=0;i<size;i++){		//받은 사이즈, 자릿수 
        start[i] = '0';
    }
    int current = size - 1;		//자릿수 맞추기 위해 
    while(address > 0){ 
        start[current--] = address % 10 + '0';	//한자리씩 없어지게 때문에 결국 0이되어 벗어남 
        address = address / 10;
    }
    start[size] = '\0';
    sprintf(output, "%s", start);
}

void objectFile(){
    printf("Object Program has been generated.\n\n");
    printf("Object Program:\n\n");
    char left[100];
    charIntToAddress(left, startAddress, 6);			//H^ 출력하기위해 
    char right[100];
    charIntToAddress(right, endAddress, 6);
    int isFirst = 0;	//befor_last 값 재발 방지를 위해 사용 
    
    printf("H^%s^%s^%s\n",file_op_code[0].label,left,right);	//시작주소부터 마지막주소까지 
    char mnemonic[4][6] = { "LDA","WORD","RESW","BYTE"};
    printf("T^00");		//시작주소를 4자리로 받았기 때문에 앞에 00붙임 
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
                    charIntToAddress(temp, startAddress, 4);	//T^00시작주소(4자리) 
                    isFirst = 1;	//재발방지 
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
    
    cA = startAddress;		//재선언 
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
            int t = 0;	//16진수 출력에 사용 
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
            for(int x=2;x<6;x++){	//CHARZ 부분 출력 
                if(file_op_code[i].operand[x]!='\''){
                    buf[t++] =file_op_code[i].operand[x];
                }else{
                    buf[t++] ='\0';	//멈춰라 
                }
            }
            string2hexString(buf,current->datas);	//현제 데이터 값 
            cA += 1;
        }else if(strcmp(file_op_code[i].opcode, "RESB") == 0){
            char t[100];
            charIntToAddress(t, cA, 4);
            printf("%s^%s",t, "00");
            charIntToAddress(temp->address, loc, 4);
            cA += 1* atoi(file_op_code[i].operand);			//바이트는 1씩증가 
        }else if(strcmp(file_op_code[i].opcode, "RESW") == 0){
            cA += 3 * atoi(file_op_code[i].operand);	//word는 3 * 수만큼 , 문자로 선언되어있기 때문에 atoi사용 
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
    current = root;			//CHAR BYTE C'EOF' -> 16진수로 출력 
    while(current!=NULL){
        printf("%s",current->address);
        struct linked * sameAddress = current;
        while(sameAddress!=NULL){
            printf("^%s",sameAddress->datas);
            sameAddress = sameAddress->sameAddressNext;
        }
        current = current->next;
    }
    printf("\nE^%s\n",left);	//시작주소 
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

