#pragma once
#include <mysql.h>
#include <iostream>
#include "ConexionBD.h"
#include "compras.h"
#include <string>
#include "productos.h"

using namespace std;

class detalle_compras {
	// atributos

	   // metodo constructor
protected: string cantidad, precio_costo_u, id_Compras, id_Producto,existencia;
		 //int id_Producto = 0;

		 productos pd = productos();
public:
	detalle_compras() {
	}

	detalle_compras(string cn, string idpro, string cantc, string pcu, string exist) {
		id_Compras = cn;
		id_Producto = idpro;
		cantidad = cantc;
		precio_costo_u = pcu;
		existencia = exist;
		
	}
	// metodos de modificar datos
	// set ( modificar)
	void setcantidad(string cantc) { cantidad = cantc; }
	void setprecio_costo_u(string pcu) { precio_costo_u = pcu; }
	void setid_Producto(string idpro) { id_Producto = idpro; }
	void setid_Compras(string cn) { id_Compras = cn; }
	void set_existencia(string exist) { existencia = exist; }


	// get(mostrar)
	string getcantidad() { return cantidad; }
	string getprecio_costo_u() { return precio_costo_u; }
	string getid_Producto() { return id_Producto; }
	string getid_Compras() { return id_Compras; }
	string get_existencia() { return existencia; }



	void crearComprasDetalle() {
		int q_estado;
		ConexionBD cn = ConexionBD();
		string produc = id_Producto;
		int subtotal = 0;
		string total = "";
		int ultimaexistencia = 0;
		string existenciaactual = "";
		cn.abrir_conexion();
		if (cn.getConectar()) {
			existenciaactual = pd.consulta_productoexistencia(id_Producto);
			subtotal = stoi(cantidad) * stoi(precio_costo_u);
			ultimaexistencia = stoi(cantidad) + stoi(existenciaactual);
			string insert = " insert into compras_detalle (idcompra,idproducto, cantidad, precio_costo_unitario, subtotal) VALUES (" + id_Compras + "," + id_Producto + ",  " + cantidad + "," + precio_costo_u + "," + to_string(subtotal) + ");";
			// executar el query
			const char* h = insert.c_str();
			q_estado = mysql_query(cn.getConectar(), h);
			if (!q_estado) {
				cout << "Ingreso Exitoso ..." << endl;
				total = totalDetalle(id_Compras);
				modificarCompraTotal(id_Compras, total);
				pd.update_productosDatos(5, stoi(id_Producto), precio_costo_u);
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

	string totalDetalle(string idcompra) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string total = "";
		if (cn.getConectar()) {
			string consulta = "select sum(subtotal) as subtotal from compras_detalle where idcompra = " + idcompra;
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					total = fila[0];
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
		return total;
	}

	void modificarCompra(string idventa, string totalfactura) {
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
			string update = " update compras set totalcompra = " + totalfactura + " WHERE idcompra = " + idventa + "";
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

	void leerComprasDetalle(string idcompra) {

		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			cout << "\n" << endl;
			cout << "----------------------------DETALLE COMPRAS------------------------" << endl;
			cout << "\n" << endl;
			string consulta = "select  cd.idcompras_detalle, cd.idcompra, cd.idproducto, p.producto, cd.cantidad, cd.precio_costo_unitario, cd.subtotal from compras_detalle as cd inner join compras as c on cd.idcompra = c.idcompras  left outer join productos as p on cd.idproducto = p.idproductos where cd.idcompra = " + idcompra;

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


	

	void modificarComprasDetalle() {

		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		string PRO = id_Producto;

		if (cn.getConectar()) {
			string id_Compras_Detalle;
			cout << " ingrese id a modificar :";
			cin >> id_Compras_Detalle;
			string update = " update ventas_detalle   set id_Producto='" + PRO + "', cantidad='" + cantidad + "', precio_costo_u='" + precio_costo_u + "', id_Compras='" + id_Compras + "' WHERE id_Ventas_Detalle= '" + id_Compras_Detalle + "'";
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


	void modificarDetalle(string idcompradetalle, int cantidadmodifica, int precio) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		string PR = id_Producto;
		//int precio = 0;
		int subtotal = 0;
		string idcompra = "";
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
			subtotal = (cantidadmodifica * precio);
			idproducto = consulta_detallecompraidproducto(idcompradetalle);
			existenciaactual = pd.consulta_productoexistencia(idproducto);
			cantidadAnterior = consulta_detallecompraExistencia(idcompradetalle);
			exitenciatemp = (stoi(existenciaactual) - stoi(cantidadAnterior));
			ultimaexistencia = (exitenciatemp + cantidadmodifica);
			string update = " update compras_detalle  set cantidad=" + to_string(cantidadmodifica) + ", precio_costo_unitario = "+ to_string(precio) +", subtotal = " + to_string(subtotal) + " WHERE idcompras_detalle= " + idcompradetalle + "";
			const char* o = update.c_str();
			q_estado = mysql_query(cn.getConectar(), o);
			if (!q_estado) {
				//cout << " modificacion Exitosa..." << endl;
				idcompra = consulta_detallecompraidcompra(idcompradetalle);
				total = totalDetalle(idcompra);
				modificarCompraTotal(idcompra, total);
				pd.update_productosDatos(5, stoi(idproducto), to_string(precio));
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

	void modificarCompraTotal(string idcompra, string totalcompra) {
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
			string update = " update compras set totalcompra = " + totalcompra + " WHERE idcompras = " + idcompra + "";
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


	string consulta_detallecompraidproducto(string idcompradetalle) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string idproducto = "";
		if (cn.getConectar()) {
			string consulta = "select  cd.idcompras_detalle, cd.idcompra, cd.idproducto, p.producto, cd.cantidad, cd.precio_costo_unitario, cd.subtotal from compras_detalle as cd inner join compras as c on cd.idcompra = c.idcompras  left outer join productos as p on cd.idproducto = p.idproductos where  cd.idcompras_detalle = " + idcompradetalle;

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

	string consulta_detallecompraExistencia(string idcompradetalle) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string cantidad = "";
		if (cn.getConectar()) {
			string consulta = "select  cd.idcompras_detalle, cd.idcompra, cd.idproducto, p.producto, cd.cantidad, cd.precio_costo_unitario, cd.subtotal from compras_detalle as cd inner join compras as c on cd.idcompra = c.idcompras  left outer join productos as p on cd.idproducto = p.idproductos where  cd.idcompras_detalle = " + idcompradetalle;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					cantidad = fila[4];
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
		return cantidad;
	}

	string consulta_detallecompraidcompra(string idcompradetalle) {

		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string idcompra = "";
		if (cn.getConectar()) {
			string consulta = "select  cd.idcompras_detalle, cd.idcompra, cd.idproducto, p.producto, cd.cantidad, cd.precio_costo_unitario, cd.subtotal from compras_detalle as cd inner join compras as c on cd.idcompra = c.idcompras  left outer join productos as p on cd.idproducto = p.idproductos where  cd.idcompras_detalle = " + idcompradetalle;

			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());

				while (fila = mysql_fetch_row(resultado)) {
					idcompra = fila[1];
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

	void eliminarDetalleCompra(string idcompradetalle) {
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string id_Ventas_Detalle;
			int precio = 0;
			int subtotal = 0;
			string idcompra = "";
			string total = "";

			string idproducto = "";
			int ultimaexistencia = 0;
			string existenciaactual = "";
			string cantidadAnterior = "";
			idproducto = consulta_detallecompraidproducto(idcompradetalle);
			existenciaactual = pd.consulta_productoexistencia(idproducto);
			cantidadAnterior = consulta_detallecompraExistencia(idcompradetalle);
			ultimaexistencia = (stoi(existenciaactual) - stoi(cantidadAnterior));
			idcompra = consulta_detallecompraidcompra(idcompradetalle);
			string sel = " DELETE FROM compras_detalle WHERE idcompras_detalle= " + idcompradetalle + "";
			const char* u = sel.c_str();
			q_estado = mysql_query(cn.getConectar(), u);
			if (!q_estado) {
				//cout << " eliminacion exitosa ..." << endl;
				total = totalDetalle(idcompra);
				modificarCompraTotal(idcompra, total);
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

	

	void eliminarComprasDetalle() {

		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar()) {
			string id_Compras_Detalle;
			cout << " ingrese id a eliminar :";
			cin >> id_Compras_Detalle;
			string sel = " DELETE FROM compras   WHERE id_Compras_Detalle= '" + id_Compras_Detalle + "'";
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

	void eliminarT() {
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
	}


	

};