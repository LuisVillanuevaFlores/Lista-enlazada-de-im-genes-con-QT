#include "Imagen_.h"

QImage Imagen_::image() const
{
    return image_;
}

void Imagen_::setImage(const QImage &image)
{
    image_ = image;
}

QString Imagen_::getTitle() const
{
    return title;
}

void Imagen_::setTitle(const QString &value)
{
    title = value;
}

QString Imagen_::getTags() const
{
    return tags;
}

void Imagen_::setTags(const QString &value)
{
    tags = value;
}

Imagen_::Imagen_(){
    title="No declarado";
    tags="Vacio";
}
QString Imagen_::getPath() const
{
    return path;
}

void Imagen_::setPath(const QString &value)
{
    path = value;
}

Imagen_::Imagen_(QImage image,QString title, QString tags,QString path):
    image_(image),tags(tags),title(title),path(path){


}
