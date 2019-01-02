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
        void SetLayer(GLdouble** imgInput, ImageHeader imgHdr);
        void SetLabel(GLdouble * lblInput, LabelHeader lblHdr);
        void CalculateWeight();

    private:
        Layer * layerOne;
        int layerSize;
        GLdouble * imgLbl;

};


#endif //DEEPLENS_RL_33111264_PERCEPTRON_H
