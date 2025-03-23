#ifndef ANALISIS_H
#define ANALISIS_H

using namespace std;
#include <string>

class Analisis {
private:
  string tipo_analisis;
  string objeto;
  string comentario;

public:
  Analisis(string x, string y, string z) {
    tipo_analisis = x;
    objeto = y;
    comentario = z;
  }

  string getTipoAnalisis() const { return tipo_analisis; }
  string getObjeto() const { return objeto; }
  string getComentario() const { return comentario; }
  void setTipoAnalisis(string x) { tipo_analisis = x; }
  void setObjeto(string x) { objeto = x; }
  void setComentario(string x) { comentario = x; }
};

#endif
// ANALISIS_H