/*============================================================================
					TAREA 08 - CURVAS
PROFESOR  	 : 		PAUCAR CURASMA, Herminio
INTEGRANTES	 :
				[3] AZORSA SALAZAR, Stephanie 			17200317
				[3] MARROQUIN GAVELAN, Juan Patricio	17200329
				[3] MINCIA RETAMOZO, Alessandra Yvonne	17200289
				[3] OSCO PUPE, Jean William				17200082
				[3] ROJAS CAMARGO, Melinna Victoria		17200106
				[3] VELAZCO HUERE, Leydi Mabel			17200307
================================================================================*/

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
GLfloat *m_Vertices2;

GLuint m_VBO;
GLuint m_VAO;
GLuint m_VBO2;
GLuint m_VAO2;

class ptCtrl
{
	public:
    	GLfloat x, y, z;
};

// Declarando los puntos de control
ptCtrl c01[4] = {{0.5517, 0.6457}, {0.3991, 0.6280}, {0.3991, 0.9567}, {0.5517, 0.9391}}; // Ojo izquierdo
ptCtrl c02[4] = {{0.5400, 0.6457}, {0.7161, 0.6280}, {0.7161, 0.9567}, {0.5517, 0.9391}}; // Ojo izquierdo
ptCtrl c03[4] = {{0.53923, 0.77842}, {0.51931, 0.76846}, {0.51793, 0.80842}, {0.53822, 0.80504}}; // Pupila izquierda
ptCtrl c04[4] = {{0.53923, 0.77842}, {0.55968, 0.77372}, {0.55862, 0.81132}, {0.53822, 0.80504}}; // Pupila izquierda

ptCtrl c05[4] = {{0.6691, 0.8452}, {0.7043, 0.9391}, {0.8570, 0.9391}, {0.8804, 0.8100}}; // Ojo derecho
ptCtrl c06[4] = {{0.7630, 0.6457}, {0.8217, 0.6457}, {0.8922, 0.6809}, {0.8804, 0.8100}}; // Ojo derecho
ptCtrl c07[4] = {{0.77662, 0.78328}, {0.75692, 0.77248}, {0.75867, 0.81398}, {0.77562, 0.80638}}; // Pupila derecha
ptCtrl c08[4] = {{0.77562, 0.80638}, {0.79433, 0.81398}, {0.79374, 0.77482}, {0.77662, 0.78328}}; // Pupila derecha

ptCtrl c09[4] = {{0.3991, 0.8452}, {0.3991, 0.8452}, {0.4343, 0.8217}, {0.4343, 0.8217}}; // Pestañas ojo izquierdo
ptCtrl c10[4] = {{0.4461, 0.9391}, {0.4461, 0.9391}, {0.4696, 0.9039}, {0.4696, 0.9039}}; // Pestañas ojo izquierdo
ptCtrl c11[4] = {{0.5283, 0.9743}, {0.5283, 0.9763}, {0.5400, 0.9391}, {0.5400, 0.9391}}; // Pestañas ojo izquierdo
ptCtrl c12[4] = {{0.6104, 0.9274}, {0.6104, 0.9274}, {0.6222, 0.9626}, {0.6222, 0.9626}}; // Pestañas ojo izquierdo
ptCtrl c13[4] = {{0.7630, 0.9098}, {0.7630, 0.9098}, {0.7748, 0.9450}, {0.7748, 0.9450}}; // Pestañas ojo derecho
ptCtrl c14[4] = {{0.8217, 0.8922}, {0.8217, 0.8922}, {0.8452, 0.9274}, {0.8452, 0.9274}}; // Pestañas ojo derecho
ptCtrl c15[4] = {{0.8687, 0.8452}, {0.8687, 0.8452}, {0.9039, 0.8804}, {0.9039, 0.8804}}; // Pestañas ojo derecho
ptCtrl c16[4] = {{0.8840, 0.7865}, {0.8840, 0.7865}, {0.9239, 0.8100}, {0.9239, 0.8100}}; // Pestañas ojo derecho

ptCtrl c17[4] = {{0.6457, 0.6926}, {0.7043, 0.6926}, {0.7630, 0.6809}, {0.7630, 0.6457}}; // Nariz
ptCtrl c18[4] = {{0.6339, 0.5870}, {0.7043, 0.5635}, {0.7630, 0.5752}, {0.7630, 0.6457}}; // Nariz

ptCtrl c19[4] = {{0.8100, 0.6515}, {0.8100, 0.6515}, {0.8804, 0.5635}, {0.8804, 0.5635}}; // Boca
ptCtrl c20[4] = {{0.4343, 0.5048}, {0.5870, 0.4109}, {0.8217, 0.4285}, {0.8804, 0.5670}}; // Boca
ptCtrl c21[4] = {{0.4226, 0.4813}, {0.4226, 0.4813}, {0.4461, 0.5283}, {0.4461, 0.5283}}; // Boca

ptCtrl c22[4] = {{0.3874, 0.5165}, {0.2817, 0.4637}, {0.2817, 0.6633}, {0.3874, 0.6104}}; // Oreja
ptCtrl c23[4] = {{0.3404, 0.5400}, {0.3052, 0.5635}, {0.3404, 0.5987}, {0.3639, 0.5752}}; // Oreja

ptCtrl c24[4] = {{0.3522, 0.5048}, {0.3639, 0.4343}, {0.3580, 0.4109}, {0.3522, 0.3522}}; // Cuello
ptCtrl c25[4] = {{0.2817, 0.5048}, {0.2817, 0.5048}, {0.2817, 0.4226}, {0.2817, 0.4226}}; // Cuello
ptCtrl c26[4] = {{0.2817, 0.4226}, {0.2817, 0.4226}, {0.3580, 0.4226}, {0.3580, 0.4226}}; // Cuello
ptCtrl c27[4] = {{0.6691, 0.4461}, {0.6457, 0.4109}, {0.6104, 0.4226}, {0.6104, 0.3991}}; // Menton
ptCtrl c28[4] = {{0.6104, 0.3991}, {0.5870, 0.3522}, {0.5870, 0.3287}, {0.5752, 0.2935}}; // Cuello

ptCtrl c29[4] = {{0.2817, 0.5048}, {0.1174, 0.5048}, {0.1174, 0.5048}, {0.2358, 0.7043}}; // Cabello
ptCtrl c30[4] = {{0.2348, 0.7043}, {0.0822, 0.8217}, {0.0822, 0.8217}, {0.2348, 0.9391}}; // Cabello
ptCtrl c31[4] = {{0.2348, 0.9391}, {0.2113, 1.1152}, {0.1526, 1.1152}, {0.3522, 1.1504}}; // Cabello
ptCtrl c32[4] = {{0.3522, 1.1504}, {0.4696, 1.3500}, {0.4109, 1.3500}, {0.5635, 1.2326}}; // Cabello
ptCtrl c33[4] = {{0.5635, 1.2326}, {0.7043, 1.3500}, {0.6457, 1.3500}, {0.7748, 1.1739}}; // Cabello
ptCtrl c34[4] = {{0.7748, 1.1739}, {0.9391, 1.1504}, {0.8804, 1.1504}, {0.8804, 0.9978}}; // Cabello
ptCtrl c35[4] = {{0.8804, 0.9978}, {0.9743, 0.9157}, {0.9743, 0.9157}, {0.8804, 0.8100}}; // Cabello

ptCtrl c36[4] = {{0.32446, 0.27672}, {0.28175, 0.30582}, {0.30738, 0.35814}, {0.35089, 0.35066}}; // Collar circulo 1
ptCtrl c37[4] = {{0.35089, 0.35066}, {0.40054, 0.32878}, {0.37384, 0.26631}, {0.32446, 0.27672}}; // Collar circulo 1
ptCtrl c38[4] = {{0.39386, 0.25377}, {0.35329, 0.29194}, {0.38799, 0.34052}, {0.43257, 0.32664}}; // Collar circulo 2
ptCtrl c39[4] = {{0.43257, 0.32664}, {0.47421, 0.29754}, {0.44271, 0.23909}, {0.39386, 0.25377}}; // Collar circulo 2
ptCtrl c40[4] = {{0.47603, 0.23759}, {0.42823, 0.25309}, {0.4376, 0.31704}, {0.49057, 0.31284}}; // Collar circulo 3
ptCtrl c41[4] = {{0.49057, 0.31284}, {0.53966, 0.29896}, {0.52448, 0.23985}, {0.47603, 0.23759}}; // Collar circulo 3
ptCtrl c42[4] = {{0.54773, 0.22596}, {0.50801, 0.23565}, {0.51059, 0.29024}, {0.55516, 0.29734}}; // Collar circulo 4
ptCtrl c43[4] = {{0.55516, 0.29734}, {0.59909, 0.28765}, {0.5936, 0.23016}, {0.54773, 0.22596}}; // Collar circulo 4
ptCtrl c44[4] = {{0.56679, 0.29443}, {0.65594, 0.32318}, {0.63882, 0.19592}, {0.56679, 0.23242}}; // Collar circulo 5

ptCtrl c45[4] = {{0.07901, -0.13053}, {0.13786, 0.16062}, {0.18432, 0.23186}, {0.29892, 0.32169}}; // Cuerpo
ptCtrl c46[4] = {{0.22348, -0.13162}, {0.26795, 0.03673}, {0.28653, 0.13894}, {0.41043, 0.1947}}; // Cuerpo
ptCtrl c47[4] = {{0.29583, 0.0739}, {0.5, 0}, {0.57769, 0.05222}, {0.57928, 0.11833}}; // Cuerpo
ptCtrl c48[4] = {{0.64051, -0.12184}, {0.60527, -0.03658}, {0.5684, 0.12965}, {0.56679, 0.23242}}; // Cuerpo
ptCtrl c49[4] = {{0.22348, -0.13162}, {0.35554, -0.19543}, {0.57928, -0.19538}, {0.64051, -0.12184}}; // Cuerpo

ptCtrl c50[4] = {{0.36394, 0.30153}, {1.10128, 0.57687}, {0.6454, 1.12418}, {0.3522, 1.1504}}; // Extra
ptCtrl c51[4] = {{0.8804, 0.9978}, {0.54107, 1.09786}, {0.00292, 0.80572}, {0.67604, 0.57679}}; // Extra
ptCtrl c52[4] = {{0.6104, 0.3991}, {0.49435, 0.66375}, {0.29118, 0.25807}, {0.5752, 0.2935}}; // Extra
ptCtrl c53[4] = {{0.2348, 0.9391}, {0.47602, 1.06095}, {0.70667, 0.79608}, {0.35698, 0.51186}}; // Extra
ptCtrl c54[4] = {{0.2817, 0.5048}, {0.35004, 0.49781}, {0.3504, 0.43428}, {0.2817, 0.4226}}; // Extra

// Arreglos para el ojo izquierdo
GLfloat m_V1[1503], m_V2[1503], m_V3[1503], m_V4[1503];
// Arreglos para el ojo derecho
GLfloat m_V5[1503], m_V6[1503], m_V7[1503], m_V8[1503];
// Arreglos para las pestañas
GLfloat m_V9[1503], m_V10[1503], m_V11[1503], m_V12[1503];
GLfloat m_V13[1503], m_V14[1503],  m_V15[1503], m_V16[1503];
// Arreglos para la nariz
GLfloat m_V17[1503], m_V18[1503];
// Arreglos para la boca
GLfloat m_V19[1503], m_V20[1503], m_V21[1503];
// Arreglos para la oreja
GLfloat m_V22[1503], m_V23[1503];
// Arreglos para el cuello
GLfloat m_V24[1503], m_V25[1503], m_V26[1503], m_V27[1503], m_V28[1503];
// Arreglos para el cabello
GLfloat m_V29[1503], m_V30[1503], m_V31[1503], m_V32[1503];
GLfloat m_V33[1503], m_V34[1503], m_V35[1503];
// Arreglos para el collar
GLfloat m_V36[1503], m_V37[1503], m_V38[1503], m_V39[1503], m_V40[1503];
GLfloat m_V41[1503], m_V42[1503], m_V43[1503], m_V44[1503];
// Arreglos para el cuerpo
GLfloat m_V45[1503], m_V46[1503], m_V47[1503], m_V48[1503], m_V49[1503];
// Extra
GLfloat m_V50[1503], m_V51[1503], m_V52[1503], m_V53[1503], m_V54[1503];

void computeBezPt(GLfloat u, ptCtrl *bezPt, GLint nCtrlPts, ptCtrl *ctrlPts, GLint *C)
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

void bezier(ptCtrl *ctrlPts, GLint nCtrlPts, GLint nBezCurvePts, GLfloat m_Verts[])
{
    ptCtrl bezCurvePt;
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

// Creando las curvas
void drawCurves()
{
	// Grado de la curva de Bezier, numero de puntos para la curva
	GLint nCtrlPts = 4, nBezCurvePts = 500;

	// Llenando los arreglos con los puntos de Bezier
	bezier(c01, nCtrlPts, nBezCurvePts, m_V1);
	bezier(c02, nCtrlPts, nBezCurvePts, m_V2);
	bezier(c03, nCtrlPts, nBezCurvePts, m_V3);
	bezier(c04, nCtrlPts, nBezCurvePts, m_V4);
	bezier(c05, nCtrlPts, nBezCurvePts, m_V5);
	bezier(c06, nCtrlPts, nBezCurvePts, m_V6);
	bezier(c07, nCtrlPts, nBezCurvePts, m_V7);
	bezier(c08, nCtrlPts, nBezCurvePts, m_V8);
	bezier(c09, nCtrlPts, nBezCurvePts, m_V9);
	bezier(c10, nCtrlPts, nBezCurvePts, m_V10);
	bezier(c11, nCtrlPts, nBezCurvePts, m_V11);
	bezier(c12, nCtrlPts, nBezCurvePts, m_V12);
	bezier(c13, nCtrlPts, nBezCurvePts, m_V13);
	bezier(c14, nCtrlPts, nBezCurvePts, m_V14);
	bezier(c15, nCtrlPts, nBezCurvePts, m_V15);
	bezier(c16, nCtrlPts, nBezCurvePts, m_V16);
	bezier(c17, nCtrlPts, nBezCurvePts, m_V17);
	bezier(c18, nCtrlPts, nBezCurvePts, m_V18);
	bezier(c19, nCtrlPts, nBezCurvePts, m_V19);
	bezier(c20, nCtrlPts, nBezCurvePts, m_V20);
	bezier(c21, nCtrlPts, nBezCurvePts, m_V21);
	bezier(c22, nCtrlPts, nBezCurvePts, m_V22);
	bezier(c23, nCtrlPts, nBezCurvePts, m_V23);
	bezier(c24, nCtrlPts, nBezCurvePts, m_V24);
	bezier(c25, nCtrlPts, nBezCurvePts, m_V25);
	bezier(c26, nCtrlPts, nBezCurvePts, m_V26);
	bezier(c27, nCtrlPts, nBezCurvePts, m_V27);
	bezier(c28, nCtrlPts, nBezCurvePts, m_V28);
	bezier(c29, nCtrlPts, nBezCurvePts, m_V29);
	bezier(c30, nCtrlPts, nBezCurvePts, m_V30);
	bezier(c31, nCtrlPts, nBezCurvePts, m_V31);
	bezier(c32, nCtrlPts, nBezCurvePts, m_V32);
	bezier(c33, nCtrlPts, nBezCurvePts, m_V33);
	bezier(c34, nCtrlPts, nBezCurvePts, m_V34);
	bezier(c35, nCtrlPts, nBezCurvePts, m_V35);
	bezier(c36, nCtrlPts, nBezCurvePts, m_V36);
	bezier(c37, nCtrlPts, nBezCurvePts, m_V37);
	bezier(c38, nCtrlPts, nBezCurvePts, m_V38);
	bezier(c39, nCtrlPts, nBezCurvePts, m_V39);
	bezier(c40, nCtrlPts, nBezCurvePts, m_V40);
	bezier(c41, nCtrlPts, nBezCurvePts, m_V41);
	bezier(c42, nCtrlPts, nBezCurvePts, m_V42);
	bezier(c43, nCtrlPts, nBezCurvePts, m_V43);
	bezier(c44, nCtrlPts, nBezCurvePts, m_V44);
	bezier(c45, nCtrlPts, nBezCurvePts, m_V45);
	bezier(c46, nCtrlPts, nBezCurvePts, m_V46);
	bezier(c47, nCtrlPts, nBezCurvePts, m_V47);
	bezier(c48, nCtrlPts, nBezCurvePts, m_V48);

	bezier(c49, nCtrlPts, nBezCurvePts, m_V49);
	bezier(c50, nCtrlPts, nBezCurvePts, m_V50);
	bezier(c51, nCtrlPts, nBezCurvePts, m_V51);
	bezier(c52, nCtrlPts, nBezCurvePts, m_V52);
	bezier(c53, nCtrlPts, nBezCurvePts, m_V53);
	bezier(c54, nCtrlPts, nBezCurvePts, m_V54);
}

void paintFigure(GLfloat m_Verts[], GLfloat m_V[], int k, float r, float g, float b)
{
	for (GLuint i=0; i< 1503; i++) {
	    m_Verts[(i+1503*k)*6+0] = m_V[i*3+0];
		m_Verts[(i+1503*k)*6+1] = m_V[i*3+1];
		m_Verts[(i+1503*k)*6+2] = m_V[i*3+2];
		m_Verts[(i+1503*k)*6+3] = r;
		m_Verts[(i+1503*k)*6+4] = g;
		m_Verts[(i+1503*k)*6+5] = b;
	}
}

void borderFigure(GLfloat m_Verts[]) {
	// Volcando todo los vertices en un arreglo general para el VAO
	for (GLuint i = 0; i < 1503; i++)
	{
		m_Verts[i + 1503 * 0] = m_V1[i];
	    m_Verts[i + 1503 * 1] = m_V2[i];
	    m_Verts[i + 1503 * 2] = m_V3[i];
	    m_Verts[i + 1503 * 3] = m_V4[i];
	    m_Verts[i + 1503 * 4] = m_V5[i];
	    m_Verts[i + 1503 * 5] = m_V6[i];
	    m_Verts[i + 1503 * 6] = m_V7[i];
	    m_Verts[i + 1503 * 7] = m_V8[i];
	    m_Verts[i + 1503 * 8] = m_V9[i];
	    m_Verts[i + 1503 * 9] = m_V10[i];
	    m_Verts[i + 1503 * 10] = m_V11[i];
	    m_Verts[i + 1503 * 11] = m_V12[i];
	    m_Verts[i + 1503 * 12] = m_V13[i];
	    m_Verts[i + 1503 * 13] = m_V14[i];
	    m_Verts[i + 1503 * 14] = m_V15[i];
	    m_Verts[i + 1503 * 15] = m_V16[i];
	    m_Verts[i + 1503 * 16] = m_V17[i];
	    m_Verts[i + 1503 * 17] = m_V18[i];
	    m_Verts[i + 1503 * 18] = m_V19[i];
	    m_Verts[i + 1503 * 19] = m_V20[i];
	    m_Verts[i + 1503 * 20] = m_V21[i];
	    m_Verts[i + 1503 * 21] = m_V22[i];
	    m_Verts[i + 1503 * 22] = m_V23[i];
	    m_Verts[i + 1503 * 23] = m_V24[i];
	    m_Verts[i + 1503 * 24] = m_V25[i];
	    m_Verts[i + 1503 * 25] = m_V26[i];
	    m_Verts[i + 1503 * 26] = m_V27[i];
	    m_Verts[i + 1503 * 27] = m_V28[i];
	    m_Verts[i + 1503 * 28] = m_V29[i];
	    m_Verts[i + 1503 * 29] = m_V30[i];
	    m_Verts[i + 1503 * 30] = m_V31[i];
	    m_Verts[i + 1503 * 31] = m_V32[i];
	    m_Verts[i + 1503 * 32] = m_V33[i];
	    m_Verts[i + 1503 * 33] = m_V34[i];
	    m_Verts[i + 1503 * 34] = m_V35[i];
	    m_Verts[i + 1503 * 35] = m_V36[i];
	    m_Verts[i + 1503 * 36] = m_V37[i];
	    m_Verts[i + 1503 * 37] = m_V38[i];
	    m_Verts[i + 1503 * 38] = m_V39[i];
	    m_Verts[i + 1503 * 39] = m_V40[i];
	    m_Verts[i + 1503 * 40] = m_V41[i];
	    m_Verts[i + 1503 * 41] = m_V42[i];
	    m_Verts[i + 1503 * 42] = m_V43[i];
	    m_Verts[i + 1503 * 43] = m_V44[i];
	    m_Verts[i + 1503 * 44] = m_V45[i];
	    m_Verts[i + 1503 * 45] = m_V46[i];
	    m_Verts[i + 1503 * 46] = m_V47[i];
	    m_Verts[i + 1503 * 47] = m_V48[i];
	}
}

void init(GLFWwindow *window)
{
    // Utils
    renderingProgram = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");

    // Llamamos a la función que dibuja las curvas
    drawCurves();

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    GLfloat m_Vertices[1503*6*45];

    paintFigure(m_Vertices, m_V1, 0, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V2, 1, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V3, 2, 0.0, 0.0, 0.0);
    paintFigure(m_Vertices, m_V4, 3, 0.0, 0.0, 0.0);

    paintFigure(m_Vertices, m_V5, 4, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V6, 5, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V7, 6, 0.0, 0.0, 0.0);
    paintFigure(m_Vertices, m_V8, 7, 0.0, 0.0, 0.0);

    paintFigure(m_Vertices, m_V17, 8, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V18, 9, 0.99, 0.93, 0.0);

    paintFigure(m_Vertices, m_V19, 10, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V20, 11, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V21, 12, 0.99, 0.93, 0.0);

    paintFigure(m_Vertices, m_V22, 13, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V23, 14, 0.99, 0.93, 0.0);

    paintFigure(m_Vertices, m_V24, 15, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V26, 16, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V27, 17, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V28, 18, 0.99, 0.93, 0.0);

    paintFigure(m_Vertices, m_V29, 19, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V30, 20, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V31, 21, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V32, 22, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V33, 23, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V34, 24, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V35, 25, 0.99, 0.93, 0.0);

    paintFigure(m_Vertices, m_V36, 26, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V37, 27, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V38, 28, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V39, 29, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V40, 30, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V41, 31, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V42, 32, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V43, 33, 1.0, 1.0, 1.0);
    paintFigure(m_Vertices, m_V44, 34, 1.0, 1.0, 1.0);

    paintFigure(m_Vertices, m_V45, 35, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V46, 36, 1.0, 0.49, 0.0);
    paintFigure(m_Vertices, m_V47, 37, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V48, 38, 0.99, 0.93, 0.0);

    paintFigure(m_Vertices, m_V49, 39, 1.0, 0.49, 0.0);
    paintFigure(m_Vertices, m_V50, 40, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V51, 41, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V52, 42, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V53, 43, 0.99, 0.93, 0.0);
    paintFigure(m_Vertices, m_V54, 44, 0.99, 0.93, 0.0);

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
        6 * sizeof(GLfloat),
        (GLvoid *)0
	);
    glEnableVertexAttribArray(0); // Habilita este atributo
    
    glVertexAttribPointer(
    	1,
    	3,
    	GL_FLOAT,
    	GL_FALSE,
    	6 * sizeof(GLfloat),
    	(GLvoid*) (3 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(1);		// Habilita este atributo

    glBindVertexArray(0);


    /******************* BORDEANDO FIGURA ****************/
    glGenVertexArrays(1, &m_VAO2);
    glBindVertexArray(m_VAO2);

    GLfloat m_Vertices2[1503*48];

    borderFigure(m_Vertices2);

    glGenBuffers(1, &m_VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO2);
    glBufferData(
    	GL_ARRAY_BUFFER,
        sizeof(m_Vertices2),
        m_Vertices2,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*) 0
    );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*) (3 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void display(GLFWwindow *window, double currentTime)
{
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearColor(0.57, 0.36, 0.51, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(renderingProgram);

    glBindVertexArray(m_VAO);
    // Extra
    glDrawArrays(GL_TRIANGLE_FAN, 1503*39, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*40, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*41, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*42, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*43, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*44, 501);
    // Coloreando el cabello
    glDrawArrays(GL_TRIANGLE_FAN, 1503*19, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*20, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*21, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*22, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*23, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*24, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*25, 502);
    // Coloreando el cuerpo
    glDrawArrays(GL_TRIANGLE_FAN, 1503*35, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*36, 700);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*37, 502);
    // Coloreando ojo derecho
    glDrawArrays(GL_TRIANGLE_FAN, 1503*4, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*5, 502);
    // Coloreando la nariz
    glDrawArrays(GL_TRIANGLE_FAN, 1503*8, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*9, 502);
    // Coloreando ojo izquierdo
    glDrawArrays(GL_TRIANGLE_FAN, 1503*0, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*1, 501);
    // Coloreando pupilas
    glDrawArrays(GL_TRIANGLE_FAN, 1503*2, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*3, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*6, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*7, 501);
    // Coloreando la boca
    glDrawArrays(GL_TRIANGLE_FAN, 1503*10, 700);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*11, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*12, 600);
    // Coloreando la oreja
    glDrawArrays(GL_TRIANGLE_FAN, 1503*13, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*14, 501);
    // Coloreando el cuello
    glDrawArrays(GL_TRIANGLE_FAN, 1503*15, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*16, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*17, 502);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*18, 700);
    // Coloreando el collar
    glDrawArrays(GL_TRIANGLE_FAN, 1503*26, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*27, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*28, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*29, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*30, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*31, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*32, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*33, 501);
    glDrawArrays(GL_TRIANGLE_FAN, 1503*34, 501);
    glBindVertexArray(0);

    glBindVertexArray(m_VAO2);
    glDrawArrays(GL_POINTS, 0, 501*48);
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
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(700, 600, "T08 - Curvas", NULL, NULL);

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
