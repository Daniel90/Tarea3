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
     float A[1000][50];
     
     int cont=0;
     float sum=0;
     float prof=0;
     float curs=0;
     int chip=1;

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
                    
                    value = atof(PQgetvalue(result,i,j));
                    A[i][j]=value;
                    //cout << PQgetvalue(result,i,j) << " | "<<i<< " | "<<j<< " | ";
                    //system("PAUSE");
                    //system("CLS");
                                
                }
                cout << endl;
            }
            for (i=0; i<tuplas; i++) {
                for (int j=0; j<campos; j++) {
                    
                    cout << A[i][j] << " | ";
                                                   
                }
                cout << endl;
            }
            
            system("PAUSE");
            
            for (i=0; i<tuplas; i++) {
                for (int j=0; j<campos; j++) {
                    
                    if(j=0)
                    {      if(A[i][0]==A[i-1][0])
                           {        cont++;
                                    sum=sum+A[i][2];
                                    prof=A[i][1];
                                    curs=A[i][0];
                           }
                           else
                           {        cout<<"Curso: "<<curs<<" Profesor: "<<prof<<" Promedio: "<<sum/cont<<endl;
                                    system("PAUSE");
                                    chip=1;
                                    cont=0;
                                    sum=0;
                           }
                           if(chip==1)
                           {        cont++;
                                    sum=sum+A[i][2];
                                    prof=A[i][1];
                                    curs=A[i][0];
                                    chip=0;
                           }
                           
                    }
                                                   
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
