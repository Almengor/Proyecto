#pragma once
#include <iostream>
#include <mysql.h>
#include <iostream>
#include "ConexionBD.h"
#include <string>
#include <fstream>            
#include <stdlib.h> 

using namespace std;

class compras {
protected: string fecha_orden, fecha_ingreso, id_proveedor;
		 int no_orden_compra = 0;
		 //int id_proveedor = 0;
		 // constructor
public:
	compras() {
	}
	compras(int noc, string fo, string idpro, string ing) {

		no_orden_compra = noc;
		fecha_orden = fo;
		id_proveedor = idpro;
		fecha_ingreso = ing;
	}
	void setordencompra(int noc) { no_orden_compra = noc; }
	void setfecha_orden(string fo) { fecha_orden = fo; }
	void setid_proveedor(string idpro) { id_proveedor = idpro; }
	void setfecha_ingreso(string ing) { fecha_ingreso = ing; }

	// get(mostrar)
	int getordencompra() { return no_orden_compra; }
	string getfecha_orden() { return fecha_orden; }
	string getid_proveedor() { return id_proveedor; }
	string getfecha_ingreso() { return fecha_ingreso; }

	string asignar (int no_orden_compra) {

		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string nofac = to_string(no_orden_compra);
			string consulta = "select id_ventas from  ventas where no_factura values('" + nofac + "')";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "----------------------------Compra Detalle------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					return fila[0];
				}
			}
			else {

				cout << "xxxxx error de  consulta xxxx" << endl;
			}

		}
		else {

			cout << " xxxxx error en la conexion xxxxx";
		}

		cn.cerrar_conexion();

	}

	void insert_compras() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		string NOC = to_string(no_orden_compra);
		string IP = id_proveedor;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string insert = "insert into compras(no_orden_compra, idproveedor, fecha_orden, fechaingreso, totalcompra) VALUES (" + to_string(no_orden_compra) + ", " + id_proveedor + ",now(),now(),0);";
			// executar el query
			const char* h = insert.c_str();
			q_estado = mysql_query(cn.getConectar(), h);
			if (!q_estado) {
				cout << "Ingreso Exitoso ..." << endl;
			}
			else {
				cout << " xxx Error al Ingresar en venta  xxx" << endl;
			}
		}
		else {
			cout << " xxx Error en la Conexion xxxx" << endl;
		}

		cn.cerrar_conexion();
	}

	void leer_compras() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			cout << "\n" << endl;
			cout << "----------------------------COMPRAS------------------------" << endl;
			cout << "\n" << endl;
			string consulta = "select c.idcompras, c.no_orden_compra, c.idproveedor, p.proveedor, c.fecha_orden, c.fechaingreso, c.totalcompra from compras as c left outer join proveedores as p on c.idproveedor = p.idproveedores;";
			
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << "  |  " << fila[1] << "  |  " << fila[2] << "  |  " << fila[3] << "  |  " << fila[4] << "  |  " << fila[5] << "  |  " << fila[6] << endl;
				}

			}
			else {

				cout << "xxxxx error de  consulta xxxx" << endl;
			}
		}
		else {

			cout << " xxxxx error en la conexion xxxxx";
		}

		cn.cerrar_conexion();
	}

	void consulta_comprasnoorden(string noorden) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			cout << "\n" << endl;
			cout << "----------------------------COMPRAS------------------------" << endl;
			string str = "";
			str = "select c.idcompras, c.no_orden_compra, c.idproveedor, p.proveedor, c.fecha_orden, c.fechaingreso, c.totalcompra from compras as c left outer join proveedores as p on c.idproveedor = p.idproveedores where c.no_orden_compra =" + noorden;
			string consulta = str;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << "  |  " << fila[1] << "  |  " << fila[2] << "  |  " << fila[3] << "  |  " << fila[4] << "  |  " << fila[5] << "  |  " << fila[6] << endl;
				}

			}
			else {

				cout << "xxxxx error de  consulta xxxx" << endl;
			}
		}
		else {

			cout << " xxxxx error en la conexion xxxxx";
		}

		cn.cerrar_conexion();
	}

	string consulta_comprasid(string noorden) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string idcompra = "";
		if (cn.getConectar()) {
			
			string str = "";
			str = "select c.idcompras, c.no_orden_compra, c.idproveedor, p.proveedor, c.fecha_orden, c.fechaingreso, c.totalcompra from compras as c left outer join proveedores as p on c.idproveedor = p.idproveedores where c.no_orden_compra =" + noorden;
			string consulta = str;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					idcompra = fila[0];
				}
			}
			else {

				cout << "xxxxx error de  consulta xxxx" << endl;
			}
		}
		else {

			cout << " xxxxx error en la conexion xxxxx";
		}
		cn.cerrar_conexion();
		return idcompra;
	}

	void imprimir_compras(string noorden) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			cout << "\n" << endl;
			cout << "\n" << endl;
			cout << "\n" << endl;
			cout << "\n" << endl;
			cout << "----------------------------COMPRAS------------------------" << endl;
			cout << "\n" << endl;
			string str = "";
			str = "select c.idcompras, c.no_orden_compra, c.idproveedor, p.proveedor, c.fecha_orden, c.fechaingreso, c.totalcompra from compras as c left outer join proveedores as p on c.idproveedor = p.idproveedores where c.no_orden_compra =" + noorden;
			string consulta = str;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << "  |  " << fila[1] << "  |  " << fila[2] << "  |  " << fila[3] << "  |  " << fila[4] << "  |  " << fila[5] << "  |  " << fila[6] << endl;
				}

			}
			else {

				cout << "xxxxx error de  consulta xxxx" << endl;
			}
		}
		else {

			cout << " xxxxx error en la conexion xxxxx";
		}

		cn.cerrar_conexion();

		//DETALLE
		
		cn.abrir_conexion();

		if (cn.getConectar()) {
			cout << "\n" << endl;
			cout << "----------------------------DETALLE COMPRAS------------------------" << endl;
			cout << "\n" << endl;
			string consulta = "select  cd.idcompras_detalle, cd.idcompra, cd.idproducto, p.producto, cd.cantidad, cd.precio_costo_unitario, cd.subtotal from compras_detalle as cd inner join compras as c on cd.idcompra = c.idcompras  left outer join productos as p on cd.idproducto = p.idproductos where c.no_orden_compra = " + noorden;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << "  |  " << fila[1] << "  |  " << fila[2] << "  |  " << fila[3] << "  |  " << fila[4] << "  |  " << fila[5] << "  |  " << fila[6] << endl;
				}

			}
			else {

				cout << "xxxxx error de  consulta xxxx" << endl;
			}
		}
		else {

			cout << " xxxxx error en la conexion xxxxx";
		}

		cn.cerrar_conexion();

	}


	void generar_ordencompra(string noorden) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		char cadena[30];
		int x = 0;
		ofstream ordencompra;
		string nombreArchivo, frase;
		char rpt;

		string nombreOrdenCompra = "";
		nombreOrdenCompra = "OrdenCompraNo" + noorden + ".txt";
		ordencompra.open(nombreOrdenCompra.c_str(), ios::out); //Creamos el archivo
		if (ordencompra.fail()) { //Si a ocurrido algun error
			cout << "No se pudo abrir el archivo";
			exit(1);
		}

		string cajero = "";
		string totalorden = "";
		string fechaingreso = "";
		int totalproductos = 0;
		if (cn.getConectar()) {
			ordencompra << "\n" << endl;
			ordencompra << "--------------------- ORDEN COMPRA No. " + noorden + " -------------------" << endl;
			ordencompra << "\n" << endl;
			string str = "";
			str = "select c.idcompras, c.no_orden_compra, c.idproveedor, p.proveedor, c.fecha_orden, c.fechaingreso, c.totalcompra from compras as c left outer join proveedores as p on c.idproveedor = p.idproveedores where c.no_orden_compra =" + noorden;
			string consulta = str;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					ordencompra << "No. Orden: " << fila[1] << endl;
					ordencompra << "Fecha: " << fila[4] << endl;
					ordencompra << "Proveedor: " << fila[3] << endl;
					fechaingreso = fila[5];
					totalorden = fila[6];
				}
			}
			else {

				cout << "xxxxx error de  consulta xxxx" << endl;
			}
		}
		else {

			cout << " xxxxx error en la conexion xxxxx";
		}

		cn.cerrar_conexion();

		//DETALLE

		cn.abrir_conexion();

		if (cn.getConectar()) {
			ordencompra << "\n" << endl;
			ordencompra << "---------------------------- DETALLE ------------------------" << endl;
			ordencompra << "\n" << endl;
			string consulta = "select  cd.idcompras_detalle, cd.idcompra, cd.idproducto, p.producto, cd.cantidad, cd.precio_costo_unitario, cd.subtotal from compras_detalle as cd inner join compras as c on cd.idcompra = c.idcompras  left outer join productos as p on cd.idproducto = p.idproductos where c.no_orden_compra = " + noorden;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					ordencompra << fila[0] << "  |  " << fila[1] << "  |  " << fila[2] << "  |  " << fila[3] << "  |  " << fila[4] << "  |  " << fila[5] << "  |  " << fila[6] << endl;
					totalproductos++;
				}
			}
			else {

				cout << "xxxxx error de  consulta xxxx" << endl;
			}
		}
		else {

			cout << " xxxxx error en la conexion xxxxx";
		}

		ordencompra << "\n" << endl;
		ordencompra << "-------------------------------------------------------------" << endl;
		ordencompra << "Total productos: " << totalproductos;
		ordencompra << "\n" << endl;
		ordencompra << "\n" << endl;
		ordencompra << "Total : Q " << totalorden;
		ordencompra << "\n" << endl;
		ordencompra << "Fecha: " << fechaingreso;
		cn.cerrar_conexion();

		ordencompra.close();

		ifstream canal(nombreArchivo);
		canal.getline(cadena, 30);

		while (x < 20)
		{
			cout << cadena[x];
			x++;
		}

	}


	void modificar_compras() {

		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		string NOC = to_string(no_orden_compra);
		string IP = id_proveedor;
		if (cn.getConectar()) {
			string id_Compras;
			cout << " ingrese id a modificar :";
			cin >> id_Compras;
			string update = " update compras   set no_orden_compra='" + NOC + "', fecha_orden='" + fecha_orden + "', id_proveedor='" + IP + "', fecha_ingreso='" + fecha_ingreso + "' WHERE id_Compras= '" + id_Compras + "'";
			const char* o = update.c_str();
			q_estado = mysql_query(cn.getConectar(), o);
			if (!q_estado) {
				cout << " modificacion Exitosa..." << endl;

			}
			else {

				cout << "xxxxx error de  modificacion xxxx" << endl;
			}

		}
		else {

			cout << " xxxxx error en la conexion xxxxx";
		}

		cn.cerrar_conexion();
	}

	void eliminar_compras() {

		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string id_Compras;
			cout << " ingrese id a eliminar :";
			cin >> id_Compras;
			string sel = " DELETE FROM compras  WHERE id_Compras= '" + id_Compras + "'";
			const char* u = sel.c_str();
			q_estado = mysql_query(cn.getConectar(), u);
			if (!q_estado) {
				cout << " eliminacion exitosa ..." << endl;

			}
			else {

				cout << "xxxxx error al eliminar xxxx" << endl;
			}





		}
		else {

			cout << " xxxxx error en la conexion xxxxx";
		}
		cn.cerrar_conexion();

	}

	int ultima_orden() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		int noorden = 0;
		if (cn.getConectar()) {
			string str = "";
			str = "select max(no_orden_compra) from compras;";
			string consulta = str;
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					noorden = stoi(fila[0]);
				}
			}
			else {
				cout << "xxxxx error de  consulta xxxx" << endl;
			}
		}
		else {

			cout << " xxxxx error en la conexion xxxxx";
		}
		cn.cerrar_conexion();
		return noorden;
	}


};