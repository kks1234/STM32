#include <stdio.h>
#define MAXLEN  50
#define TURE  1
#define FALSE 0

typedef struct{
    char ch[MAXLEN];
    int len;
}Str;

int Creat_Strings(Str* s,int len){
	int i;
	s->len=len;
	for(i=0;i<len;i++)
	{
		s->ch[i]=getchar();
		getchar();
	}
}
/*insert strings*/
int Str_Insert(Str* s,int pos,const Str p){
    int i;
    /*check parameters*/
    if(s==NULL||p.ch==NULL) return FALSE;
    if(pos<=0||pos>s->len)  return FALSE;
    
    if(s->len+p.len<MAXLEN)
    {
        for(i=s->len+p.len-1;i>=pos+p.len-1;i--)
            s->ch[i]=s->ch[i-p.len];
        for(i=pos-1;i<pos+p.len-1;i++)
            s->ch[i]=p.ch[i-pos+1];
        s->len=s->len+p.len;
    }
    else if(pos+p.len-1<MAXLEN)
    {
        for(i=MAXLEN-1;i>=pos+p.len-1;i--)
            s->ch[i]=s->ch[i-p.len];
        for(i=pos-1;i<pos+p.len-1;i++)
            s->ch[i]=p.ch[i-pos+1];
        s->len=MAXLEN;
    }
    else
    {
        for(i=pos-1;i<MAXLEN;i++)
            s->ch[i]=p.ch[i-pos+1];
        s->len=0;
    }
    return TURE;
}

int main(int argc, char const *argv[])
{
    int i;
 	Str a,b;
 	Creat_Strings(&a,4);
 	Creat_Strings(&b,4);
 	
    Str_Insert(&a,3,b);
	
	printf("%d\n",a.len); 
    for(i=0;i<a.len;i++)
    printf("%c",a.ch[i]);
    return 0;
}
