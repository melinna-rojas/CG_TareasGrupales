//============================================================================
// 			TAREA 08
// Profesor		: Herminio Paucar
// Integrantes	:
//
//============================================================================

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

// Include GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

#include <string>
#include <fstream>
#include "Utils.h"

using namespace std;
GLuint renderingProgram;

GLfloat *m_Vertices;

GLuint m_VBO;
GLuint m_VAO;

//Para crear mis circulos
GLint numberOfSides = 1000;
GLint numberOfVertices = numberOfSides + 2;

float curAngle = 0.0f;
void drawCircles(GLfloat x, GLfloat y, GLfloat z, GLfloat r, GLfloat g, GLfloat b, GLfloat radius, GLfloat matriz[])
{

    GLfloat twicePi = 2.0f * M_PI;

    GLfloat verticesX[numberOfVertices];
    GLfloat verticesY[numberOfVertices];
    GLfloat verticesZ[numberOfVertices];

    verticesX[0] = x;
    verticesY[0] = y;
    verticesZ[0] = z;

    //Creo los puntos
    for (int i = 1; i < numberOfVertices; i++)
    {
        verticesX[i] = x + (radius * cos(i * twicePi / numberOfSides));
        verticesY[i] = y + (radius * sin(i * twicePi / numberOfSides));
        verticesZ[i] = z;
    }

    //Acá relleno la matriz con los puntos creados en la otra funcion
    for (int i = 0; i < numberOfVertices; i++)
    {
        matriz[i * 3] = verticesX[i];
        matriz[i * 3 + 1] = verticesY[i];
        matriz[i * 3 + 2] = verticesZ[i];
        //matriz[i * 6 + 3] = r;
        //matriz[i * 6 + 4] = g;
        //matriz[i * 6 + 5] = b;
    }
}

class wcPt3D
{
public:
    GLfloat x, y, z;
};

void computeBezPt(GLfloat u, wcPt3D *bezPt, GLint nCtrlPts, wcPt3D *ctrlPts, GLint *C)
{
    GLint k, n = nCtrlPts - 1;
    GLfloat bezBlendFcn;

    bezPt->x = bezPt->y = bezPt->z = -0.5;

    // calcula las funciones de combinacion y combina los puntos de control
    for (k = 0; k < nCtrlPts; k++)
    {
        bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
        bezPt->x += ctrlPts[k].x * bezBlendFcn;
        bezPt->y += ctrlPts[k].y * bezBlendFcn;
        bezPt->z += ctrlPts[k].z * bezBlendFcn;
    }
}

// calcula los coeficientes binomiales C para un valor dado de n
void binomialCoeffs(GLint n, GLint *C)
{
    GLint k, j;

    for (k = 0; k <= n; k++)
    {
        // calcula n!/k!(n-k)!
        C[k] = 1;
        for (j = n; j >= k + 1; j--)
            C[k] *= j;
        for (j = n - k; j >= 2; j--)
            C[k] /= j;
    }
}

void bezier(wcPt3D *ctrlPts, GLint nCtrlPts, GLint nBezCurvePts, GLfloat m_Verts[])
{
    wcPt3D bezCurvePt;
    GLfloat u;
    GLint *C, k;

    // asigna el espacio para los coeficientes binomiales
    C = new GLint[nCtrlPts];

    binomialCoeffs(nCtrlPts - 1, C);
    for (k = 0; k <= nBezCurvePts; k++)
    {
        u = GLfloat(k) / GLfloat(nBezCurvePts);
        computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);
        m_Verts[k * 3 + 0] = bezCurvePt.x;
        m_Verts[k * 3 + 1] = bezCurvePt.y;
        m_Verts[k * 3 + 2] = 0;
    }
    delete[] C;
}

void init(GLFWwindow *window)
{
    // Utils
    //renderingProgram = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    GLfloat m_Vertices[3003 * 44];
    GLuint n_Vertices = 3003;

    GLfloat m_V1[3003];
    GLfloat m_V2[3003];
    GLfloat m_V3[3003];
    GLfloat m_V4[3003];
    GLfloat m_V5[3003];
    GLfloat m_V6[3003];
    GLfloat m_V7[3003];
    GLfloat m_V8[3003];
    GLfloat m_V9[3003];
    GLfloat m_V10[3003];
    GLfloat m_V11[3003];
    GLfloat m_V12[3003];
    GLfloat m_V13[3003];
    GLfloat m_V14[3003];
    GLfloat m_V15[3003];
    GLfloat m_V16[3003];
    GLfloat m_V17[3003];
    GLfloat m_V18[3003];
    GLfloat m_V19[3003];
    GLfloat m_V20[3003];
    GLfloat m_V21[3003];
    GLfloat m_V22[3003];
    GLfloat m_V23[3003];
    GLfloat m_V24[3003];
    GLfloat m_V25[3003];
    GLfloat m_V26[3003];
    GLfloat m_V27[3003];
    GLfloat m_V28[3003];
    GLfloat m_V29[3003];
    GLfloat m_V30[3003];
    GLfloat m_V31[3003];
    GLfloat m_V32[3003];
    GLfloat m_V33[3003];
    GLfloat m_V34[3003];
    GLfloat m_V35[3003];
    GLfloat m_V36[3003];
    GLfloat m_V37[3003];
    GLfloat m_V38[3003];
    GLfloat m_V39[3003];
    GLfloat m_V40[3003];
    GLfloat m_V41[3003];
    GLfloat m_V42[3003];
    GLfloat m_V43[3003];
    GLfloat m_V44[3003];
    GLint nCtrlPts = 4, nBezCurvePts = 1000;

    //Estos dos ojos deben achicarse
    wcPt3D c15[4] = {{0.5517, 0.6457},
                     {0.3991, 0.6280},
                     {0.3991, 0.9567},
                     {0.5517, 0.9391}}; //Ojo Completo
    wcPt3D c16[4] = {{0.5400, 0.6457},
                     {0.7161, 0.6280},
                     {0.7161, 0.9567},
                     {0.5517, 0.9391}};

    wcPt3D c17[4] = {{0.6457, 0.6926},
                     {0.7043, 0.6926},
                     {0.7630, 0.6809},
                     {0.7630, 0.6457}}; //Nariz
    wcPt3D c18[4] = {{0.6339, 0.5870},
                     {0.7043, 0.5635},
                     {0.7630, 0.5752},
                     {0.7630, 0.6457}}; //Nariz

    wcPt3D c19[4] = {{0.6691, 0.8452},
                     {0.7043, 0.9391},
                     {0.8570, 0.9391},
                     {0.8804, 0.8100}}; //ojo derecho
    wcPt3D c20[4] = {{0.7630, 0.6457},
                     {0.8217, 0.6457},
                     {0.8922, 0.6809},
                     {0.8804, 0.8100}}; //ojo derecho

    wcPt3D c29[4] = {{0.8100, 0.6515},
                     {0.8100, 0.6515},
                     {0.8804, 0.5635},
                     {0.8804, 0.5635}}; //Boca
    wcPt3D c30[4] = {{0.4343, 0.5048},
                     {0.5870, 0.4109},
                     {0.8217, 0.4285},
                     {0.8804, 0.5670}}; //
    wcPt3D c32[4] = {{0.4226, 0.4813},
                     {0.4226, 0.4813},
                     {0.4461, 0.5283},
                     {0.4461, 0.5283}}; //

    wcPt3D c31[4] = {{0.3874, 0.5165},
                     {0.2817, 0.4637},
                     {0.2817, 0.6633},
                     {0.3874, 0.6104}}; //Oreja
    wcPt3D c28[4] = {{0.3404, 0.5400},
                     {0.3052, 0.5635},
                     {0.3404, 0.5987},
                     {0.3639, 0.5752}}; //Oreja

    wcPt3D c33[4] = {{0.3522, 0.5048},
                     {0.3639, 0.4343},
                     {0.3580, 0.4109},
                     {0.3522, 0.3522}}; //Cuello
    wcPt3D c34[4] = {{0.2817, 0.5048},
                     {0.2817, 0.5048},
                     {0.2817, 0.4226},
                     {0.2817, 0.4226}}; //Cabello
    wcPt3D c35[4] = {{0.2817, 0.4226},
                     {0.2817, 0.4226},
                     {0.3580, 0.4226},
                     {0.3580, 0.4226}}; //Cabello
    wcPt3D c36[4] = {{0.6691, 0.4461},
                     {0.6457, 0.4109},
                     {0.6104, 0.4226},
                     {0.6104, 0.3991}}; //Menton
    wcPt3D c37[4] = {{0.6104, 0.3991},
                     {0.5870, 0.3522},
                     {0.5870, 0.3287},
                     {0.5752, 0.2935}}; //cuello

    //Ojo 2 (Completo)
    wcPt3D c38[4] = {{0.3991, 0.8452},
                     {0.3991, 0.8452},
                     {0.4343, 0.8217},
                     {0.4343, 0.8217}}; //Pestañas
    wcPt3D c39[4] = {{0.4461, 0.9391},
                     {0.4461, 0.9391},
                     {0.4696, 0.9039},
                     {0.4696, 0.9039}}; //Pestañas
    wcPt3D c40[4] = {{0.5283, 0.9743},
                     {0.5283, 0.9763},
                     {0.5400, 0.9391},
                     {0.5400, 0.9391}}; //Pestañas
    wcPt3D c41[4] = {{0.6104, 0.9274},
                     {0.6104, 0.9274},
                     {0.6222, 0.9626},
                     {0.6222, 0.9626}}; //Pestañas
    //Ojo 2
    wcPt3D c42[4] = {{0.7630, 0.9098},
                     {0.7630, 0.9098},
                     {0.7748, 0.9450},
                     {0.7748, 0.9450}}; //Pestañas
    wcPt3D c43[4] = {{0.8217, 0.8922},
                     {0.8217, 0.8922},
                     {0.8452, 0.9274},
                     {0.8452, 0.9274}}; //Pestañas
    wcPt3D c44[4] = {{0.8687, 0.8452},
                     {0.8687, 0.8452},
                     {0.9039, 0.8804},
                     {0.9039, 0.8804}}; //Pestañas
    wcPt3D c45[4] = {{0.8840, 0.7865},
                     {0.8840, 0.7865},
                     {0.9239, 0.8100},
                     {0.9239, 0.8100}}; //Pestañas

    wcPt3D c26[4] = {{0.2817, 0.5048},
                     {0.1174, 0.5048},
                     {0.1174, 0.5048},
                     {0.2358, 0.7043}}; //PELO
    wcPt3D c27[4] = {{0.2348, 0.7043},
                     {0.0822, 0.8217},
                     {0.0822, 0.8217},
                     {0.2348, 0.9391}}; //PELO
    wcPt3D c25[4] = {{0.2348, 0.9391},
                     {0.2113, 1.1152},
                     {0.1526, 1.1152},
                     {0.3522, 1.1504}}; //ARRIBA
    wcPt3D c24[4] = {{0.3522, 1.1504},
                     {0.4696, 1.3500},
                     {0.4109, 1.3500},
                     {0.5635, 1.2326}}; //PELO
    wcPt3D c23[4] = {{0.5635, 1.2326},
                     {0.7043, 1.3500},
                     {0.6457, 1.3500},
                     {0.7748, 1.1739}}; //OREJA
    wcPt3D c22[4] = {{0.7748, 1.1739},
                     {0.9391, 1.1504},
                     {0.8804, 1.1504},
                     {0.8804, 0.9978}};
    wcPt3D c21[4] = {{0.8804, 0.9978},
                     {0.9743, 0.9157},
                     {0.9743, 0.9157},
                     {0.8804, 0.8100}};

    wcPt3D c50[4] = {{0.53923, 0.77842},
                     {0.51931, 0.76846},
                     {0.51793, 0.80842},
                     {0.53822, 0.80504}}; //Ojito izquierdo
    wcPt3D c51[4] = {{0.53923, 0.77842},
                     {0.55968, 0.77372},
                     {0.55862, 0.81132},
                     {0.53822, 0.80504}};

    wcPt3D c52[4] = {{0.77662, 0.78328},
                     {0.75692, 0.77248},
                     {0.75867, 0.81398},
                     {0.77562, 0.80638}}; //Ojito derecho
    wcPt3D c53[4] = {{0.77562, 0.80638},
                     {0.79433, 0.81398},
                     {0.79374, 0.77482},
                     {0.77662, 0.78328}};

    //Collar
    wcPt3D c54[4] = {{0.32446, 0.27672},
                     {0.28175, 0.30582},
                     {0.30738, 0.35814},
                     {0.35089, 0.35066}}; //Ojo Completo
    wcPt3D c55[4] = {{0.35089, 0.35066},
                     {0.40054, 0.32878},
                     {0.37384, 0.26631},
                     {0.32446, 0.27672}};

    //Segundo circulo
    wcPt3D c56[4] = {{0.39386, 0.25377},
                     {0.35329, 0.29194},
                     {0.38799, 0.34052},
                     {0.43257, 0.32664}}; //Ojo Completo
    wcPt3D c57[4] = {{0.43257, 0.32664},
                     {0.47421, 0.29754},
                     {0.44271, 0.23909},
                     {0.39386, 0.25377}};
    //Tercer collar
    wcPt3D c58[4] = {{0.47603, 0.23759},
                     {0.42823, 0.25309},
                     {0.4376, 0.31704},
                     {0.49057, 0.31284}}; //Ojito derecho
    wcPt3D c59[4] = {{0.49057, 0.31284},
                     {0.53966, 0.29896},
                     {0.52448, 0.23985},
                     {0.47603, 0.23759}};
    //Cuarto collar
    wcPt3D c60[4] = {{0.54773, 0.22596},
                     {0.50801, 0.23565},
                     {0.51059, 0.29024},
                     {0.55516, 0.29734}}; //Ojito derecho
    wcPt3D c61[4] = {{0.55516, 0.29734},
                     {0.59909, 0.28765},
                     {0.5936, 0.23016},
                     {0.54773, 0.22596}};
    //5t0
    wcPt3D c62[4] = {{0.56679, 0.29443},
                     {0.65594, 0.32318},
                     {0.63882, 0.19592},
                     {0.56679, 0.23242}};
    bezier(c15, nCtrlPts, nBezCurvePts, m_V1);
    bezier(c16, nCtrlPts, nBezCurvePts, m_V2);

    bezier(c17, nCtrlPts, nBezCurvePts, m_V3);
    bezier(c18, nCtrlPts, nBezCurvePts, m_V4);

    bezier(c19, nCtrlPts, nBezCurvePts, m_V5);
    bezier(c20, nCtrlPts, nBezCurvePts, m_V6);

    bezier(c29, nCtrlPts, nBezCurvePts, m_V7);
    bezier(c30, nCtrlPts, nBezCurvePts, m_V8);
    bezier(c32, nCtrlPts, nBezCurvePts, m_V9);

    bezier(c31, nCtrlPts, nBezCurvePts, m_V10);
    bezier(c28, nCtrlPts, nBezCurvePts, m_V11);

    bezier(c33, nCtrlPts, nBezCurvePts, m_V12);
    bezier(c34, nCtrlPts, nBezCurvePts, m_V13);
    bezier(c35, nCtrlPts, nBezCurvePts, m_V14);
    bezier(c36, nCtrlPts, nBezCurvePts, m_V15);
    bezier(c37, nCtrlPts, nBezCurvePts, m_V16);

    bezier(c38, nCtrlPts, nBezCurvePts, m_V17);
    bezier(c39, nCtrlPts, nBezCurvePts, m_V18);
    bezier(c40, nCtrlPts, nBezCurvePts, m_V19);
    bezier(c41, nCtrlPts, nBezCurvePts, m_V20);

    bezier(c42, nCtrlPts, nBezCurvePts, m_V21);
    bezier(c43, nCtrlPts, nBezCurvePts, m_V22);
    bezier(c44, nCtrlPts, nBezCurvePts, m_V23);
    bezier(c45, nCtrlPts, nBezCurvePts, m_V24);

    bezier(c26, nCtrlPts, nBezCurvePts, m_V25);
    bezier(c27, nCtrlPts, nBezCurvePts, m_V26);
    bezier(c25, nCtrlPts, nBezCurvePts, m_V27);
    bezier(c24, nCtrlPts, nBezCurvePts, m_V28);
    bezier(c23, nCtrlPts, nBezCurvePts, m_V29);
    bezier(c22, nCtrlPts, nBezCurvePts, m_V30);
    bezier(c21, nCtrlPts, nBezCurvePts, m_V31);

    bezier(c50, nCtrlPts, nBezCurvePts, m_V32);
    bezier(c51, nCtrlPts, nBezCurvePts, m_V33);

    bezier(c52, nCtrlPts, nBezCurvePts, m_V34);
    bezier(c53, nCtrlPts, nBezCurvePts, m_V35);

    bezier(c54, nCtrlPts, nBezCurvePts, m_V36);
    bezier(c55, nCtrlPts, nBezCurvePts, m_V37);

    bezier(c56, nCtrlPts, nBezCurvePts, m_V38);
    bezier(c57, nCtrlPts, nBezCurvePts, m_V39);

    bezier(c58, nCtrlPts, nBezCurvePts, m_V40);
    bezier(c59, nCtrlPts, nBezCurvePts, m_V41);

    bezier(c60, nCtrlPts, nBezCurvePts, m_V42);
    bezier(c61, nCtrlPts, nBezCurvePts, m_V43);
    bezier(c62, nCtrlPts, nBezCurvePts, m_V44);

    for (GLuint i = 0; i < n_Vertices; i++)
    {
        m_Vertices[i + 3003 * 0] = m_V1[i];
        m_Vertices[i + 3003 * 1] = m_V2[i];
        m_Vertices[i + 3003 * 2] = m_V3[i];
        m_Vertices[i + 3003 * 3] = m_V4[i];
        m_Vertices[i + 3003 * 4] = m_V5[i];
        m_Vertices[i + 3003 * 5] = m_V6[i];
        m_Vertices[i + 3003 * 6] = m_V7[i];
        m_Vertices[i + 3003 * 7] = m_V8[i];
        m_Vertices[i + 3003 * 8] = m_V9[i];
        m_Vertices[i + 3003 * 9] = m_V10[i];
        m_Vertices[i + 3003 * 10] = m_V11[i];
        m_Vertices[i + 3003 * 11] = m_V12[i];
        m_Vertices[i + 3003 * 12] = m_V13[i];
        m_Vertices[i + 3003 * 13] = m_V14[i];
        m_Vertices[i + 3003 * 14] = m_V15[i];
        m_Vertices[i + 3003 * 15] = m_V16[i];
        m_Vertices[i + 3003 * 16] = m_V17[i];
        m_Vertices[i + 3003 * 17] = m_V18[i];
        m_Vertices[i + 3003 * 18] = m_V19[i];
        m_Vertices[i + 3003 * 19] = m_V20[i];
        m_Vertices[i + 3003 * 20] = m_V21[i];
        m_Vertices[i + 3003 * 21] = m_V22[i];
        m_Vertices[i + 3003 * 22] = m_V23[i];
        m_Vertices[i + 3003 * 23] = m_V24[i];
        m_Vertices[i + 3003 * 24] = m_V25[i];
        m_Vertices[i + 3003 * 25] = m_V26[i];
        m_Vertices[i + 3003 * 26] = m_V27[i];
        m_Vertices[i + 3003 * 27] = m_V28[i];
        m_Vertices[i + 3003 * 28] = m_V29[i];
        m_Vertices[i + 3003 * 29] = m_V30[i];
        m_Vertices[i + 3003 * 30] = m_V31[i];
        m_Vertices[i + 3003 * 31] = m_V32[i];
        m_Vertices[i + 3003 * 32] = m_V33[i];
        m_Vertices[i + 3003 * 33] = m_V34[i];
        m_Vertices[i + 3003 * 34] = m_V35[i];
        m_Vertices[i + 3003 * 35] = m_V36[i];
        m_Vertices[i + 3003 * 36] = m_V37[i];
        m_Vertices[i + 3003 * 37] = m_V38[i];
        m_Vertices[i + 3003 * 38] = m_V39[i];
        m_Vertices[i + 3003 * 39] = m_V40[i];
        m_Vertices[i + 3003 * 40] = m_V41[i];
        m_Vertices[i + 3003 * 41] = m_V42[i];
        m_Vertices[i + 3003 * 42] = m_V43[i];
        m_Vertices[i + 3003 * 43] = m_V44[i];
    }

    //Acá creamos los ojos

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(m_Vertices),
        m_Vertices,
        GL_STATIC_DRAW);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0 * sizeof(GLfloat),
        (GLvoid *)0);

    glEnableVertexAttribArray(0); // Habilita este atributo

    /* SHADERS DESHABILITADOS
    glVertexAttribPointer(
    	1,
    	3,
    	GL_FLOAT,
    	GL_FALSE,
    	6 * sizeof(GLfloat),
    	(GLvoid*) (3 * sizeof(GLfloat))
    );

    glEnableVertexAttribArray(1);		// Habilita este atributo
	*/

    glBindVertexArray(0);
}

void display(GLFWwindow *window, double currentTime)
{
    //glUseProgram(renderingProgram);

    // Use este VAO e suas configurações
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_POINTS, 0, 1001 * 44);
    //glDrawArrays(GL_TRIANGLE_FAN, 1001*31 + 1 , numberOfVertices);
    glBindVertexArray(0);
}

int main(void)
{

    // Initialise GLFW
    if (!glfwInit())
    {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);           //
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);                      // Resizable option.

    GLFWwindow *window = glfwCreateWindow(600, 600, "Tarea08", NULL, NULL);

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window))
    {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
