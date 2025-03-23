// Andrés Felipe Marroquin
// José Tomás Suárez Acero
// Juan Nicolás Avella
// Santiago Nicolas Ceron Dimate

#include "funciones.h"
#include <ctype.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

  Vehiculo curiosity(0, 0, 0);
  vector<Movimiento> movimiento;
  vector<Analisis> analisis;
  vector<Elemento> elementos;
  Quad q(Point(0, 0), Point(100, 100));
  Grafo grafo;
  int flag;

  string userin;
  cout << " _________________" << endl;
  cout << "|                 |" << endl;
  cout << "| CURIOSITY       |" << endl;
  cout << "| NASA's EXPLORER |" << endl;
  cout << "|_________________| " << endl << endl;
  cout << "Bienvenido al sistema del vehiculo Curiosity" << endl;
  cout << "\nEscriba ayuda para ver una lista de los comandos" << endl;
  cout << "\nEscriba salir para salir del programa" << endl;

  do {

    cout << "\ningrese un comando:  " << endl << "$";
    getline(cin, userin);
    cout << endl;

    vector<string> comando;
    string palabraAux;
    for (int i = 0; i < userin.length(); i++) {
      if (userin[i] == ' ') {
        comando.push_back(palabraAux);
        palabraAux = "";
      } else {
        palabraAux += userin[i];
      }
    }
    comando.push_back(palabraAux);

    if (comando[0].rfind("cargar_comandos", 0) == 0) {
      if (comando.size() != 2) {
        cout << "cantidad de parametros incorrecta" << endl;
      } else {
        cout << "cargando comandos del archivo: " << comando[1] << endl;
        cargar_comandos(comando[1] + ".txt", &movimiento, &analisis);
      }
    }

    else if (comando[0].rfind("cargar_elementos", 0) == 0) {
      if (comando.size() != 2) {
        cout << "cantidad de parametros incorrecta" << endl;
      } else {
        cout << "cargando comandos del archivo: " << comando[1] << endl;
        cargar_elementos(comando[1] + ".txt", &elementos);
      }
    }

    else if (comando[0].rfind("agregar_movimiento", 0) == 0) {

      if (comando.size() != 4) {
        cout << "cantidad de parametros incorrecta" << endl;
      } else if ((comando[1] != "girar" && comando[1] != "avanzar") ||
                 (comando[3] != "grd" && comando[3] != "rad" &&
                  comando[3] != "cm" && comando[3] != "m" &&
                  comando[3] != "km"))

      {
        cout << "La información del movimiento no tiene los datos esperados "
                "(tipo movimiento (avanzar, girar), magnitud, unidad de "
                "medida "
                "(grd, rad))."
             << endl;
      } else {
        cout << "agregando movimiento de tipo " << comando[1]
             << " con magnitud de " << comando[2]
             << " usado de unidad de medida " << comando[3] << endl;

        agregar_movimiento(comando[1], stod(comando[2]), comando[3],
                           &movimiento);
      }
    }

    else if (comando[0].rfind("agregar_analisis", 0) == 0) {
      if ((comando[1] != "fotografiar" && comando[1] != "composicion" &&
           comando[1] != "perforar") ||
          (comando[2] != "roca" && comando[2] != "crater" &&
           comando[2] != "monticulo" && comando[2] != "duna")) {
        cout << "La información del analisis no tiene los datos esperados "
                "(tipo analisis (fotografiar, composicion, perforar), objeto "
                "(roca, crater, monticulo, duna), comantario)."
             << endl;
      } else {
        for (int i = 4; i < comando.size(); i++) {
          comando[3] = comando[3] + " " + comando[i];
        }
        comando[3] = "'" + comando[3] + "'";
        agregar_analisis(comando[1], comando[2], comando[3], &analisis);
        cout << "agregando anlisis de tipo " << comando[1] << " al objeto "
             << comando[2] << " (comentario: " << comando[3] << ")" << endl;
      }
    }

    else if (comando[0].rfind("agregar_elemento", 0) == 0) {
      if (comando.size() != 6) {
        cout << "cantidad de parametros incorrecta" << endl;
      } else if ((comando[1] != "roca" && comando[1] != "crater" &&
                  comando[1] != "monticulo" && comando[1] != "duna") ||
                 (comando[3] != "cm" && comando[3] != "m" &&
                  comando[3] != "km")) {
        cout << "La información del elemnto no tiene los datos esperados (tipo "
                "elemento (roca, crater, monticulo, duna), tamaño, unidad de "
                "medida (cm, m, km), cordenada en x, cordenada en y)."
             << endl;
      } else {
        agregar_elemento(comando[1], stod(comando[2]), comando[3],
                         stod(comando[4]), stod(comando[5]), &elementos);
        cout << "agregando elemnto de tipo " << comando[1]
             << " con un tamaño de " << comando[2]
             << " usando una unidad de medida de " << comando[3]
             << " en las cordenadas x:" << comando[4] << " y: " << comando[5]
             << endl;
      }
    }

    else if (comando[0].rfind("guardar", 0) == 0) {
      if (comando.size() != 3) {
        cout << "cantidad de parametros incorrecta" << endl;
      } else if (comando[1] != "comandos" && comando[1] != "elementos") {
        cout << "debe ingresar un tipo entre (comandos, elementos)" << endl;
      } else {
        if (comando[1] == "comandos" && movimiento.empty() &&
            analisis.empty()) {
          cout << "La información requerida no está almacenada en memoria"
               << endl;
        } else {
          guardar(comando[1], comando[2], movimiento, analisis, elementos);
          cout << "guardadonde archivo de tipo: " << comando[1]
               << " como: " << comando[2] << ".txt" << endl;
        }
      }
    }

    else if (comando[0].rfind("simular_comandos", 0) == 0) {
      if (comando.size() != 3) {
        cout << "cantidad de parametros incorrecta" << endl;
      } else {
        cout << "simulando comandos en cordenadas x: " << comando[1]
             << " y: " << comando[2] << endl;
        simular_comandos(stod(comando[1]), stod(comando[2]), &curiosity,
                         &movimiento);
      }
    }

    else if (comando[0].rfind("ubicar_elementos", 0) == 0) {
      if (comando.size() != 1) {
        cout << "cantidad de parametros incorrecta" << endl;
      } else {

        cout << "ubicando elementos" << endl;
        ubicar_elementos(&elementos, q);
      }
    }

    else if (comando[0].rfind("en_cuadrante", 0) == 0) {
      if (comando.size() != 5) {
        cout << "cantidad de parametros incorrecta" << endl;
      } else {
        cout << "el cuadrante va desde las cordenadas x: " << comando[1]
             << " y: " << comando[3]
             << " hasta las cordenadas x: " << comando[2]
             << " y: " << comando[4] << endl;

        en_cuadrante(stod(comando[1]), stod(comando[2]), stod(comando[3]),
                     stod(comando[4]), &elementos, q);
      }
    }

    else if (comando[0].rfind("crear_mapa", 0) == 0) {
      if (comando.size() != 2) {
        cout << "cantidad de parametros incorrecta" << endl;
      } else {
        cout << "creando mapa con coeficiente de conectividad de: "
             << comando[1] << endl;

        grafo = crear_mapa(stod(comando[1]), grafo, &elementos);
      }
    }

    else if (comando[0].rfind("ruta_mas_larga", 0) == 0) {
      if (comando.size() != 1) {
        cout << "cantidad de parametros incorrecta" << endl;
      } else {
        cout << "buscando ruta mas larga" << endl;

        ruta_mas_larga(grafo);
      }
    }

    ///////////COMANDOS DE AYUDA////////////////////////

    else if (comando[0] == "ayuda" && comando.size() != 1) {
      if ((comando[0].rfind("ayuda", 0) == 0) &&
          (comando[1].rfind("cargar_comandos", 0) == 0)) {
        cout << "\tcargar_comandos nombre_archivo" << endl;
        cout << "\n\tej:  cargar_comandos comandos" << endl;
        cout << "\n\tCarga los comandos de un archivo de texto." << endl;
      } else if (comando[1].rfind("cargar_elementos", 0) == 0) {
        cout << "\tcargar_elementos nombre_archivo" << endl;
        cout << "\n\tej:  cargar_elementos elementos" << endl;
        cout << "\n\tCarga los elementos de un archivo de texto." << endl;
      } else if (comando[1].rfind("agregar_movimiento", 0) == 0) {
        cout << "\tagregar_movimiento tipo_mov magnitud unidad_med" << endl;
        cout << "\n\tej; agregar_movimiento avanzar 20 m" << endl;
        cout << "\n\tAgrega un comando de movimiento a la lista de comandos "
                "del vehículo, los tipos de movimiento pueden ser girar o "
                "avanzar, la magnitud debe ser un número y las unidades de "
                "medida son cm, m y km."
             << endl;
      } else if (comando[1].rfind("agregar_analisis", 0) == 0) {
        cout << "\tagregar_analisis tipo_analisis objeto comentario" << endl;
        cout << "\n\tej; agregar_analisis fotografiar colinas ’sistema de "
                "montañas’"
             << endl;
        cout << "\n\tagrega un analiss donde el tipo puede ser desde "
                "(fotografiar, composicion, perforar) a un objeto de los que "
                "los disponibles son (roca, crater, monticulo, duna) y por "
                "ultimo un comentario el cual es de libre texto a agregar"
             << endl;
      } else if (comando[1].rfind("agregar_elemento", 0) == 0) {
        cout << "\tagregar_elemento tipo_comp tamaño unidad_med coordX coordY"
             << endl;
        cout << "\n\tej; agregar_elemento roca 13 cm 3.45 15.4’" << endl;
        cout << "\n\tagrega un elemento donde el objeto puede ser desde (roca, "
                "crater, monticulo, duna) tamaño es un numero de cuanto va a "
                "medir luego unidad de medida que puede ser cm, m o km y por "
                "ultimo dos valores mas que son las cordenadas en X y en Y"
             << endl;
      } else if (comando[1].rfind("guardar", 0) == 0) {
        cout << "\tguardar tipo_archivo nombre_archivo" << endl;
        cout << "\n\tej; guardar elementos ejemploarchivo" << endl;
        cout << "\n\tguarda los elmentos analisis y movimientos en sus "
                "respectivos archivos dependiendo el tipo de archivo que se "
                "elija si se elige elementos guaradara todos los elementos ahi "
                "mismo y si se elige comandos guaradara ahi los movimientos y "
                "los analisis y or ultimo se agrega el nombre del archivo en "
                "el que se va a guardar todo"
             << endl;
      } else if (comando[1].rfind("simular_comandos", 0) == 0) {
        cout << "\tsimular_comandos coordX coordY" << endl;
        cout << "\n\tej; simular_comandos 12.5 13.6" << endl;
        cout << "\n\tSimula el movimiento del vehículo utilizando los comandos "
                "de movimiento guardados y actualiza la posición del "
                "curiosity. Para esto recibe como parámetros la posición "
                "inicial del curiosity (coordX, coordY)"
             << endl;
      } else if (comando[1].rfind("ubicar_elementos", 0) == 0) {
        cout << "\tubicar_elementos" << endl;
        cout << "\n\tej; ubicar_elementos" << endl;
        cout << "\n\tCarga los elemntos desde que estan almacenados para "
                "ubicarlos de forma que su busqueda sea mas rapida"
             << endl;
      } else if (comando[1].rfind("en_cuadrante", 0) == 0) {
        cout << "\ten_cuadrante coordX1 coordX2 coordY1 coordY2" << endl;
        cout << "\n\tej; en_cuadrante 0 10 0 10" << endl;
        cout << "\n\tManda una lista de los objetos encontrados entre las dos "
                "cordenadas entregadas como un cuadrante"
             << endl;
      } else if (comando[1].rfind("crear_mapa", 0) == 0) {
        cout << "\tcrear_mapa coeficiente_conectividad" << endl;
        cout << "\n\tej; crear_mapa 0.4" << endl;
        cout << "\n\tcrea la conectividad entre puntos de interes tomando en "
                "cuenta un coeficioente de conectividad para determinar la "
                "cantidad de vecinos que puede tener"
             << endl;
      } else if (comando[1].rfind("ruta_mas_larga", 0) == 0) {
        cout << "\truta_mas_larga" << endl;
        cout << "\n\tej; ruta_mas_larga" << endl;
        cout << "\n\tSe encarga de buscar los dos componentes mas alejados "
                "entre si mostrandolos de forma de saber cual seria el camino "
                "mas largo que el robot puede llegar a tomar"
             << endl;
      } else {
        cout << "Comando invalido escriba 'ayuda' para ver la lista de comandos"
             << endl;
      }
    }

    //////////// TODOS LOS COMANDOS DE AYUDA ///////////////

    else if (comando[0].rfind("ayuda", 0) == 0) {
      cout << "--COMANDOS--" << endl;
      cout << "\tcargar_comandos" << endl;
      cout << "\tcargar_elementos" << endl;
      cout << "\tagregar_movimiento" << endl;
      cout << "\tagregar_analisis" << endl;
      cout << "\tagregar_elemento" << endl;
      cout << "\tguardar tipo_archivo" << endl;
      cout << "\tsimular_comandos" << endl;
      cout << "\tubicar_elementos" << endl;
      cout << "\ten_cuadrante" << endl;
      cout << "\tcrear_mapa" << endl;
      cout << "\truta_mas_larga" << endl;
      cout << "\tsalir" << endl;
      cout << "\nescriba la palabra 'ayuda' seguida de un comando para ver "
              "informacion mas especifica"
           << endl;
      cout << "\tej: ayuda cargar_comandos" << endl;
    }

    // SALIDA

    else if (comando[0].rfind("salir", 0) == 0) {
      break;
    }

    // COMANDO FUERA DE LAS BASES

    else {
      cout << "Comando invalido escriba 'ayuda' para ver la lista de comandos"
           << endl;
    }
  } while (true);
  return 0;
}
