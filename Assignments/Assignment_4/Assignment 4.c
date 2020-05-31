#include <stdio.h> 
#include <stdlib.h>

int diff(int x, int y){
  int z; 
  z = x - y; 
  if(z < 0)
    return -z;
  else
    return z;
}

int main(){

  int choice, a, b, x, i, j, start, pos, min;
  int arr[10000];
  int FCFS, SSTF, SCAN, C_SCAN, LOOK;

  a = 1000;
  b = 1000;

  printf("Total number of cylinders: 10,000 \n");
  printf("Total number of requests: 1000 \n");
  printf("\nEnter current position: ");
  scanf("%d", &start);

  for(i = 0; i < b; i++){
    arr[i] = rand()%1000;
    if(arr[i] >= a){
      printf("\nTry again! Invalid input!");
      scanf("%d", &arr[i]);
    }
  }

do {
  
  // Menu for algorithm choice
  printf("\nDISK SCHEDULING ALGORITHMS: ");
  printf("\n1. FCFS");
  printf("\n2. SSTF");
  printf("\n3. SCAN");
  printf("\n4. C-SCAN");
  printf("\n5. LOOK \n");

  printf("Enter choice: ");
  scanf("%d", &choice);
  x = start;

  switch(choice){

    case 1:
      printf("\nFCFS Algorithm:\n"); 
      printf("Services are:\n\n%d\t", start); 
      for(i=0;i<b;i++){
        x -= arr[i]; 
        if(x<0)
          x = -x;
        FCFS += x;
        x = arr[i]; 
        printf("%d\t", x);
      }

      printf("\nTotal Head Movement: %d Cylinders", FCFS);
      break;
    /* ------------------------------------------------------- */
    case 2:
      printf("\nSSTF Algorithm:\n");
      printf("Services are:\n\n%d\t", start); 
      for(i = 0; i < b; i++){
        min = diff(arr[i],x); 
        pos = i;

        for(j = i; j < b; j++)
          if(min > diff(x, arr[j])){
            pos = j;
            min = diff(x, arr[j]);
          } 

        SSTF += diff(x,arr[pos]);
        x = arr[pos]; 
        arr[pos] = arr[i]; 
        arr[i] = x; 
        printf("%d\t",x); 
      }

      printf("\nTotal Head Movement: %d Cylinders", SSTF);
      break;
    /* ------------------------------------------------------- */
    case 3:
      printf("\nSCAN Algorithm:\n");
      printf("Services are:\n\n"); 
      SCAN=0;
      pos=0;

      for(i = 0; i < b; i++)
        for(j = 0; j < b - i - 1; j++)
          if(arr[j] > arr[j+1])
            for(i = 0; i < b; i++) 
              if(arr[i] < start)
                pos++; 

      for(i = 0; i < pos; i++)
        for(j = 0; j < pos - i - 1; j++)
          if(arr[j] < arr[j+1]){
            x = arr[j]; 
            arr[j] = arr[j+1];
            arr[j+1] = x;
          }

      x=start; 
      printf("%d\t", x); 
      for(i = 0; i < pos; i++){
        SCAN += diff(arr[i],x); 
        x = arr[i];
        printf("%d\t", x);
      }
      
      SCAN += diff(x, 0); 
      x = 0;
      printf("%d\t", x); 
      for(i = pos; i < b; i++){
        SCAN += diff(arr[i], x); 
        x = arr[i];
        printf("%d\t", x);
      }

      printf("\nTotal Head Movement: %d Cylinders", SCAN);
      break;
    /* ------------------------------------------------------- */
    case 4:
      printf("\nC-SCAN:\n");
      printf("Services are:\n\n%d\t", start); 
      C_SCAN = 0;
      pos = 0;

      for(i = 0; i < b; i++)
        for(j = 0; j < b - i - 1; j++) 
          if(arr[j] > arr[j + 1]){
            x = arr[j]; 
            arr[j] = arr[j+1]; 
            arr[j+1] = x;
          }{
            x = arr[j]; 
            arr[j] = arr[j+1]; 
            arr[j+1] = x;
          }{
            C_SCAN += diff(x, arr[i]); 
            x = arr[i];
            printf("%d\t", x);
          }
      
      C_SCAN += diff(a - 1, x); 
      x=0;
      printf("%d\t%d\t", a - 1, 0); 
      for(i = 0; i < pos; i++){
        C_SCAN += diff(x, arr[i]); 
        x = arr[i];
        printf("%d\t", x);
      }

      printf("\nTotal Head movement: %d Cylinders", C_SCAN);
      break;
    /* ------------------------------------------------------- */
    case 5:
      printf("\nLOOK Algorithm:\n");
      printf("\nServices are :\n\n%d\t", start); 
      LOOK = 0;
      pos = 0;

      for(i = 0; i < b; i++)
        for(j = 0; j < b - i - 1; j++) 
          if(arr[j] > arr[j+1])
            for(i = 0; i < b; i++) 
              if(arr[i] < start)
                pos++;

      x = start; 
      for(i = pos; i < b; i++)
        for(i = 0; i < b; i++) 
          if(arr[i] < start)
            pos++; 

      for(i = 0; i < pos; i++)
        for(j = 0; j < pos - i - 1; j++) 
          if(arr[j] < arr[j+1]){
            x = arr[j]; 
            arr[j] = arr[j+1]; 
            arr[j+1] = x;
          }

      x=start; 
      for(i = 0; i < pos; i++){
        LOOK += diff(arr[i], x); 
        x = arr[i];
        printf("%d\t", x);
      }

      for(i = pos; i < b; i++){
        LOOK += diff(arr[i] , x);
        x = arr[i]; 
        printf("%d\t", x); 
      }
      printf("Toal Head Movement: %d Cylinders", LOOK); 
      break;
    }
  /* -------------------------------------------------------- */
  
  // Asks user if they would like to perform another algorithm
    printf("\nDo you want to continue (Enter 1 to continue): "); 
    scanf("%d", &choice);
  }

  while(choice == 1);

  /* Constructs table with algorithms followed by total head movement */
  printf("\n Algorith name \t Total head movement "); 
  printf("\n FCFS \t\t\t %d",FCFS);
  printf("\n SSTF \t\t\t %d",SSTF);
  printf("\n SCAN \t\t\t %d",SCAN);
  printf("\n C-SCAN \t\t %d",C_SCAN);
  printf("\n LOOK \t\t\t %d",LOOK);
}