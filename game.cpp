#include "game.h"

int Game::val=0;
int Game::result=0;

Game::Game():QWidget()
{
    time=new QTimer;
    wind=new QLCDNumber;

    wind->setFixedSize(width()/3,height()/5);
    wind->setStyleSheet("border:2px solid rgb(222,30,141) ;color:rgb(45,187,255)");
    QPushButton * butt=new QPushButton("Start");
    butt->setFixedSize(width()/5,height()/8);
    butt->setFont(QFont("Impact",20));
    butt->setStyleSheet("border:2px solid rgb(45,187,255);border-radius:20px;");

    operation=new QPushButton("((((96+45)÷3-40)+13)÷10)");
    operation->setFont(QFont("Comic Sans MS",20));
    operation->setMinimumHeight(height()/3);
    operation->setStyleSheet("background:#211842;border: 2px solid rgb(219,88,173);"
                             "color:#211842;"
                             "opacity:0");

    QPushButton* equal=new QPushButton("=");
    equal->setFont(QFont("Comic Sans MS",50));

    resultBox=new Result;
    resultBox->setEnabled(false);
    resultBox->setMaximum(10000);
    resultBox->setMinimumSize(width()/4,height()/4);
    resultBox->setStyleSheet("font-size: 40px;font-family: Comic Sans MS;color:rgb(219,88,173)");

    QVBoxLayout* layout=new QVBoxLayout;
    QHBoxLayout* lay1=new QHBoxLayout;
    QHBoxLayout* lay2=new QHBoxLayout;
    QHBoxLayout* lay3=new QHBoxLayout;
    QHBoxLayout* lay4=new QHBoxLayout;

    lay1->addWidget(operation);
    lay1->setAlignment(Qt::AlignTop|Qt::AlignCenter);

    lay2->addWidget(wind);
    lay2->addWidget(butt);
    lay2->setAlignment(Qt::AlignBottom|Qt::AlignCenter);

    lay3->addWidget(equal);
    lay3->setAlignment(Qt::AlignTop|Qt::AlignCenter);

    lay4->addWidget(resultBox);
    lay4->setAlignment(Qt::AlignTop|Qt::AlignCenter);


    layout->addLayout(lay1);
    layout->addLayout(lay3);
    layout->addLayout(lay4);
    layout->addLayout(lay2);

    setLayout(layout);
    setMinimumSize(600,500);

    connect(time,SIGNAL(timeout()),this,SLOT(change()));
    connect(time,SIGNAL(timeout()),this,SLOT(repaint()));
    connect(butt,SIGNAL(clicked(bool)),this,SLOT(start()));
    connect(resultBox,SIGNAL(pressed()),this,SLOT(assess()));
}
void Game::paintEvent(QPaintEvent*)
{
    QPainter paint(this);
    QImage background;
    if(val%2==0)
        background=QImage("1B.image.jpg");
    else
        background=QImage("2E.image.jpg");
    /*if(val%2==0)
        paint.fillRect(0,0,width(),height(),QBrush(QImage::scaled("1B.image.jpg")));
    else
        paint.fillRect(0,0,width(),height(),QBrush(QImage("2E.image.jpg")));*/
    paint.fillRect(0,0,width(),height(),QBrush(background.scaled(QSize(width(),height()))));
}

void Game::change()
{
    val=wind->value();
    wind->display(val+1);
    if(val+1==20)
        time->stop();
}
void Game::start()
{
    operation->setStyleSheet("background: white;color:rgb(219,88,173)");
    resultBox->setEnabled(true);
    if(val+1<20)
        time->start(1000);
    else
    {
        int answer=QMessageBox::question(this,"Critical error",
                                         "Do you want to restart the timer?",
                                         QMessageBox::Yes|QMessageBox::No);
        if(answer==QMessageBox::Yes)
        {
            wind->display(0);
            time->start(1000);
        }

        else
            QMessageBox::information(this,"Information","You don't want to restart");
    }
}

void Game::assess()
{
    QChar emoji(128549);
    if(result==2)
        QMessageBox::information(this,"Congratulations","You did it !!!!!!!");
    else
        QMessageBox::information(this,"Unfortunately",QString("You failed %1").arg(emoji));
}

Result::Result(){}

void Result::keyPressEvent(QKeyEvent *event)
{
    QSpinBox::keyPressEvent(event);
    if(event->key()==Qt::Key_Return)
    {
        Game::result=value();
        emit pressed();
    }
}
