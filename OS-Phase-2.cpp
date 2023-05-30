/* B2_G1_Phase_2
1) Rajan Ner 
2) Ubed Shaikh
3) Sanket Patil
4) Omkar Nimase
5) Tejas Shinde 
*/

#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int flag = 0;
int currentLine ;


char M [300][4];
char IR [5];
char R [5];
int IC;
int C;
int SI;

struct PCB{
    char JID[5];
    int TTL;
    int TLL; 
};

int MOS();
void simulation();
void INIT();
void EXECUTE_USER_PROGRAM();
void START_EXECUTION();
void PD();
void GD();
void H();
void LR();
void SR();
void CR();
void BT();

struct PCB info;

int TTC;
int LLC;
int PI;
int TI;

int PTR;

int generated_no[100];
int generated_no_index;
int Program_card_couter;
int count=0;

int key[30];
int value[30];
int key_index;

int gen_address;
int message;
char str[100];

int T;

// void print_status(){
//     printf("\nPI : %d\n",PI);
//     printf("TI : %d\n",TI);
//     printf("TTC : %d\n",TTC);
//     printf("LLC : %d\n",LLC);
//     printf("Ic : %d\n",IC);
//     printf("T : %d\n",T);
//     printf("IR : %s\n",IR);
// }

//Allocate function to generate a random memory block
int Allocate(){
    srand(time(NULL));
    int address;
    int l=0;
    while(1){
        address = rand()%30;
        for(int i=0;i<=generated_no_index;i++){
        if(generated_no[i] == address){
            l=1;
            break;
        }
       
        }
        if(l==0){
            break;
        }
        else{
            l=0;
        }

    }

    generated_no_index++;
    generated_no[generated_no_index] = address;
    
    return address;
}

void print_generated_no(){
    printf("\n\n");
    for(int i=0;i<=generated_no_index;i++){
        printf("%d ",generated_no[i]);
    }
    printf("\n\n");
}

//print the memory block
void print_memory_block()
{
    printf("Memory block is:\n\n");
    printf("\n\n");
    int i,j;
    for(i=0;i<300;i++)
    {   if(i>=100) printf("%d  ",i);
        else if(i>=10 && i<100) printf("%d   ",i);
        else printf("%d    ",i);
        for(j=0;j<4;j++)
        {
            printf("|%c",M[i][j]);
        }
        
        printf("|\n");
        
    
    }
}

void print_instruction_register()
{
    int i;
    for(i=0;i<4;i++)
    {
        printf("%c",IR[i]);
    }
    printf("\n");
}

void print_general_purpose_register()
{
    int i;
    for(i=0;i<4;i++)
    {
        printf("%c",R[i]);
    }
    printf("\n");
}

int Address_Map(int IC ){
        if(IC%10 == 0 && IC!=0){
            count++;
        }
        int address=(M[PTR+count][2]-'0')*10+(M[PTR+count][3]-'0');
        address=address*10+IC%10;
        return address;
    
    }
    
int map(int add){
    if(IR[0]=='H' && IR[1]==' ' && IR[2]==' ' && IR[3]==' ') return 0;

    if(IR[0]=='B' && IR[1]=='T') return 0; 
    
    if(IR[2]-'0'<0 || IR[2]-'0'>9 || IR[3]-'0'<0 || IR[3]-'0'>9){
        PI=2;
        MOS();
        return 0;
    } 
    
    for(int i=0;i<=key_index;i++){
        if(key[i]==(add/10)*10){
            return (value[i])*10+add%10;
        }
    }
    
    {
        PI=3;
        MOS();
        
        return 0;

    }
}

void Terminate(int msg){
    T=1;
    FILE *fp=NULL;
    fp=fopen("output_2.txt","a");
    char id[10];
    fprintf(fp,"\nJob ID: %s\n",info.JID);
    
    switch (msg)
    {
    case 0:
        fputs("     No Error\n",fp);
        break;
    case 1:
        fputs("     Out of Data \n",fp);
        break;
    case 2:
        fputs("     Line limit exceeded error \n",fp);
        break;
    case 3:
        fputs("     Time limit exceeded error \n",fp);
        break;
    case 4:
        fputs("     Opcode error \n",fp);
        break;
    case 5:
        fputs("     Operand error \n",fp);
        break;
    case 6:
        fputs("     Invalid page fault error \n",fp);
        break;
    case 7:
        fputs("     Time limit exceeded and invalid opcode \n",fp);
        break;
    case 8:
        fputs("     Time limit exceeded and invalid operand \n",fp);
        break;
    
    }
    fputs("IC : ",fp);
    fprintf(fp,"%d\n",IC);
    fputs("IR : ",fp);
    fputs(IR,fp);
    fputs("\nTTC : ",fp);
    fprintf(fp,"%d\n",TTC);
    fputs("LLC : ",fp);
    fprintf(fp,"%d\n",LLC);
    fputs("TTL : ",fp);
    fprintf(fp,"%d\n",info.TTL);
    fputs("TLL : ",fp);
    fprintf(fp,"%d\n",info.TLL);

}

void print_map(){
    for(int i=0;i<=key_index;i++){
        printf("%d  %d\n",key[i],value[i]);
    }
    printf("\n\n");
}


void Load(){
int i=0;
FILE *fp=NULL;
char ch;
fp=fopen("input_phase2.txt","r");


while (fgets(str, 41, fp) != NULL)
{
    if (str[0]=='$' && str[1]=='A' && str[2]=='M' && str[3]=='J')
    {
        PTR=Allocate()*10;
        info.JID[0]=str[4];
        info.JID[1]=str[5];
        info.JID[2]=str[6];
        info.JID[3]=str[7];

        info.TTL=(str[8]-'0')*1000+(str[9]-'0')*100+(str[10]-'0')*10+(str[11]-'0');
        info.TLL=(str[12]-'0')*1000+(str[13]-'0')*100+(str[14]-'0')*10+(str[15]-'0');

    for(int i=PTR;i<PTR+10;i++){
        M[i][0]='0';

        M[i][2]='*';
        M[i][3]='*';
    }

        printf("AMJ instruction found\n");
        printf("JID : %s\n",info.JID);
        printf("TTL : %d\n",info.TTL);
        printf("TLL : %d\n\n\n",info.TLL);
        printf("PTR : %d\n",PTR);
        getchar();
        
        int col=0;
        int temp,temp1;

        while(1)
        {
         
        fgets(str, 100, fp);
        if((str[0]=='$' && str[1]=='D' && str[2]=='T' && str[3]=='A')) break;
        temp=Allocate();
        temp1=temp*10;
        M[PTR+Program_card_couter][0]='1';
        M[PTR+Program_card_couter][3]=temp%10+'0';
        M[PTR+Program_card_couter][2]=temp/10+'0';
        Program_card_couter++;
        
        col=0;
        for(int i=0;i<strlen(str)-1;i++){
            if (str[i]==' ') break;
            M[temp1][col]=str[i];
            col++;
            if(col==4){
                temp1++;
                col=0;
        }
        
       }
       
       
        }
        
        currentLine =ftell(fp);
        
    }
    if((str[0]=='$' && str[1]=='D' && str[2]=='T' && str[3]=='A')){

        START_EXECUTION();

    }


    if((str[0]=='$' && str[1]=='E' && str[2]=='N' && str[3]=='D')){
        i++;
        
        print_memory_block();

        printf("\n\n\n  Job id. %d done\n\n\n",i);
        printf("%s\n\n",str);
        
        if(message==1){
            fseek(fp,ftell(fp)+2,SEEK_SET);
            printf("position is %d\n",ftell(fp));
        }
        
        printf("Press enter for another job to execute:\n");
        getchar();
        INIT();
    }
    }
 
}

void INIT(){
    for(int i=0;i<300;i++){
        for(int j=0;j<4;j++){
            M[i][j]=' ';
        }
    }
    for(int i=0;i<4;i++){
        IR[i]=' ';
        R[i]=' ';
    }
    IC=0;
    SI=0;
    C=0;
    T=0;
    currentLine=0;

    info.TTL=0;
info.TLL=0;
TTC=0;
LLC=0;
PI=0;
TI=0;
message=0;

generated_no_index=-1;
Program_card_couter=0;
key_index=-1;
count=0;

}


void START_EXECUTION(){
    IC=0;
    EXECUTE_USER_PROGRAM();
}


void EXECUTE_USER_PROGRAM(){
    while(1){
    int addr=Address_Map(IC);
    for(int i=0;i<4;i++){
        
        IR[i]=M[addr][i];
    }
    IC++;
    
    simulation();
    gen_address=map((IR[2]-'0')*10+(IR[3]-'0'));
    if(T==1){
        break;
    }
    

    if(!((IR[0]=='G' && IR[1]=='D') || (IR[0]=='P' && IR[1]=='D' )|| (IR[0]=='H' && IR[1]==' ') || (IR[0]=='L' && IR[1]=='R') || (IR[0]=='S' && IR[1]=='R') || (IR[0]=='C' && IR[1]=='R') || (IR[0]=='B' && IR[1]=='T'))){
        PI=1;
        MOS();
        break;
        
    }

    if(TI==2){
        MOS();
        break;
    }
    
    
    else if(IR[0]=='G' && IR[1]=='D'){
        SI=1;
        MOS();
        if(T==1) break;
        
    }
    else if(IR[0]=='P' && IR[1]=='D'){
        SI=2;
        MOS();
        if(T==1) break;
            
    }
    else if(IR[0]=='H' && IR[1]==' '){
        SI=3;
        MOS();
        break;
    }
    else if(IR[0]=='L' && IR[1]=='R'){
        LR();
    }
    else if(IR[0]=='S' && IR[1]=='R'){
        SR();
    }
    else if(IR[0]=='B' && IR[1]=='T'){
        BT();
    }
    else if(IR[0]=='C' && IR[1]=='R'){
        CR();
    }
    
    }
}
    

void simulation(){
    TTC++;
    if(TTC>info.TTL){
        TI=2;
        
    }
}


int MOS(){

    if(TI==0){

        if(SI==1){
            GD();
        }
        else if(SI==2){
            PD();
        }
        else if(SI==3){
            H();
        }
        else if(PI==1){
            Terminate(4);
        }
        else if(PI==2){
            Terminate(5);
        }
        else if(PI==3){

            if((IR[0]=='G' && IR[1]=='D') || (IR[0]=='S' && IR[1]=='R') ){
     
                key_index++;
                key[key_index]=(IR[2]-'0')*10+(IR[3]-'0');
                value[key_index]=Allocate();
                int temp = value[key_index];
                M[PTR+Program_card_couter][0]='1';
                M[PTR+Program_card_couter][3]=temp%10+'0';
                M[PTR+Program_card_couter][2]=temp/10+'0';
                Program_card_couter++;
                PI=0;
                return value[key_index]*10;
                }
                else{
                    Terminate(6);
                }
        }

    }

    else if(TI==2){
        if(PI==0){
            if(IR[0]=='P' && IR[1]=='D'){
                PD();
            }
            Terminate(3);
        }
        else if(PI==1){
            Terminate(7);
        }
        else if(PI==2){
            Terminate(8);
        }
        else if(PI==3){
            Terminate(3);
        }

    }
    
        
}

void GD(){

   int row = map((IR[2]-'0')*10+(IR[3]-'0'));

    int col = 0;

    FILE *fp=NULL;
    fp=fopen("input_phase2.txt","r");

    fseek(fp,currentLine,SEEK_SET);
    fgets(str, 100, fp);
    if((str[0]=='$' && str[1]=='E' && str[2]=='N' && str[3]=='D')){
        message=1;
        Terminate(1);
        return;
    }
    for(int i=0;i<strlen(str)-1;i++){
        M[row][col]=str[i];
        col++;
        if(col==4){
            row++;
            col=0;
        }
    }
    currentLine =ftell(fp);
    SI=0;
   
    
}

void PD(){
    FILE *fp=NULL;
    LLC++;
        if(LLC>info.TLL){
            Terminate(2);
            
            return;
        }
    fp=fopen("output_2.txt","a");
    if(flag==0) flag++;
    else fprintf(fp,"\n");

    int row = map((IR[2]-'0')*10+(IR[3]-'0'));

    int col = 0;
    for(int i=row;i<row+10;i++){
        for(int j=0;j<4;j++){
            
            fputc(M[i][j],fp);

        }
          
    }
    SI=0;
    
}
void H(){
    Terminate(0);
}

void LR(){
    int row = map((IR[2]-'0')*10+(IR[3]-'0'));
    for(int i=0;i<4;i++){
        R[i]=M[row][i];
    }

}

void SR(){
    int row = map((IR[2]-'0')*10+(IR[3]-'0'));
    for(int i=0;i<4;i++){
        M[row][i]=R[i];
    }
    
}

void CR(){
    int row = map((IR[2]-'0')*10+(IR[3]-'0'));
    
    for(int i=0;i<4;i++){
        if(R[i]!=M[row][i]){
            C=0;
            break;
            
        }
        else{
            C=1;
        }
    }
    
}


void BT(){
    if(C==1){
        IC=(IR[2]-'0')*10+(IR[3]-'0');
        C=0;
    }
}


//write main function
int main()
{
    //declare variables
    printf("\n\n########################### TY_IT_G6 ##########################\n\n\n\n"); 

    FILE *f=NULL;
    char ch;
    f=fopen("input_phase2.txt","r");
    if(f==NULL)
    {
        printf("File not found");
        exit(1);
    }
    while((ch=fgetc(f))!=EOF)
    {
        printf("%c",ch);
    }
fclose(f);

printf("\n\n\nPress enter to continue\n\n");

INIT();

Load();

    return 0; 
}