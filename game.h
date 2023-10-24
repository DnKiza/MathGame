#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QtWidgets>

class Result:public QSpinBox
{
    Q_OBJECT
public:
    Result();
signals:
    void pressed();
protected:
    void keyPressEvent(QKeyEvent* event);
};

class Game:public QWidget
{
    Q_OBJECT
public:
    Game();
    static int result;
public slots:
    void change();
    void start();
    void assess();
private:
    QLCDNumber* wind;
    QTimer* time;
    QPushButton* operation;
    Result* resultBox;
protected:
    void paintEvent(QPaintEvent *event);
    static int val;
};

#endif // GAME_H
