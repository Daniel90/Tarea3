// Daniel Abrilot 
// Jhon Lopez
#include <cstdlib>
#include <iostream>
#include <libpq-fe.h>
using namespace std;

PGconn *cnn = NULL;
PGresult *result = NULL;

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
        cout << "Conexion exitosa!" << endl;
        cout << "host: "<<host<<endl<<"Puerto: "<<port<<endl<<"Base de datos: "<<dataBase<<endl<<"Usuario: "<<user<<endl<<"password: ****"<<endl;
        result = PQexec(cnn, "select c.curso_id, avg(a.nota) as Promedio,c.docente_id,sqrt((sum(power((nota-(select avg(a.nota) from asignaturas_cursadas as a)),2)))/(select count(a.nota)-1 from asignaturas_cursadas as a)) as Desv_Estandar from asignaturas_cursadas as a,cursos as c where c.curso_id = a.curso_id group by c.curso_id");
        if (result != NULL) {
            int tuplas = PQntuples(result);
            int campos = PQnfields(result);
            
            cout << "La informacion se muestra a continuacion:" << endl << endl;
            
            
            
            for (i=0; i<campos; i++) {
                cout << PQfname(result,i) << "          ";
            }
            cout<<endl<<endl;
            for (i=0; i<tuplas; i++) {
                for (int j=0; j<campos; j++) {
                    cout << PQgetvalue(result,i,j) << "         ";
                }
                cout << endl;
            }
        }
        
        PQclear(result);
    } else {
        cout << "Error de conexion" << endl;
       
    }
    PQfinish(cnn);
  system("PAUSE");
    return EXIT_SUCCESS;
}
