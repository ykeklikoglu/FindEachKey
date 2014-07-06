#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define Max_word 30
typedef struct Node
{
	char word[Max_word];
	int repeat_size;
	Node *next;
}Node;
typedef struct First_Node
{
	char harf;
	int total_size;
	Node *icerik;
	First_Node *sonrakiharf,*öncekiharf;
}FirstNode;
Node * CreateNode(char kelime[])
{
	Node *ptr=(Node*) malloc(sizeof(Node));
	if(ptr==NULL)
		exit(0);
	ptr->next=NULL;
	strcpy(ptr->word,kelime);
	ptr->repeat_size=0;
	return(ptr);
}
First_Node* CreateFirst_Node(char harfim)
{
	First_Node *ptr=(First_Node*)malloc(sizeof(First_Node));
	if(ptr==NULL)
		exit(0);
	ptr->harf=harfim;
	ptr->total_size=0;
	ptr->icerik=NULL;
	ptr->öncekiharf=ptr->sonrakiharf=NULL;
	return(ptr);
}
First_Node * HelpAddWord(First_Node * h,char kelimem[])//will run if size of list >1; (by AddWord() function)
{
		Node *f1,*f2;
		f1=h->icerik;
		f2=h->icerik->next;
		if(  strcmp(f1->word,kelimem)==0)//if first element equal to kelimem
		{
			f1->repeat_size++;
			h->total_size++;
			return h;
		}
		else if(strcmp(f2->word,kelimem)==0)//if second element equal to kelimem
		{
			f2->repeat_size++;
			h->total_size++;
			return h;
		}
		while(	!  (strcmp(f1->word,kelimem)==1  &&	strcmp(f2->word,kelimem)==-1) )//start to find kelimem
		{
			f1=f1->next;
			f2=f2->next;
			if(  strcmp(f1->word,kelimem)==0)//if searching word is already exist
			{
				f1->repeat_size++;
				h->total_size++;
				return h;
			}
			if(f2==NULL)//if can not find
			{
				f1->next=CreateNode(kelimem);
				h->total_size++;
				return h;
			}
		}
		f1->next=CreateNode(kelimem);//else)  if the word will fit to between two elements
		f1->next->next=f2;
		h->total_size++;
		return(h);
}
First_Node * AddWord(First_Node * h,char kelimem[])
	{
		if(h->icerik==NULL)//will run if size of list=0;
		{
			h->icerik=CreateNode(kelimem);
			h->total_size++;
			return h;
		}
		else if(h->icerik->next==NULL)//will run if size of list =1.
		{
			switch(strcmp(h->icerik->word,kelimem))
			{
			case 1://add item to first
				{
					Node *tmp=h->icerik;
					h->icerik=CreateNode(kelimem);
					h->icerik->next=tmp;
					h->total_size++;
					return h;
				}
			case 0:// increase by 1 to word repeat
				{
					h->icerik->repeat_size++;
					h->total_size++;
					return h;

				}
			case -1://add item to last
				{
					h->icerik->next=CreateNode(kelimem);	
					h->total_size++;
					return h;
				}
			}
			
		}
		return(HelpAddWord(h,kelimem));//will run if size of list >1;
	}
First_Node * print(First_Node *sözlük)
{
	int i=1;
	FILE *Pout=fopen("deneme.txt","w");
	First_Node *söz=sözlük;
	Node *kelimeler=CreateNode("a");
	fprintf(Pout,"\nTüm kelimeler:\n\n");
	while(söz!=NULL)
	{
		kelimeler=söz->icerik;
		fprintf(Pout,"%c{\n 	",toupper(söz->harf));
		while(kelimeler!=NULL)
		{
			fprintf(Pout," %s(%d) ,",kelimeler->word,kelimeler->repeat_size+1);
			kelimeler=kelimeler->next;
			if(i++%30==0)
				fprintf(Pout,"\n	");
		}
		fprintf(Pout,"}\n--Have %d words--\n\n",söz->total_size);
		söz=söz->sonrakiharf;
		i=0;
	}
	fclose(Pout);
	return sözlük;
}
int main ()
{
	int i=0;
	unsigned char character;
	char word[Max_word];
	word[0]=0;
	First_Node *sözlük,*harf;
	sözlük=CreateFirst_Node(97+i);					 //	97+0=a
	harf=sözlük;
	for(i=1;i<26;i++)
	{
		harf->sonrakiharf=CreateFirst_Node(97+i);//		 97+1=b   97+2=b ...
		harf=harf->sonrakiharf;
	}
	harf=sözlük;
	char kelimem[Max_word];
	FILE *Pin;
	if ((Pin = fopen("inputText.txt","r")) == NULL) {
		printf("there is not any words\n");
		return 0;
	}
	while(!feof(Pin))
	{
		i=0;
		character=tolower(getc(Pin));
		if(isalpha(character))
		{
			word[0]=character;
			character=tolower(getc(Pin));
			while(	isalpha(character)	&&	(i<Max_word-1)  ) //(i<Max_word-1) for control system 
			{
				word[++i]=tolower(character);
				character=tolower(getc(Pin));
			}
			word[i+1]=0;
			while(tolower(word[0])!=harf->harf )
			{
				harf=harf->sonrakiharf;
			}
			harf=AddWord(harf,word);
			harf=sözlük;	
		}
	}
	fclose(Pin);
	sözlük=print(sözlük);
	return(0);
}