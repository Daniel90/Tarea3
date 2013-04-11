#include <cstdlib>
#include <iostream>
#include <libpq-fe.h>
using namespace std;

PGconn *cnn = NULL;
PGresult *result1 = NULL, *result2 = NULL;

char *host = "localhost";
char *port = "5432";
char *dataBase = "tarea";
char *user = "postgres";
char *passwd = "root";

int main(int argc, char *argv[])
{
     int i;
     float Promedio=0;
     float DesvEst=0;
     float Suma=0;
     float value=0;
     float A[100][100];

     cnn = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);

    if (PQstatus(cnn) != CONNECTION_BAD) {
        cout << "Coneccion exitosa!" << endl;
        //result = PQexec(cnn, "SELECT AVG(nota) from asignaturas_cursadas");
        result = PQexec(cnn, "SELECT c.curso_id,c.docente_id,a.nota FROM cursos as c,asignaturas_cursadas as a where c.curso_id = a.curso_id");
        
        if (result != NULL) {
            int tuplas = PQntuples(result);
            int campos = PQnfields(result);
            cout << "No. Filas:" << tuplas << endl;
            cout << "No. Campos:" << campos << endl;

            cout << "Los nombres de los campos son:" << endl;

            for (i=0; i<campos; i++) {
                cout << PQfname(result,i) << " | ";
            }

            cout << endl << "Contenido de la tabla" << endl;
            //system("PAUSE");
            for (i=0; i<tuplas; i++) {
                for (int j=0; j<campos; j++) {
                    
                    //value = atof(PQgetvalue(result,i,j));
                    //Suma=Suma+value;
                    //cout << Suma << " | ";
                    cout << PQgetvalue(result,i,j) << " | "<<i<< " | "<<j<< " | ";
                    system("PAUSE");
                    system("CLS");
                    
                    
                    
                    
                    
                    
                    
                    
                }
                cout << endl;
            }
            //cout << endl << "PROMEDIO :" <<Suma/tuplas<< endl;
            
        }

        // Ahora nos toca liberar la memoria
        PQclear(result);
        PQclear(result2);

    } else {
        cout << "Error de conexion" << endl<<PQerrorMessage(cnn);
        
        
    }

    PQfinish(cnn);

  
    system("PAUSE");
    return EXIT_SUCCESS;
}
