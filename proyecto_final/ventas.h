#pragma once
#include <iostream>
#include <string>
#include "ConexionBD.h"    
#include <fstream>            
#include <stdlib.h>  

using namespace std;

class ventas {
protected: string cantidad, precio_uni, serie, fecha_factura, fecha_ingreso, no_factura, id_Clientes, id_Empleados;
		 //int no_factura = 0;
		 //int id_Clientes = 0;
		 //int id_Empleados = 0;



		 // constructor
public:
	ventas() {
	}
	ventas(string nf, string se, string fft, string idc, string ide, string ing) {

		no_factura = nf;
		serie = se;
		fecha_factura = fft;
		id_Clientes = idc;
		id_Empleados = ide;
		fecha_ingreso = ing;


	}
	void setno_factura(int nf) { no_factura = nf; }
	void setserie(string se) { serie = se; }
	void setfecha_factura(string fft) { fecha_factura = fft; }
	void setid_Clientes(int ide) { id_Empleados = ide; }
	void setfecha_ingreso(string ing) { fecha_ingreso = ing; }


	// get(mostrar)
	string getno_factura() { return no_factura; }
	string getserie() { return serie; }
	string getfecha_factura() { return fecha_factura; }
	string getid_Clientes() { return id_Empleados; }
	string getfecha_ingreso() { return fecha_ingreso; }

	string asignar(int no_factura) {

		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string nofac = to_string(no_factura);
			string consulta = "select id_ventas from  ventas where no_factura values('" + nofac + "')";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);

			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "----------------------------Ventas Detalle------------------------" << endl;
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

	void crearVentas() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		string NF = no_factura;
		string IDC = id_Clientes;
		string IDE = id_Empleados;
		cn.abrir_conexion();
		if (cn.getConectar()) {
			//string consultaid = "select id_Ventas from  ventas order by id_Ventas desc limit 1";
			//consultaid = (id_Ventas);
			string insert = "insert into ventas(nofactura, serie, fechafactura, idcliente, idempleado, fechaingreso, totalfactura) VALUES (" + no_factura + ",  '" + serie + "','"+ fecha_ingreso  +"', " + id_Clientes + "," + id_Empleados + ",'"+ fecha_ingreso +"',0);";
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

	void leerVentas() {

		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			string consulta = "select v.idventas, v.nofactura, v.serie, v.fechafactura, v.idcliente, concat(c.nombres,' ', c.apellidos) as nombreCliente, v.idempleado, concat(em.nombres,' ', em.apellidos) as nombreEmpleado, v.fechaingreso, v.totalfactura from ventas as v left outer join clientes as c on v.idcliente = c.idcliente left outer join empleados as em on v.idempleado = em.idempleados";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "	--------------------------------------------------------------------------------------------" << endl;
				cout << "	|			         Listado de Facturas de ventas		    	           |" << endl;
				cout << "	|			         SUPERMERCADO 'ANTIGUA COLONIAL'	            	   |" << endl;
				cout << "	--------------------------------------------------------------------------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << "	--------------------------------------------------------------------------------------------" << endl;
					cout << fila[0] << ".	No. Factura:  " << fila[1] << "   | Serie:  " << fila[2] << " | Fecha y hora de registro:  " << fila[3] << endl;
					cout << "	Id de cliente:  " << fila[4] << " | Nombre de Cliente:  " << fila[5] << " | Registro de empleado:  " << fila[6] << endl;
					cout << "	--------------------------------------------------------------------------------------------" << endl;
					cout << "\n" << endl;
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

	void consulta_ventasnofactura(string nofactura) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			cout << "\n" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "	|			         Registro de Facturas de ventas		    	           |" << endl;
			cout << "	|			         SUPERMERCADO 'ANTIGUA COLONIAL'	            	   |" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			string str = "";
			str = "select v.idventas, v.nofactura, v.serie, v.fechafactura, v.idcliente, concat(c.nombres,' ', c.apellidos) as nombreCliente, v.idempleado, concat(em.nombres,' ', em.apellidos) as nombreEmpleado, v.fechaingreso, v.totalfactura from ventas as v left outer join clientes as c on v.idcliente = c.idcliente left outer join empleados as em on v.idempleado = em.idempleados where v.nofactura = " + nofactura;
			//str = "select vd.idventas_detalle, vd.idventa, vd.idproducto, pro.producto, vd.cantidad, vd.precio_unitario from ventas_detalle as vd left outer join productos as pro on vd.idproducto = pro.idproductos left outer join ventas as v on vd.idventa = v.idventas where v.nofactura = " + nofactura;
			string consulta = str;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					cout << "	|" << fila[0] << "   |   No. Factura: " << fila[1] << "  | Serie:  " << fila[2] << "  |  Fecha y hora de ingreso:  " << fila[3] <<"  |"<< endl;
					cout << "	--------------------------------------------------------------------------------------------" << endl;
					cout << "	|Id Cliente: " << fila[4] << "  | Nombre de cliente: " << fila[5] << "                                    |" << endl; 
					cout << "	--------------------------------------------------------------------------------------------" << endl;
					cout << "	|Id Empleado: " << fila[6] << " | Nombre de Empleado:  " << fila[7] << "                                       |  " << endl;
					cout << "	--------------------------------------------------------------------------------------------" << endl;
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


	string consulta_ventasid(string nofactura) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string idventas = "";
		if (cn.getConectar()) {

			string str = "";
			str = "select v.idventas, v.nofactura, v.serie, v.fechafactura, v.idcliente, concat(c.nombres,' ', c.apellidos) as nombreCliente, v.idempleado, concat(em.nombres,' ', em.apellidos) as nombreEmpleado, v.fechaingreso, v.totalfactura from ventas as v left outer join clientes as c on v.idcliente = c.idcliente left outer join empleados as em on v.idempleado = em.idempleados where v.nofactura = " + nofactura;
			string consulta = str;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					idventas = fila[0];
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
		return idventas;
	}

	void imprimir_ventas(string nofactura) {
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
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "	|			         SUPERMERCADO 'ANTIGUA COLONIAL'	    	           |" << endl;
			cout << "	|			      28 calle norte La Antigua Guatemala	            	   |" << endl;
			cout << "	|		 Nit: 447814-1 - Tel: 78324488 - anitguacolonial@gmail.com            	   |" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "\n" << endl;
			string str = "";
			str = "select v.idventas, v.nofactura, v.serie, v.fechafactura, v.idcliente, concat(c.nombres,' ', c.apellidos) as nombreCliente, v.idempleado, concat(em.nombres,' ', em.apellidos) as nombreEmpleado, v.fechaingreso, v.totalfactura from ventas as v left outer join clientes as c on v.idcliente = c.idcliente left outer join empleados as em on v.idempleado = em.idempleados where v.nofactura = " + nofactura;
			string consulta = str;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					cout << "	--------------------------------------------------------------------------------------------" << endl;
					cout << fila[0] << ".	No. Factura:  " << fila[1] << "   | Serie:  " << fila[2] << " | Fecha y hora de registro:  " << fila[3] << endl;
					cout << "	Id de cliente:  " << fila[4] << " | Nombre de Cliente:  " << fila[5] << " | Registro de empleado:  " << fila[6] << endl;
					cout << "	--------------------------------------------------------------------------------------------" << endl;
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
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "	|			                DETALLE DE VENTA		    	                 |" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			string consulta = "select vd.idventas_detalle, vd.idventa, vd.idproducto, pro.producto, vd.cantidad, vd.precio_unitario, vd.subtotal from ventas_detalle as vd left outer join productos as pro on vd.idproducto = pro.idproductos left outer join ventas as v on vd.idventa = v.idventas where v.nofactura = " + nofactura;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					cout << "	|  " << fila[0] << " |Id venta:  " << fila[1] << "  | Id producto:  " << fila[2] << "  | Nombre del producto: " << fila[3] << "  |  " << endl;
					cout << "	--------------------------------------------------------------------------------------------" << endl;
					cout << "	|Cantidad: " << fila[4] << "  |  Precio por unidad: " << fila[5] << "  |  Precio por productos: Q" << fila[6] << "|" << endl;
					cout << "	--------------------------------------------------------------------------------------------" << endl;
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


	void modificar() {

		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		string NF = no_factura;
		string IDC = id_Clientes;
		string IDE = id_Empleados;
		if (cn.getConectar()) {
			string id_Ventas;
			cout << " ingrese id a modificar :";
			cin >> id_Ventas;
			string update = " update ventas   set no_factura='" + NF + "', serie='" + serie + "', fecha_factura='" + fecha_factura + "', id_Clientes='" + IDC + "', id_Empleado='" + IDE + "', fecha_ingreso= '" + fecha_ingreso + "' WHERE id_Ventas= '" + id_Ventas + "'";
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

	void eliminar() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string id_Ventas;
			cout << " ingrese id a eliminar :";
			cin >> id_Ventas;
			string sel = " DELETE FROM ventas   WHERE id_Ventas= '" + id_Ventas + "'";
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


	int ultima_factura() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		int nofactura = 0;
		if (cn.getConectar()) {
			string str = "";
			str = "select max(nofactura) from ventas;";
			string consulta = str;
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					nofactura = stoi(fila[0]);
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
		return nofactura;
	}


	void crearFactura(string nofactura) {
		/*char cadena[30];
		int x = 0;
		string nombreFactura = "";
		nombreFactura = "facturaNo" + nofactura + ".txt";
		ofstream tutorial(nombreFactura);
		tutorial << "no entieno " << endl;
		tutorial << "Que hago " << endl;
		tutorial.close();

		ifstream canal(nombreFactura);
		canal.getline(cadena, 30);

		while (x < 20)
		{
			cout << cadena[x];
			x++;
		}*/

		char cadena[30];
		int x = 0;
		ofstream archivo;
		string nombreArchivo, frase;
		char rpt;

		string nombreFactura = "";
		nombreFactura = "facturaNo" + nofactura + ".txt";
		
		archivo.open(nombreFactura.c_str(), ios::out); //Creamos el archivo

		if (archivo.fail()) { //Si a ocurrido algun error
			cout << "No se pudo abrir el archivo";
			exit(1);
		}

		archivo << "no entieno " << endl;
		archivo << "Que hago " << endl;

		archivo.close();

		ifstream canal(nombreFactura);
		canal.getline(cadena, 30);

		while (x < 20)
		{
			cout << cadena[x];
			x++;
		}
	}

	void generar_factura(string nofactura) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		char cadena[30];
		int x = 0;
		ofstream factura;
		string nombreArchivo, frase;
		char rpt;

		string nombreFactura = "";
		nombreFactura = "facturaNo" + nofactura + ".txt";
		factura.open(nombreFactura.c_str(), ios::out); //Creamos el archivo
		if (factura.fail()) { //Si a ocurrido algun error
			cout << "No se pudo abrir el archivo";
			exit(1);
		}

		string cajero = "";
		string totalfactura = "";
		string fechaingreso = "";
		int totalproductos = 0;
		if (cn.getConectar()) {
			factura << "\n" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "	|			         SUPERMERCADO 'ANTIGUA COLONIAL'	    	           |" << endl;
			cout << "	|			      28 calle norte La Antigua Guatemala	            	   |" << endl;
			cout << "	|		 Nit: 447814-1 - Tel: 78324488 - anitguacolonial@gmail.com            	   |" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			factura << "------------------------- FACTURA No. "+ nofactura +" ---------------------" << endl;
			factura << "\n" << endl;
			string str = "";
			str = "select v.idventas, v.nofactura, v.serie, v.fechafactura, v.idcliente, concat(c.nombres,' ', c.apellidos) as nombreCliente, v.idempleado, concat(em.nombres,' ', em.apellidos) as nombreEmpleado, v.fechaingreso, v.totalfactura from ventas as v left outer join clientes as c on v.idcliente = c.idcliente left outer join empleados as em on v.idempleado = em.idempleados where v.nofactura = " + nofactura;
			string consulta = str;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					factura << "No. Factura: " << fila[1] << endl;
					factura << "Serie: " << fila[2] << endl;
					factura << "Fecha: " << fila[3] << endl;
					factura << "Cliente: " << fila[5] << endl;
					cajero = fila[7];
					fechaingreso = fila[8];
					totalfactura = fila[9];
					/*cout << fila[0] << "  |  " << fila[1] << "  |  " << fila[2] << "  |  " << fila[3] << "  |  " << fila[4] << "  |  " << fila[5] << "  |  " << fila[6] << "  |  " << fila[7] << "  |  " << fila[8] << "  |  " << fila[9] << endl;*/
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
			factura << "\n" << endl;
			factura << "----------------------------- DETALLE -------------------------" << endl;
			factura << "\n" << endl;
			string consulta = "select vd.idventas_detalle, vd.idventa, vd.idproducto, pro.producto, vd.cantidad, vd.precio_unitario, vd.subtotal from ventas_detalle as vd left outer join productos as pro on vd.idproducto = pro.idproductos left outer join ventas as v on vd.idventa = v.idventas where v.nofactura = " + nofactura;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					factura << fila[0] << "  |  " << fila[1] << "  |  " << fila[2] << "  |  " << fila[3] << "  |  " << fila[4] << "  |  " << fila[5] << "  |  " << fila[6] << endl;
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

		factura << "\n" << endl;
		factura << "-------------------------------------------------------------" << endl;
		factura << "Total productos: " << totalproductos;
		factura << "\n" << endl;
		factura << "\n" << endl;
		factura << "Total : Q " << totalfactura;
		factura << "\n" << endl;
		factura << "Cajero: " << cajero << " - Fecha: " << fechaingreso;
		cn.cerrar_conexion();

		factura.close();

		ifstream canal(nombreFactura);
		canal.getline(cadena, 30);

		while (x < 20)
		{
			cout << cadena[x];
			x++;
		}

	}

};