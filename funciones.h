#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Analisis.h"
#include "Elemento.h"
#include "Movimiento.h"
#include "Quadtree.hxx"
#include "Vehiculo.h"
#include "Grafo.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void cargar_comandos(string nombre_archivo, vector<Movimiento> *movimiento,
                     vector<Analisis> *analisis) {
  ifstream archivo(nombre_archivo);
  vector<Movimiento> comandosaux;
  vector<Analisis> comandosaux1;
  vector<string> partes;
  string linea, aux;
  Movimiento mov1("", 0, "");
  Movimiento mov2("", 0, "");
  Analisis an1("", "", "");
  Analisis an2("", "", "");

  if (!archivo.is_open()) {
    cout << nombre_archivo << " no se encuentra o no puede leerse." << endl;
    return;
  }

  while (getline(archivo, linea)) {
    for (int i = 0; i < linea.length(); i++) {
      if (linea[i] == ',') {
        partes.push_back(aux);
        aux = "";
      } else {
        aux += linea[i];
      }
    }
    partes.push_back(aux);
    aux = "";

    try {
      mov1.setTipoMov(partes[0]);
      mov1.setMagnitud(stod(partes[1]));
      mov1.setUnidadMed(partes[2]);
      comandosaux.push_back(mov1);
      comandosaux1.push_back(an2);
    } catch (invalid_argument &e) {
      an1.setTipoAnalisis(partes[0]);
      an1.setObjeto(partes[1]);
      an1.setComentario(partes[2]);
      comandosaux1.push_back(an1);
      comandosaux.push_back(mov2);
    }

    partes.clear();
  }

  archivo.close();

  if (comandosaux.empty() && comandosaux1.empty()) {
    cout << nombre_archivo << " está vacio." << endl;
  } else {
    movimiento->clear();
    analisis->clear();

    *movimiento = comandosaux;
    *analisis = comandosaux1;

    cout << movimiento->size() << " Comandos cargados correctamente desde "
         << nombre_archivo << ".\n"
         << endl;
  }
}

void cargar_elementos(string nombre_archivo, vector<Elemento> *elemento) {
  ifstream archivo(nombre_archivo);
  vector<Elemento> elementos;
  vector<string> partes;
  string linea, aux;
  Elemento ele("", 0, "", 0, 0);
  if (!archivo.is_open()) {
    cout << nombre_archivo << " no se encuentra o no puede leerse." << endl;
    return;
  }

  while (getline(archivo, linea)) {
    for (int i = 0; i < linea.length(); i++) {
      if (linea[i] == ',') {
        partes.push_back(aux);
        aux = "";
      } else {
        aux += linea[i];
      }
    }
    partes.push_back(aux);
    ele.set_tipo_comp(partes[0]);
    ele.set_tamano(stod(partes[1]));
    ele.set_unidad_med(partes[2]);
    ele.set_coordX(stod(partes[3]));
    ele.set_coordY(stod(partes[4]));
    elementos.push_back(ele);
    partes.clear();
    aux = "";
  }

  archivo.close();

  if (elementos.empty()) {
    cout << nombre_archivo << " está vacio." << endl;
  } else {
    elemento->clear();
    *elemento = elementos;
    cout << elemento->size() << " Elementos cargados correctamente desde "
         << nombre_archivo << "." << endl;
  }

  for (const auto &element : *elemento) {
    std::cout << endl
              << element.get_tipo_comp() << " " << element.get_tamano() << " "
              << element.get_unidad_med() << " " << element.get_coordX() << " "
              << element.get_coordY() << endl;
  }
}

void agregar_movimiento(string tipo_mov, double magnitud, string unidad_med,
                        vector<Movimiento> *movimiento) {
  Movimiento mov1(tipo_mov, magnitud, unidad_med);
  movimiento->push_back(mov1);
  cout << "El comando ha sido agregado exitosamente." << endl;
}

void agregar_analisis(string tipo_analisis, string objeto, string comentario,
                      vector<Analisis> *analisis) {
  Analisis ana(tipo_analisis, objeto, comentario);
  analisis->push_back(ana);
  cout << "El analisis ha sido agregado exitosamente." << endl;
}

void agregar_elemento(string tipo_comp, double tamano, string unidad_med,
                      double coordX, double coordY,
                      vector<Elemento> *elemento) {
  Elemento ele(tipo_comp, tamano, unidad_med, coordX, coordY);
  elemento->push_back(ele);
  cout << "El elemento ha sido agregado exitosamente." << endl;
}

void guardar(string tipoArchivo, string nombreArchivo,
             vector<Movimiento> movimiento, vector<Analisis> analisis,
             vector<Elemento> elemento) {
  ofstream archivoSalida(nombreArchivo + ".txt");
  if (archivoSalida.is_open()) {
    if (tipoArchivo == "comandos") {
      for (int i = 0; i < movimiento.size(); i++) {
        if (movimiento[i].getTipoMov() != "" && movimiento[i].getMagnitud() != 0 && movimiento[i].getUnidadMed() != ""){
          archivoSalida << movimiento[i].getTipoMov() << ","
                        << movimiento[i].getMagnitud() << ","
                        << movimiento[i].getUnidadMed() << endl;
        }
        else if (analisis[i].getTipoAnalisis() != "" && analisis[i].getObjeto() != "" && analisis[i].getComentario() != ""){
          archivoSalida << analisis[i].getTipoAnalisis() << ","
                      << analisis[i].getObjeto() << ","
                      << analisis[i].getComentario() << endl;
        }
      }
    } else if (tipoArchivo == "elementos") {
      for (int i = 0; i < elemento.size(); i++) {
        archivoSalida << elemento[i].get_tipo_comp() << ","
                      << elemento[i].get_tamano() << ","
                      << elemento[i].get_unidad_med() << ","
                      << elemento[i].get_coordX() << ","
                      << elemento[i].get_coordY() << endl;
      }
    }
    archivoSalida.close();
    cout << "Archivo creado exitosamente." << endl;
  } else {
    cout << "No se pudo crear el archivo." << endl;
  }
}
void simular_comandos(double cordx, double cordy, Vehiculo *carro,
                      vector<Movimiento> *movimiento) {

  double tempx = carro->getCoordX(), tempy = carro->getCoordY(),
         tempg = carro->getDireccion(), conversion = 0;

  carro->setCoordX(cordx);
  carro->setCoordY(cordy);
  carro->setDireccion(0);

  for (std::vector<Movimiento>::iterator it = movimiento->begin();
       it != movimiento->end(); it++) {
    if (it->getTipoMov() == "" && it->getMagnitud() == 0 &&
        it->getUnidadMed() == "") {
      continue;

    } else if (it->getTipoMov().find("avanzar") != std::string::npos) {
      cout << "\nComando: " << it->getTipoMov() << " " << it->getMagnitud()
           << " " << it->getUnidadMed();

      conversion = it->getMagnitud();

      if (it->getUnidadMed().find("km") != std::string::npos)
        conversion = it->getMagnitud() * 1000;
      if (it->getUnidadMed().find("cm") != std::string::npos)
        conversion = it->getMagnitud() / 100;

      cout << "\nAvanzando " << conversion << " m" << endl;

      carro->setCoordX(carro->getCoordX() +
                       (cos(carro->getDireccion()) * (conversion)));
      carro->setCoordY(carro->getCoordY() +
                       (sin(carro->getDireccion()) * (conversion)));

      cout << "Se avanzo hasta la posición (" << carro->getCoordX() << ","
           << carro->getCoordY() << ")" << endl;

    } else if (it->getTipoMov().find("girar") != std::string::npos) {
      cout << "\nComando: " << it->getTipoMov() << " " << it->getMagnitud()
           << " " << it->getUnidadMed();

      conversion = it->getMagnitud();

      if (it->getUnidadMed().find("grd") != std::string::npos)
        conversion = it->getMagnitud() * (M_PI / 180);

      cout << "\nGirando " << conversion << " rad" << endl;

      carro->setDireccion(carro->getDireccion() + conversion);

      cout << "El carro tiene la direccion " << carro->getDireccion() << " rad"
           << endl;
    }
  }
  cout << "\nLa simulación de los comandos, a partir de la posición (" << cordx
       << "," << cordy << "),deja al robot en la nueva posición ("
       << carro->getCoordX() << "," << carro->getCoordY() << ")" << endl;
  carro->setCoordX(tempx);
  carro->setCoordY(tempy);
  carro->setDireccion(tempg);
}

// SEGUNDA ENTREGA

void ubicar_elementos(vector<Elemento> *elementos, Quad q) {
    if (elementos->empty()) {
        cout << "(No hay información) La información requerida no está almacenada en memoria. Correr el comando cargar_elementos" << endl;
        return;
    }
    // insertar cada elemento en el quadtree
    vector<Elemento> elementos_problema;
    for (Elemento e : *elementos) {
        Node* n = new Node(&e);
        if (q.inBoundary(n->pos)) {
            q.insert(n);
        } else {
            elementos_problema.push_back(e);
        }
    }

    if (elementos_problema.empty()) {
        cout << "(Resultado exitoso) Los elementos han sido procesados exitosamente." << endl;
    } else {
        cout << "(Problemas con elementos) Los siguientes elementos no pudieron procesarse adecuadamente:" << endl;
        for (Elemento e : elementos_problema) {
            cout << "- " << e.get_tipo_comp() << endl;
        }
        cout << "(Resultado exitoso) Los demás elementos han sido procesados exitosamente." << endl;
    }
}

void en_cuadrante(int coordX1, int coordX2, int coordY1, int coordY2,vector<Elemento> *elementos, Quad q) {
  Quad q2(Point(coordX1, coordY1), Point(coordX2, coordY2));
    for (Elemento e : *elementos) {
        Node* n = new Node(&e);
        if (q2.inBoundary(n->pos)) {
            cout <<"el elemento"<<e.get_tipo_comp()<< " esta dentro de cuadrante"<<endl;
              } else {
        }
    }
}


// TERCERA ENTREGA
Grafo crear_mapa (double coeficiente, Grafo g, vector<Elemento> *elementos){

  // Sacar tamaño del vector elementos y el numero de vertices
  int tam = elementos->size(), num_vertices = 0;
      num_vertices = elementos->size();

  // Calcular la cantidad de vecinos
  int num_vecinos = ceil(num_vertices * coeficiente);
  
  double distancia = 0;
  
  for (int  i = 0; i < tam; i++){
    // insertar los elementos en el grafo
    g.insertarVertice((*elementos)[i]);
  }

  for (int i = 0; i < tam; i++) {
  vector<Elemento> vecinos;
  vector<double> distancias;

  // comparar las distancias de los vectores
  for (int j = 0; j < tam; j++) {
    if (i == j) {
      continue; // Saltar la comparación si es el mismo elemento
    }

    distancia = sqrt(pow((*elementos)[i].get_coordX() - (*elementos)[j].get_coordX(), 2) +
                     pow((*elementos)[i].get_coordY() - (*elementos)[j].get_coordY(), 2));

    // Insertar en el vector de vecinos solo si es una distancia más corta que alguna ya almacenada
    if (vecinos.size() < num_vecinos) {
      vecinos.push_back((*elementos)[j]);
      distancias.push_back(distancia);
    } else {
      // Buscar la distancia máxima actual y reemplazarla si la nueva distancia es menor
      double maxDistancia = *max_element(distancias.begin(), distancias.end());
      auto maxDistanciaIter = find(distancias.begin(), distancias.end(), maxDistancia);
      if (distancia < maxDistancia) {
        *maxDistanciaIter = distancia;
        vecinos[maxDistanciaIter - distancias.begin()] = (*elementos)[j];
      }
    }
  }

  for (int k = 0; k < vecinos.size(); k++) {
         
    g.insertarArista((*elementos)[i], vecinos[k], distancias[k]);
          
  }
}
  int cantVertices = g.cantVertices();
  
  cout << "\nSe han insertado " << cantVertices << " elementos en el mapa\n"<< endl;

  int numAristas = g.cantAristas();

    g.imprimirMatrizAdyacencia();

    cout << "\nSe crearon " << numAristas <<  " aristas.\n" << endl;

    
    if (cantVertices > 0)
    {
        cout << "El mapa se ha generado exitosamente. Cada elemento tiene " << num_vecinos << " vecinos." << endl;
    } else if (cantVertices == 0){
        cout << "El mapa no se ha podido generar exitosamente " << endl;
    }

  return g;
}

void ruta_mas_larga(Grafo g) {
  vector<Elemento> vertices = g.getVertices();
  int numVertices = vertices.size();

  if (numVertices == 0){
    cout << "\nNo se ha creado el mapa usando la funcion crear_mapa" << endl;
    return;
  }

  int maxDistancia = -1;
  Elemento origen, destino;
  double distanciaTotal = 0.0, costoTotal = 0.0;

  // Realizar un recorrido exhaustivo para encontrar los componentes más alejados
  for (int i = 0; i < numVertices; i++) {
    for (int j = i + 1; j < numVertices; j++) {
      vector<Elemento> ruta = g.obtenerRuta(vertices[i], vertices[j]);
      double costo = 0.0;

      if (ruta.size() > 1) {
        // Calcular el costo de la ruta sumando los costos de las aristas
        for (int k = 0; k < ruta.size() - 1; k++) {
          Elemento origen = ruta[k];
          Elemento destino = ruta[k + 1];
          double costoArista = g.buscarArista(origen, destino);
          costo += costoArista;
        }
      }

      if (ruta.size() > distanciaTotal) {
        costoTotal = costo;
        distanciaTotal = ruta.size();
        maxDistancia = ruta.size() - 1;
        maxDistancia = ruta.size() - 1;
        origen = vertices[i];
        destino = vertices[j];
      }
    }
  }

  cout << "Componentes más alejados:\n";
  cout << "Origen: " << origen.get_tipo_comp() << "\n";
  cout << "Destino: " << destino.get_tipo_comp() << "\n";
  cout << "Distancia total: " << maxDistancia << " aristas\n";
  cout << "Costo total: " << costoTotal << "\n";

  // Obtener la secuencia de elementos para ir del origen al destino
  vector<Elemento> secuencia = g.obtenerRuta(origen, destino);
  cout << "Secuencia de elementos:\n";
  for (const Elemento& elemento : secuencia) {
    cout << elemento.get_tipo_comp() << " ";
  }
  cout << "\n";
}




#endif
