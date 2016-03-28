#ifndef draft1
#define draft1

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nn.h"

int main()
{
  printf("ANN Modeling Program\n");

  // initialise 5 inputs
  int ninputs = 5;
  float** inputs;
  inputs = (float**)malloc(ninputs * sizeof(float*));
  InitInputs(ninputs, inputs, 0.5f);
  
  // initialise 6 neurones
  int nneurones = 6;
  neurone** neurones;
  neurones = (neurone**)malloc(nneurones * sizeof(neurone*));
  InitNeurones(nneurones, neurones);
  
  // initialise 'brain'
  net brain;
  InitNet(&brain, 1.0f, ninputs, inputs, nneurones, neurones);
  brain.ntargets = 1;
  brain.targetNeurones = (int*)malloc(brain.ntargets * sizeof(int));
  brain.targetValues = (float*)malloc(brain.ntargets * sizeof(float));

  // define net output neurones
  (*brain.neurones[5]).nlayer = 1;

  // connect neurones within brain together
  (*brain.neurones[0]).nninputs = 3;
  (*brain.neurones[0]).ninputs = (int*)malloc((*brain.neurones[0]).nninputs * sizeof(int));
  (*brain.neurones[0]).ninputs[0] = 0;
  (*brain.neurones[0]).ninputs[1] = 1;
  (*brain.neurones[0]).ninputs[2] = 2;

  (*brain.neurones[1]).nninputs = 3;
  (*brain.neurones[1]).ninputs = (int*)malloc((*brain.neurones[1]).nninputs * sizeof(int));
  (*brain.neurones[1]).ninputs[0] = 1;
  (*brain.neurones[1]).ninputs[1] = 2;
  (*brain.neurones[1]).ninputs[2] = 3;

  (*brain.neurones[2]).nninputs = 3;
  (*brain.neurones[2]).ninputs = (int*)malloc((*brain.neurones[2]).nninputs * sizeof(int));
  (*brain.neurones[2]).ninputs[0] = 2;
  (*brain.neurones[2]).ninputs[1] = 3;
  (*brain.neurones[2]).ninputs[2] = 4;

  (*brain.neurones[3]).niinputs = 2;
  (*brain.neurones[3]).iinputs = (int*)malloc((*brain.neurones[3]).niinputs * sizeof(int));
  (*brain.neurones[3]).iinputs[0] = 0;
  (*brain.neurones[3]).iinputs[1] = 1;
  (*brain.neurones[3]).weights = (float*)malloc((*brain.neurones[3]).niinputs * sizeof(float));
  (*brain.neurones[3]).weights[0] = 0.5f;
  (*brain.neurones[3]).weights[1] = 0.5f;

  (*brain.neurones[4]).niinputs = 2;
  (*brain.neurones[4]).iinputs = (int*)malloc((*brain.neurones[4]).niinputs * sizeof(int));
  (*brain.neurones[4]).iinputs[0] = 1;
  (*brain.neurones[4]).iinputs[1] = 2;
  (*brain.neurones[4]).weights = (float*)malloc((*brain.neurones[4]).niinputs * sizeof(float));
  (*brain.neurones[4]).weights[0] = 0.5f;
  (*brain.neurones[4]).weights[1] = 0.5f;

  (*brain.neurones[5]).niinputs = 2;
  (*brain.neurones[5]).iinputs = (int*)malloc((*brain.neurones[5]).niinputs * sizeof(int));
  (*brain.neurones[5]).iinputs[0] = 3;
  (*brain.neurones[5]).iinputs[1] = 4;
  (*brain.neurones[5]).weights = (float*)malloc((*brain.neurones[5]).niinputs * sizeof(float));
  (*brain.neurones[5]).weights[0] = 0.5f;
  (*brain.neurones[5]).weights[1] = 0.5f;

  // assign neurones to layers
  AssignLayersinNet(&brain);

  // main loop
  int maxIters = 200;
  int i;
  for(i =0; i <= maxIters; i++)
  {
    // iterate over neurones in brain
    int j;
    for(j =0; j < brain.nneurones; j++)
    {
      //temp accumalator
      float t = 0;

      int k;
      // iterate over net inputs at this neurone
      for(k =0; k < (*brain.neurones[j]).nninputs; k++)
      {
        t += *brain.inputs[(*brain.neurones[j]).ninputs[k]];
      }
      
      // iterate over neurone inputs at this neurone
      for(k =0; k < (*brain.neurones[j]).niinputs; k++)
      {
        t += (*brain.neurones[j]).weights[k] * (*brain.neurones[(*brain.neurones[j]).iinputs[k]]).output0;
      }

      // set neurone output to t
      (*brain.neurones[j]).output1 = (float)(1.0f - exp(-t))/(1.0f + exp(-t));
    }

    /* train nn with the back propagation algorithm */
    
    float t = 0.75f;
    
    // iterate over neurones in final layer
    for(j =0; j < brain.nneurones; j++)
    {
      if((*brain.neurones[j]).nlayer = brain.nlayers)
      {
        (*brain.neurones[j]).delta = ((*brain.neurones[j]).output1 - t) * (*brain.neurones[j]).output1 * (1.0f - (*brain.neurones[j]).output1);
      }
    }
    
    // iterate over layers
    int layer;
    for(layer = brain.nlayers-1; layer > 0; layer--)
    {
      for(j =0; j < brain.nneurones; j++)
      {
        if((*brain.neurones[j]).nlayer == layer)
        {
          float sigma = 0;
          int k;
          for(k =0; k < brain.nneurones; k++)
          {
            if((*brain.neurones[k]).nlayer == layer+1)
            {
              int l;
              for(l = 0; l < (*brain.neurones[k]).niinputs; l++)
              {
                if((*brain.neurones[k]).iinputs[l] == j)
                {
                  sigma += (*brain.neurones[k]).weights[l] * (*brain.neurones[k]).output1;
                }
              }
            }
          }
      
          (*brain.neurones[j]).delta = (sigma) * (*brain.neurones[j]).output1 * (1.0f - (*brain.neurones[j]).output1);
        }
      }
    }
    
    // update weights
    for(j =0; j < brain.nneurones; j++)
    {
      int k;
      for(k =0; k < (*brain.neurones[j]).niinputs; k++)
      {
        float update = brain.lrate * (*brain.neurones[j]).delta * (*brain.neurones[(*brain.neurones[j]).iinputs[k]]).output0;
        (*brain.neurones[j]).weights[k] -= update;
      }
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

void InitInputs(int ninputs, float** inputs, float defaultValue)
{
  int i;
  for(i =0; i <= ninputs; i++)
  {
    inputs[i] = (float*)malloc(sizeof(float));
    *inputs[i] = 1;
  }
  return;
}

void InitNeurones(int nneurones, neurone** neurones)
{
  int i;
  for(i =0; i <= nneurones; i++)
  {
    neurones[i] = (neurone*)malloc(sizeof(neurone));
    (*neurones[i]).nninputs = 0;
    (*neurones[i]).niinputs = 0;
    (*neurones[i]).nlayer  = -1;
    (*neurones[i]).output0 = 0;
    (*neurones[i]).output1 = 0;
  }
}

void InitNet(net* n, float learningRate, int ninputs, float** inputs, int nneurones, neurone** neurones)
{
  n->lrate = learningRate;
  n->nlayers = 1;
  n->iter = 0;
  n->ninputs = ninputs;
  n->inputs = inputs;
  n->nneurones = nneurones;
  n->neurones = neurones;
  return;
}

void AssignLayersinNet(net* brain)
{
  int changed = 1;
  while(changed)
  {
    changed = 0;

    // iterate over each neurone
    int j;
    for(j =0; j < brain->nneurones; j++)
    {
      // if this neurone has been assigned a layer
      if((*brain->neurones[j]).nlayer > 0)
      {
        // iterate over neurone inputs
        int k;
        for(k =0; k < (*brain->neurones[j]).niinputs; k++)
        {
          // if new layer value is larger than previous, update
          if((*brain->neurones[(*brain->neurones[j]).iinputs[k]]).nlayer < (*brain->neurones[j]).nlayer+1)
          {
            (*brain->neurones[(*brain->neurones[j]).iinputs[k]]).nlayer = (*brain->neurones[j]).nlayer+1;
            changed = 1;
            
            // set number of layers in net
            if(brain->nlayers < (*brain->neurones[j]).nlayer+1)
              brain->nlayers = (*brain->neurones[j]).nlayer+1;
          }
        }
      }
    }
  }
  return;
}

float getGlobalError(int noutputs, neurone** outputs, float* targets)
{
  // Error value at each output neurone is 0.5*(target - output)^2
  // Total error is simply the sum of all the error values

  float terror = 0.0f;

  int out;
  for(out =0; out < noutputs; out++)
  {
    terror += 0.5*(targets[out] - outputs[out]->output1)*(targets[out] - outputs[out]->output1);
  }

  return terror;
}

void updateWeights()
{
  return;
}

#endif
