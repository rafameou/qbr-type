#ifndef QFRAMECUSTOM_H
#define QFRAMECUSTOM_H

#include "global.h"
#include "cobjeto.h"

class QFrameCustom : public QFrame
{
    Q_OBJECT
private:
    QList<CObjeto> displayFile;
    QList<QString> listaDePalavras;

    int timerId;
    int prioridade;
public:
    int nivel;
    int nivel_backup;
    int erros;
    int pontos;
    void novoNivel();
    QVector3D fontmetrics3d;
    explicit QFrameCustom(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *ev) override;
    void keyReleaseEvent(QKeyEvent *ev) override;
    //void mousePressEvent(QMouseEvent *event) override;
    void timerEvent(QTimerEvent *event);
signals:

};

//200
static QString facil[] = {
    "amor", "fato", "mito", "vies", "voce", "como", "caos", "esmo", "brio", "vide", "açao", "sede", "apos", "pois", "vida",
    "casa", "auge", "saga", "medo", "onus", "ermo", "suma", "vovo", "mote", "alem", "sina", "tolo", "idem", "urge", "crer",
    "pela", "apto", "zelo", "veio", "pude", "tudo", "mais", "ruim", "area", "amar", "rude", "coxo", "cota", "para", "soar",
    "ater", "sera", "fase", "ente", "auto", "tras", "doce", "voga", "logo", "onde", "deus", "rima", "pelo", "ante", "cedo",
    "jugo", "meio", "alma", "arte", "meta", "cujo", "sela", "traz", "numa", "cela", "teor", "sido", "noia", "face", "asco",
    "nojo", "alvo", "foco", "isso", "pose", "sair", "base", "vale", "odio", "agir", "teve", "alto", "todo", "ocio", "rito",
    "eita", "irao", "novo", "agil", "alva", "tese", "alta", "bojo", "nexo", "orla",
    "sagaz", "amago", "negro", "termo", "exito", "mexer", "nobre", "senso", "afeto", "algoz", "etica", "plena", "mutua",
    "tenue", "fazer", "assim", "vigor", "sutil", "aquem", "porem", "seçao", "fosse", "sanar", "poder", "audaz", "ideia",
    "cerne", "inato", "moral", "sobre", "desde", "muito", "justo", "honra", "quiça", "torpe", "sonho", "razao", "futil",
    "etnia", "icone", "anexo", "amigo", "egide", "tange", "lapso", "haver", "expor", "mutuo", "dengo", "tempo", "casal",
    "entao", "habil", "seara", "boçal", "avido", "ardil", "pesar", "saber", "causa", "graça", "dizer", "genro", "obice",
    "posse", "coser", "paria", "dever", "brado", "tenaz", "prole", "sendo", "crivo", "corja", "comum", "temor", "detem",
    "ainda", "animo", "apice", "ceder", "ansia", "estar", "pauta", "digno", "assaz", "xibiu", "culto", "mundo", "atroz",
    "fugaz", "censo", "gleba", "forte", "vicio", "vulgo", "cozer", "valha", "denso"
};

//150
static QString medio[] = {
    "exceto", "cinico", "idoneo", "ambito", "nescio", "indole", "mister", "vereda", "apogeu", "inocuo", "convem", "utopia",
    "sadico", "escopo", "enfase", "idiota", "casual", "merito", "alusao", "hostil", "anseio", "cetico", "legado", "hetero",
    "pressa", "gentil", "alheio", "nocivo", "infame", "cliche", "paixao", "eximio", "defina", "afavel", "adorno", "dadiva",
    "extase", "sobrio", "adesao", "larica", "aferir", "astuto", "tambem", "otario", "sessao", "limiar", "solene", "julgar",
    "gloria", "labaro", "formal", "empatia", "aurelio", "conjuge", "embuste", "exceçao", "carater", "efemero", "prolixo",
    "verbete", "idilico", "analogo", "genuino", "estoria", "sublime", "familia", "pesames", "inferir", "apatico", "sucinto",
    "acepçao", "redimir", "astucia", "prodigo", "cultura", "audacia", "estigma", "recesso", "virtude", "refutar", "iconico",
    "soberba", "estavel", "cinismo", "exortar", "morbido", "trivial", "mitigar", "sintese", "aspecto", "luxuria", "cordial",
    "sucesso", "alegria", "imputar", "escoria", "emergir", "anatema", "ademais", "candura", "orgulho", "deboche", "inerente",
    "respeito", "peculiar", "denegrir", "genocida", "anuencia", "deferido", "equidade", "prudente", "pandemia", "iminente",
    "essencia", "misogino", "desgraça", "invasivo", "alienado", "eminente", "abstrato", "premissa", "extensao", "empirico",
    "conceito", "talarico", "ardiloso", "ascensao", "rapariga", "reiterar", "lascivia", "devaneio", "relativo", "prodigio",
    "passivel", "conserto", "gratidao", "analogia", "inserçao", "modestia", "apologia", "ativista", "remissao", "inospito",
    "destarte", "mediocre", "monotono", "despeito", "fomentar", "inefavel", "respaldo"
};

//200
static QString hard[] = {
    "perspicaz", "reciproco", "concessao", "impressao", "escrupulo", "superfluo", "retificar", "paradigma", "dicotomia", "proposito",
    "presunçao", "concepçao", "hipocrita", "ratificar", "implicito", "plenitude", "essencial", "hegemonia", "corolario", "incidente",
    "esdruxulo", "altruismo", "vagabundo", "altruista", "hermetico", "aleatorio", "esperança", "promiscuo", "persuadir", "confiança",
    "deliberar", "sapiencia", "indelevel", "demasiado", "mesquinho", "diligente", "impetuoso", "descriçao", "regozijar", "resignado",
    "inusitado", "eminencia", "compaixao", "prudencia", "pretensao", "discriçao", "analitico", "explicito", "ordinario", "percepçao",
    "exequivel", "dicionario", "intrinseco", "prescindir", "presunçoso", "diligencia", "corroborar", "intemperie", "detrimento",
    "maturidade", "parcimonia", "referencia", "inspiraçao", "inexoravel", "pragmatico", "prepotente", "incipiente", "disruptivo",
    "sororidade", "serenidade", "arbitrario", "indulgente", "auspicioso", "iniquidade", "pertinente", "sagacidade", "resignaçao",
    "hipocrisia", "preconizar", "precedente", "vislumbrar", "incidencia", "lisonjeado", "suscetivel", "entretanto", "disposiçao",
    "excentrico", "subestimar", "preliminar", "tribulaçao", "depreender", "fleumatico", "anacronico", "equivocado", "escrutinio",
    "retrogrado", "indolencia", "excelencia", "ingerencia", "democracia", "infortunio", "compassivo", "significado", "perspectiva",
    "resiliencia", "dissimulado", "vicissitude", "complacente", "contundente", "peremptorio", "comorbidade", "compreensao",
    "perspicacia", "expectativa", "pressuposto", "beneplacito", "subterfugio", "preconceito", "experiencia", "indiferente",
    "consonancia", "pretensioso", "transcender", "imensuravel", "contingente", "intensidade", "proeminente", "beligerante",
    "necessidade", "superficial", "concernente", "benignidade", "contencioso", "inenarravel", "animosidade", "intervençao",
    "incumbencia", "vocabulario", "antagonismo", "cumprimento", "resistencia", "indiferença", "reivindicar", "compreender",
    "supracitado", "subsequente", "estereotipo", "integridade", "diversidade", "ambiguidade", "deliberaçao", "especulaçao",
    "indulgencia", "perseverança", "condolencias", "remanescente", "prerrogativa", "extrovertido", "complacencia", "procrastinar",
    "discrepancia", "determinaçao", "independente", "consequencia", "intermitente", "conveniencia", "benevolencia", "compartilhar",
    "eclesiastico", "contingencia", "transgressao", "felicitaçoes", "consideraçao", "concomitante", "convergencia", "cordialidade",
    "conhecimento", "cumplicidade", "convencional", "subsistencia", "disseminaçao", "proselitismo", "sistematizar", "coincidencia",
    "complexidade", "prescindivel", "controversia", "imprevisivel", "impertinente", "inverossimil", "escatologico", "displicencia",
    "interlocutor", "libertinagem", "ninfomaniaco", "conformidade", "proporcionar", "intempestivo", "maledicencia", "extemporaneo"
};

//21
static QString WTF[] = {
    "otorrinolaringologista", "histerossalpingectomia", "histerossalpingografia", "anticonstitucionalismo",
    "acrocefalossindactilia", "parassimpaticomimetico", "meningoencefalomielite", "preterintencionalidade",
    "traquelatloidoccipital", "aeropiesotermoterapico", "dacriocistorrinostomia", "pneumartrorradiografia",
    "coronografopolarimetro", "interconfessionalidade", "coledocoduodenostomico", "fotocromometalografico",
    "diacetilenodicarbonato", "ureteropieloneostomico", "esternoclidomastoideos", "ultraestruturabilidade",
    "intradermorreatividade"
};

#endif // QFRAMECUSTOM_H
