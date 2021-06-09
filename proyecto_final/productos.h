#pragma once
#include <iostream>
#include <string>
#include "ConexionBD.h"

using namespace std;

class productos
{
private:  string producto, descripcion, imagen, fecha_ingreso;
	   int idmarca = 0, existencia = 0;
	   double precio_costo = 0, precio_venta = 0;
public:
	productos() {	}
	productos(string prod, int idm, string des, string im, double precioc, double preciov, int exis, string fein)
	{
		producto = prod;	idmarca = idm;	descripcion = des;	imagen = im;	precio_costo = precioc;
		precio_venta = preciov;	existencia = exis;	fecha_ingreso = fein;
	}

	void setproducto(string prod) { producto = prod; }
	void setidmarca(int idm) { idmarca = idm; }
	void setdescripcion(string des) { descripcion = des; }
	void setimagen(string im) { imagen = im; }
	void setprecio_costo(double precioc) { precio_costo = precioc; }
	void setprecio_venta(double preciov) { precio_venta = preciov; }
	void setexistencias(int exis) { existencia = exis; }
	void setfecha_ingreso(string fein) { fecha_ingreso = fein; }

	string getproducto() { return producto; }
	int getidmarca() { return idmarca; }
	string getdescripcion() { return descripcion; }
	string getimagen() { return imagen; }
	double getprecio_costo() { return precio_costo; }
	double getprecio_venta() { return precio_venta; }
	int getexistencia() { return existencia; }
	string getfecha_ingreso() { return fecha_ingreso; }

	/**********************************************************************************/

	void insert_producto()
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();

		string idm = to_string(idmarca);
		string precioc = to_string(precio_costo);
		string preciov = to_string(precio_venta);
		string ex = to_string(existencia);

		if (cn.getConectar())
		{
			string insertar = "insert into productos(producto, idmarca, descripcion, imagen, precio_costo, precio_venta, existencia, fecha_ingreso) values ('" + producto + "'," + idm + ",'" + descripcion + "', '" + imagen + "'," + precioc + "," + preciov + "," + ex + ",'" + fecha_ingreso + "')";
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado)
			{
				cout << "ingreso exitoso" << endl;
			}
			else
			{
				cout << "Error en el ingreso" << endl;
			}
		}
		else
		{
			cout << "Error en la conexion" << endl;
		}
		cn.cerrar_conexion();
	}

	/**********************************************************************************/

	void leer_productos()
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "	|		    	             Listado de Productos	   	                   |" << endl;
			cout << "	|			         SUPERMERCADO 'ANTIGUA COLONIAL'	            	   |" << endl;
			cout << "	--------------------------------------------------------------------------------------------" << endl;
			cout << "\n" << endl;
			string consulta = "select p.idproductos, p.producto, m.marca, p.descripcion, p.imagen, p.precio_costo, p.precio_venta, p.existencia, p.fecha_ingreso from productos as p inner join marcas as m on p.idmarca = m.idmarcas; ";
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					cout << "	--------------------------------------------------------------------------------------------" << endl;
					cout << "	" << fila[0] << ".|  Productos: " << fila[1] << " | Marca: " << fila[2] << " | Descripcion: " << fila[3] << endl;
					cout << "	Precio costo: " << fila[5] << "         | Precio venta: " << fila[6] << "          | Existencia: " << fila[7] << endl;
					cout << "	Fecha de ingreso: " << fila[8] << endl;
					cout << "	Imagen: " << fila[4] << endl;
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

	/**********************************************************************************/

	void consulta_producto(string idproducto)
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();

		if (cn.getConectar()) {
			string consulta = "select p.idproductos, p.producto, m.marca, p.descripcion, p.precio_venta, p.existencia from productos as p inner join marcas as m on p.idmarca = m.idmarcas where p.idproductos = " + idproducto;
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				if (resultado > 0) {
					while (fila = mysql_fetch_row(resultado)) {
						cout << "Producto: " << fila[0] << " | " << fila[1] << " | " << fila[2] << " | " << fila[3] << " | " << fila[4] << " | " << fila[5] << endl;
					}
				}
				else
				{
					cout << " xxx Error: el producto no existe  xxx" << endl;
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

	string consulta_productoprecio(string idproducto)
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string precio = "";
 		if (cn.getConectar()) {
			string consulta = "select p.idproductos, p.producto, m.marca, p.descripcion, p.precio_venta, p.existencia from productos as p inner join marcas as m on p.idmarca = m.idmarcas where p.idproductos = " + idproducto;
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					precio = fila[4];
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
		return precio;
	}

	string consulta_productoexistencia(string idproducto)
	{
		int q_estado;
		ConexionBD cn = ConexionBD();
		MYSQL_ROW fila;
		MYSQL_RES* resultado;
		cn.abrir_conexion();
		string existencia = "";
		if (cn.getConectar()) {
			string consulta = "select p.idproductos, p.producto, m.marca, p.descripcion, p.precio_venta, p.existencia from productos as p inner join marcas as m on p.idmarca = m.idmarcas where p.idproductos = " + idproducto;
			const char* c = consulta.c_str();
			q_estado = mysql_query(cn.getConectar(), c);
			if (!q_estado) {
				resultado = mysql_store_result(cn.getConectar());
				while (fila = mysql_fetch_row(resultado)) {
					existencia = fila[5];
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
		return existencia;
	}


	/**********************************************************************************/

	int datos_modificar()
	{
		int opcion3;

		system("cls");
		cout << "-------------------- LISTADO DE DATOS DE LA TABLA PRODUCTOS --------------------" << endl;
		cout << "1. Producto" << endl;
		cout << "2. Idmarca" << endl;
		cout << "3. Descripcion" << endl;
		cout << "4. Imagen" << endl;
		cout << "5. Precio_costo" << endl;
		cout << "6. Precio_venta" << endl;
		cout << "7. existencia " << endl;
		/*cout << "8. Fecha ingreso" << endl << endl;*/
		cout << "\tQue elemento desea modificar: ";
		cin >> opcion3;
		cin.ignore();
		return opcion3;
	}

	void update_productos(int opcion2, int id_prod)
	{
		int q_estado;
		string idp = to_string(id_prod);
		string idm = to_string(idmarca);
		string precioc = to_string(precio_costo);
		string preciov = to_string(precio_venta);
		string ex = to_string(existencia);
		string consulta;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar())
		{

			switch (opcion2)
			{
			case 1:
				consulta = "update productos set producto='" + producto + "' where idproductos=" + idp;
				break;
			case 2:
				consulta = "update productos set idmarca=" + idm + " where idproductos=" + idp;
				break;
			case 3:
				consulta = "update productos set descripcion='" + descripcion + "' where idproductos=" + idp;
				break;
			case 4:
				consulta = "update productos set imagen='" + imagen + "' where idproductos=" + idp;
				break;
			case 5:
				consulta = "update productos set precio_costo= '" + precioc + "' where idproductos=" + idp;
				break;
			case 6:
				consulta = "update productos set precio_venta=" + preciov + " where idproductos=" + idp;
				break;
			case 7:
				consulta = "update productos set existencia='" + ex + "' where idproductos=" + idp;
				break;
			case 8:
				/*consulta = "update productos set fecha_ingreso='" + fecha_ingreso + "' where idproductos=" + idp;*/
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
				cout << "Error al intentar elimanar" << endl;
			}
		}
		cn.cerrar_conexion();
	}


	void update_productosDatos(int opcion, int idproducto, string valorupdate)
	{
		int q_estado;
		string idp = to_string(idproducto);
		string idm = to_string(idmarca);
		string precioc = to_string(precio_costo);
		string preciov = to_string(precio_venta);
		string ex = to_string(existencia);
		string consulta;
		ConexionBD cn = ConexionBD();
		cn.abrir_conexion();
		if (cn.getConectar())
		{

			switch (opcion)
			{
			case 1:
				consulta = "update productos set producto='" + producto + "' where idproductos=" + idp;
				break;
			case 2:
				consulta = "update productos set idmarca=" + idm + " where idproductos=" + idp;
				break;
			case 3:
				consulta = "update productos set descripcion='" + descripcion + "' where idproductos=" + idp;
				break;
			case 4:
				consulta = "update productos set imagen='" + imagen + "' where idproductos=" + idp;
				break;
			case 5:
				consulta = "update productos set precio_costo= " + valorupdate + " where idproductos=" + idp;
				break;
			case 6:
				consulta = "update productos set precio_venta=" + valorupdate + " where idproductos=" + idp;
				break;
			case 7:
				consulta = "update productos set existencia = " + valorupdate + " where idproductos= " + idp;
				break;
			case 8:
				/*consulta = "update productos set fecha_ingreso='" + fecha_ingreso + "' where idproductos=" + idp;*/
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
				cout << "Error al intentar elimanar" << endl;
			}
		}
		cn.cerrar_conexion();
	}

	/**********************************************************************************/

	void eliminar_productos(int id_prod)
	{
		string idp = to_string(id_prod);
		int q_estado;
		ConexionBD cn = ConexionBD();

		cn.abrir_conexion();

		if (cn.getConectar()) {
			string  insertar = "delete from productos where idproductos= " + idp;
			const char* i = insertar.c_str();
			q_estado = mysql_query(cn.getConectar(), i);
			if (!q_estado) {
				cout << "Se ha eliminado el producto exitosamente" << endl;
			}
			else {
				cout << "Error al intentar elimnar el producto" << endl;
			}
		}
		else {
			cout << " xxx Error en la Conexion xxxx" << endl;
		}
		cn.cerrar_conexion();
	}
};
