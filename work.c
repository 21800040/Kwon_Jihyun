#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){

  int buffer[51][51];
  int i = 0, j = 0;
  int row = 0, col = 0;
  char *splitPtr = NULL;
  char max[500];
  int val=0;


  FILE * fin = fopen(argv[1], "r");
/*
  if(argc == 1){
    printf("enter your input file name\n");
    return -1;
  }
*/
  while(1){
    if(feof(fin)) break;
    col = val;
    val = 0;


    fgets(max, sizeof(max), fin);

    splitPtr = strtok(max, " ");
    buffer[row][val] = atoi(splitPtr);
    val++;

    while(splitPtr != NULL) {

      splitPtr = strtok(NULL, " ");
      if(splitPtr != NULL){
        buffer[row][val] = atoi(splitPtr);
        val++;
      }
    }
    row++;
  }
  row -= 1;

  fclose(fin);

  for(i = 0; i < row; i++){
    for(j = 0; j < col; j++){
      if(i == 0 && j == col-1)  continue;
      printf("%d ", buffer[i][j]);
    }
    printf("\n");
  }
//  printf("%d %d\n",row, col );
/*
  int **arr;
  arr = (int **)malloc(row+1 * sizeof(int *));
//   = (char **)malloc(row * sizeof(char *));
  for(int o = 0; o < row+1; o++){
    arr[o] = (int *)malloc(col+1 * sizeof(int));
  }

  int sum_arr*[2];
  sum_arr[0] = (int *)malloc(col * sizeof(int));
  sum_arr[1] = (int *)malloc(row * sizeof(int));
*/
//N == column, M == row

/////////////formula///////////////

  FILE *fp = fopen("formula", "w");

  for(i = 0; i <= row; i++){
    for(j = 0; j <= col; j++){
      fprintf(fp, "(declare-const a%d/%d Int)\n", i, j);
    }
  }
  fprintf(fp, "(assert(");
  for(i = 1; i<= row; i++){
    fprintf(fp, "(");
    for(j = 1; j <= col; j++){
      fprintf(fp, "(or (=a%d/%d 1)(=a%d/%d 0)))\n", i, j, i, j);
    }
    fprintf(fp, ")");
  }
  fprintf(fp, "))\n");

  for(i = 1; i<= row; i++){
    fprintf(fp, "(assert (= ");
    for(int h = 1; h < col; h++){
      fprintf(fp, "(+ ");
      for(j = 1; j <= col; j++){
        fprintf(fp, "(* a%d/%d %d)", i, j, buffer[i][j]);
      }

    }
    fprintf(fp, "%d)\n", buffer[0][i-1]);
  }

  for(i = 1; i <= col; i++){
    fprintf(fp, "(assert (= ");
    for(int k = 1; k < col; k++){
      fprintf(fp, "(+ ");
    }
    for(j = 1; j<= row; j++){
      fprintf(fp, "(* a%d/%d %d", i, j, buffer[i][j]);
    }
    fprintf(fp, "%d)\n", buffer[col][i-1]);
  }


  fprintf(fp, "(check-sat)\n(get-model)\n");
  fclose(fp);

FILE * f = popen("z3 formula", "r");

 char b[128];
 char s[128];
 char t[128];
 char buf[128];

 int** board = (int**) malloc(sizeof(int*) * row);
 for(i = 0; i < row; i++) {
   board[i] = (int*) malloc(sizeof(int) * col);
 }

 for(i = 0; i< row; i++){
  for(j =0; j < col; j++){
    board[i][j] = 0;
  }
}

 fscanf(f, "%s", buf);
 if(strcmp(b, "unsat") == 0) {
   printf("No solution\n");
   free(board);
   fclose(f);
 }

   while(!feof(f)){
     fscanf(f, "%s %s %s %s %s", b, s, b, b, t);
     sscanf(s, "a%d/%d", &i, &j);
     //board[i-1][j-1] = t[0] - '0';
     if(strcmp(t, "0)") != 0){
       board[i][j] = 1;
     }
   }
   fclose(f);

   for(i=0; i<row; i++){
     for(j=0; j<col; j++) printf("%d ", board[i][j]);
     printf("\n");
   }
 printf("\n");
 free(board);
 pclose(f);

  return 0;
}

