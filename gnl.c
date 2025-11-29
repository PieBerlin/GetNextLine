#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define BUFSIZE 2048
char *gnl(void);
char *zero(char *);
char *zero( char *p){
    unsigned int n;
    for (n=0;n<BUFSIZE;*(p + n++)=0);
    return p;

}
char *gnl(){
    unsigned int n;
    char *p, *s;
    int r;
    n=0;
    
    s=p=malloc(BUFSIZE);
    zero(s);

    //0== end return
    // -1 return (unless its the first byte)

    // \n return above
    // otherwise =add to  buffer and continue

    while(1){
        r=read(0,p,1);
        if (r<1) {
            if (n<1) return 0;
        
        else{
            return s;
        }

    }
    else if (n>(BUFSIZE-2)){
        return s;

    }
    
    switch(*p)
    {
        case 0:
        case '\n':
        /*
        if(p !=s)
         if(*(p-1)=='\n')
         *(p-1)=0;
         */
        *p=0;
        return s;
        break;

        case '\r':
        *p=0;
         break;

         default:
         p++;  
         n++;
        
    }

}
return (n<1)?0:s;
}

int main(){
    char *p1,*p2;
    p1=gnl();
    p2=gnl();

    printf(
        " '%s'\n "
        " '%s'\n "
    ,p1,p2);

    free(p2);
    free(p1);
return 0;
}