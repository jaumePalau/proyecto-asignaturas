#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>
#include <QXmlStreamReader>
#include "utils.h"
#include <QTemporaryFile>
#include <QDomDocument>
#include <QDomElement>
QStringList leerXML(const QString &ruta){
    QString asignatura;
    QString nombre;
    QString estado;
    QString nota;
    QString cursada;
    QString tipo;
    QStringList ta;
    QFile archivo(ruta);
    if (!archivo.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "No se pudo abrir el archivo XML.";
        return {"ERROR"};
    }
    QXmlStreamReader xmlReader(&archivo);
    while (!xmlReader.atEnd() && !xmlReader.hasError()) {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement) {
            if (xmlReader.name() ==  QString("ASIGNATURA")) {

                while (!(xmlReader.tokenType() == QXmlStreamReader::EndElement && xmlReader.name() == QString("ASIGNATURA"))) {
                    xmlReader.readNext();
                    if (xmlReader.tokenType() == QXmlStreamReader::StartElement) {
                        if (xmlReader.name() ==  QString("NOMBRE")) {
                            xmlReader.readNext();
                            nombre = xmlReader.text().toString();
                        }else if (xmlReader.name() == QString("ESTADO")) {
                            xmlReader.readNext();
                            estado = xmlReader.text().toString();
                        }else if (xmlReader.name() == QString("NOTA")){
                            xmlReader.readNext();
                            nota = xmlReader.text().toString();
                        }else if (xmlReader.name() == QString("CURSADA")){
                            xmlReader.readNext();
                            cursada = xmlReader.text().toString();
                        }else if (xmlReader.name() == QString("TIPO")){
                            xmlReader.readNext();
                            tipo = xmlReader.text().toString();
                        }

                    }
                }
                //qDebug() << "ASIGNATURAS: Asignatura =" << asignatura << ", estado =" << estado << ", nota = " << nota << ", Cursada = " << cursada << ", tipo = " << tipo;
                asignatura = nombre  + ", " + estado + ", " + nota + ", " + cursada + ", " + tipo;
                // asignaturas << asignatura;
                ta << asignatura ;

            }
        }

    }

    return ta;
}



QStringList buscarElementos(const QString &archivo, const QString &valorBuscado, const QString &elementoBuscar, bool dialogo) {
    QString asignatura;
    QStringList ta;
    QString elementBuscar;

    QFile file(archivo);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "No se pudo abrir el archivo";
        return {"ERROR"};
    }

    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError()) {
        if (xml.isStartElement() && xml.name() == QString("ASIGNATURA")) {
            QString nombre, estado, nota, cursada, tipo;
            while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() ==  QString("ASIGNATURA"))) {
                xml.readNext();
                if (xml.isStartElement()) {
                    if (xml.name() ==  QString("NOMBRE")) {
                        nombre = xml.readElementText();
                    } else if (xml.name() ==  QString("ESTADO")) {
                        estado = xml.readElementText();
                    } else if (xml.name() == QString("NOTA")) {
                        nota = xml.readElementText();
                    } else if (xml.name() ==  QString("CURSADA")) {
                        cursada = xml.readElementText();
                    } else if (xml.name() ==  QString("TIPO")) {
                        tipo = xml.readElementText();
                    }
                    if(elementoBuscar =="NOMBRE"){
                        elementBuscar = nombre;
                    }else if(elementoBuscar =="ESTADO"){
                        elementBuscar = estado;
                    }else if(elementoBuscar =="NOTA"){
                        elementBuscar = nota;
                    }else if(elementoBuscar =="CURSADA"){
                        elementBuscar = cursada;
                    }else if(elementoBuscar =="TIPO"){
                        elementBuscar = tipo;

                    }

                }
            }
            // Verificar si el elemento cumple con la condición
            if (elementBuscar == valorBuscado) {
                asignatura = nombre  + ", " + estado + ", " + nota + ", " + cursada + ", " + tipo;
                // asignaturas << asignatura;
                if(dialogo){
                    ta << nombre;
                }else{
                    ta << asignatura ;
                }
            }
        }
        xml.readNext();
    }
    return ta;
}


void testModificar(const QString &archivo, const QString &rutaDestino){
    QFile archivox(archivo);
    if (!archivox.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "No se pudo abrir el archivo XML.";
    }else{
        qDebug() << "se pudo abrir el archivo XML.";
    }
    qDebug() <<"Ruta destino";
    QFile archivoW(rutaDestino);
    if (!archivoW.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "No se pudo abrir el archivo XML.";
    }else{
        qDebug() << "se pudo abrir el archivo XML.";
    }

    QXmlStreamReader xmlReader(&archivox);
    QXmlStreamWriter xmlWriter(&archivoW);

}


void verificarPermisos(const QString &fileName) {
    qDebug() << "Verificando permisos";
    QFile file(fileName);
    if (!file.exists()) {
        qDebug() << "El archivo no existe.";
        return;
    }else{
        qDebug() <<"El arhcivo existe";
    }
    qDebug() << "Probando de abrir";
    if (!file.open(QFile::ReadOnly  | QFile::Text)) {
        qDebug() << "No se pudo abrir el archivo para lectura";
        qDebug() << "Motivo:" << file.errorString();
        return;
    }else{
        qDebug() << "Se pudo abrir el archivo para lectura.";
        file.close();
    }
    if (!file.open(QFile::ReadWrite  | QFile::Text)) {
        qDebug() << "No se pudo abrir el archivo para escritura";
        qDebug() << "Motivo:" << file.errorString();
        return;
    }else{
        qDebug() << "Se pudo abrir el archivo para escritura.";
        file.close();
    }

    // La aplicación tiene permisos suficientes para leer y escribir en el archivo
    qDebug() << "La aplicación tiene permisos suficientes para leer y escribir en el archivo.";
}



bool modificarXML(const QString &archivoOriginal, const QString &nombreA, const QString &hijo_modificar, const QString &parametro) {
    qDebug() << "HERE";
    QDomDocument xmlDocument;
    QFile file(archivoOriginal);
    if (!file.open(QFile::ReadOnly) ) {
        qDebug() << "Error al abrir el archivo XML";
        qDebug() << file.errorString();
        return false;
    }else{
        qDebug() << "ABierto";
    }
    if(!xmlDocument.setContent(&file)){
        qDebug() << "Error en la funcion setcontent";
    }else{
        qDebug() << "Error en la funcion setcontent";

    }
    file.close();

    // Obtener la raíz del documento
    QDomElement root = xmlDocument.documentElement();

    // Obtener todas las asignaturas
    QDomNodeList asignaturas = root.elementsByTagName("ASIGNATURA");

    // Iterar sobre las asignaturas
    for (int i = 0; i < asignaturas.size(); ++i) {
        QDomElement asignatura = asignaturas.at(i).toElement();
        QString nombre = asignatura.elementsByTagName("NOMBRE").at(0).toElement().text();

        // Si el nombre coincide, cambiar el estado a "Cursando"
        if (nombre == nombreA) {
            QDomElement hijo = asignatura.elementsByTagName(hijo_modificar).at(0).toElement();
            hijo.firstChild().setNodeValue(parametro);
            if(hijo_modificar == "ESTADO"){//Cambia el estado a Cursando
                qDebug() << "Cambia el estado a Cursando";
                QDomElement hijo2 = asignatura.elementsByTagName("CURSADA").at(0).toElement();
                hijo2.firstChild().setNodeValue("SI");
            }else if(hijo_modificar == "NOTA"){
                QDomElement hijo2 = asignatura.elementsByTagName("ESTADO").at(0).toElement();
                hijo2.firstChild().setNodeValue("Completa");
                QDomElement hijo3 = asignatura.elementsByTagName("CURSADA").at(0).toElement();
                hijo3.firstChild().setNodeValue("SI");
            }
        }
    }

    // Guardar los cambios en el archivo XML
    if (!file.open(QFile::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Error al abrir el archivo XML para escritura";
        return false;
    }

    QTextStream out(&file);
    xmlDocument.save(out, 4);
    qDebug() << "Fichero modidificado correctamente";
    file.close();
    return true;
}
