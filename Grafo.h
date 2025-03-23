#include "Elemento.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

#ifndef GRAFO_H
#define GRAFO_H

using namespace std;

class Grafo {
private:
  vector<Elemento>
      vertices; // lista de vértices que proporciona el índice en la matriz
  double **aristas; // matriz de adyacencia con doble puntero (memoria dinámica)
public:
  Grafo() { aristas = nullptr; }
  void setVertices(vector<Elemento> v) { vertices = v; }
  void setAristas(double **a) { aristas = a; }
  vector<Elemento> getVertices() { return vertices; }
  double **getAristas() { return aristas; }
  int cantVertices() const { return vertices.size(); }

  int cantAristas() {
    int suma = 0;
    for (int i = 0; i < cantVertices(); i++) {
      for (int j = 0; j < cantVertices(); j++) {
        if (*(*(aristas + i) + j) != 0)
          suma++;
      }
    }
    return suma;
  }
  int buscarVertice(Elemento vert) {
    int ind = -1;
    for (int i = 0; i < cantVertices(); i++) {
      if (vertices[i] == vert)
        ind = i;
    }
    return ind;
  }
  bool insertarVertice(Elemento vert) {
    bool res = false;
    if (buscarVertice(vert) == -1) {
      vertices.push_back(vert);
      double **nmatriz = new double *[cantVertices()];
      for (int i = 0; i < cantVertices(); i++) {
        nmatriz[i] = new double[cantVertices()];
      }
      for (int i = 0; i < cantVertices() - 1; i++) {
        for (int j = 0; j < cantVertices() - 1; j++) {
          nmatriz[i][j] = aristas[i][j];
        }
      }
      for (int i = 0; i < cantVertices(); i++) {
        nmatriz[i][cantVertices() - 1] = 0;
        nmatriz[cantVertices() - 1][i] = 0;
      }
      for (int i = 0; i < cantVertices() - 1; i++) {
        delete[] aristas[i];
      }
      delete[] aristas;
      aristas = nmatriz;
      res = true;
    }
    return res;
  }
  bool insertarArista(Elemento ori, Elemento des, double cos) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if (i_ori != -1 && i_des != -1) {
      if (aristas[i_ori][i_des] == 0) {
        aristas[i_ori][i_des] = cos;
        res = true;
      }
    }
    return res;
  }
  double buscarArista(Elemento ori, Elemento des) {
    double res = -1;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if (i_ori != -1 && i_des != -1) {
      res = aristas[i_ori][i_des];
    }
    return res;
  }
  bool eliminarArista(Elemento ori, Elemento des) {
    bool res = false;
    int i_ori = buscarVertice(ori);
    int i_des = buscarVertice(des);
    if (i_ori != -1 && i_des != -1) {
      aristas[i_ori][i_des] = 0;
      res = true;
    }
    return res;
  }
  vector<Elemento> recorrerGrafo() {
    vector<Elemento> camino; // Vector que almacenará el camino recorrido
    vector<bool> visitado(cantVertices(),
                          false); // Vector para marcar los vértices visitados
    int indiceActual = 0;         // Índice del vértice actual

    visitado[indiceActual] = true; // Marcar el primer vértice como visitado
    camino.push_back(
        vertices[indiceActual]); // Agregar el primer vértice al camino

    // Realizar el recorrido hasta visitar todos los vértices
    while (camino.size() < cantVertices()) {
      double distanciaMinima =
          numeric_limits<double>::max(); // Inicializar la distancia mínima con
                                         // un valor máximo
      int siguienteIndice = -1; // Índice del siguiente vértice a visitar

      // Buscar la arista de menor distancia desde el vértice actual
      for (int i = 0; i < cantVertices(); i++) {
        if (!visitado[i] && aristas[indiceActual][i] != 0 &&
            aristas[indiceActual][i] < distanciaMinima) {
          distanciaMinima = aristas[indiceActual][i];
          siguienteIndice = i;
        }
      }
      // Si se encontró una arista válida, avanzar al siguiente vértice
      if (siguienteIndice != -1) {
        indiceActual = siguienteIndice;
        visitado[indiceActual] = true;
        camino.push_back(vertices[indiceActual]);
      } else {
        // Si no se encontró una arista válida, significa que no hay más caminos
        // posibles
        break;
      }
    }

    return camino;
  }

  vector<Elemento> obtenerRuta(Elemento origen, Elemento destino) {
    vector<Elemento> ruta; // Vector que almacenará la ruta encontrada
  
    // Crear un conjunto de vértices visitados y no visitados
    unordered_set<int> visitados;
    unordered_map<int, double> distancias;
  
    // Inicializar las distancias a infinito excepto para el vértice origen
    for (int i = 0; i < cantVertices(); i++) {
      distancias[i] = numeric_limits<double>::max();
    }
    int indiceOrigen = buscarVertice(origen);
    int indiceDestino = buscarVertice(destino);
    if (indiceOrigen == -1 || indiceDestino == -1) {
      // Si el origen o el destino no existen en el grafo, devolver una ruta vacía
      return ruta;
    }
  
    distancias[indiceOrigen] = 0; // La distancia del origen a sí mismo es 0
  
    // Crear una cola de prioridad (min-heap) para almacenar los vértices a visitar
    priority_queue<pair<double, int>, vector<pair<double, int>>,
                   greater<pair<double, int>>>
        pq;
    pq.push({0, indiceOrigen});
  
    // Crear un mapa para almacenar los padres de cada vértice en la ruta más corta
    unordered_map<int, int> padres;
    padres[indiceOrigen] = -1;
  
    // Realizar el algoritmo de Dijkstra
    while (!pq.empty()) {
      int u = pq.top().second;
      pq.pop();
  
      // Marcar el vértice actual como visitado
      visitados.insert(u);
  
      // Si se ha alcanzado el destino, construir la ruta y finalizar el algoritmo
      if (u == indiceDestino) {
        int v = u;
        while (v != -1) {
          ruta.push_back(vertices[v]);
          v = padres[v];
        }
        reverse(ruta.begin(), ruta.end());
        break;
      }
  
      // Explorar los vértices adyacentes al vértice actual
      for (int v = 0; v < cantVertices(); v++) {
        if (aristas[u][v] != 0 && visitados.count(v) == 0) {
          double peso = aristas[u][v];
          double distanciaActual = distancias[u] + peso;
  
          // Si se encuentra un camino más corto hacia el vértice adyacente, actualizar la distancia
          if (distanciaActual < distancias[v]) {
            distancias[v] = distanciaActual;
            padres[v] = u;
            pq.push({distanciaActual, v});
          }
        }
      }
    }
  
    return ruta;
  }

  void imprimirMatrizAdyacencia() {
    for (int i = 0; i < cantVertices(); i++) {
      for (int j = 0; j < cantVertices(); j++) {
        cout << aristas[i][j] << " ";
      }
      cout << endl;
    }
  }
};

#endif