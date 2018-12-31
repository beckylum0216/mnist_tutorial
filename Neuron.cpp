//
// Created by becky on 23/12/2018.
//

#include <iostream>
#include "Neuron.h"

Neuron::Neuron()
{
    inputArr = new GLdouble **[10]();
    weight = new GLdouble **[10]();

    for(int ii = 0; ii < 10; ii +=1)
    {
        inputArr[ii] = new GLdouble * [28]();
        weight[ii] = new GLdouble * [28]();
        for (int jj = 0; jj < 28; jj += 1)
        {
            inputArr[ii][jj] = new GLdouble[28]();
            weight[ii][jj] = new GLdouble[28]();
        }
    }


    output = 0;
    bias = 0;
}

Neuron::Neuron(ImageHeader imgHdr, LabelHeader lblHdr)
{
    GLdouble *** tempArr;
    GLdouble *** tempWeight;

    // initialise new arrays;
    tempArr = new GLdouble **[imgHdr.maxImages];
    tempWeight = new GLdouble **[imgHdr.maxImages];
    for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
    {
        tempArr[ii] = new GLdouble*[imgHdr.imgWidth];
        tempWeight[ii] = new GLdouble*[imgHdr.imgWidth];
        for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
        {
            tempArr[ii][jj] = new GLdouble[imgHdr.imgHeight];
            tempWeight[ii][jj] = new GLdouble[imgHdr.imgHeight];
        }
    }

    for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
        {
            tempWeight[ii] = new GLdouble*[imgHdr.imgWidth];
            for(int kk = 0; kk < imgHdr.imgHeight; kk += 1)
            {
                tempArr[ii][jj][kk] = inputArr[ii][jj][kk];
                tempWeight[ii][jj][kk] = weight[ii][jj][kk];
            }
        }
    }

    delete [] inputArr;
    delete [] weight;

    inputArr = tempArr;
    weight = tempWeight;

    delete [] tempArr;
    delete [] tempWeight;
}

Neuron::~Neuron()
{
    delete [] inputArr;
    delete [] weight;
}

Neuron& Neuron::operator=(Neuron rhsNeuron)
{
    this->Swap(rhsNeuron);
    return *this;
}

void Neuron::Swap(Neuron &rhsNeuron)
{
    std::swap(this->inputArr, rhsNeuron.inputArr);
    std::swap(this->weight, rhsNeuron.weight);
    std::swap(this->output, rhsNeuron.output);
    std::swap(this->bias, rhsNeuron.bias);

}

void Neuron::ResizeNeuron(ImageHeader imgHdr, LabelHeader lblHdr){
    std::cout << "Running neuron resize..." << std::endl;

    GLdouble *** tempArr;
    GLdouble *** tempWeight;

    // initialise new arrays;
    tempArr = new GLdouble **[imgHdr.maxImages];
    tempWeight = new GLdouble **[imgHdr.maxImages];
    for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
    {
        tempArr[ii] = new GLdouble*[imgHdr.imgWidth];
        tempWeight[ii] = new GLdouble*[imgHdr.imgWidth];
        for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
        {
            tempArr[ii][jj] = new GLdouble[imgHdr.imgHeight];
            tempWeight[ii][jj] = new GLdouble[imgHdr.imgHeight];
        }
    }

    // copying original arrays
    for(int ii = 0; ii < 10; ii += 1)
    {
        for(int jj = 0; jj < 28; jj += 1)
        {
            for(int kk = 0; kk < 28; kk += 1)
            {
                tempArr[ii][jj][kk] = inputArr[ii][jj][kk];
                tempWeight[ii][jj][kk] = weight[ii][jj][kk];
            }
        }
    }

    // clear arrays
    delete [] inputArr;
    delete [] weight;

    // redeclaring arrays and copying contents from temp to class arrays
    inputArr = new GLdouble ** [imgHdr.maxImages]();
    weight = new GLdouble ** [imgHdr.maxImages]();
    for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
    {
        inputArr[ii] = new GLdouble * [imgHdr.imgWidth]();
        weight[ii] = new GLdouble * [imgHdr.imgWidth]();
        for(int jj = 0; jj < imgHdr.imgWidth; jj += 1)
        {
            inputArr[ii][jj] = new GLdouble [imgHdr.imgHeight]();
            weight[ii][jj] = new GLdouble [imgHdr.imgHeight]();
            for(int kk = 0; kk < imgHdr.imgHeight; kk += 1)
            {
                tempArr[ii][jj][kk] = inputArr[ii][jj][kk];
                tempWeight[ii][jj][kk] = weight[ii][jj][kk];
            }
        }
    }

    delete [] tempArr;
    delete [] tempWeight;

    std::cout << "Finished resizing neuron..." << std::endl;
}