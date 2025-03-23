#ifndef ELEMENTO_H
#define ELEMENTO_H

using namespace std;
#include <string>

class Elemento {
private:
  string tipo_comp;
  double tamano;
  string unidad_med;
  double coordX;
  double coordY;

public:
  Elemento() {
    tipo_comp = "";
    tamano = 0.0;
    unidad_med = "";
    coordX = -1;
    coordY = -1;
  }

  Elemento(string x, double y, string z, double w, double v) {
    tipo_comp = x;
    tamano = y;
    unidad_med = z;
    coordX = w;
    coordY = v;
  }
  string get_tipo_comp() const { return tipo_comp; }
  double get_tamano() const { return tamano; }
  string get_unidad_med() const { return unidad_med; }
  double get_coordX() const { return coordX; }
  double get_coordY() const { return coordY; }
  void set_tipo_comp(string x) { tipo_comp = x; }
  void set_tamano(double x) { tamano = x; }
  void set_unidad_med(string x) { unidad_med = x; }
  void set_coordX(double x) { coordX = x; }
  void set_coordY(double x) { coordY = x; }

  bool operator==(const Elemento& other) const {
    return (tipo_comp == other.tipo_comp &&
            tamano == other.tamano &&
            unidad_med == other.unidad_med &&
            coordX == other.coordX &&
            coordY == other.coordY);
  }

};
#endif
// ELEMENTO_H