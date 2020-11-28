#ifndef C_IMAGE_H
#define C_IMAGE_H
#include <string>
#include <vector>
#include <QFileDialog>
#include<QVector>
using namespace std;
class Imagen_
{
private:
    QImage image_;
    QString tags;
    QString title;
    QString path;
    friend class DoubleLinkedList;
public:
    Imagen_(QImage,QString, QString,QString);
    Imagen_();
    QImage image() const;
    void setImage(const QImage &image);
    QString getTitle() const;
    void setTitle(const QString &value);
    QString getTags() const;
    void setTags(const QString &value);
    QString getPath() const;
    void setPath(const QString &value);
};

#endif // C_IMAGE_H
