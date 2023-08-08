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
const qreal FEEDBACK_OPACITY = 0.75;
const int TEXT_SIZE_PX = 20;  // will be scaled
const TextConfig BASE_TEXT_CONFIG(TEXT_SIZE_PX, QColor(255, 255, 255),
                                  static_cast<int>(SCENE_WIDTH), Qt::AlignCenter);

TextConfig::TextConfig(int font_size_px,
                       const QColor& colour,
                       const int width,
                       const Qt::Alignment alignment) :
    font_size_px(font_size_px),
    colour(colour),
    width(width),
    alignment(alignment)
{
}

App::App(int& argc, char* argv[]) :
    QApplication(argc, argv){
}


int App::run()
{
    auto scene = new QGraphicsScene(SCENE_RECT);
    scene->setBackgroundBrush(QBrush(QColor(0, 0, 0)));
    auto graphics_widget = makeGraphicsWidget(scene, QColor(0, 0, 0));

    const QString& text = "Correct";
    const QColor& colour = QColor(0, 128, 0);
    makeObscuringRect(scene, SCENE_RECT, FEEDBACK_OPACITY, colour);

    auto answer_backdrop_rect = centredRect(SCENE_CENTRE,
                                            0.3 * SCENE_WIDTH,
                                            0.1 * SCENE_HEIGHT);

    scene->addRect(answer_backdrop_rect, QPen(Qt::NoPen), QBrush(colour));
    makeText(scene, SCENE_CENTRE, BASE_TEXT_CONFIG, text);

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



QRectF App::centredRect(const QPointF& centre, const qreal w, const qreal h)
{
    return QRectF(centre.x() - w / 2.0, centre.y() - h / 2.0, w, h);
}


QGraphicsRectItem* App::makeObscuringRect(QGraphicsScene* scene,
                                          const QRectF& rect, const qreal opacity,
                                          const QColor& colour_ignoring_opacity)
{
    const QPen pen(Qt::NoPen);
    QColor colour(colour_ignoring_opacity);
    const int alpha = qBound(0, qRound(qBound(0.0, opacity, 1.0) * 255), 255);
    colour.setAlpha(alpha);
    const QBrush brush(colour);
    return scene->addRect(rect, pen, brush);
}

void App::makeText(QGraphicsScene* scene,  // text is added to scene
                            const QPointF& pos,
                            const TextConfig& config,
                            const QString& text,
                            QFont font,
                            QWidget* parent)
{
    Q_ASSERT(scene);
    QString css = labelCss(config.colour);

    auto label = new QLabel(text, parent);
    label->setStyleSheet(css);
    font.setPixelSize(config.font_size_px);
    label->setFont(font);
    label->setOpenExternalLinks(false);
    label->setTextInteractionFlags(Qt::NoTextInteraction);
    label->setAlignment(config.alignment);  // alignment WITHIN label

    QRectF rect(pos, QSizeF());
    if (config.width == -1) {
        label->setWordWrap(false);
        rect.setSize(label->size());
    } else {
        // word wrap
        label->setWordWrap(true);
        rect.setSize(QSizeF(config.width,
                            label->heightForWidth(config.width)));
    }

    // Now fix alignment of WHOLE object
    alignRect(rect, config.alignment);

    auto proxy = scene->addWidget(label);
    proxy->setGeometry(rect);
}

QString App::labelCss(const QColor& colour)
{
    return QString("background-color: rgba(0,0,0,0);"  // transparent
                   "border: 0;"
                   "color: %1;"
                   "margin: 0;"
                   "padding: 0;")
            .arg(colourCss(colour));
}

QString App::colourCss(const QColor& colour)
{
    return QString("rgba(%1,%2,%3,%4)")
            .arg(colour.red())
            .arg(colour.green())
            .arg(colour.blue())
            .arg(colour.alpha());
}

void App::alignRect(QRectF& rect, const Qt::Alignment alignment)
{
    // Horizontal
    qreal dx = 0;
    if (alignment & Qt::AlignLeft ||
            alignment & Qt::AlignJustify ||
            alignment & Qt::AlignAbsolute) {
        dx = 0;
    } else if (alignment & Qt::AlignHCenter) {
        dx = -rect.width() / 2;
    } else if (alignment & Qt::AlignRight) {
        dx = -rect.width();
    } else {
        qWarning() << Q_FUNC_INFO << "Unknown horizontal alignment";
    }

    // Vertical
    qreal dy = 0;
    if (alignment & Qt::AlignTop) {
        dy = 0;
    } else if (alignment & Qt::AlignVCenter) {
        dy = -rect.height() / 2;
    } else if (alignment & Qt::AlignBottom ||
               alignment & Qt::AlignBaseline) {
        dy = -rect.height();
    } else {
        qWarning() << Q_FUNC_INFO << "Unknown horizontal alignment";
    }

    rect.translate(dx, dy);
}
