/*
*   Copyright (C) 2019-2020  Wei Lisi (Willis) <weilisi16@gmail.com>
*	This file is part of ChaosTranslate
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "QColorPicker.h"
#include <QColorDialog>

QColorPicker::QColorPicker(QWidget* parent)
{
    //connect(this, SIGNAL(clicked()), this, SLOT(changeColor()));
}

void QColorPicker::updateColor()
{
    setStyleSheet("background-color: " + color.name());
}

void QColorPicker::changeColor()
{
    QColor newColor = QColorDialog::getColor(color, parentWidget());
    if (newColor != color)
    {
        setColor(newColor);
    }
}

void QColorPicker::setColor(const QColor& color)
{
    this->color = color;
    updateColor();
}

const QColor& QColorPicker::getColor()
{
    return color;
}