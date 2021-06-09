#pragma once
#include "persona.h"
#include <iostream>
#include "ConexionBD.h"
#include <string>
using namespace std;

class clientes : persona
{
private: string nit, correo_electronico;
public:
	clientes()
	{
	}
	clientes(string nom, string ape, string nt, string gen, int tel, string correo, string fein) : persona(nom, ape, fein, tel, gen)
	{
		nit = nt;   correo_electronico = correo;
	}

	void setnombres(string nom) { nombres = nom; }
	void setapellidos(string ape) { apellidos = ape; }
	void setnit(string nt) { nit = nt; }
	void setgenero(string gen) { genero = gen; }
	void settelefono(int tel) { telefono = tel; }
	void setcorreo_electronico(string correo) { correo_electronico = correo; }
	void setfechaingreso(string fein) { fechaingreso = fein; }


	string getnombres() { return nombres; }
	string getapellidos() { return apellidos; }
	string getnit() { return nit; }
	string getgenero() { return genero; }
	int gettelefono() { return telefono; }
	string gercorreo_electronico() { return correo_electronico; }
	string getfechaingreso() { return fechaingreso; }

	/**********************************************************************************/

	void insert_clientes() {
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();
		string t = to_string(telefono);
		//string g = genero;
		if (cn.getConectar()) {
			string  insertar = "INSERT INTO clientes(nombres, apellidos, nit, genero, telefono, correo_electronico, fechaingreso) VALUES ('" + nombres + "','" + apellidos + "','" + nit + "','" + genero + "','" + t + "','" + correo_electronico + "','" + fechaingreso + "')";
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Cliente ingresado exitosamente" << endl;
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

	void leer_clientes()
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "	|		    	              Listado de Clientes	   	                   |" << endl;
			cout << "	|			         SUPERMERCADO 'ANTIGUA COLONIAL'	            	   |" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "\n" << endl;
			string consulta = "select * from clientes ";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "	--------------------------------------------------------------------------------------------" << endl;
					cout << "	" << fila[0] << ".|  Nombres: " << fila[1] << " " << fila[2] << "     |     NIT:  " << fila[3] << "    |    Genero: " << fila[4] << endl;
					cout <<"	Telefono: "<<fila[5] << " | Correo electronico: " << fila[6] << " | Fecha de ingreso:  " << fila[7]  << endl;
					cout << "	--------------------------------------------------------------------------------------------" << endl;
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

	void consultar_cliente(string nitcliente)
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "	|			                 DATOS DE CLIENTE		         	       |" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			string consulta = "select c.idcliente, c.nombreS, c.apellidos, c.nit, c.genero, c.telefono, c.correo_electronico, c.fechaingreso from clientes as c where c.nit = '" + nitcliente + "';";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "	--------------------------------------------------------------------------------------------" << endl;
					cout << "	Id cliente: " << fila[0] << "   | Nombre: " << fila[1] << " " << fila[2] << "        | NIT: " << fila[3] << "     | Genero: " << fila[4] << endl; 
					cout << "	Telefono:  " << fila[5] << "           | Correo electronico: " << fila[6] << endl;
					cout <<	"	Fecha de ingreso: " << fila[7] << endl;
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

	string consultar_clienteid(string nitcliente)
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string idproveedor = "";
		if (cn.getConectar()) {
			cout << "\n" << endl;
			string consulta = "select c.idcliente, c.nombreS, c.apellidos, c.nit, c.genero, c.telefono, c.correo_electronico, c.fechaingreso from clientes as c where c.nit = '" + nitcliente + "';";
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
		cout << "-------------------- LISTADO DE DATOS DE LA TABLA Clientes --------------------" << endl;
		cout << "1. Nombres" << endl;
		cout << "2. Apellidos" << endl;
		cout << "3. NIT" << endl;
		cout << "4. Genero" << endl;
		cout << "5. Telefono" << endl;
		cout << "6. Correo Electronico" << endl;
		/*cout << "7. Fecha ingreso" << endl << endl;*/
		cout << "\tQue elemento desea modificar: ";
		cin >> opcion3;
		cin.ignore();
		return opcion3;
	}

	void update_clientes(int opcion2, int id_cli)
	{
		int q_estado;
		string id_c = to_string(id_cli);
		string tel = to_string(telefono);
		//string gen = to_string(genero);
		string consulta;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar())
		{

			switch (opcion2)
			{
			case 1:
				consulta = "update clientes set nombres='" + nombres + "' where idcliente=" + id_c;
				break;
			case 2:
				consulta = "update clientes set apellidos='" + apellidos + "' where idcliente=" + id_c;
				break;
			case 3:
				consulta = "update clientes set nit='" + nit + "' where idcliente=" + id_c;
				break;
			case 4:
				consulta = "update clientes set genero='" + genero + "' where idcliente=" + id_c;
				break;
			case 5:
				consulta = "update clientes set telefono= '" + tel + "' where idcliente=" + id_c;
				break;
			case 6:
				consulta = "update clientes set correo_electronico='" + correo_electronico + "' where idcliente=" + id_c;
				break;
			case 7:
				/*consulta = "update clientes set fechaingreso='" + fechaingreso + "' where idcliente=" + id_c;*/
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
				cout << "Error al intentar modificar registro" << endl;
			}
		}
		cn.cerrar_conexion();
	}

	/**********************************************************************************/
	void eliminar_clientes(int id_cli)
	{
		string id_c = to_string(id_cli);
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string  insertar = "delete from clientes where idcliente= " + id_c;
			const char* i = insertar.c_str();
			// executar el query
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "El registro se ha modificado con exito." << endl;
			}
			else {
				cout << "Error al intentar modificar" << endl;
			}
		}
		else {
			cout << " xxx Error en la Conexion xxxx" << endl;
		}
		cn.cerrar_conexion();
	}

};


