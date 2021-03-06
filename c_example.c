/*
 *Author : Guo Qi
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "mine.h"
//#define BUILD_FROM_FILE

int main (int argc, char **argv)
{
  mine_problem prob;
  mine_parameter param;
  mine_score *score;

  double PI = 3.14159265;
  int i, j;
  char *ret;
  
  //printf("libmine version %d\n\n", libmine_version);
 
  /* set the parameters */
  param.alpha = 0.6;
  param.c = 15;
  
  /* check the parameters */ 
  ret = mine_check_parameter(&param);
  if (ret)
  {
    printf("ERROR: %s\n", ret);
    return 1;
  }

  /* build the problem */
#ifndef BUILD_FROM_FILE	
  prob.n = 1000;
  prob.x = (double *) malloc (prob.n * sizeof (double));
  prob.y = (double *) malloc (prob.n * sizeof (double));
  for (i=0; i<prob.n; i++)
  {
    /* build x = [0, 0.005, ..., 1] */
    prob.x[i] = (double) i / (double) (prob.n-1);

    /* build y = sin(10 * pi * x) + x */
    prob.y[i] = sin(10 * PI * prob.x[i]) + prob.x[i]; 
  }
#else
	FILE *fp = fopen("data.txt","r");
	if(fp == NULL)
	{
		printf("No Input Data!\n");
		return 0;
	}
	fscanf(fp, "%d", &prob.n);
	prob.x = (double *) malloc (prob.n * sizeof (double));
	prob.y = (double *) malloc (prob.n * sizeof (double));
	for (i=0; i<prob.n; i++)
	{
		fscanf(fp, "%lf", &prob.x[i]);
	}
	for (i=0; i<prob.n; i++)
	{
		fscanf(fp, "%lf", &prob.y[i]);
	}
#endif
  /* compute score */
  score = mine_compute_score(&prob, &param);
  if (score == NULL)
  {
    printf("ERROR: mine_compute_score()\n");
    return 1;
  }

	/* print the MINE statistics */
  printf ("MINE statistics:\n\n");
  printf ("MIC: %.3lf\n", mine_mic(score));
  printf ("MAS: %.3lf\n", mine_mas(score));
  printf ("MEV: %.3lf\n", mine_mev(score));
  printf ("MCN (eps=0): %.3lf\n", mine_mcn(score, 0));
  printf ("MCN (eps=1-MIC): %.3lf\n", mine_mcn_general(score));

  /* print the characteristic matrix M */
  printf ("\nCharacteristic Matrix:\n\n");
  
  for (i=0; i<score->n; i++)
  {
    for (j=0; j<score->m[i]; j++)
			printf ("%.3lf ", score->M[i][j]);
    printf ("\n");
  }
  
  /* free score */
  mine_free_score(&score);
  
  /* free prob */
  free(prob.x);
  free(prob.y);
  
  return 0;
}
