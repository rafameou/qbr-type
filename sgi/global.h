
/*
 * Eu sei que usar global é errado, mas vai ficar assim
 * https://www.learncpp.com/cpp-tutorial/why-non-const-global-variables-are-evil/
 * Atenciosamente,
 * Rafael Mazzutti.
 *
*/


#ifndef GLOBAL_H
#define GLOBAL_H

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QVector4D>
#include <QMatrix4x4>
#include <QObject>
#include <QWidget>
#include <QFrame>
#include <QPainter>
#include <QKeyEvent>
#include <QThread>

#include <iostream>
#include <stdlib.h>
#include <math.h>

class Global {
public:
    QMatrix4x4 viewport;
    QPainter* painter;
    float xwMin, xwMax, ywMin, ywMax; //window
    float xvpMin, xvpMax, yvpMin, yvpMax; //viewport
    bool pause = false;
    bool firing = false;
};

extern Global g;

#endif // GLOBAL_H
