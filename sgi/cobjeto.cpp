#include "cobjeto.h"

CObjeto::CObjeto(QString nome, Tipo tipo, QVector3D posicao, QVector3D tamanho)
{
    this->nome = nome;
    this->tipo = tipo;
    this->posicao = posicao;
    this->tamanho = tamanho;
    this->criarObjeto();
}

void CObjeto::setNome(QString nome)
{
    this->nome = nome;
}

QMatrix4x4 CObjeto::getMTrans()
{
    QMatrix4x4 matrizTrans;
    matrizTrans.setToIdentity();
    matrizTrans(0, 3) = novaPos.x();
    matrizTrans(1, 3) = novaPos.y();
    matrizTrans(2, 3) = novaPos.z();
    return matrizTrans;
}

QMatrix4x4 CObjeto::getMatrizDeTransformacao()
{
    return g.viewport * getMTrans();
}

QVector4D CObjeto::getPontos0()
{
    return this->listaDePontos[0];
}

void CObjeto::atualizarPontos()
{
    this->listaDePontos.clear();
    for (QVector4D lPO : this->copialDP)
    {
        QVector4D ponto = lPO;
        ponto = getMatrizDeTransformacao() * ponto;
        this->listaDePontos.push_back(ponto);
    }
}

void CObjeto::sP(QVector4D ponto)
{
    this->copialDP.push_back(ponto); //Copia lista de pontos
}

void CObjeto::translate(float x, float y, float z)
{
    this->novaPos += QVector3D(x, y, z);
    atualizarPontos();
}

void CObjeto::criarObjeto(){
    switch (this->tipo){
    case NA:
    default:
        break;
    case QUADRADO:
        this->sP(QVector4D(this->posicao.x(),
                           this->posicao.y(),
                           this->posicao.z(),
                           1.f));
        this->sP(QVector4D(this->posicao.x()+this->tamanho.x(),
                           this->posicao.y(),
                           this->posicao.z(), 1.f));
        this->sP(QVector4D(this->posicao.x()+this->tamanho.x(),
                           this->posicao.y()+this->tamanho.y(),
                           this->posicao.z(), 1.f));
        this->sP(QVector4D(this->posicao.x(),
                           this->posicao.y()+this->tamanho.y(),
                           this->posicao.z(), 1.f));
        break;
    case TRIANGULO:
        this->sP(QVector4D(this->posicao.x(),
                           this->posicao.y() + this->tamanho.y(),
                           this->posicao.z(),
                           1.f));
        this->sP(QVector4D(this->posicao.x()+(this->tamanho.x()/2),
                           this->posicao.y(),
                           this->posicao.z(), 1.f));
        this->sP(QVector4D(this->posicao.x()+this->tamanho.x(),
                           this->posicao.y()+this->tamanho.y(),
                           this->posicao.z(), 1.f));
        break;
    case RETA:
        this->sP(QVector4D(this->posicao.x(),
                           this->posicao.y() + this->tamanho.y(),
                           this->posicao.z(),
                           1.f));
        this->sP(QVector4D(this->posicao.x() + this->tamanho.x(),
                           this->posicao.y() + this->tamanho.y(),
                           this->posicao.z(),
                           1.f));
        break;
    case TEXTO:
        this->sP(QVector4D(this->posicao.x(),
                           this->posicao.y(),
                           this->posicao.z(),
                           1.f));
    }
    this->atualizarPontos();
}

void CObjeto::desenhar()
{
    if (this->tipo == TEXTO)
    {
        g.painter->drawText(QRectF(this->listaDePontos[0].x(), this->listaDePontos[0].y(), INT_MAX, INT_MAX), this->nome);
    }
    else
    {
        int vish = this->listaDePontos.size();
        for (int i = 0; i < vish; i++)
        {
            QVector4D q0 = this->listaDePontos[i], q1 = this->listaDePontos[(i+1)%vish];
            g.painter->drawLine(QLineF(q0.toPointF(), q1.toPointF()));
        }
    }
}
