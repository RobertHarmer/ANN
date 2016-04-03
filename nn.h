#ifndef NN_H
#define NN_H

typedef struct neurone neurone;
struct neurone
{
  float delta;
  int id; // id = index
  
  // Net Inputs at this Neurone
  int nninputs; // number of net inputs
  int* ninputs; //indices of net inputs
  int nninputssize; // actual size of nninputs
  
  
  // Input Neurones
  int niinputs; // number of inputs neurones
  int* iinputs; // indices of input neurones
  float* weights; // associated weights
  int iinputssize; // actual size of iinputs
  
  // Output Neurones
  int nioutputs;
  int* ioutputs;
  int ioutputssize; // actual size of ionputs
    
  float output0; // last iter
  float output1; // current iter
  int nlayer;
};

typedef struct net net;
struct net
{
  float lrate;
  int iter;
  int ninputs;
  float** inputs;
  int nneurones;
  neurone** neurones;
  
  int ntargets;
  int* targetNeurones;
  float** targetValues;
  
  // layers
  int nlayers;
  int* ninLayer;
  int** ninLayerID;
};

void InitInputs(int ninputs, float** inputs, float defaultValue);
void InitNeurones(int nneurones, neurone** neurones);
void InitNet(net* n,float learningRate, int ninputs, float** inputs, int nneurones, neurone** neurones);
void AssignLayersinNet(net* brain);
float getGlobalError(int noutputs, neurone** outputs, float* targets);
void AddConnection(net* brain, int sourceN, int sinkN, float weight);
void AddInputtoNeurone(net* brain, int neuroneID, int inputIndex);
void updateWeights();


#endif