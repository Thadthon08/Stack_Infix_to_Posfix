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

	char st[size];		
	char output[size];											
	for(int i=0;i<size;i++){													
		st[i]='\0';																
		output[i]='\0';															
	}
	int i,numst=0,numoutput=0;															
	for(i=0;i<size;i++){														
		if(ch[i]=='('){															
			push(ch[i]);														
			st[numst++]=ch[i];													
			printf("%-6d%-12c%-15s%-15s\n",i+1,ch[i],st,output);				
		}
		else if(ch[i]==')'){													
			while(stacktop()!='('){												
				output[numoutput++]=pop();												
				st[numst--]='\0';													
			}
			pop();																
			st[numst--]='\0';														
			st[numst]='\0';														
			printf("%-6d%-12c%-15s%-15s\n",i+1,ch[i],st,output);			
		}
		else if(isdigit(ch[i])||isalpha(ch[i])){								
			output[numoutput++]=ch[i];													
			printf("%-6d%-12c%-15s%-15s\n",i+1,ch[i],st,output);					
		}
		else{																	
			if(stacktop()== '\0'||stacktop()=='('){								
				push(ch[i]);													
				st[numst++]=ch[i];												
				printf("%-6d%-12c%-15s%-15s\n",i+1,ch[i],st,output);				
			}
			else{																
				if(checkpr(ch[i])<=checkpr(stacktop())){						
					while((checkpr(ch[i])<=checkpr(stacktop()))&&(stacktop()!='\0')){
						                                                        
						st[numst--]='\0';											
						output[numoutput++]=pop();										
					}
				}
				push(ch[i]);													
 				st[numst++]=ch[i];												
				printf("%-6d%-12c%-15s%-15s\n",i+1,ch[i],st,output);			
			}
		}
	}
	int count=0;																
	while(stacktop()!='\0'){													
		output[numoutput++]=pop();														
		count++;																
	}
	if(count>0){																
		printf("%-6d%-13c%-15s%-14s\n",i+1,ch[i],st,output);						
	}
	printf("========================================================\n");
	printf("Postfix: %s\n",output);												
	printf("========================================================\n");
	
}


int main(){
	char infix[100];
    printf("========================================================\n");
	printf("---------------------# [G18] #------------------------\n");
    printf("------------------# Infix To Posfix #-------------------\n");
   	printf("========================================================\n");	
	printf("Infix: ");
	scanf("%s",infix);
	int size = strlen(infix);
	printf("========================================================");			 
	printf("\n%-6s%-12s%-15s%-15s\n","Step","Symbol","Stack","Output"); 
	printf("========================================================\n");
	process(infix, size);
    return 0;
}
