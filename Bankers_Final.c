#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>
int n;    //n number of process
 int r;      // number of resources
 int i,j,k,cnt,cntt,q;
 int avail[10],p[10];
 int need[10][10],alloc[10][10],max[10][10],req[10][10];
 int h[10]={0,0,0,0,0,0,0,0,0,0};
 pthread_mutex_t l;//MUTEX LOCK
 //********************************************
 //***************INPUT****************************
 void *input(){
     pthread_mutex_lock(&l);
     printf("\nEnter number of process :");
 scanf("%d",&n);
 printf("\n Enter  resources available : ");
 scanf("%d",&r);
 printf("\nEnter instances for resources :\n");
 for(i=0;i<r;i++)
 {  printf("R %d :",i+1);
  scanf("%d",&avail[i]);
  }
 printf("\n Enter allocation matrix  \n");
 for(i=0;i<n;i++)
 {
 printf("P %d :",i+1);          p[i]=0;
 for(j=0;j<r;j++)
 {
  scanf("%d",&alloc[i][j]);
 }
}
  printf("\n Enter MAX matrix  \n");

 for(i=0;i<n;i++)
 {
 printf("P %d :",i+1);
 for(j=0;j<r;j++)
 {
  scanf("%d",&max[i][j]);
 }
 }
 pthread_mutex_unlock(&l);
 }
 //*******************CURRENT AVAILABLE****************
 void *cur(){
     pthread_mutex_lock(&l);
     printf("CURRENT AVAILABLE RESOURCES");
 for(j=0;j<r;j++)

 {for(i=0;i<n;i++)
 {

  h[j]=h[j]+alloc[i][j];



  }avail[j]=avail[j]-h[j];

  printf("\nR %d :",j+1);
       printf("%d ",avail[j]);}
       pthread_mutex_unlock(&l);
 }
//***************printing ALL MATRICES aND NEED mATRIX*************
void *all(){
    pthread_mutex_lock(&l);
    printf("\nprocess\t\tALLOCATION\t\t\tMAX\t\t\tNEED") ;
 for(i=0;i<n;i++)
 {
 printf("\np%d\t",i+1) ;
 for(j=0;j<r;j++)
 {
  printf("\t%d",alloc[i][j]);

  }
  for(j=0;j<r;j++)
 {
  printf("\t%d",max[i][j]);
  }
 for(j=0;j<r;j++)
 {
  need[i][j]=max[i][j]-alloc[i][j];
  printf("\t%d",need[i][j]);
  }
 }
 pthread_mutex_unlock(&l);
}
//***************printing ALL MATRICES aND NEED mATRIX AFTER REQUEST*************
void all2(){
    pthread_mutex_lock(&l);
    printf("\nprocess\t\tALLOCATION\t\t\tMAX\t\t\tNEED") ;
 for(i=0;i<n;i++)
 {
 printf("\np%d\t",i+1) ;
 for(j=0;j<r;j++)
 {
  printf("\t%d",alloc[i][j]);

  }
  for(j=0;j<r;j++)
 {
  printf("\t%d",max[i][j]);
  }
 for(j=0;j<r;j++)
 {
  need[i][j]=max[i][j]-alloc[i][j];
  printf("\t%d",need[i][j]);
  }
 }
 pthread_mutex_unlock(&l);
}
//***********
void Request(){
   pthread_mutex_lock(&l);
   i=0;
   int count=0;
 printf("\n REQUESTING \n");
 printf("enter the Process Number :");
   scanf("%d",&i);
   printf("ENTER RESOURCE REQUEST \n");
   for(j=0;j<r;j++)
   {
       printf("\nR %d :",j+1);
       scanf("%d",&req[i][j]);
   }
   for(j=0;j<r;j++)
   {
       if(req[i][j]<=need[i][j]&&req[i][j]<=avail[j])
       {
           count++;
       }

   }
   if(count==r)
   {
       printf("request accepted");
       for(j=0;j<r;j++)
       {
           avail[j]=avail[j]-req[i][j];
           alloc[i][j]=alloc[i][j]+req[i][j];
           need[i][j]=need[i][j]-req[i][j];
       }
   }
   else{printf("REQUEST REJECTED and the safe condition checked for INPUT BEFORE REQUEST");}
   pthread_mutex_unlock(&l);
 }
//********CHECKING FOR SAFE SEQUENCE*******************
void safe()
{pthread_mutex_lock(&l);
k=0;     cntt=0;
 printf("\n\n");

 while(k<15)
 {
 for(i=0;i<n;i++)
 {  cnt=0;
 for(j=0;j<r;j++)
 {
  if(p[i]==1) break;

  if(need[i][j]<=avail[j])
  {
  cnt++;
  }
  if(cnt==r)
  {
  for(j=0;j<r;j++)
  {
  avail[j]+=alloc[i][j];
  }
  printf("p%d\t",i+1);  p[i]=1;     cntt++;
  }
 }
 } k++;
 }
 if(cntt<n-1)
 {
 printf("\n deadlock ");
 }
 pthread_mutex_unlock(&l);
}



int main(){
    
    pthread_mutex_init(&l,NULL);
    pthread_t p1,p2,p3,p4,p5,p6;
    pthread_create(&p1,NULL,input,NULL);
    pthread_create(&p2,NULL,cur,NULL);
    pthread_create(&p3,NULL,all,NULL);
    // pthread_create(&p5,NULL,Request,NULL);
    // pthread_create(&p6,NULL,all2,NULL);

    // pthread_create(&p4,NULL,safe,NULL);


    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);
    char f;
    printf("\nDO YOU WANT TO ReqUesT(Y/N) :");
    scanf(" %c",&f);
    if(f=='y'||f=='Y')
    //if(f=1)
    {
        Request();
        all2();
        safe();

    
    }
    else
    {
    safe();
    //  pthread_join(p4,NULL);
    }
  

}
