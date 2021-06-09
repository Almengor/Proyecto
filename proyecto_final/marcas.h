#pragma once
#include <iostream>
#include "ConexionBD.h"
#include <string>
using namespace std;

class marcas
{
private: string marca;
public:
	marcas() {	}
	marcas(string mar)
	{
		marca = mar;
	}
	void setmarca(string mar) { marca = mar; }
	string getmarca() { return marca; }


	void insert_marcas() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();
		if (cn.getConectar()) {
			string  insertar = "INSERT INTO marcas(marca) VALUES ('" + marca + "')";
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Marca ingresada Exitosamente" << endl;
			}
			else {
				cout << " xxx Error al Ingresar  xxx" << endl;
			}
		}
		else {
			cout << " xxx Error en la Conexion xxxx" << endl;
		}
		cn.cerrar_conexion();
	}

	/**********************************************************************************/

	void leer_marcas()
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "	|		    	              Listado de Marcas 	   	                   |" << endl;
			cout << "	|			         SUPERMERCADO 'ANTIGUA COLONIAL'	            	   |" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "\n" << endl;
			string consulta = "select * from marcas";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << ". " << fila[1] << endl << endl;
				}
			}
			else {
				cout << " xxx Error al Consultar  xxx" << endl;
			}

		}
		else {
			cout << " xxx Error en la Conexion xxxx" << endl;
		}
		cn.cerrar_conexion();
	}

	/**********************************************************************************/

	void update_marcas(int id_mar)
	{
		string id_m = to_string(id_mar);
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();

		if (cn.getConectar())
		{
			string update = "update marcas set marca= '" + marca + "' where idmarcas= " + id_m;
			const char* i = update.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado)
			{
				cout << "Registro actualizado exitosamente" << endl;
			}
			else
			{
				cout << "error en el intentar actualizar" << endl;
			}
		}
		else {
			cout << " xxx Error en la Conexion xxxx" << endl;
		}
		cn.cerrar_conexion();
	}

	/**********************************************************************************/

	void eliminar_marcas(int id_mar)
	{
		string id_m = to_string(id_mar);
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string  insertar = "delete from marcas where idmarcas= " + id_m;
			const char* i = insertar.c_str();
			// executar el query
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Marca eliminada con exito" << endl;
			}
			else {
				cout << " Error al eliminar registro" << endl;
			}
		}
		else {
			cout << " xxx Error en la Conexion xxxx" << endl;
		}
		cn.cerrar_conexion();
	}
};


