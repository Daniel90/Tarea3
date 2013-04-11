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

int main(int argc, char * argv[])
{
    int i;
    cnn = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);
    if (PQstatus(cnn) != CONNECTION_BAD) {
        cout << "Estamos conectados a PostgreSQL!" << endl;
        result = PQexec(cnn, "select c.curso_id, avg(a.nota) as Promedio,c.docente_id from asignaturas_cursadas as a,cursos as c where c.curso_id = a.curso_id group by c.curso_id");
        if (result != NULL) {
            int tuplas = PQntuples(result);
            int campos = PQnfields(result);
            cout << "No. Filas:" << tuplas << endl;
            cout << "No. Campos:" << campos << endl<<endl;
            cout << "Los nombres de los campos son:" << endl;
            for (i=0; i<campos; i++) {
                cout << PQfname(result,i) << " | ";
            }
            cout << endl<<endl;
            
            cout<<"Contenido de la tabla" << endl;
            for (i=0; i<campos; i++) {
                cout << PQfname(result,i) << "       |       ";
            }
            cout<<endl;
            for (i=0; i<tuplas; i++) {
                for (int j=0; j<campos; j++) {
                    cout << PQgetvalue(result,i,j) << "       |       ";
                }
                cout << endl;
            }
        }
        // Ahora nos toca liberar la memoria
        PQclear(result);
    } else {
        cout << "Error de conexion" << endl;
        return 0;
    }
    PQfinish(cnn);
  system("PAUSE");
    return EXIT_SUCCESS;
}
