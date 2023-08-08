#include "app.h"

#include <QApplication>
#include <QBrush>
#include <QColor>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLayout>
#include <QMainWindow>
#include <QPen>
#include <QPointF>
#include <QRectF>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <QFont>
#include <QLabel>

const qreal SCENE_WIDTH = 1000;
const qreal SCENE_HEIGHT = 750;  // 4:3 aspect ratio
const QRectF SCENE_RECT(0, 0, SCENE_WIDTH, SCENE_HEIGHT);


App::App(int& argc, char* argv[]) :
    QApplication(argc, argv){
}


int App::run()
{
    auto scene = new QGraphicsScene(SCENE_RECT);

    auto graphics_view = new QGraphicsView(scene);
    auto graphics_widget = new QWidget();

    QLayout* l = graphics_widget->layout();
    delete l;

    auto vl = new QVBoxLayout(graphics_widget);
    graphics_widget->setLayout(vl);
    vl->addWidget(graphics_view);

    auto label = new QLabel("Correct");

    auto font = QFont();
    font.setPixelSize(20);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    scene->addWidget(label);

    auto main_window = new QMainWindow();

    main_window->setCentralWidget(graphics_widget);
    main_window->showMaximized();

    return exec();
}
