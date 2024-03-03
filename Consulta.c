//programa en C para consultar los datos de la base de datos
//Incluir esta libreria para poder hacer las llamadas en shiva2.upc.es
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
MYSQL *conn;
int err;
// Estructura especial para almacenar resultados de consultas
MYSQL_RES *resultado;
MYSQL_ROW row;
int ID;
char JUGADOR[10];
char consulta [80];
//Creamos una conexion al servidor MYSQL
conn = mysql_init(NULL);
if (conn==NULL) {
printf ("Error al crear la conexion: %u %s\n",
mysql_errno(conn), mysql_error(conn));
exit (1);
}
//(conn, "localhost","user", "pass", "JUEGO",0, NULL, 0);
//inicializar la conexion
conn = mysql_real_connect (conn, "localhost","root", "mysql", NULL, 0, NULL, 0);
if (conn==NULL) {
printf ("Error al inicializar la conexion: %u %s\n",
mysql_errno(conn), mysql_error(conn));
exit (1);
}
// consulta SQL para obtener una tabla con todos los datos
// de la base de datos
err=mysql_query (conn, "SELECT * FROM JUEGO");
if (err!=0) {
printf ("Error al consultar datos de la base %u %s\n",
mysql_errno(conn), mysql_error(conn));
exit (1);
}
//recogemos el resultado de la consulta. El resultado de la
//consulta se devuelve en una variable del tipo puntero a
//MYSQL_RES tal y como hemos declarado anteriormente.
//Se trata de una tabla virtual en memoria que es la copia
//de la tabla real en disco.
resultado = mysql_store_result (conn);
// El resultado es una estructura matricial en memoria
// en la que cada fila contiene los datos de una persona.
// Ahora obtenemos la primera fila que se almacena en una
// variable de tipo MYSQL_ROW
row = mysql_fetch_row (resultado);
// En una fila hay tantas columnas como datos tiene una
// persona. En nuestro caso hay tres columnas: JUGADOR(row[0]),
// nombre(row[1]) y ID (row[2]).
if (row == NULL)
printf ("No se han obtenido datos en la consulta\n");
else
while (row !=NULL) {
// la columna 2 contiene una palabra que es la ID
// la convertimos a entero
ID = atoi (row[2]);
// las columnas 0 y 1 contienen JUGADOR y nombre
printf ("JUGADOR: %s\n", row[0], ID);
// obtenemos la siguiente fila
row = mysql_fetch_row (resultado);
}
// Ahora vamos a buscar el nombsre de la persona cuyo JUGADOR es uno
// dado por el usuario
printf ("Dame el nombre del jugador que quieres buscar\n");
scanf ("%s", JUGADOR);
// construimos la consulta SQL
strcpy (consulta,"SELECT nombre FROM JUEGO WHERE JUGADOR = '");
strcat (consulta, JUGADOR);
strcat (consulta,"'");
// hacemos la consulta
err=mysql_query (conn, consulta);
if (err!=0) {
printf ("Error al consultar datos de la base %u %s\n",
mysql_errno(conn), mysql_error(conn));
exit (1);
}
//recogemos el resultado de la consulta
resultado = mysql_store_result (conn);
row = mysql_fetch_row (resultado);
if (row == NULL)
printf ("No se han obtenido datos en la consulta\n");
else
// El resultado debe ser una matriz con una sola fila
// y una columna que contiene el nombre
printf ("Nombre del jugador: %s\n", row[0] );
// cerrar la conexion con el servidor MYSQL
mysql_close (conn);
exit(0);
}