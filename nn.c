#ifndef draft1
#define draft1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "nn.h"
#include "dllist.h"

int main()
{
  printf("ANN Modeling Program\n");

  /* test dllist implementation */
  dllnode* list = (dllnode*)malloc(sizeof(dllnode));
  list->prev = null;
  list->next = null;
  
  list->n = 1;
  push(list, 3);
  push(list, 4);
  push(list, 6);
  
  list = removeAt(list, 0);
  
  printdllist(list);
  
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
  brain.targetValues = (float**)malloc(brain.ntargets * sizeof(float*));

  // define net output neurones
  (*brain.neurones[5]).nlayer = 1;

  // connect neurones within brain together
  AddInputtoNeurone(&brain, 0, 0);
  AddInputtoNeurone(&brain, 0, 1);
  AddInputtoNeurone(&brain, 0, 2);

  AddInputtoNeurone(&brain, 1, 1);
  AddInputtoNeurone(&brain, 1, 2);
  AddInputtoNeurone(&brain, 1, 3);

  AddInputtoNeurone(&brain, 2, 2);
  AddInputtoNeurone(&brain, 2, 3);
  AddInputtoNeurone(&brain, 2, 4);

  AddConnection(&brain, 0, 3, 0.5f);
  AddConnection(&brain, 1, 3, 0.5f);

  AddConnection(&brain, 1, 4, 0.5f);
  AddConnection(&brain, 2, 4, 0.5f);

  AddConnection(&brain, 3, 5, 0.5f);
  AddConnection(&brain, 4, 5, 0.5f);

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
    (*neurones[i]).iinputssize = 0;
    (*neurones[i]).ioutputssize = 0;
  }
}

void InitNet(net* n, float learningRate, int ninputs, float** inputs, int nneurones, neurone** neurones)
{
  n->lrate = learningRate;
  n->iter = 0;
  n->ninputs = ninputs;
  n->inputs = inputs;
  n->nneurones = nneurones;
  n->neurones = neurones;

  // init layer information
  n->nlayers = 1;
  n->ninLayer = 0;
  n->ninLayerID = 0;
  return;
}

void AssignLayersinNet(net* brain)
{
  // assign a layer to each neurone
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

  /* set up layers */
  brain->ninLayer = (int*)malloc((brain->nlayers) * sizeof(int));
  int j;
  for(j =0; j < brain->nlayers; j++)
  {
    brain->ninLayer[j] = 0;
  }

  // array to store the top of ninlayers as we push neurones onto it
  int* top = (int*)malloc(brain->nlayers * sizeof(int));
  for(j =0; j < brain->nlayers; j++)
  {
    top[j] = 0;
  }

  // record the number of neurones in each layer
  for(j =0; j < brain->nneurones; j++)
  {
    brain->ninLayer[(*brain->neurones[j]).nlayer-1]++;
  }

  // allocate memory to store neurones ids, per layer
  brain->ninLayerID = (int**)malloc((brain->nlayers) * sizeof(int*));
  for(j =0; j < brain->nlayers; j++)
  {
    brain->ninLayerID[j] = (int*)malloc(brain->ninLayer[j] * sizeof(int));
  }

  // iterate over all neurones and add their ids to each layer
  for(j =0; j < brain->nneurones; j++)
  {
    int next = top[(*brain->neurones[j]).nlayer-1];
    brain->ninLayerID[(*brain->neurones[j]).nlayer-1][next] = j;

    top[(*brain->neurones[j]).nlayer-1]++;
  }

  return;
}

void AddConnection(net* brain, int sourceN, int sinkN, float weight)
{
  /* add sinkN to sourceN as an output */
  if(brain->neurones[sourceN]->nioutputs == 0)
  {
    brain->neurones[sourceN]->nioutputs = 1;
    brain->neurones[sourceN]->ioutputssize = 1;
    brain->neurones[sourceN]->ioutputs = (int*)malloc(sizeof(int));
  }
  else if(brain->neurones[sourceN]->nioutputs == brain->neurones[sourceN]->ioutputssize)
  {
    int* resizedList = (int*)malloc(brain->neurones[sourceN]->ioutputssize * sizeof(int) * 2);
    memcpy(resizedList, brain->neurones[sourceN]->ioutputs, (brain->neurones[sourceN]->nioutputs * sizeof(int)));
    free(brain->neurones[sourceN]->ioutputs);
    brain->neurones[sourceN]->ioutputs = resizedList;

    brain->neurones[sourceN]->ioutputssize *= 2;
    brain->neurones[sourceN]->nioutputs++;
  }
  else
  {
    brain->neurones[sourceN]->nioutputs++;
  }
  brain->neurones[sourceN]->ioutputs[brain->neurones[sourceN]->nioutputs-1] = sinkN;

  /* add sourceN to sinkN as an input, with its associated weight */
  if(brain->neurones[sinkN]->niinputs == 0)
  {
    brain->neurones[sinkN]->niinputs++;
    brain->neurones[sinkN]->iinputssize++;
    brain->neurones[sinkN]->iinputs = (int*)malloc(sizeof(int));
    brain->neurones[sinkN]->weights = (float*)malloc(sizeof(float));
  }
  else if(brain->neurones[sinkN]->niinputs == brain->neurones[sinkN]->iinputssize)
  {
    // double physical size of iinputs
    int* resizedList = (int*)malloc(brain->neurones[sinkN]->iinputssize * sizeof(int) * 2);
    memcpy(resizedList, brain->neurones[sinkN]->iinputs, (brain->neurones[sinkN]->niinputs * sizeof(int)));
    free(brain->neurones[sinkN]->iinputs);
    brain->neurones[sinkN]->iinputs = resizedList;

    //double physical size of weights
    float* resizedList2 = (float*)malloc(brain->neurones[sinkN]->iinputssize * sizeof(float) * 2);
    memcpy(resizedList2, brain->neurones[sinkN]->weights, (brain->neurones[sinkN]->niinputs * sizeof(float)));
    free(brain->neurones[sinkN]->weights);
    brain->neurones[sinkN]->weights = resizedList2;

    brain->neurones[sinkN]->iinputssize *= 2;
    brain->neurones[sinkN]->niinputs++;
  }
  else
  {
    brain->neurones[sinkN]->niinputs++;
  }
  brain->neurones[sinkN]->iinputs[brain->neurones[sinkN]->niinputs-1] = sourceN;
  brain->neurones[sinkN]->weights[brain->neurones[sinkN]->niinputs-1] = weight;

  return;
}

void AddInputtoNeurone(net* brain, int neuroneID, int inputIndex)
{
  if(brain->neurones[neuroneID]->nninputs == 0)
  {
    brain->neurones[neuroneID]->nninputs = 1;
    brain->neurones[neuroneID]->nninputssize = 1;
    brain->neurones[neuroneID]->ninputs = (int*)malloc(sizeof(int));
  }
  else if(brain->neurones[neuroneID]->nninputs == brain->neurones[neuroneID]->nninputssize)
  {
    int* resizedList = (int*)malloc(brain->neurones[neuroneID]->nninputssize * sizeof(int) * 2);
    memcpy(resizedList, brain->neurones[neuroneID]->ninputs, (brain->neurones[neuroneID]->nninputs * sizeof(int)));
    free(brain->neurones[neuroneID]->ninputs);
    brain->neurones[neuroneID]->ninputs = resizedList;
    
    brain->neurones[neuroneID]->nninputssize *= 2;
    brain->neurones[neuroneID]->nninputs++;
  }
  else
  {
    brain->neurones[neuroneID]->nninputs++;
  }
    brain->neurones[neuroneID]->ninputs[brain->neurones[neuroneID]->nninputs-1] = inputIndex;
  
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
