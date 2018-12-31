//
// Created by becky on 23/12/2018.
//

#include <cstdlib>
#include <GL/freeglut.h>
#include <iostream>
#include "Perceptron.h"
#include "ImageHeader.h"

Perceptron::Perceptron()
{
    layerOne = new Layer();
    layerSize = 1;
    imgLbl = new GLdouble();
}

Perceptron::Perceptron(ImageHeader imgHdr, LabelHeader lblHdr, int inputSize)
{
    std::cout << "num of images: " << imgHdr.maxImages << std::endl;

    layerOne = new Layer(imgHdr, lblHdr, inputSize);
    imgLbl = new GLdouble[lblHdr.maxLabels]();
}

Perceptron::~Perceptron()
{
    delete[] layerOne;
    delete[] imgLbl;
}

Layer * Perceptron::GetLayer()
{
    return layerOne;
}

void Perceptron::InitLayer(ImageHeader imgHdr, LabelHeader lblHdr, int inputSize)
{
    std::cout << "Running initialisation..." << std::endl;

    for(int ii = 0; ii < inputSize; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.maxImages; jj += 1)
        {
            for(int kk = 0; jj < imgHdr.imgWidth; kk += 1)
            {
                for(int ll = 0; ll < imgHdr.imgHeight; ll += 1)
                {
                    layerOne->GetNeurons()[ii].inputArr[jj][kk][ll] = 0;
                    layerOne->GetNeurons()[ii].weight[jj][kk][ll] = 0;
                }
            }

        }

        layerOne->GetNeurons()[ii].bias = 0;
        layerOne->GetNeurons()[ii].output = 0;
    }

    for(int aa = 0; aa < lblHdr.maxLabels; aa += 1)
    {
        imgLbl[aa] = 0;
    }
}

void Perceptron::ResizePerceptron(ImageHeader imgHdr, LabelHeader lblHdr, int inputSize)
{
    std::cout << "Running Resize perceptron..." << std::endl;

    layerOne->ResizeLayer(imgHdr, lblHdr, inputSize);

    std::cout << "Finished resizing perceptron..." << std::endl;
}

void Perceptron::SetLayer(GLdouble*** imgInput, ImageHeader imgHdr)
{
    for(int ii = 0; ii < 10; ii += 1)
    {
        for(int jj = 0; jj < imgHdr.maxImages; jj += 1)
        {
            for(int kk = 0; kk < imgHdr.imgWidth; kk += 1)
            {
                for(int ll = 0; ll < imgHdr.imgHeight; ll += 1)
                {
                    layerOne->GetNeurons()[ii].inputArr[jj][kk][ll] = imgInput[jj][kk][ll];
                }
            }
        }
    }
}

void Perceptron::SetLabel(GLdouble *lblInput, LabelHeader lblHdr)
{
    for(int ii = 0; ii < lblHdr.maxLabels; ii += 1)
    {
        imgLbl[ii] = lblInput[ii];
    }
}


