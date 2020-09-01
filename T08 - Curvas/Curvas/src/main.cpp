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
using namespace std;
#include <string>
#include <fstream>
#include "Utils.h"

using namespace std;
GLuint renderingProgram;

//GLfloat* m_Vertices;
//GLfloat* m_Vertices;
GLuint m_VBO;
GLuint m_VAO;
GLfloat m_Vertices[3003*2*2];
GLuint n_Vertices = 3003*2;
class wcPt3D {
public:
    GLfloat x, y, z;
};

//Declarando puntos de control
  wcPt3D c15[4] = {{0.3678, 0.4304}, {0.2661, 0.4187}, {0.2661, 0.6378}, {0.3678, 0.6261}}; //Ojo Completo
  wcPt3D c16[4] = {{0.3600, 0.4304},{0.4774, 0.4187}, {0.4774, 0.6378},  {0.3678, 0.6261}};
  wcPt3D c17[4] = {{0.4304, 0.4617}, {0.4696, 0.4617}, {0.5087, 0.4395},{0.5087, 0.4304}}; //Nariz
  wcPt3D c18[4] = {{0.4226, 0.3913}, {0.4696, 0.3757},{0.5087, 0.3835}, {0.5087, 0.4304}}; //Nariz
  wcPt3D c19[4] = {{0.4461, 0.5635}, {0.4696, 0.6261}, {0.5713, 0.6261},{0.5870, 0.5400}};   //ojo derecho
  wcPt3D c20[4] = {{0.5087, 0.4304}, {0.5478, 0.4304}, {0.5948, 0.4539},{0.5870, 0.5400}}; //ojo derecho
  wcPt3D c29[4] = {{0.5400, 0.4343},  {0.5400, 0.4343}, {0.5870, 0.3757}, {0.5870, 0.3757}}; //Boca
  wcPt3D c30[4] = {{0.2896, 0.3365}, {0.3913, 0.2739},  {0.5478, 0.2857}, {0.5870, 0.3780}};        //
  wcPt3D c32[4] = {{0.2817, 0.3209},  {0.2817, 0.3209}, {0.2974, 0.3522},  {0.2974, 0.3522}};   //
  wcPt3D c31[4] = {{0.2583, 0.3443}, {0.1878, 0.3091}, {0.1878, 0.4422}, {0.2583, 0.4070}}; //Oreja
  wcPt3D c28[4] = {{0.2270, 0.3600}, {0.2035, 0.3757}, {0.2270, 0.3991}, {0.2426, 0.3835}};   //Oreja
  wcPt3D c33[4] = {{0.2348, 0.3365}, {0.2426, 0.2896},{0.2426, 0.2739}, {0.2348, 0.2348}};   //Cuello
  wcPt3D c34[4] = {{0.1878, 0.3365},{0.1878, 0.3365}, {0.1878, 0.2817}, {0.1878, 0.2817}};   //Cabello
  wcPt3D c35[4] = {{0.1878, 0.2817}, {0.1878, 0.2817},  {0.2387, 0.2817},  {0.2387, 0.2817}}; //Cabello
  wcPt3D c36[4] = {{0.4461, 0.2974}, {0.4304, 0.2739}, {0.4070, 0.2817}, {0.4070, 0.2661}};   //Menton
  wcPt3D c37[4] = {{0.4070, 0.2661}, {0.3913, 0.2348},  {0.3913, 0.2191}, {0.3835, 0.1957}};    //cuello
 //Ojo 2 (Completo)
  wcPt3D c38[4] = {{0.2661, 0.5635}, {0.2661, 0.5635}, {0.2896, 0.5478}, {0.2896, 0.5478}}; //Pestañas
  wcPt3D c39[4] = {{0.2974, 0.6261},  {0.2974, 0.6261}, {0.3130, 0.6026}, {0.3130, 0.6026}}; //Pestañas
  wcPt3D c40[4] = {{0.3522, 0.6496}, {0.3522, 0.6496}, {0.3600, 0.6261}, {0.3600, 0.6261}}; //Pestañas
  wcPt3D c41[4] = {{0.4070, 0.6183}, {0.4070, 0.6183},  {0.4148, 0.6417}, {0.4148, 0.6417}}; //Pestañas
 //Ojo 2
   wcPt3D c42[4] = {{0.5087, 0.6065}, {0.5087, 0.6065}, {0.5165, 0.6300},{0.5165, 0.6300}}; //Pestañas
   wcPt3D c43[4] = {{0.5478, 0.5948}, {0.5478, 0.5948},  {0.5635, 0.6183}, {0.5635, 0.6183}};     //Pestañas
   wcPt3D c44[4] = {{0.5791, 0.5635}, {0.5791, 0.5635},  {0.6026, 0.5870}, {0.6026, 0.5870}};     //Pestañas
   wcPt3D c45[4] = {{0.5893, 0.5243}, {0.5893, 0.5243},{0.6159, 0.5400},{0.6159, 0.5400}}; //Pestañas
   wcPt3D c26[4] = {{0.1878, 0.3365},{0.0783, 0.3365}, {0.0783, 0.3365}, {0.1565, 0.4696}};          //PELO
   wcPt3D c27[4] = {{0.1565, 0.4696},{0.0548, 0.5478},{0.0548, 0.5478},{0.1565, 0.6261}};              //PELO
   wcPt3D c25[4] = {{0.1565, 0.6261},{0.1409, 0.7435},{0.1017, 0.7435}, {0.2348, 0.7670}};          //ARRIBA
   wcPt3D c24[4] = {{0.2348, 0.7670}, {0.3130, 0.9000}, {0.2739, 0.9000}, {0.3757, 0.8217}};  //PELO
   wcPt3D c23[4] = {{0.3757, 0.8217},{0.4696, 0.9000}, {0.4304, 0.9000}, {0.5165, 0.7826}}; //OREJA
   wcPt3D c22[4] = {{0.5165, 0.7826},{0.6261, 0.7670}, {0.5870, 0.7670},  {0.5870, 0.6652}};
   wcPt3D c21[4] = {{0.5870, 0.6652}, {0.6496, 0.6104}, {0.6496, 0.6104},{0.5870, 0.5400}};




void computeBezPt(GLfloat u, wcPt3D *bezPt, GLint nCtrlPts, wcPt3D *ctrlPts, GLint *C) {
    GLint k, n = nCtrlPts - 1;
    GLfloat bezBlendFcn;

    bezPt->x = bezPt->y = bezPt->z = -0.5;

    // calcula las funciones de combinacion y combina los puntos de control
    for (k = 0; k < nCtrlPts; k++) {
        bezBlendFcn = C[k] * pow(u, k) * pow(1 - u, n - k);
        bezPt->x += ctrlPts[k].x * bezBlendFcn;
        bezPt->y += ctrlPts[k].y * bezBlendFcn;
        bezPt->z += ctrlPts[k].z * bezBlendFcn;
    }
}

// calcula los coeficientes binomiales C para un valor dado de n
void binomialCoeffs(GLint n, GLint *C) {
    GLint k, j;

    for (k = 0; k <= n; k++) {
        // calcula n!/k!(n-k)!
        C[k] = 1;
        for (j = n; j >= k + 1; j--)
            C[k] *= j;
        for (j = n - k; j >= 2; j--)
            C[k] /= j;
    }
}

void bezier(wcPt3D *ctrlPts, GLint nCtrlPts, GLint nBezCurvePts, GLfloat m_Verts[]) {
    wcPt3D bezCurvePt;
    GLfloat u;
    GLint *C, k;

    // asigna el espacio para los coeficientes binomiales
    C = new GLint[nCtrlPts];

    binomialCoeffs(nCtrlPts - 1, C);
    for (k = 0; k <= nBezCurvePts; k++) {
        u = GLfloat(k) / GLfloat(nBezCurvePts);
        computeBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, C);
        m_Verts[k*6+0] = bezCurvePt.x;
        m_Verts[k*6+1] = bezCurvePt.y;
        m_Verts[k*6+2] = 0;
        //Colores
        m_Verts[k*6+3] = 0.0f;
        m_Verts[k*6+4] = 1.0f;
        m_Verts[k*6+5] = 1.0f;

    }
   // m_Vertices.push_back(bezCurvePt.x);
    delete[] C;
}


void init (GLFWwindow* window) {
	// Utils
	renderingProgram = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");

    GLfloat m_V1[3003*2];
    GLfloat m_V2[3003*2];
   /* GLfloat m_V3[3003];
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
    GLfloat m_V31[3003];*/

    GLint nCtrlPts = 4, nBezCurvePts = 1000;

    bezier(c15, nCtrlPts, nBezCurvePts, m_V1);
    bezier(c16, nCtrlPts, nBezCurvePts, m_V2);

   /* bezier(c17, nCtrlPts, nBezCurvePts, m_V3);
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
*/

 //   for (GLuint i=0; i< n_Vertices; i++) {
    for (GLuint i=0; i< n_Vertices; i++) {
    	m_Vertices[i+3003*2*0] = m_V1[i];
    	cout <<m_Vertices[i+3003*2*0]<<endl;
    //	m_Vertices[i+3003*2*1] = m_V2[i];

    	/*
    	m_Vertices[i+3003*2] = m_V3[i];
    	m_Vertices[i+3003*3] = m_V4[i];
    	m_Vertices[i+3003*4] = m_V5[i];
    	m_Vertices[i+3003*5] = m_V6[i];
    	m_Vertices[i+3003*6] = m_V7[i];
    	m_Vertices[i+3003*7] = m_V8[i];
    	m_Vertices[i+3003*8] = m_V9[i];
    	m_Vertices[i+3003*9] = m_V10[i];
    	m_Vertices[i+3003*10] = m_V11[i];
    	m_Vertices[i+3003*11] = m_V12[i];
    	m_Vertices[i+3003*12] = m_V13[i];
    	m_Vertices[i+3003*13] = m_V14[i];
    	m_Vertices[i+3003*14] = m_V15[i];
    	m_Vertices[i+3003*15] = m_V16[i];
    	m_Vertices[i+3003*16] = m_V17[i];
    	m_Vertices[i+3003*17] = m_V18[i];
    	m_Vertices[i+3003*18] = m_V19[i];
    	m_Vertices[i+3003*19] = m_V20[i];
    	m_Vertices[i+3003*20] = m_V21[i];
    	m_Vertices[i+3003*21] = m_V22[i];
    	m_Vertices[i+3003*22] = m_V23[i];
    	m_Vertices[i+3003*23] = m_V24[i];
    	m_Vertices[i+3003*24] = m_V25[i];
    	m_Vertices[i+3003*25] = m_V26[i];
    	m_Vertices[i+3003*26] = m_V27[i];
    	m_Vertices[i+3003*27] = m_V28[i];
    	m_Vertices[i+3003*28] = m_V29[i];
    	m_Vertices[i+3003*29] = m_V30[i];
    	m_Vertices[i+3003*30] = m_V31[i];*/
    }

    glGenVertexArrays(1, &m_VAO);
      glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(
    	GL_ARRAY_BUFFER,
    	sizeof(m_Vertices),
    	m_Vertices,
    	GL_STATIC_DRAW
    );


    glVertexAttribPointer(
    	0,
    	3,
    	GL_FLOAT,
    	GL_FALSE,
    	6 * sizeof(GLfloat),
    	0
    );

    glEnableVertexAttribArray(0);	// Habilita este atributo

    // SHADERS DESHABILITADOS
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

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    	glBindVertexArray(m_VAO);

}

void display(GLFWwindow* window, double currentTime) {

	glClearColor(1,0,0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(m_VAO);

	glDrawArrays(GL_TRIANGLES, 0, 3003);
	//glDrawArrays(GL_LINE_LOOP, 1002, 1000);
	//glDrawElements(GL_TRIANGLES, 15 , GL_UNSIGNED_INT, 0);
	// for (int i=1; i< 32; i++) {
	//	 glDrawArrays(GL_LINE_LOOP, 3003*i +1, 3003);
	 //}
	glBindVertexArray(0);

}

int main(void) {

	// Initialise GLFW
    if (!glfwInit()) {
    	exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  //
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            //
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); 	// Resizable option.

    GLFWwindow* window = glfwCreateWindow(600, 600, "Tarea08", NULL, NULL);

    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
    	exit(EXIT_FAILURE);
    }

    glfwSwapInterval(1);

    init(window);

    while (!glfwWindowShouldClose(window)) {
        display(window, glfwGetTime());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
