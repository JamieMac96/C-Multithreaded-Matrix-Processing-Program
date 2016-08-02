#include <omp.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findMatches(int, int, int, int, int, float **);
float** createArray(int, int);

int main(int argc, char **argv){
  char *refStr, *tolStr;
  char *refStop, *tolStop;
  int verbose = 0;
  int i;
  int count;
  int rct, cct;
  int max, min;
  float ref, tol;

  refStr = tolStr = NULL;

  for(i = 0; i < argc; i++){
    if(strcmp("-r", argv[i]) == 0){
      refStr = argv[i+1];
    }
    else if(strcmp("-t", argv[i]) == 0){
      tolStr = argv[i+1];
    }
    else if(strcmp("-v", argv[i]) == 0){
      verbose = 1;
    }
  }


  if ((argc != 5 && argc != 6) || refStr == NULL || tolStr == NULL){
    fprintf(stderr, "Usage: %s -r ref -t tol (-v optional)\n", argv[0]);
    exit(1);
  }

  ref = strtof(refStr, &refStop);
  tol = strtof(tolStr, &tolStop);
  max = ref + tol;
  min = ref - tol;

  if(tol < 0){
    printf("Error: Tolerance value (-t) must be positive.\n");
    return 0;
  }

  scanf("%d\n", &rct);
  scanf("%d\n", &cct);

  float** rows = createArray(rct, cct);

  struct timeval myTime;
  gettimeofday(&myTime, NULL);
  double t1 = myTime.tv_sec+(myTime.tv_usec/1000000.0);

  count = findMatches(rct, cct, max, min, verbose, rows);

  gettimeofday(&myTime, NULL);
  double t2 = myTime.tv_sec+(myTime.tv_usec/1000000.0);
  printf("%.6lf seconds elapsed\n", t2-t1);

  fprintf(stdout, "Found %d approximate matches.\n", count);


  free(rows);
  exit(0);
}


float** createArray(int rct, int cct){
  float** rows = (float **) malloc(rct * sizeof(float *));
  int i, j;

  if (rows == 0){
    fprintf(stderr, "Couldn’t alocate sufficient space.\n");
    exit(1);
  }

  for (i = 0; i < rct; i++){
    float* row = (float *) malloc(cct * sizeof(float));
    if (row == 0){
      fprintf(stderr, "Couldn’t alocate sufficient row space.\n");
      exit(1);
    }
    rows[i] = row;
  }

  for(i = 0; i < rct; i++){
    for(j = 0; j < cct; j++){
      scanf("%f\n", &rows[i][j]);
    }
  }

  return rows;
}


int findMatches(int rct, int cct, int max, int min, int verbose, float **rows){
  int sh_count = 0;
  int r,c;

  #pragma omp parallel private(r,c) shared(sh_count) num_threads(8)
  {
    #pragma omp for
    for (r = 0; r < rct; r++){
      for (c = 0; c < cct; c++){
        if(rows[r][c] <= max && rows[r][c] >= min){
          if (verbose){
            fprintf(stdout, "r=%d, cc=%d: %.6f (thread= %d)\n",
            r, c, rows[r][c], omp_get_thread_num());
          }
          #pragma omp critical(dataupdate)
          {
            sh_count++;
          }
        }
      }
    }
  }

  return sh_count;
}
