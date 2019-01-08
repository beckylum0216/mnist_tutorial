//
// Created by becky on 23/12/2018.
//

#ifndef DEEPLENS_RL_33111264_PERCEPTRON_H
#define DEEPLENS_RL_33111264_PERCEPTRON_H

#include <vector>
#include "Layer.h"
#include "ImageHeader.h"

class Perceptron {
    public:
        Perceptron();
        Perceptron(ImageHeader imgHdr, LabelHeader lblHdr, int inputSize);
        ~Perceptron();
        Layer * GetLayer();
        void InitLayer(ImageHeader imgHdr, LabelHeader lblHdr, int inputSize);
        void ResizePerceptron(ImageHeader imgHdr, LabelHeader lblHdr, int inputSize);
        //training perceptron
        void SetLayer(GLdouble** imgInput, ImageHeader imgHdr, int inputSize);
        void SetLabel(GLdouble * lblInput, LabelHeader lblHdr);
        void CalculateOutput(ImageHeader imgHdr, int inputSize);
        GLdouble CalculateError(ImageHeader imgHdr, int targetNeuron);
        void UpdateNeuronWeights(ImageHeader imgHdr, int targetNeuron, GLdouble stdError, GLdouble learningRate);

        // testing perceptron
        std::vector <GLdouble> SetTargetOutput(int targetIndex, int outputSize);
        int  GetLayerPrediction(int outputSize);

    private:
        Layer * layerOne;
        int layerSize;
        GLdouble * imgLbl;

};


#endif //DEEPLENS_RL_33111264_PERCEPTRON_H
