#ifndef COBJETO_H
#define COBJETO_H

#include "global.h"

#define TOPLEFT 9       //1001
#define TOP 8           //1000
#define TOPRIGHT 10     //1010

#define LEFT 1          //0001
#define INSIDE 0        //0000
#define RIGHT 2         //0010

#define BOTTOMLEFT 5    //0101
#define BOTTOM 4        //0100
#define BOTTOMRIGHT 6   //0110

enum Tipo{
    NA = 0,
    QUADRADO,
    RETA,
    TRIANGULO,
    TEXTO
};

class CObjeto
{
private:
    QList<QVector4D> listaDePontos;
    QList<QVector4D> copialDP;
    QVector3D posicao;
    QVector3D tamanho;
    QVector3D novaPos;
    QString nome;
    Tipo tipo;
public:
    CObjeto(QString nome, Tipo tipo, QVector3D posicao, QVector3D tamanho);
    void setNome(QString nome);
    QMatrix4x4 getMTrans();
    QMatrix4x4 getMatrizDeTransformacao();
    QVector4D getPontos0();
    void atualizarPontos();

    void sP(QVector4D ponto);
    void translate(float x = 0.f, float y = 0.f, float z = 0.f);

    void criarObjeto();
    void desenhar();
};

#endif // COBJETO_H
