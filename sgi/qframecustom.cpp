#include "qframecustom.h"

/* * * * * * * * * * * * * * *
 * Inicializar variaveis     *
 * * * * * * * * * * * * * * */
QFrameCustom::QFrameCustom(QWidget *parent)
    : QFrame{parent}
{
    this->timerId = startTimer(10);
    srand(time(0));
    this->nivel = 0;
    this->nivel_backup = -1;
    this->prioridade = -1;
    this->erros = -1;
    this->pontos = 0;
}

/* * * * * * * * * * * * * * * * * *
 * timer que reinicia o paintevent *
 * * * * * * * * * * * * * * * * * */
void QFrameCustom::timerEvent(QTimerEvent *event)
{
    if (!g.pause)
        update();
}

/* * * * * * * * * * * * * * * * * * *
 * quando usuario preciona uma tecla *
 * * * * * * * * * * * * * * * * * * */
void QFrameCustom::keyPressEvent(QKeyEvent *ev)
{
    //qInfo() << ev->text();
    if (ev->key() == Qt::Key_Space)
    {
        g.pause = !g.pause;
        return;
    }

    if (g.pause) return;

    g.firing = true;
    for (int i = 3; i < this->listaDePalavras.size(); i++)
    {
        if (prioridade != -1 && prioridade != i) continue;
        if (this->listaDePalavras[i][0] == ev->text())
        {
            if (this->displayFile[i].getPontos0().y() < 0) //ignorar items fora da janela
                continue;
            this->listaDePalavras[i].remove(0, 1);
            this->prioridade = i;
            this->pontos += 1;
        }
        else if (prioridade == i)
        {
            this->erros += 1;
            this->pontos -= 1;
        }

        if (this->listaDePalavras[i].isEmpty())
        {
            this->listaDePalavras.removeAt(i);
            this->displayFile.removeAt(i);
            this->prioridade = -1;
            this->pontos += 2;
        }
    }
}

/* * * * * * * * * * * * * * * * * * *
 * quando usuario solta uma tecla    *
 * * * * * * * * * * * * * * * * * * */
void QFrameCustom::keyReleaseEvent(QKeyEvent *ev)
{
    //qInfo() << ev->text();
    //this->displayFile[1].translate(0.f, g.ywMax);
    g.firing = false;
}

//https://stackoverflow.com/a/686376
float randomfloat(float a, float b)
{
    return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

int randomint(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

bool init = false;
void QFrameCustom::novoNivel()
{
    if (this->listaDePalavras.size() > 3)
        return;

    if (this->nivel_backup == -1)
    {
        this->nivel_backup = this->nivel;
        this->nivel = -1;
    }
    else if (this->nivel_backup == -2)
    {
        this->nivel_backup = -1;
    }

    //this->setWindowTitle(QString("Nivel " + this->nivel));

    this->listaDePalavras.clear();

    /* * * * * * * * * * * * * * * * * * * * *
     *                                       *
     * Não mexer, equivale ao player, tiros  *
     * e statusbar respectivamente           *
     *                                       *
     * * * * * * * * * * * * * * * * * * * * */
    this->listaDePalavras.push_back("player");
    this->listaDePalavras.push_back("tiros");
    this->listaDePalavras.push_back("helper");

    auto cfacil = [&](int qnts)
    {
        for (int i = 0; i < qnts; i++)
            this->listaDePalavras.push_back(facil[randomint(0, 200-1)]);
    };

    auto cmedio = [&](int qnts)
    {
        for (int i = 0; i < qnts; i++)
            this->listaDePalavras.push_back(medio[randomint(0, 150-1)]);
    };

    auto chard = [&](int qnts)
    {
        for (int i = 0; i < qnts; i++)
            this->listaDePalavras.push_back(hard[randomint(0, 200-1)]);
    };

    switch (this->nivel)
    {
    case -1:
        if (this->erros == -5)
        {
            this->listaDePalavras.push_back("voce");
            this->listaDePalavras.push_back("perdeu");
        }
        if (this->erros == 0 && this->erros != -1)
            this->listaDePalavras.push_back("parabens");

        if (this->nivel_backup == 0 && this->erros != -5)
        {
            this->listaDePalavras.push_back("digite");
            this->listaDePalavras.push_back("para");
            this->listaDePalavras.push_back("atirar");
        }
        else
        {
            this->listaDePalavras.push_back("nivel");
            this->listaDePalavras.push_back(QString::number(this->nivel_backup+1));
            if ((this->nivel_backup+1) % 5 == 0)
            {
                this->listaDePalavras.push_back("chefao");
            }
        }
        this->nivel = this->nivel_backup + 1;
        this->nivel_backup = -2;
        this->erros = 0;
        break;
    case 1:
        cfacil(randomint(3, 5));
        break;
    case 2:
        cmedio(randomint(2, 4));
        break;
    case 3:
        chard(randomint(1, 3));
        break;
    default:
        if (this->nivel % 5 == 0)
        {
            for(int i = 0; i < this->nivel*2; i++)
                this->listaDePalavras.push_back(QString(WTF[randomint(0, 20)][i]));

            for (int i  = 0; i < (this->nivel / 5); i++)
                this->listaDePalavras.push_back(WTF[randomint(0, 20)]);
        }
        else
        {
            for(int i = 0; i < randomint(0, this->nivel); i++)
                this->listaDePalavras.push_back(QString(WTF[randomint(0, 20)][i]));

            cfacil(randomint(1, this->nivel/2));
            cmedio(randomint(1, this->nivel/2));
            chard(randomint(1, this->nivel/4));
        }
        break;
    }

    init = false;
}

void QFrameCustom::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    //QPainter painter(this);
    g.painter = new QPainter(this);

    if (!init)
    {
        /* * * * * * * * * * * * * * *
         * Dropar displayfile antigo *
         * * * * * * * * * * * * * * */
        this->displayFile.clear();

        /* * * * * * * * * *
         * Tamanho window  *
         * * * * * * * * * */
        g.xwMin = 0.f;
        g.xwMax = 100.f;
        g.ywMin = 0.f;
        g.ywMax = 100.f;

        /* * * * * * * * * * *
         * Tamanho viewport  *
         * * * * * * * * * * */
        g.xvpMin = 0.f;
        g.xvpMax = this->width();
        g.yvpMin = 0.f;
        g.yvpMax = this->height();

        g.viewport.setToIdentity();
        g.viewport(0, 0) = (g.xvpMax - g.xvpMin) / (g.xwMax - g.xwMin);
        g.viewport(3, 0) = -g.xwMin * (g.xvpMax - g.xvpMin) / (g.xwMax - g.xwMin) + g.xvpMin;
        g.viewport(1, 1) = (g.yvpMax - g.yvpMin) / (g.ywMax - g.ywMin);
        g.viewport(3, 1) = (1.f - g.ywMin / (g.ywMax - g.ywMin)) * (g.yvpMax - g.yvpMin) + g.yvpMin;
        g.viewport(2, 2) = 1.f;

        /* * * * * * * * *
         * nao funciona  *
         * * * * * * * * */
        /*QFont font = g.painter->font() ;
        font.setPointSizeF(10.f);
        QFontMetrics fontmetrics = QFontMetrics(font);
        g.painter->setFont(font);
        float fontheight = (fontmetrics.height() 10.f * 100.f) / g.yvpMax;*/

        this->displayFile.push_back(CObjeto("player", TRIANGULO, QVector3D((g.ywMax/2.f) - (5.f/2.f), (g.ywMax)-20.f, 1.f), QVector3D(5.f, 10.f, 1.f)));
        this->displayFile.push_back(CObjeto("tiros", QUADRADO, QVector3D((g.ywMax/2.f) - 0.5f, (g.ywMax)-20.f-0.5f, 1.f), QVector3D(1.f, 1.f, 1.f)));
        this->displayFile.push_back(CObjeto("Bem-Vindo", TEXTO, QVector3D(1.f, (g.ywMax)-(2.8f), 1.f), QVector3D(1.f,1.f,1.f)));

        for (int i = 3; i < this->listaDePalavras.size(); i++)
        {
            QVector3D local = QVector3D(randomfloat(-10.f, g.xwMax-(g.xwMax/10.f)), randomfloat(-(i * 10.f), -10.f), 1.f);
            if (this->nivel % 5 == 0)
            {
                local.setX(randomfloat(0, g.xwMax - (g.xwMax/4.f)));
            }
            this->displayFile.push_back(CObjeto(this->listaDePalavras[i], TEXTO, local, QVector3D(1.f,1.f,1.f)));
        }
        init = true;
    }

    g.painter->setPen(Qt::green);

    if (prioridade != -1)
    {
        if (this->displayFile[prioridade].getPontos0().x()  > this->displayFile[0].getPontos0().x())
        {
           this->displayFile[0].translate(5.f, randomfloat(-0.1f, 0.1f));
           this->displayFile[1].translate(5.f, 0.f);
        }
        if (this->displayFile[prioridade].getPontos0().x() < this->displayFile[0].getPontos0().x())
        {
           this->displayFile[0].translate(-5.f, randomfloat(-0.1f, 0.1f));
           this->displayFile[1].translate(-5.f, 0.f);
        }
    }

    this->displayFile[0].desenhar(); //Player
    if (g.firing)
        //if (this->displayFile[0].getPontos0().y() > this->displayFile[1].getPontos0().y())
            this->displayFile[1].desenhar(); //tiros

    QString temp;
    //#FIXME, deprecated
    temp.sprintf("Nivel: %d | Pontos: %d | Erros: %d | Espaço para pausar",
                 this->nivel, this->pontos, this->erros);
    this->displayFile[2].setNome(temp);
    this->displayFile[2].desenhar();

    novoNivel();
    for (int i = 3; i < this->displayFile.size(); i++)
    {
        this->displayFile[i].setNome(this->listaDePalavras[i]);
        int x = this->displayFile[i].getPontos0().x();
        int y = this->displayFile[i].getPontos0().y();

        if (y < (g.yvpMax))
        {
            this->displayFile[i].translate(0.f + randomfloat(-0.2f, 0.2f), 0.1f + randomfloat(-0.1f, 0.1f));
        }
        else
        {
            //#FIXME, se a pessoa perder na troca de nivel, o jogo quebra
            this->nivel -= 1;
            this->erros = -5;
            this->prioridade = -1;
            this->listaDePalavras.clear();
            this->pontos -= 5;
            novoNivel();
            break;
        }

        if (x < ((g.xvpMin) + randomfloat(0, 50.f)))
            this->displayFile[i].translate(0.1f, 0.f);

        if (x > ((g.xvpMax) + randomfloat(-50.f, 0)))
            this->displayFile[i].translate(-0.1f, 0.f);

        if (this->prioridade == i)
        {
            int ny = g.firing ? y : this->displayFile[0].getPontos0().y();
            if (ny < this->displayFile[1].getPontos0().y())
                this->displayFile[1].translate(0.f, -5.f);
            else if (ny > this->displayFile[1].getPontos0().y())
                this->displayFile[1].translate(0.f, 5.f);

            g.painter->setPen(Qt::red);
        }
        else
        {
            g.painter->setPen(Qt::white);
        }

        this->displayFile[i].desenhar();
    }

    delete g.painter;
}
