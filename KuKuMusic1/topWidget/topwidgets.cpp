#include "topwidgets.h"
#include<QPushButton>
#include<QLabel>
#include<QHBoxLayout>
#include<QDebug>
#include<QFile>
#include<QApplication>


TopWidgets::TopWidgets(QWidget *parent) : baseWidget(parent)
{
    setStyleSheet("TopWidgets{background:transparent;}");
    setMouseTracking(true);
    initWidget();
    m_mainWindow=(mainWindow*)parent;
}
void TopWidgets::slot_serTipsClick(QListWidgetItem *it)
{
    searchFromLineEdit(it->text());
}

bool TopWidgets::eventFilter(QObject *o, QEvent *e)
{
    return QObject::eventFilter(o,e);
}

void TopWidgets::mouseMoveEvent(QMouseEvent *e)
{
    baseWidget::mouseMoveEvent(e);
   // m_mainWindow->mouseMoveEvent(e);
}

void TopWidgets::initWidget()
{
    setMinimumSize(1000,50);
    setMaximumSize(1920,50);
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    //主布局
    QHBoxLayout *hmainyout = new QHBoxLayout;
    //第一块布局 图标
    QHBoxLayout *hyout1 = new QHBoxLayout;
    myPushButton*btn = new myPushButton(this);
    btn->setFixedSize(30,30);
    btn->setStyleSheet("QPushButton{background:transparent;"    //样式表
                       "border-image:url(:/image/topwidget/label_icon.png)}");

    hyout1->addWidget(btn);
    hyout1->addSpacing(6);

    hyout1->setSpacing(5);
    hyout1->setContentsMargins(0,0,0,0);
    //第二块布局  搜索框
    QHBoxLayout *hyout2 = new QHBoxLayout;
    m_lineEdit = new QLineEdit(this); //搜索框
    m_lineEdit->setMinimumSize(260,26);
    m_lineEdit->setMaximumSize(320,26);
    m_lineEdit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    m_lineEdit->setStyleSheet("QLineEdit{border-radius:13px; background:rgb(255,255,255,180); "
                              "font-size:13px; font-family:微软雅黑}");
    m_lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
    myPushButton *serbtn = new myPushButton(m_lineEdit);  //搜索按钮
    serbtn->setFixedSize(16,16);
    serbtn->setStyleSheet("QPushButton{background:transparent;border-image: url(:/image/topwidget/btn_search (1).png);}"
                          "QPushButton::hover{border-image: url(:/image/topwidget/btn_search (2).png);}"
                          "QPushButton::pressed{border-image: url(:/image/topwidget/btn_search (3).png);}");
    m_lineEdit->setPlaceholderText("周杰伦-东风破");
    QMargins margins = m_lineEdit->textMargins();
    m_lineEdit->setTextMargins(margins.left()+15, margins.top(), serbtn->width()+15, margins.bottom());

    QHBoxLayout *pSearchLayout = new QHBoxLayout(this);
    pSearchLayout->addStretch();
    pSearchLayout->addWidget(serbtn);
    pSearchLayout->setSpacing(0);
    pSearchLayout->setContentsMargins(0,0,15,0);
    m_lineEdit->setLayout(pSearchLayout);

    hyout2->addWidget(m_lineEdit);
    hyout2->setSpacing(20);
    hyout2->setContentsMargins(0,0,0,0);

    //第三块布局
    QHBoxLayout *hyout3 = new QHBoxLayout;
    m_btnexit = new myPushButton(this);       //退出按钮
    m_btnmini = new myPushButton(this);       //最小化按钮
    m_btnskin = new myPushButton(this);       //皮肤按钮

    m_btnexit->setFixedSize(18,18);
    m_btnmini->setFixedSize(16,16);
    m_btnskin->setFixedSize(16,16);

    m_btnexit->setObjectName("m_btnexit");
    m_btnmini->setObjectName("m_btnmini");
    m_btnskin->setObjectName("m_btnskin");

#if 1
    m_btnexit->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_close (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/topwidget/btn_close (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/topwidget/btn_close (3).png);}");
    m_btnmini->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_mini (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/topwidget/btn_mini (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/topwidget/btn_mini (3).png);}");

    m_btnskin->setStyleSheet("QPushButton{border-image:url(:/image/topwidget/btn_skin (1).png);}"
                             "QPushButton::hover{border-image:url(:/image/topwidget/btn_skin (2).png);}"
                             "QPushButton::pressed{border-image:url(:/image/topwidget/btn_skin (3).png);}");

#endif
    QLabel*label3=new QLabel("丨",this); //分割线
    label3->setFixedSize(6,16);
    label3->setStyleSheet("color:rgb(255,255,255,50);");
    label3->adjustSize();

    hyout3->addWidget(m_btnskin);
    hyout3->addWidget(label3);
    hyout3->addWidget(m_btnmini);
    hyout3->addWidget(m_btnexit);
    hyout3->setSpacing(12);

    hmainyout->addLayout(hyout1);
    hmainyout->addSpacing(190);
    hmainyout->addSpacerItem(new QSpacerItem(80,30,QSizePolicy::Maximum));//设置它最大膨胀！！！
    hmainyout->addLayout(hyout2);
    hmainyout->addSpacerItem(new QSpacerItem(110,30,QSizePolicy::Expanding));//膨胀
    hmainyout->addLayout(hyout3);
    hmainyout->setSpacing(0);
    hmainyout->setContentsMargins(16,0,15,0);
    setLayout(hmainyout);

    connect(serbtn,SIGNAL(clicked(bool)),m_lineEdit,SIGNAL(returnPressed()));
}

void TopWidgets::searchFromLineEdit(const QString str)
{
    m_lineEdit->setText(str);
    emit m_lineEdit->returnPressed();
}
