#include <iostream>
#include <GL/freeglut.h>
#include "UtilityFunctions.h"
#include "Layer.h"
#include "Perceptron.h"

ImageHeader imgHdr;
LabelHeader lblHdr;
Perceptron oneLayerNN;

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

void TrainModel(Perceptron & layerOne)
{
    std::cout << "Running Training..." << std::endl;

    UtilityFunctions getFiles;
    std::string imgFile = "./mnist/train-images.idx3-ubyte";
    std::string lblFile = "./mnist/train-labels.idx1-ubyte";

    layerOne.InitLayer(imgHdr, lblHdr, 10);
    layerOne.SetLayer(getFiles.ReadImageFile(imgFile, imgHdr), imgHdr);
    layerOne.SetLabel(getFiles.ReadLabelFile(lblFile, lblHdr), lblHdr);
    //getFiles.DeallocateMemory();

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
    std::cout << "Checkpoint 1..." << std::endl;
    oneLayerNN.ResizePerceptron(imgHdr, lblHdr, 10);
    std::cout << "Finished running program..." << std::endl;
    //TrainModel(oneLayerNN);
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
