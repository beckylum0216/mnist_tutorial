#include <iostream>
#include <GL/freeglut.h>
#include "UtilityFunctions.h"
#include "Layer.h"
#include "Perceptron.h"

ImageHeader imgHdr;
LabelHeader lblHdr;
Perceptron * oneLayerNN;

void init(ImageHeader &imgHdr, LabelHeader &lblHdr)
{

}

void GetHeaders()
{
    UtilityFunctions getFiles;
    std::string imgFile = "./mnist/train-images.idx3-ubyte";
    std::string lblFile = "./mnist/train-labels.idx1-ubyte";

    imgHdr = getFiles.ReadImageHeader(imgFile);
    lblHdr = getFiles.ReadLabelHeader(lblFile);
}

void TrainModel(Perceptron * & layerOne)
{
    std::cout << "Running Training..." << std::endl;

    UtilityFunctions getFiles;
    std::string imgFile = "./mnist/train-images.idx3-ubyte";
    std::string lblFile = "./mnist/train-labels.idx1-ubyte";

    layerOne->SetLabel(getFiles.ReadLabelFile(lblFile, lblHdr), lblHdr);

    GLdouble *** tempImgMatrix = new GLdouble **[imgHdr.maxImages]();
    for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
    {
        tempImgMatrix[ii] = new GLdouble*[imgHdr.imgWidth]();
        for(int jj = 0; jj < imgHdr.imgHeight; jj += 1)
        {
            tempImgMatrix[ii][jj] = new GLdouble[imgHdr.imgWidth]();
        }
    }

    tempImgMatrix = getFiles.ReadImageFile(imgFile, imgHdr);

    layerOne->InitLayer(imgHdr, lblHdr, 10);

    for(int epoch = 0; epoch < 10; epoch += 1)
    {
        for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
        {
            layerOne->SetLayer(tempImgMatrix[ii], imgHdr, 10);
            layerOne->CalculateOutput(imgHdr, 10);
        }

        // calculate error and update weights
        for(int ii = 0; ii < 10; ii += 1)
        {
            GLdouble stdError;
            stdError = layerOne->CalculateError(imgHdr, ii);
            layerOne->UpdateNeuronWeights(imgHdr, ii, stdError, 0.001);

        }
    }


    delete [] tempImgMatrix;
}

void GetTestingHeaders()
{
    UtilityFunctions getFiles;
    std::string imgFile = "./mnist/t10k-images.idx3-ubyte";
    std::string lblFile = "./mnist/t10k-labels.idx1-ubyte";

    imgHdr = getFiles.ReadImageHeader(imgFile);
    lblHdr = getFiles.ReadLabelHeader(lblFile);
}


void TestModel(Perceptron * layerOne)
{
    UtilityFunctions getFiles;
    std::string imgFile = "./mnist/t10k-images.idx3-ubyte";
    std::string lblFile = "./mnist/t10k-labels.idx1-ubyte";

    GLdouble * testImgLbl = new GLdouble[lblHdr.maxLabels]();
    testImgLbl = getFiles.ReadLabelFile(lblFile, lblHdr);

    GLdouble *** testImgMatrix = new GLdouble **[imgHdr.maxImages]();
    for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
    {
        testImgMatrix[ii] = new GLdouble*[imgHdr.imgWidth]();
        for(int jj = 0; jj < imgHdr.imgHeight; jj += 1)
        {
            testImgMatrix[ii][jj] = new GLdouble[imgHdr.imgWidth]();
        }
    }

    testImgMatrix = getFiles.ReadImageFile(imgFile, imgHdr);

    int errorCount = 0;

    for(int ii = 0; ii < imgHdr.maxImages; ii += 1)
    {

        layerOne->SetLayer(testImgMatrix[ii], imgHdr, 10);
        layerOne->CalculateOutput(imgHdr, 10);

        int layerPrediction = layerOne->GetLayerPrediction(10);

        if(layerPrediction != testImgLbl[ii])
        {
            errorCount++;
        }

        std::cout << "Prediction: " << layerPrediction << " Actual: " << testImgLbl[ii] << std::endl;


    }
    double tempErrorRate;
    tempErrorRate = (double) errorCount / imgHdr.maxImages;
    std::cout.precision(5);
    std::cout << "Error Count: " << errorCount << " % incorrect: " << std::fixed << tempErrorRate << std::endl;
}

void display()
{

    // clear the drawing buffer. dont need depth but anyways
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    GLdouble width = w;
    GLdouble height = h;

    glViewport(0, 0, w, h);
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0) h = 1;
    GLfloat ratio = 1.0f * w / h;
    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    //gluPerspective(45, ratio, 1, 500);
    gluOrtho2D(0.0, (1.0/width)* imgHdr.imgWidth, 0.0, (1.0/height)*imgHdr.imgHeight);
    //gluLookAt(0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
    GetHeaders();
    oneLayerNN = new Perceptron(imgHdr, lblHdr, 10);

    TrainModel(oneLayerNN);
    GetTestingHeaders();
    TestModel(oneLayerNN);

    return 0;
}

/*
int main(int argc, char** argv)
{


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(50,50);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Image");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    std::cout << "Checkpoint 1..." << std::endl;
    glutMainLoop();
    return 0;
}
*/
