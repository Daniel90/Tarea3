#include <cstdlib>
#include <iostream>
#include <libpq-fe.h>
using namespace std;

PGconn *cnn = NULL;
PGresult *result = NULL, *result2 = NULL;

char *host = "localhost";
char *port = "5432";
char *dataBase = "transaction";
char *user = "postgres";
char *passwd = "root";

int main(int argc, char *argv[])
{
     int i;

     cnn = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);

    if (PQstatus(cnn) != CONNECTION_BAD) {
        cout << "Coneccion exitosa!" << endl;
        //result = PQexec(cnn, "SELECT AVG(nota) from asignaturas_cursadas");
        result = PQexec(cnn, "SELECT sqrt((sum(power((nota-(select avg(nota) from asignaturas_cursadas)),2)))/(select count(nota)-1 from asignaturas_cursadas)) from asignaturas_cursadas");
        result2 = PQexec(cnn, "SELECT AVG(nota) from asignaturas_cursadas");
        if (result != NULL) {
            int tuplas = PQntuples(result);
            int campos = PQnfields(result);
            cout << "No. Filas:" << tuplas << endl;
            cout << "No. Campos:" << campos << endl;

            cout << "Los nombres de los campos son:" << endl;

            for (i=0; i<campos; i++) {
                cout << PQfname(result,i) << " | ";
            }

            cout << endl << "La desviacion estandar de notas fue" << endl;
            
            for (i=0; i<tuplas; i++) 
            {
                for (int j=0; j<campos; j++) 
                {
                    
                    cout << PQgetvalue(result,i,j) << " | ";
                    
                }
                cout << endl;
            }
            
            cout << endl << "El promedio de notas fue" << endl;
            for (i=0; i<tuplas; i++) 
            {
                for (int j=0; j<campos; j++) 
                {
                    
                    cout << PQgetvalue(result2,i,j) << " | ";
                    
                }
                cout << endl;
            }
            
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
