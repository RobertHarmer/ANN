#ifndef draft1
#define draft1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct neurone neurone;
struct neurone
{
  int ninputs;
  float** inputs;
  float output0; // last iter
  float output1; // current iter
};

typedef struct net net;
struct net
{
  int iter;
  int ninputs;
  float** inputs;
  int nneurones;
  neurone** neurones;
};


int main()
{
  printf("ANN Modeling Program\n");

  // initialise 5 inputs
  int ninputs = 5;
  float** inputs;
  inputs = (float**)malloc(ninputs * sizeof(float*));
  int i;
  for(i =0; i <= ninputs; i++)
  {
    inputs[i] = (float*)malloc(sizeof(float));
    *inputs[i] = 1;
  }

  // initialise 6 neurones
  int nneurones = 6;
  neurone** neurones;
  neurones = (neurone**)malloc(nneurones * sizeof(neurone*));
  for(i =0; i <= nneurones; i++)
  {
    neurones[i] = (neurone*)malloc(sizeof(neurone));
    (*neurones[i]).output0 = 0;
    (*neurones[i]).output1 = 0;
  }

  // initialise 'brain'
  net brain;
  brain.iter = 0;
  brain.ninputs = ninputs;
  brain.inputs = inputs;
  brain.nneurones = nneurones;
  brain.neurones = neurones;

  // connect neurones within brain together
  (*brain.neurones[0]).ninputs = 3;
  (*brain.neurones[0]).inputs = (float**)malloc((*brain.neurones[0]).ninputs * sizeof(float*));
  (*brain.neurones[0]).inputs[0] = brain.inputs[0];
  (*brain.neurones[0]).inputs[1] = brain.inputs[1];
  (*brain.neurones[0]).inputs[2] = brain.inputs[2];

  (*brain.neurones[1]).ninputs = 3;
  (*brain.neurones[1]).inputs = (float**)malloc((*brain.neurones[1]).ninputs * sizeof(float*));
  (*brain.neurones[1]).inputs[0] = brain.inputs[1];
  (*brain.neurones[1]).inputs[1] = brain.inputs[2];
  (*brain.neurones[1]).inputs[2] = brain.inputs[3];

  (*brain.neurones[2]).ninputs = 3;
  (*brain.neurones[2]).inputs = (float**)malloc((*brain.neurones[2]).ninputs * sizeof(float*));
  (*brain.neurones[2]).inputs[0] = brain.inputs[2];
  (*brain.neurones[2]).inputs[1] = brain.inputs[3];
  (*brain.neurones[2]).inputs[2] = brain.inputs[4];

  (*brain.neurones[3]).ninputs = 2;
  (*brain.neurones[3]).inputs = (float**)malloc((*brain.neurones[3]).ninputs * sizeof(float*));
  (*brain.neurones[3]).inputs[0] = &(*brain.neurones[0]).output0;
  (*brain.neurones[3]).inputs[1] = &(*brain.neurones[1]).output0;

  (*brain.neurones[4]).ninputs = 2;
  (*brain.neurones[4]).inputs = (float**)malloc((*brain.neurones[4]).ninputs * sizeof(float*));
  (*brain.neurones[4]).inputs[0] = &(*brain.neurones[1]).output0;
  (*brain.neurones[4]).inputs[1] = &(*brain.neurones[2]).output0;

  (*brain.neurones[5]).ninputs = 2;
  (*brain.neurones[5]).inputs = (float**)malloc((*brain.neurones[5]).ninputs * sizeof(float*));
  (*brain.neurones[5]).inputs[0] = &(*brain.neurones[3]).output0;
  (*brain.neurones[5]).inputs[1] = &(*brain.neurones[4]).output0;

  // main loop
  int maxIters = 100;
  for(i =0; i <= maxIters; i++)
  {
    // iterate over neurones in brain
    int j;
    for(j =0; j < brain.nneurones; j++)
    {
      //temp accumalator
      float t = 0;

      int k;
      for(k =0; k < (*brain.neurones[j]).ninputs; k++)
      {
        t += *(*brain.neurones[j]).inputs[k];
      }

      // set neurone output to t
      (*brain.neurones[j]).output1 = (float)(1.0f - exp(-t))/(1.0f + exp(-t));
    }

    // set last iter values as current iter
    for(j =0; j < brain.nneurones; j++)
    {
      (*brain.neurones[j]).output0 = (*brain.neurones[j]).output1;
    }

    // print neurone 6's output
//    printf("Output for neurone 6: %f\n", (*brain.neurones[5]).output0);
 printf("%d, %f\n",i, (*brain.neurones[5]).output0);
  }
}
#endif
