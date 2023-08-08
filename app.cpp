#include "app.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMainWindow>
#include <QRectF>
#include <QVBoxLayout>
#include <QWidget>
#include <QFont>
#include <QLabel>

const qreal SCENE_WIDTH = 800;
const qreal SCENE_HEIGHT = 600;
const QRectF SCENE_RECT(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
const int TEXT_SIZE_PT = 20;

App::App(int& argc, char* argv[]) :
    QApplication(argc, argv){
}


int App::run()
{
    auto scene = new QGraphicsScene(SCENE_RECT);

    auto graphics_view = new QGraphicsView(scene);
    auto graphics_widget = new QWidget();

    delete graphics_widget->layout();

    auto layout = new QVBoxLayout();
    graphics_widget->setLayout(layout);
    layout->addWidget(graphics_view);

    auto label = new QLabel("Testing...");

    auto font = QFont();
    font.setPointSize(TEXT_SIZE_PT);
    label->setFont(font);

    scene->addWidget(label);

    auto main_window = new QMainWindow();

    main_window->setCentralWidget(graphics_widget);
    main_window->showMaximized();

    return exec();
}
