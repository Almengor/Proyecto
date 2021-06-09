#pragma once
#include <iostream>
#include <string>
#include "ConexionBD.h"
using namespace std;

class proveedores
{
private: string proveedor, nit, direccion;
	   int telefono = 0;
public:
	proveedores() {	}
	proveedores(string prov, string nt, string dir, int tel)
	{
		proveedor = prov;	nit = nt;	direccion = dir;	telefono = tel;
	}

	void setproveedor(string prov) { proveedor = prov; }
	void setnit(string nt) { nit = nt; }
	void setdireccion(string dir) { direccion = dir; }
	void settelefono(int tel) { telefono = tel; }

	string getproveedor() { return proveedor; }
	string getnit() { return nit; }
	string getdireccion() { return direccion; }
	int gettelefono() { return telefono; }

	/**********************************************************************************/

	void insert_proveedores() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();
		string t = to_string(telefono);
		if (cn.getConectar()) {
			string  insertar = "INSERT INTO proveedores(proveedor, nit, direccion, telefono) VALUES ('" + proveedor + "','" + nit + "','" + direccion + "','" + t + "')";
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Ingreso Exitoso ..." << endl;
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

	void leer_proveedores()
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {

			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "	|		    	             Listado de Proveedores	   	                   |" << endl;
			cout << "	|			         SUPERMERCADO 'ANTIGUA COLONIAL'	            	   |" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "\n" << endl;
			string consulta = "select * from proveedores ";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "	---------------------------------------------------------------------------------------------" << endl;
					cout << fila[0] << ".	Proveedor: " << fila[1] << "                   NIT: " << fila[2] << "    " << endl;
					cout <<"	Direccion:  " << fila[3] << "             Telefono: " << fila[4] << "   " << endl;
					cout << "	---------------------------------------------------------------------------------------------" << endl;
					cout << "\n" << endl;
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

	void consultar_proveedor(string nitproveedor)
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			/*cout << "\n" << endl;
			cout << "\n" << endl;*/
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "	|			             DATOS DE PROVEEDORES	          	           |" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			string consulta = "select pr.idproveedores, pr.proveedor, pr.nit, pr.direccion, pr.telefono from proveedores as pr where pr.nit = '" + nitproveedor + "';";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "	--------------------------------------------------------------------------------------------" << endl;
					cout << "	Id proveedor: " << fila[0] << "   | Proveedor: " << fila[1] << " | NIT: " << fila[2] << endl;
					cout << "	Direccion: " << fila[3] << " | Telefono: " << fila[4] << endl;
					cout << "	--------------------------------------------------------------------------------------------" << endl;
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


	string consultar_proveedorid(string nitproveedor)
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string idproveedor = "";
		if (cn.getConectar()) {
			cout << "\n" << endl;
			string consulta = "select pr.idproveedores, pr.proveedor, pr.nit, pr.direccion, pr.telefono from proveedores as pr where pr.nit = '" + nitproveedor + "';";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					idproveedor = fila[0];
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
		return idproveedor;
	}

	/**********************************************************************************/

	int datos_modificar()
	{
		int opcion3;

		system("cls");
		cout << "-------------------- LISTADO DE DATOS DE LA TABLA PROVEEDORES --------------------" << endl;
		cout << "1. Proveedor" << endl;
		cout << "2. NIT" << endl;
		cout << "3. Direccion" << endl;
		cout << "4. Telefono" << endl;
		cout << "\tQue elemento desea modificar: ";
		cin >> opcion3;
		cin.ignore();
		return opcion3;
	}


	void update_proveedores(int opcion2, int id_prov)
	{
		int q_estado;
		string id_pro = to_string(id_prov);
		string tel = to_string(telefono);
		string consulta;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar())
		{

			switch (opcion2)
			{
			case 1:
				consulta = "update proveedores set proveedor='" + proveedor + "' where idproveedores=" + id_pro;
				break;
			case 2:
				consulta = "update proveedores set nit='" + nit + "' where idproveedores=" + id_pro;
				break;
			case 3:
				consulta = "update proveedores set direccion='" + direccion + "' where idproveedores=" + id_pro;
				break;
			case 4:
				consulta = "update proveedores set telefono='" + tel + "' where idproveedores=" + id_pro;
				break;
			}

			const char* i = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado)
			{
				cout << "Modificacion exitosa" << endl;
			}
			else
			{
				cout << "Error al modificar" << endl;
			}
		}
		cn.cerrar_conexion();
	}

	/**********************************************************************************/

	void eliminar_proveedores(int id_prov)
	{
		string id_pro = to_string(id_prov);
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string  insertar = "delete from proveedores where idproveedores= " + id_pro;
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Se ha eliminado proveer exitosamente" << endl;
			}
			else {
				cout << "Error al eliminar" << endl;
			}
		}
		else {
			cout << " xxx Error en la Conexion xxxx" << endl;
		}
		cn.cerrar_conexion();
	}
};
