#ifndef VEHICULO_H
#define VEHICULO_H

using namespace std;

class Vehiculo {
private:
  double coordX;
  double coordY;
  double direccion;

public:
  Vehiculo(double x, double y, double z) {
    direccion = z;
    coordX = x;
    coordY = y;
  }

  double getCoordX() const { return coordX; }
  double getCoordY() const { return coordY; }
  double getDireccion() const { return direccion; }
  void setCoordX(double x) { coordX = x; }
  void setCoordY(double x) { coordY = x; }
  void setDireccion(double x) { direccion = x; }
};
#endif
// VEHICULO_H
