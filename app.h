/*
    Copyright (C) 2012, University of Cambridge, Department of Psychiatry.
    Created by Rudolf Cardinal (rnc1001@cam.ac.uk).

    This file is part of CamCOPS.

    CamCOPS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    CamCOPS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with CamCOPS. If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once
#include <QApplication>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QWidget>

struct TextConfig {
public:
    TextConfig(int font_size_px,
               const QColor& colour,
               int width = -1,
               Qt::Alignment alignment = Qt::AlignCenter);
    TextConfig& setFontSize(int font_size_px);
    TextConfig& setColour(const QColor& colour);
    TextConfig& setWidth(int width);
    TextConfig& setAlignment(Qt::Alignment alignment);
public:
    int font_size_px;
    QColor colour;
    int width;
    Qt::Alignment alignment;
};


class App : public QApplication
{
    Q_OBJECT

public:
    App(int& argc, char* argv[]);
    int run();
    QWidget* makeGraphicsWidget(
        QGraphicsScene* scene,
        const QColor& background_colour
    );
    void setWidgetAsOnlyContents(QWidget* graphics_widget,
                                 QWidget* graphics_view,
                                 const int margin);
    QRectF centredRect(const QPointF& centre, const qreal w, const qreal h);
    QGraphicsRectItem* makeObscuringRect(QGraphicsScene* scene,
                                         const QRectF& rect,
                                         const qreal opacity = 0.5,
                                         const QColor& colour_ignoring_opacity = QColor(0, 0, 0));
    void makeText(QGraphicsScene* scene,  // text is added to scene
                  const QPointF& pos,
                  const TextConfig& config,
                  const QString& text,
                  QFont font = QFont(),
                  QWidget* parent = nullptr);
    QString labelCss(const QColor& colour);
    QString colourCss(const QColor& colour);
    void alignRect(QRectF& rect, const Qt::Alignment alignment);
};
