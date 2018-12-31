//
// Created by becky on 24/12/2018.
//

#include <vector>
#include <iostream>
#include "Layer.h"

Layer::Layer()
{
    theNeurons = new Neuron[10]();
    neuronSize = 10;
}


Layer::Layer(ImageHeader imgHdr, LabelHeader lblHdr, int inputSize)
{
    std::cout << "running layer resize" << std::endl;
   for(int ii = 0; ii < neuronSize; ii += 1)
   {
       theNeurons[ii].ResizeNeuron(imgHdr, lblHdr);
   }
   neuronSize = inputSize;
   std::cout << "layer resized..." << std::endl;
}

Layer::~Layer()
{
    delete [] theNeurons;
}

Layer& Layer::operator=(Layer rhsVar)
{
    this->Swap(rhsVar);
    return *this;
}

void Layer::Swap(Layer &rhsVar)
{
    std::swap(this->theNeurons, rhsVar.theNeurons);
}

Neuron * Layer::GetNeurons()
{
    return theNeurons;
}

void Layer::ResizeLayer(ImageHeader imgHdr, LabelHeader lblHdr, int inputSize)
{
    std::cout << "Running layer resize..." << std::endl;

    // initialise temp neuron
    Neuron * tempNeuron;
    tempNeuron = new Neuron[inputSize];

    // resizing temp neuron
    for(int ii = 0; ii < inputSize; ii += 1)
    {
        std::cout << "Neuron index: " << ii << std::endl;
        tempNeuron[ii].ResizeNeuron(imgHdr, lblHdr);
    }


    for(int jj = 0; jj < neuronSize; jj += 1)
    {
        tempNeuron[jj] = this->theNeurons[jj];
    }

    neuronSize = inputSize;

    delete [] theNeurons;

    theNeurons = new Neuron[inputSize]();

    for(int ii = 0; ii < inputSize; ii += 1)
    {
        theNeurons[ii].ResizeNeuron(imgHdr, lblHdr);
    }

    for(int ii = 0; ii < inputSize; ii += 1)
    {
        theNeurons[ii] = tempNeuron[ii];
    }

    delete[] tempNeuron;

    std::cout << "Finished resizing layer..." << std::endl;
}