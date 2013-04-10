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

     cnn = PQsetdbLogin(host,port,NULL,NULL,dataBase,user,passwd);

    if (PQstatus(cnn) != CONNECTION_BAD) {
        cout << "Coneccion exitosa!" << endl;
        cout << "host: "<<host<<endl<<"Puerto: "<<port<<endl<<"Base de datos: "<<dataBase<<endl<<"Usuario: "<<user<<endl<<"password: ****"<<endl;
        //result = PQexec(cnn, "SELECT AVG(nota) from asignaturas_cursadas");
        result1 = PQexec(cnn, "Select docente_id as Codigo_Docente, avg(nota) as Promedio from cursos,asignaturas_cursadas where cursos.curso_id = asignaturas_cursadas.curso_id group by docente_id");
        result2 = PQexec(cnn,"Select docente_id as Codigo_Docente, sqrt((sum(power((nota-(select avg(nota) from asignaturas_cursadas)),2)))/(select count(nota)-1 from asignaturas_cursadas)) as Desv_Estandar from cursos,asignaturas_cursadas where cursos.curso_id = asignaturas_cursadas.curso_id group by docente_id");
        if (result1 != NULL) 
        {
            int tuplas = PQntuples(result1);
            int campos = PQnfields(result1);
           // cout << "No. Filas:" << tuplas << endl;
           // cout << "No. Campos:" << campos << endl;

            cout << endl <<"Promedio de notas por profesores:" << endl<<endl;

            for (i=0; i<campos; i++) {
                cout <<PQfname(result1,i) << "                   ";
            }
            cout<<endl;  
            for (i=0; i<tuplas; i++) 
            {
                for (int j=0; j<campos; j++) 
                {
                    
                    cout <<"      "<<PQgetvalue(result1,i,j)<<"            |";
                    
                }
                cout << endl;
            }
            
        }
        
        if (result2 != NULL) 
        {
            int tuplas = PQntuples(result2);
            int campos = PQnfields(result2);
           // cout << "No. Filas:" << tuplas << endl;
           // cout << "No. Campos:" << campos << endl;

            cout << endl <<"La desviacion estandar por profesores fue:" << endl<<endl;

            for (i=0; i<campos; i++) {
                cout <<PQfname(result2,i) << "                  ";
            }
            cout<<endl;  
            for (i=0; i<tuplas; i++) 
            {
                for (int j=0; j<campos; j++) 
                {
                    
                    cout <<"      "<<PQgetvalue(result2,i,j) << "          |  ";
                    
                }
                cout << endl;
            }
            
        }

        // Ahora nos toca liberar la memoria
        PQclear(result1);
        PQclear(result2);

    } else {
        cout << "Error de conexion" << endl<<PQerrorMessage(cnn);
        
        
    }

    PQfinish(cnn);

  
    system("PAUSE");
    return EXIT_SUCCESS;
}
