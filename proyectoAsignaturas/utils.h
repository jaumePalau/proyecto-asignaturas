#ifndef UTILS_H
#define UTILS_H
#include <QStringList>
QStringList leerXML(const QString &ruta);

QStringList buscarElementos(const QString &archivo, const QString &valorBuscado, const QString &elementoBuscar,bool dialogo);
bool modificarXML(const QString &archivoOriginal, const QString &nombre, const QString &hijo_modificar, const QString &parametro);
void testModificar(const QString &archivo, const QString &rutaDestino);

#endif // UTILS_H
