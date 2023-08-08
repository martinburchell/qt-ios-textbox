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
const QPointF SCENE_CENTRE(SCENE_WIDTH * 0.5, SCENE_HEIGHT * 0.5);
const QRectF SCENE_RECT(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
const int TEXT_SIZE_PX = 20;


App::App(int& argc, char* argv[]) :
    QApplication(argc, argv){
}


int App::run()
{
    auto scene = new QGraphicsScene(SCENE_RECT);
    scene->setBackgroundBrush(QBrush(QColor(0, 0, 0)));
    auto graphics_widget = makeGraphicsWidget(scene, QColor(0, 0, 0));

    makeText(scene, QPointF(0,0), "Correct");

    auto main_window = new QMainWindow();
    main_window->setCentralWidget(graphics_widget);
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
    QLayout* l = graphics_widget->layout();
    delete l;

    auto vl = new QVBoxLayout(graphics_widget);
    graphics_widget->setLayout(vl);
    vl->setContentsMargins(margin, margin, margin, margin);
    vl->addWidget(graphics_view);
}



void App::makeText(QGraphicsScene* scene,  // text is added to scene
                   const QPointF& pos,
                   const QString& text,
                   QFont font,
                   QWidget* parent)
{
    Q_ASSERT(scene);

    auto label = new QLabel(text, parent);
    font.setPixelSize(TEXT_SIZE_PX);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    QRectF rect(pos, QSizeF());
    const int width = static_cast<int>(SCENE_WIDTH);
    const int height = label->heightForWidth(width);
    rect.setSize(QSizeF(width, height));

    // alignRect(rect);

    auto proxy = scene->addWidget(label);
    proxy->setGeometry(rect);
}

void App::alignRect(QRectF& rect)
{
    qreal dx = -rect.width() / 2;
    qreal dy = -rect.height() / 2;

    rect.translate(dx, dy);
}
