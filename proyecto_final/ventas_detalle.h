#pragma once
#include "ventas.h"
#include <mysql.h>
#include <iostream>
#include"ConexionBD.h"
#include <string>
#include "productos.h"

using namespace std;

class ventas_detalle {
	// atributos

	   // metodo constructor
protected: string cantidad, precio_uni, id_Ventas, id_Producto;
		 //int id_Producto = 0;

		 productos pd = productos();
public:
	ventas_detalle() {
	}

	ventas_detalle(string vn, string pr,string cant, string unit)/* :venta(vn,nf,cant,unit,se,fft,idc,ide,ing,pr)*/ {
		id_Ventas = vn;
		id_Producto = pr;
		cantidad = cant;
		precio_uni = unit;
	}
	// metodos de modificar datos
	// set ( modificar)
	void setcantidad(string cant) { cantidad = cant; }
	void setprecio_unitario(string unit) { precio_uni = unit; }
	void setid_Producto(string pr) { id_Producto = pr; }
	void setid_Ventas(string vn) { id_Ventas = vn; }


	// get(mostrar)
	string getcantidad() { return cantidad; }
	string getprecio_unitario() { return precio_uni; }
	string getid_Producto() { return id_Producto; }
	string getid_Ventas() { return id_Ventas; }



	void crearVentaDetalle() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		string produc = id_Producto;
		//string vent = to_string(id_Ventas);
		int subtotal = 0;
		string total = "";
		cn.abrir_conexion();
		if (cn.getConectar()) {
			int ultimaexistencia = 0;
			string existenciaactual = "";
			existenciaactual = pd.consulta_productoexistencia(id_Producto);
			ultimaexistencia =  stoi(existenciaactual) - stoi(cantidad);
			subtotal = stoi(cantidad) * stoi(precio_uni);
			string insert = " insert into ventas_detalle(idventa,idproducto, cantidad, precio_unitario, subtotal) VALUES (" + id_Ventas + "," + id_Producto + ",  " + cantidad + "," + precio_uni + "," + to_string(subtotal) +");";
			// executar el query
			const char* h = insert.c_str();
			q_estado = mysql_query(cn.getConectar(), h);
			if (!q_estado) {
				cout << "Ingreso Exitoso ..." << endl;
				//idventa = consulta_detalleventaidventa(idventadetalle);
				total = totalDetalle(id_Ventas);
				modificarVenta(id_Ventas, total);
				pd.update_productosDatos(7, stoi(id_Producto), to_string(ultimaexistencia));
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

	void leerVentaDetalle() {

		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {


			string consulta = "select * from  ventasdetalle ";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				cout << "----------------------------VentaDetalle------------------------" << endl;
				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[1] << "  |  " << fila[2] << "  |  " << fila[3] << endl;
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

	void leerVentasDetalle(string idventa) {

		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			cout << "\n" << endl;
			cout << "----------------------------DETALLE VENTA------------------------" << endl;
			cout << "\n" << endl;
			string consulta = "select vd.idventas_detalle, vd.idventa, vd.idproducto, pro.producto, vd.cantidad, vd.precio_unitario from ventas_detalle as vd left outer join productos as pro on vd.idproducto = pro.idproductos left outer join ventas as v on vd.idventa = v.idventas where vd.idventa = " + idventa;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					cout << fila[0] << "  |  " << fila[1] << "  |  " << fila[2] << "  |  " << fila[3] << "  |  " << fila[4] << "  |  " << fila[5] << endl;
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

	int consulta_preciodetalleventa(string idventas_detalle) {

		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		int precioventa = 0;
		if (cn.getConectar()) {
			string consulta = "select vd.idventas_detalle, vd.idventa, vd.idproducto, pro.producto, vd.cantidad, vd.precio_unitario from ventas_detalle as vd left outer join productos as pro on vd.idproducto = pro.idproductos left outer join ventas as v on vd.idventa = v.idventas where vd.idventas_detalle = " + idventas_detalle;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					precioventa = stoi(fila[5]);
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
		return precioventa;
	}

	string consulta_detalleventaidventa(string idventas_detalle) {

		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string idventa = "";
		if (cn.getConectar()) {
			string consulta = "select vd.idventas_detalle, vd.idventa, vd.idproducto, pro.producto, vd.cantidad, vd.precio_unitario from ventas_detalle as vd left outer join productos as pro on vd.idproducto = pro.idproductos left outer join ventas as v on vd.idventa = v.idventas where vd.idventas_detalle = " + idventas_detalle;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					idventa = fila[1];
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
		return idventa;
	}

	string totalDetalle(string idventa) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string total = "";
		if (cn.getConectar()) {
			string consulta = "select sum(subtotal) as subtotal from ventas_detalle where idventa = " + idventa;
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					total = fila[0];
				}
			}else {
				cout << "xxxxx error de  consulta xxxx" << endl;
			}
		}
		else {
			cout << " xxxxx error en la conexion xxxxx";
		}
		cn.cerrar_conexion();
		return total;
	}


	void leerVentasDetalleFactura(string nofactura) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
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
					cout << "	|Cantidad: " << fila[4] << "  |  Precio por unidad: " << fila[5] << "  |  Precio por productos: Q" << fila[6] << "|"<< endl;
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

	void modificarVenta(string idventa, string totalfactura) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		string PR = id_Producto;
		string precio = "";
		string subtotal = "";
		string idventa1 = "";
		string total = "";
		if (cn.getConectar()) {
			string id_Ventas_Detalle;
			string update = " update ventas set totalfactura = " + totalfactura + " WHERE idventas = " + idventa + "";
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

	void modificarDetalle(string idventadetalle, int cantidadmodifica ) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		string PR = id_Producto;
		int precio = 0;
		int subtotal = 0;
		string idventa = "";
		string total = "";
		string idproducto = "";
		int ultimaexistencia = 0;
		int exitenciatemp = 0;
		string existenciaactual = "";
		string cantidadAnterior = "";
		if (cn.getConectar()) {
			string id_Ventas_Detalle;
			/*cout << " ingrese id a modificar :";
			cin >> id_Ventas_Detalle;*/
			precio = consulta_preciodetalleventa(idventadetalle);
			subtotal = (cantidadmodifica * precio);

			idproducto = consulta_detalleventaidproducto(idventadetalle);
			existenciaactual = pd.consulta_productoexistencia(idproducto);
			cantidadAnterior = consulta_detalleventaExistencia(idventadetalle);
			exitenciatemp = (stoi(existenciaactual) + stoi(cantidadAnterior));
			ultimaexistencia = (exitenciatemp - cantidadmodifica);
			string update = " update ventas_detalle  set cantidad=" + to_string(cantidadmodifica) + ", subtotal = " + to_string(subtotal) +" WHERE idventas_detalle= " + idventadetalle + "";
			const char* o = update.c_str();
			q_estado = mysql_query(cn.getConectar(), o);
			if (!q_estado) {
				//cout << " modificacion Exitosa..." << endl;
				idventa = consulta_detalleventaidventa(idventadetalle);
				total = totalDetalle(idventa);
				modificarVenta(idventa, total);
				pd.update_productosDatos(7, stoi(idproducto), to_string(ultimaexistencia));
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

	string consulta_detalleventaidproducto(string idventas_detalle) {

		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string idproducto = "";
		if (cn.getConectar()) {
			string consulta = "select vd.idventas_detalle, vd.idventa, vd.idproducto, pro.producto, vd.cantidad, vd.precio_unitario from ventas_detalle as vd left outer join productos as pro on vd.idproducto = pro.idproductos left outer join ventas as v on vd.idventa = v.idventas where vd.idventas_detalle = " + idventas_detalle;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					idproducto = fila[2];
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
		return idproducto;
	}

	string consulta_detalleventaExistencia(string idventas_detalle) {

		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string cant = "";
		if (cn.getConectar()) {
			string consulta = "select vd.idventas_detalle, vd.idventa, vd.idproducto, pro.producto, vd.cantidad, vd.precio_unitario from ventas_detalle as vd left outer join productos as pro on vd.idproducto = pro.idproductos left outer join ventas as v on vd.idventa = v.idventas where vd.idventas_detalle = " + idventas_detalle;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					cant = fila[4];
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
		return cant;
	}

	void eliminarDetalle(string idventadetalle) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string id_Ventas_Detalle;
			int precio = 0;
			int subtotal = 0;
			string idventa = "";
			string total = "";
			idventa = consulta_detalleventaidventa(idventadetalle);


			string idproducto = "";
			int ultimaexistencia = 0;
			string existenciaactual = "";
			string cantidadAnterior = "";
			idproducto = consulta_detalleventaidproducto(idventadetalle);
			existenciaactual = pd.consulta_productoexistencia(idproducto);
			cantidadAnterior = consulta_detalleventaExistencia(idventadetalle);
			ultimaexistencia = (stoi(existenciaactual) + stoi(cantidadAnterior));

			string sel = " DELETE FROM ventas_detalle WHERE idventas_detalle= " + idventadetalle + "";
			const char* u = sel.c_str();
			q_estado = mysql_query(cn.getConectar(), u);
			if (!q_estado) {
				//cout << " eliminacion exitosa ..." << endl;
				total = totalDetalle(idventa);
				modificarVenta(idventa, total);
				pd.update_productosDatos(7, stoi(idproducto), to_string(ultimaexistencia));
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

	void eliminarDetalleT() {
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



	}
};