#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QRegularExpression>
#include <QMimeData>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openButton_clicked()
{
    QRegularExpression rx("[.!?;:, ]");
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getOpenFileName(this, "Import txt file", "../Lab11", "*.txt");
    QFile inputFile(fname);
    QTextStream out(stdout);
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine().toLower();
          QStringList list = line.split(rx, Qt::SkipEmptyParts);

          QStringList four;
          for(QString a : list)
          {
            if (a.length() == 4)
            {
                four.append(a);
            }
          }
          four.removeDuplicates();
          ui->listWidget->addItems(four);
       }

       inputFile.close();
    }
}


void MainWindow::on_sortButton_clicked()
{
    QList<QString> items;
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        items.append(ui->listWidget->item(i)->text());
    }
    ui->listWidget->clear();
    QStringList items_sl(items);
    items_sl.sort(Qt::CaseInsensitive);
    items_sl.removeDuplicates();
    ui->listWidget->addItems(items_sl);
}


void MainWindow::on_clrButton_clicked()
{
    ui->listWidget->clear();
}

void MainWindow::on_exportButton_clicked()
{
    QFileDialog dialog = QFileDialog();
    QString fname = dialog.getSaveFileName(this, "Save txt file", "../Lab11/out", "*.txt");
    QFile outputFile(fname);
    QList<QString> items;
    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        items.append(ui->listWidget->item(i)->text());
    }
    if (outputFile.open(QIODevice::WriteOnly))
    {
       QTextStream out(&outputFile);
       for (auto s : items)
       {
           out << s << "\n";
       }
    }
}
