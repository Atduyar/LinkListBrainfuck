#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h> 

struct no{
	int value;
	struct no *n;
	struct no *p;
};

typedef struct no* node;

node newNode(int x) 
{ 
    node root = (node)malloc(sizeof(struct no)); 
    root->value = x; 
    root->n = root->p = NULL; 
    return root; 
} 

node addLastNode(node root, int x) 
{ 
    root->n = newNode(x);
    root->n->p = root; 
    return root->n; 
} 

node addFirstNode(node root, int x) 
{ 
    root->p = newNode(x);
    root->p->n = root; 
    return root->p; 
} 

node addNode(node root, int x) 
{ 
	node temp = newNode(x);
	temp->n = root->n;
    if (root->n != NULL)
	{
		temp->n->p = temp;
	}
    root->n = temp;
    temp->p = root; 

    return temp; 
} 

int deleteNode(node root) 
{ 
	int s = 0;
	if (root->n != NULL && root->p != NULL)
	{
		if (root->p == NULL)//ilk eleman sa
		{
			root->n->p = NULL;
			s = 2;
		}
		else if(root->p != NULL){
			if (root->n == NULL)//son elemansa
			{
				s = 3;
				root->p->n = NULL;
			}
			else if(root->n != NULL){
				s = 1;
				root->p->n = root->n;
				root->n->p = root->p;
			}
		}
	}
	else{//tek elemansa
		s = 0;
	}
	free(root);
	return s;
} 

///////////////

node getLastNode(node temp) 
{ 
	while (temp->n != NULL)
	{
		temp = temp->n;
	}
	return temp;
} 

node getFirstNode(node temp) 
{ 
	while (temp->p != NULL)
	{
		temp = temp->p;
	}
	return temp;
} 

node pushNode(node root, int x) 
{ 
	root = getLastNode(root);
    return addLastNode(root, x);
} 

///////////////

void printNodeColors(node root, node  temp, node froot) 
{ 
	if (froot == root)
	{
		printf("\033[1;33m");
		printf("%d ", froot->value);
   		printf("\033[0m");
	}
	else if (froot == temp)
	{
		printf("\033[1;34m");
		printf("%d ", froot->value);
   		printf("\033[0m");
	}
	else {
		printf("%d ", froot->value);
	}
} 

void printNextNode(node root, node temp, node froot) 
{ 
	printNodeColors(root, temp, froot);
	if(froot->n != NULL)
	{
		froot = froot->n;
		printNextNode(root, temp, froot);
	}
} 

void printNode(node root, node temp) 
{ 
	printNextNode(root, temp, getFirstNode(temp));
} 








node bfLeft(node root){
	if (root->p == NULL)
	{
		return addFirstNode(root, 0);
	}
	return root->p;
}

node bfRight(node root){
	if (root->n == NULL)
	{
		return addLastNode(root, 0);
	}
	return root->n;
}

void bfAdd(node root){
	root->value++;
	if(root->value > 255){
		root->value = 0;
	}
}

void bfSub(node root){
	root->value--;
	if(root->value < 0){
		root->value = 255;
	}
}

char bfGetC(node root){
	return (char)root->value;
}

char bfSetC(node root, char	c){
	return root->value = (int)c;
}

void bfLoopOn(node root, int *loop, int *loopi){
	*loop = *loop + 1;
	//printf("loop On %d\n",*loop);
}

void bfLoopS(node root, FILE *f, int *loop, int *loopi){
	char c;
	while(true){
		//printf("loop----\n");
		c = getc(f);
		fseek(f, -2, SEEK_CUR);//konumu bir geriletir
		if (c == '[')//acma görüldüyes
		{
			//printf("loop [\n");
			if (*loop == *loopi)//istenen acma ise
			{
				//printf("loop f\n");
				fseek(f, 1, SEEK_CUR);//konumu bir geriletir
				return;//döndür
			}
			*loop = *loop - 1;//değilse loop counter i bir azaltır
		}
		c = getc(f);
		fseek(f, -1, SEEK_CUR);//konumu bir geriletir
		if (c == ']')//acma kapama
		{
			//printf("loop ]\n");
			*loop = *loop + 1;
		}
		return bfLoopS(root, f, loop, loopi);
	}

}

void bfLoopOff(node root, FILE *f, int *loop, int *loopi){
	if (root->value <= 0)// loop dan direkt cıkma sartı
	{
		//printf("loop d kapa\n");
		return;
	}
	//loop un basına gider
	*loopi = *loop;
	fseek(f, -1, SEEK_CUR);//konumu bir geriletir
	bfLoopS(root, f, loop, loopi);//dosyayı loop un basına alır

	//printf("loop b kapa\n");
	return;
}


void printOutput(char c, int *outputC, int *outputLineC){ 
	for (int i = 0; i < 1; ++i)
	{
   		printf("\033[A\r");//bir satır yukarı
	}
	for (int i = 0; i < *outputC; ++i)
	{
   			printf("\x1b[C");//bir karakter sağa
	}
	if ((int)c == 10 || (int)c == 11 || (int)c == 12)
	{
		*outputC = *outputLineC + 1;
   		//printf("\033[2K");//satırı sil
   		printf("\e[41m");
   		printf("-");
   		printf("\033[0m");
		*outputC = -1;
	}
	*outputC = *outputC + 1;
	printf("%c", c);
	for (int i = 0; i < 1; ++i)
	{
   		printf("\x1b[B");//bir satır assağı
	}
}

int setSpeed(FILE *f, int *s){
   	char c = fgetc(f);
	fseek(f, -1, SEEK_CUR);//konumu bir geriletir
	if (c == '*')
	{
		fseek(f, 1, SEEK_CUR);//konumu bir geriletir
		fscanf(f, "%d",s);
	}
	else{
		*s = 0;
	}
	return *s;
}

int main(int argc, char* argv[]){
	char* inputFile = 0;
	//if(argv[1] == NULL || argv[1][0] == '-'){
	//	inputFile = "input.bf";
	//}
	//else{
	//	inputFile = argv[1];
	//}

	node root = newNode(0);
	node temp = root;
	//dosya chrosor ü
	char c;
	//loop ların toplamı ve konumu
	int lo = 0;
	int loi;
	//output uzunluk genisliği
	int oc = 9;
	int olc = 1;
	//bekleme süresi
	int speed = -1;

	while (*++argv != NULL) {
		if (strcmp("-f", *argv) == 0 || strcmp("-file", *argv) == 0 || strcmp("-input", *argv) == 0 || strcmp("-i", *argv) == 0) {
			inputFile = *++argv;
		} else if (strcmp("-s", *argv) == 0 || strcmp("-speed", *argv) == 0) {
			speed = atoi(*++argv);
		}
	}
	if(inputFile == 0){
		inputFile = "input.bf";
	}

  	FILE *dosya = fopen(inputFile, "r");
    if(dosya == NULL){
        printf("%s File not found or Unable to open file\n",inputFile);
        exit(0);
    }

	if(speed == -1){
  		setSpeed(dosya, &speed);
	}
	printf("inputFile : %s\n",inputFile );

	printf("Speed : %d\n",speed);
	speed *= 1000;

	printf("\e[?25l");//imleci gizler
   	printf("OUTPUT : \n\n");

  	while(!feof(dosya)){
   		printf("\033[A\r");//bir satır yukarı
   		printf("\033[1;32m");
   		printf("\033[2K");

   		c = fgetc(dosya);

   		switch (c){
  			case '+':
   				bfAdd(temp);
   				printf("+ \n");
  				break;
			case '-':
				bfSub(temp);
   				printf("- \n");
				break;
			case '<':
   				temp = bfLeft(temp);
   				printf("<|\n");
   				break;
   			case '>':
   				temp = bfRight(temp);
	   			printf("|>\n");
	   			break;
	   		case '.':
  				printOutput(bfGetC(temp), &oc, &olc);
   				printf(". \n");
   				break;
   			case ',':
   				printf("\e[?25h");//imleci acar
   				scanf(" %c",&c);
				printf("\e[?25l");//imleci gizler
  				bfSetC(temp,c);
   				printf(", \n");
   				break;
  			case '[':
   				bfLoopOn(temp, &lo, &loi);
   				printf("[ \n");
   				break;
  			case ']':
   				bfLoopOff(temp, dosya, &lo, &loi);//dosya nın pointer ini ayarlar
   				printf("] \n");
   				break;
   			default:
   				printf("\n");
   				break;
   		}
	   	//printf("\n");


   		printf("\033[0m");
   		printf("");//satırı sil");
   		printf("\r\033[2K\r");
   		printNode(root, temp);
   		if (speed)
   		{
   			if (c == '+' || c == '-' || c == '.' || c == ',' || c == '<' || c == '>' || c == '[' || c == ']')
   				usleep(speed);
   		}
  	}

  	fclose(dosya);
  	printf("\n");
	return 0;
}
