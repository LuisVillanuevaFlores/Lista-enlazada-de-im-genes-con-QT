#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    list = new DoubleLinkedList(30);
    current_image=list->begin();
    ui->btn_confirm->setVisible(false);
    update_image();
    update_data();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_add_clicked(){
    QString ubication=QFileDialog::getOpenFileName(this,tr("Escoger"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *..gif)"));
    if(QString::compare(ubication,QString())!=0){
        QPixmap image;
        bool valid =image.load(ubication);
        if(valid){
            ui->btn_add->setVisible(false);
            ui->btn_confirm->setVisible(true);
            update_image();
            ui->lbl_image->setPixmap(image);
            ui->txtName->setText("");
            ui->txtTags->setText("");
            ui->lbl_path->setText(ubication);
            msgBox.setText("Llene los campos necesarios y confirme");
            msgBox.exec();
        }
        else{
            msgBox.setText("No se puedo cargar la imagen");
            msgBox.exec();
        }

    }
}

void MainWindow::on_btn_search_clicked()
{
    if(verify_insertion())return;
    if(list->search(ui->txt_search->text(),current_image)>0){
        msgBox.setText("Imagen Encontrada");
        msgBox.exec();
        update_image();
        update_data();

    }
    else{
        msgBox.setText("No se encontro la imagen");
        msgBox.exec();
    }

}

void MainWindow::on_btn_delete_clicked()
{
    if(verify_insertion())return;
    DoubleLinkedList::iterator temp=current_image;
    int option;
    if(current_image.getPNode()==nullptr)
        option=0;
    else
    {
        ++current_image;
        option=list->deleteN(temp);
    }
    switch (option){
        case 0:
            current_image=nullptr;
            msgBox.setText("Lista vacia");
            msgBox.exec();
        break;
        case 1:
            msgBox.setText("Primera imagen eliminada ");
            msgBox.exec();
        break;
        case 2:
            msgBox.setText("Ultima imagen correctamente");
            msgBox.exec();
        break;
        case 3:
            msgBox.setText("Imagen eliminada correctamente");
            msgBox.exec();
        break;
    }
    update_data();
    update_image();

}

void MainWindow::on_btn_edit_clicked()
{
/*
    QPixmap pixmap = QPixmap (":/images/add.png");
    Imagen_ i(pixmap.toImage(),"d","d");
    list->push_back(i);
    Imagen_ i1(pixmap.toImage(),"b","b");
    list->push_back(i1);
    Imagen_ i2(pixmap.toImage(),"f","f");
    list->push_back(i2);
    Imagen_ i3(pixmap.toImage(),"a","a");
    list->push_back(i3);
    Imagen_ i4(pixmap.toImage(),"c","c");
    list->push_back(i4);
    Imagen_ i5(pixmap.toImage(),"e","e");
    list->push_back(i5);
    Imagen_ i6(pixmap.toImage(),"g","g");
    list->push_back(i6);
    current_image=list->end();
    update_data();update_image();
    list->showVector();*/

    if(verify_insertion())return;
    if(current_image.getPNode()==nullptr)
    {
        msgBox.setText("Lista vacia");
        msgBox.exec();
        return;
    }
    QString title = ui->txtName->text();
    QString txt_tags=ui->txtTags->text();
    QString path=ui->lbl_path->text();
    Imagen_ image((*current_image).image(),title,txt_tags,path);
    current_image.getPNode()->setDato(image);
    msgBox.setText("Actualizacion correcta");
    msgBox.exec();
}

void MainWindow::on_btn_n_clicked()
{
    if(verify_insertion())return;
    if(list->fsize()==0||list->fsize()==1)
    {
        msgBox.setText("No hay imagenes");
        msgBox.exec();
        return;
    }
    ++current_image;
    update_image();
    update_data();
}

void MainWindow::on_btn_p_clicked()
{
    if(verify_insertion())return;
    if(list->fsize()==0||list->fsize()==1)
    {
        msgBox.setText("No hay imagenes");
        msgBox.exec();
        return;
    }
    --current_image;
    update_image();
    update_data();
}

void MainWindow::update_image()
{
    if(current_image.getPNode()==nullptr)
    {
        QPixmap pixmap = QPixmap (":/images/default.png");
        ui->lbl_image->setPixmap(pixmap);
        return;
    }
    ui->lbl_image->setPixmap(QPixmap::fromImage((*current_image).image()));

}

void MainWindow::update_data()
{
    if(current_image.getPNode()==nullptr)
    {
        ui->txtName->setText("");
        ui->txtTags->setText("");
        return;
    }
    ui->txtName->setText((*current_image).getTitle());
    ui->txtTags->setText((*current_image).getTags());
    ui->lbl_path->setText((*current_image).getPath());
    QString width=QString::number((*current_image).image().width());
    QString height=QString::number((*current_image).image().height());
    ui->lbl_width->setText(width);
    ui->lbl_height->setText(height);
}

void MainWindow::on_btn_confirm_clicked(){
    DoubleLinkedList::iterator temp;
    int case_=list->search(ui->txtName->text(),temp);
    if(case_>0){
        msgBox.setText("Nombre ya ingresado,intente otra vez");
        msgBox.exec();
        if(verify_insertion())return;
    }
    else if(case_==-2){
        msgBox.setText("Excedio el limite,intente con otro nombre");
        msgBox.exec();
        return;
    }
    QPixmap image= *(ui->lbl_image->pixmap());
    QString title = ui->txtName->text();
    QString txt_tags=ui->txtTags->text();
    QString path=ui->lbl_path->text();
    Imagen_ image_(image.toImage(),title,txt_tags,path);
    list->push_back(image_);
    list->updateFile(image_);
    current_image=list->end();
    ui->btn_add->setVisible(true);
    ui->btn_confirm->setVisible(false);
    update_data();
    update_image();
    msgBox.setText("Imagen insertada correctamente");
    msgBox.exec();
}

bool MainWindow::verify_insertion()
{
    if(ui->btn_confirm->isVisible()){
        ui->btn_confirm->setVisible(false);
        ui->btn_add->setVisible(true);
        msgBox.setText("Se cancelo la insercion");
        msgBox.exec();
        update_data();
        update_image();
        return true;
    }
    return false;
}



