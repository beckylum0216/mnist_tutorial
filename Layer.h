//
// Created by becky on 24/12/2018.
//

#ifndef DEEPLENS_RL_33111264_LAYER_H
#define DEEPLENS_RL_33111264_LAYER_H


#include "Neuron.h"
#include "ImageHeader.h"
#include "LabelHeader.h"

class Layer {
    public:
        Layer();
        Layer(ImageHeader imgHdr, LabelHeader lblHdr, int inputSize);
        ~Layer();
        Layer & operator= (Layer rhsVar);
        Neuron * GetNeurons();
        void ResizeLayer(ImageHeader imgHdr, LabelHeader lblHdr, int inputSize);



    private:
        Neuron * theNeurons;
        int neuronSize;
        void Swap(Layer &rhsVar);

};


#endif //DEEPLENS_RL_33111264_LAYER_H
