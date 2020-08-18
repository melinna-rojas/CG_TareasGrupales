/*============================================================================
					TAREA 07 - CURVAS Y SUPERFICIES

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
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>

//Where everything happens
#include "minPath.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils.h"
#include "CornerTable.h"
#include "DefinitionTypes.h"

using namespace glm;
using namespace std;

GLuint rProgram;
GLuint vao[1];
GLuint vbo[1];
GLuint ebo[2];

int nPoints; //Number of Points

double *vertexList1;
int points;

CornerTable *ct; //Corner Table
vector<unsigned int> pathIndex;


//Function that generates random 2D points
void generatePoints(double &x1, double &y1, double &x2, double &y2) {
    srand(time(NULL));

    x1 = -3.0000 + (rand() % 60010) / 10000.0f;
    y1 = -3.0000 + (rand() % 60010) / 10000.0f;
    x2 = -3.0000 + (rand() % 60010) / 10000.0f;
    y2 = -3.0000 + (rand() % 60010) / 10000.0f;
}

//Function that finds the points of the x and y coordinates
void findCoord(double vertexList[], int npoint, double px1, double py1, int &p) {
    double tempX, tempY;
    double nX, nY;
    double cnX = 1000, cnY = 1000;

    for (int i = 1; i <= npoint; i++){
        tempX = vertexList[(i - 1) * 3];
        tempY = vertexList[(i - 1) * 3 + 1];

        //It is verified that the points are not negative
        nX = tempX - px1;
        nY = tempY - py1;

        if (nX <= 0) nX = nX * (-1.0);
        if (nY <= 0) nY = nY * (-1.0);

        if (((px1 - tempX) == 0) && ((py1 - tempY) == 0)) {
            p = i - 1;
            break;
        }
        else{
            if (nX < cnX && nY < cnY) {
                cnX = nX;
                cnY = nY;
                p = i - 1;
            }
        }
    }
}

void readMesh()
{
    ifstream fin;
    //Mesh 21
    fin.open("mesh/mesh21.mesh");
    string name;

    int npoint, ntriangle, var3;
    int var0;

    fin >> name;
    fin >> npoint >> ntriangle >> var3;

    double *vertexList = new double[3 * npoint];

    //Leyendo los vertices
    for (int i = 0; i < npoint; ++i)
    {
        fin >> vertexList[3 * i] >> vertexList[3 * i + 1] >> vertexList[3 * i + 2];
    }

    const CornerType numberTriangles = ntriangle;
    const CornerType numberVertices = npoint;

    CornerType *triangleList = new CornerType[3 * ntriangle];

    for (int i = 0; i < ntriangle; ++i)
    {
        fin >> var0 >> triangleList[i * 3] >> triangleList[i * 3 + 1] >> triangleList[i * 3 + 2];
    }
    int numberCoordinatesByVertex = 3;
    CornerTable *CT = new CornerTable(triangleList,
                                      vertexList,
                                      numberTriangles,
                                      numberVertices,
                                      numberCoordinatesByVertex);
    ct = CT;
    nPoints = npoint;
    vertexList1 = vertexList;
}

void buildPath(int inicio, int destino)
{
    vector<unsigned int> path;
    const CornerType *trianglesPositions = ct->getTriangleList();

    //Main function for this hw
    minimumPath(path, ct, inicio, destino);

    int aux = path[destino];

    pathIndex.push_back(trianglesPositions[destino * 3]);
    pathIndex.push_back(trianglesPositions[destino * 3 + 1]);
    pathIndex.push_back(trianglesPositions[destino * 3 + 2]);

    while (aux > -1)
    {
        pathIndex.push_back(trianglesPositions[aux * 3]);
        pathIndex.push_back(trianglesPositions[aux * 3 + 1]);
        pathIndex.push_back(trianglesPositions[aux * 3 + 2]);
        aux = path[aux];
    }
}

void setUpVertices()
{
    double *vertexPositions = ct->getAttributes();
    const CornerType *trianglesPositions = ct->getTriangleList();
    for (unsigned int i = 0; i < ct->getNumberVertices() * 3; i++)
        vertexPositions[i] *= 2;

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, ct->getNumberVertices() * 3 * sizeof(double), &vertexPositions[0], GL_STATIC_DRAW);

    glGenBuffers(2, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ct->getNumTriangles() * 3 * sizeof(CornerType), &trianglesPositions[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, pathIndex.size() * 3 * sizeof(CornerType), &pathIndex[0], GL_STATIC_DRAW);
}

void init(GLFWwindow *window)
{
    // Shaders
    rProgram = Utils::createShaderProgram("src/vertShader.glsl", "src/fragShader.glsl");

    readMesh();

    //Generamos los puntos
    double px1, py1, px2, py2;
    generatePoints(px1, py1, px2, py2);

    int nearPoint1, nearPoint2;

    //	Ubicacion de puntos
    findCoord(vertexList1, nPoints, px1, py1, nearPoint1);
    findCoord(vertexList1, nPoints, px2, py2, nearPoint2);

    cout << "Puntos generados aleatoriamente" << endl;
    cout << "-------------------------------" << endl;
    cout << "Punto 1 : [" << px1 << " , " << py1 << "]"<<endl;
    cout << "Punto 2 : [" << px2 << " , " << py2 << "]"<<endl;
    //cout << "El punto 1 est� cerca al punto #" << nearPoint1 << endl;
    //cout << "El punto 2 est� cerca al punto #" << nearPoint2 << endl;

    //	Distancia minima de puntos
    buildPath(nearPoint1, nearPoint2);

    cout<<endl;
    cout << "Camino de triangulos" << endl;
    cout << "-------------------------------" << endl;
    //	Mostrar triangulos recorridos
    for (unsigned int i = 0; i < pathIndex.size(); i += 3)
    {
        cout << "Triangulo "<< i / 3 + 1 << " : " << pathIndex[i] << " ," << pathIndex[i + 1] << " ," << pathIndex[i + 2] << endl;
    }

    setUpVertices();
}

void display(GLFWwindow *window, double currentTime)
{

    glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(rProgram);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);


    vec3 color = vec3(1.0, 0.00, 0.0);
    glUniform3fv(glGetUniformLocation(rProgram, "vColor"), 1, value_ptr(color));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);

    //Dibujando la malla
    for (int i = 0; i < (int)ct->getNumTriangles(); i++)
    {
    	//Colores aleatorios
        color = vec3(i % 3 - 0.42, i % 5 - 0.42, i % 7 - 0.43);
        if (i == 0) color = vec3(1, 0.42, 0.23);

        glUniform3fv(glGetUniformLocation(rProgram, "vColor"), 1, value_ptr(color));
        glDrawElements(GL_TRIANGLES, 3,GL_UNSIGNED_INT,(void *)(i * 3 * sizeof(GL_UNSIGNED_INT)));
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Pintando triangulos recorrido de blanco
    color = vec3(1, 1, 1);
    glUniform3fv(glGetUniformLocation(rProgram, "vColor"), 1, value_ptr(color));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
    glDrawElements(GL_TRIANGLES,pathIndex.size(),GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Pintando bordes del camino
    color = vec3(0.0, 1.0, 0.0);

    glUniform3fv(glGetUniformLocation(rProgram, "vColor"), 1, value_ptr(color));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);

    for (int i = 0; i < (int)pathIndex.size() / 3; i++)
    {
        glDrawElements(GL_LINE_LOOP, 3, GL_UNSIGNED_INT,(void *)(i * 3 * sizeof(GL_UNSIGNED_INT)));
    }
}

int main(void)
{
    if (!glfwInit())    exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(600, 600, "CG - CORNER TABLE", NULL, NULL);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)  exit(EXIT_FAILURE);
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
