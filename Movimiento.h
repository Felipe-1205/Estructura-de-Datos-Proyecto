#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include <string>
using namespace std;

class Movimiento {
private:
  string tipo_mov;
  double magnitud;
  string unidad_med;

public:
  Movimiento(string x, double y, string z) {
    tipo_mov = x;
    magnitud = y;
    unidad_med = z;
  }

  string getTipoMov() const { return tipo_mov; }
  double getMagnitud() const { return magnitud; }
  string getUnidadMed() const { return unidad_med; }
  void setTipoMov(string x) { tipo_mov = x; }
  void setMagnitud(double x) { magnitud = x; }
  void setUnidadMed(string x) { unidad_med = x; }
};

#endif
// MOVIMIENTO_H
