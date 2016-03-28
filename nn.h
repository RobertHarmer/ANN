#ifndef NN_H
#define NN_H

typedef struct neurone neurone;
struct neurone
{
  float delta;
  int id; // id = index
  int niinputs; // number of inputs neurones
  int* iinputs; // indices of input neurones
  float* weights; // weights
  int nninputs; // number of net inputs
  int* ninputs; //indices of net inputs
  float output0; // last iter
  float output1; // current iter
  int nlayer;
};

typedef struct net net;
struct net
{
  float lrate;
  int nlayers;
  int iter;
  int ninputs;
  float** inputs;
  int nneurones;
  neurone** neurones;
  
  int ntargets;
  int* targetNeurones;
  float* targetValues;
};

void InitInputs(int ninputs, float** inputs, float defaultValue);
void InitNeurones(int nneurones, neurone** neurones);
void InitNet(net* n,float learningRate, int ninputs, float** inputs, int nneurones, neurone** neurones);
void AssignLayersinNet(net* brain);
float getGlobalError(int noutputs, neurone** outputs, float* targets);
void updateWeights();


#endif