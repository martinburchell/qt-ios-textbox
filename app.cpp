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
    // auto scene = new QGraphicsScene(SCENE_RECT);
    // scene->setBackgroundBrush(QBrush(QColor(0, 0, 0)));
    // auto graphics_widget = makeGraphicsWidget(scene, QColor(0, 0, 0));
    // Q_UNUSED(graphics_widget)

    auto label = new QLabel("Correct");

    auto font = QFont();
    font.setPixelSize(20);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    // scene->addWidget(label);

    auto main_window = new QMainWindow();

    auto widget = new QWidget();
    auto vl = new QVBoxLayout(widget);
    widget->setLayout(vl);
    vl->addWidget(label);

    main_window->setCentralWidget(widget);
    main_window->showMaximized();

    return exec();
}


QWidget* App::makeGraphicsWidget(
        QGraphicsScene* scene,
        const QColor& background_colour)
{
    auto graphics_view = new QGraphicsView(scene);
    graphics_view->setBackgroundBrush(QBrush(background_colour, Qt::SolidPattern));
    auto graphics_widget = new QWidget();
    setWidgetAsOnlyContents(graphics_widget, graphics_view, 0);

    return graphics_widget;
}


void App::setWidgetAsOnlyContents(QWidget* graphics_widget,
                                  QWidget* graphics_view,
                                  const int margin)
{
    Q_UNUSED(margin)

    QLayout* l = graphics_widget->layout();
    delete l;

    auto vl = new QVBoxLayout(graphics_widget);
    graphics_widget->setLayout(vl);
    vl->addWidget(graphics_view);
}
