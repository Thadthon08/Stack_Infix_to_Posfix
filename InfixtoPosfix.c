#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct nd{
    char c;
    struct nd *next;
}node;
node *top = NULL;

void push(char x){
    node *n = malloc(sizeof(node));
    n->next = top;
    top = n;
    n->c = x;
}

char pop(){
    char p;
    node *n;
    n = top;
    top = top->next;
    p = n->c;
    free(n);
    return p;
}

char stacktop(){
    if(top == NULL){
        return '\0';
    }
    else{
        return top->c;
    }
}

int checkpr(char temp){
    int pr;

    if(temp == '^'){
        pr = 3;
    }
    else if(temp == '*'||temp =='/'){
        pr = 2;
    }
    else if(temp == '+'||temp =='-'){
        pr = 1;
    }
    else if(temp == '('){
        pr = 0;
    }
    return pr;
}
void process(char ch[],int size){												

	char stack[size];		
	char output[size];											
	for(int i=0;i<size;i++){													
		stack[i]='\0';																
		output[i]='\0';															
	}
	int i,numstack=0,numoutput=0;															
	for(i=0;i<size;i++){														
		if(ch[i]=='('){															
			push(ch[i]);														
			stack[numstack++]=ch[i];													
			printf("%-2s%-8d%-13c%-15s%-20s\n","",i+1,ch[i],stack,output);					
		}
		else if(ch[i]==')'){													
			while(stacktop()!='('){												
				output[numoutput++]=pop();												
				stack[numstack--]='\0';													
			}
			pop();																
			stack[numstack--]='\0';														
			stack[numstack]='\0';														
			printf("%-2s%-8d%-13c%-15s%-20s\n","",i+1,ch[i],stack,output);			
		}
		else if(isdigit(ch[i])||isalpha(ch[i])){								
			output[numoutput++]=ch[i];													
			printf("%-2s%-8d%-13c%-15s%-20s\n","",i+1,ch[i],stack,output);						
		}
		else{																	
			if(stacktop()== '\0'||stacktop()=='('){								
				push(ch[i]);													
				stack[numstack++]=ch[i];												
				printf("%-2s%-8d%-13c%-15s%-20s\n","",i+1,ch[i],stack,output);				
			}
			else{																
				if(checkpr(ch[i])<=checkpr(stacktop())){						
					while((checkpr(ch[i])<=checkpr(stacktop()))&&(stacktop()!='\0')){
						                                                        
						stack[numstack--]='\0';											
						output[numoutput++]=pop();										
					}
				}
				push(ch[i]);													
 				stack[numstack++]=ch[i];												
				printf("%-2s%-8d%-13c%-15s%-20s\n","",i+1,ch[i],stack,output);			
			}
		}
	}
	int count=0;																
	while(stacktop()!='\0'){													
		output[numoutput++]=pop();														
		count++;																
	}
	if(count>0){																
		printf("%-2s%-8d%-13s%-15s%-20s\n","",i+1,"","",output);						
	}
	printf("========================================================\n");
	printf("Postfix: %s\n",output);												
	printf("========================================================\n");
	
}


int main(){
	printf("========================================================\n");
	printf("---------------------# [G18] #------------------------\n");
    printf("------------------# Infix To Posfix #-------------------\n");
   	printf("========================================================\n");	
	char infix[100];
	int size;
	printf("Infix: ");
	scanf("%s",infix);
	size = strlen(infix);
	printf("========================================================\n");			 
	printf("%-8s%-13s%-15s%-20s\n"," Step","Symbol","Stack","Outout"); 
	printf("========================================================\n");
	process(infix, size);
    return 0;
}
