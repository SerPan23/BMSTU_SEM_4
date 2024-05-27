#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

#include <ranges>

#include "../constants.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    generateUi();

    qDebug() << "Этаж № 1 | Движение кабины разблокировано | Двери закрыты ";

    for (int i = 0; i < cabinButtons.size(); ++i)
    {
        connect(cabinButtons[i], &QPushButton::pressed, this, [i, this]() { onCabinBtnClicked(i + 1); });
    }

    for (int i = 0; i < floorButtons.size(); ++i)
    {
        connect(floorButtons[i], &QPushButton::pressed, this, [i, this]() { onFloorBtnClicked(i + 1); });
    }

}

void MainWindow::onCabinBtnClicked(const int btnNumber) {
    qDebug() << "Кабина | Нажата кнопка " << btnNumber;
    elevator.btnClick(btnNumber);
}

void MainWindow::onFloorBtnClicked(const int btnNumber) {
    qDebug() << "Этаж №" << btnNumber << "| Вызов лифта";
    elevator.btnClick(btnNumber);
}

void MainWindow::generateUi()
{
    QVBoxLayout *cabin_layout;
    QVBoxLayout *floors_layout;

    QLabel *cabin_label;
    QLabel *floor_label;

    auto horizontalLayout = new QHBoxLayout(ui->centralwidget);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));


    cabin_layout = new QVBoxLayout();
    cabin_layout->setObjectName(QString::fromUtf8("cabin_layout"));

    cabin_label = new QLabel(ui->centralwidget);
    cabin_label->setObjectName(QString::fromUtf8("cabin_label"));

    QFont font;
    font.setFamily(QString::fromUtf8("Helvetica"));
    font.setPointSize(16);
    cabin_label->setFont(font);
    cabin_label->setAlignment(Qt::AlignCenter);

    cabin_label->setText("Cabin btns");

    cabin_layout->addWidget(cabin_label);

    QFont btn_font;
    btn_font.setFamily(QString::fromUtf8("Helvetica"));
    btn_font.setPointSize(14);

    for (int i = 0; i < FLOORS_COUNT; ++i)
    {
        auto btn = new QPushButton(ui->centralwidget);
        btn->setMinimumSize(QSize(70, 60));
        btn->setMaximumSize(QSize(70, 60));
        btn->setFont(btn_font);
        btn->setText(QString::number(i + 1));

        cabinButtons.push_back(btn);
    }

    for (auto it = cabinButtons.rbegin(); it != cabinButtons.rend(); ++it)
    {
        cabin_layout->addWidget(*it);
    }

    horizontalLayout->addLayout(cabin_layout);

    floors_layout = new QVBoxLayout();
    floors_layout->setObjectName(QString::fromUtf8("floors_layout"));
    floor_label = new QLabel(ui->centralwidget);
    floor_label->setObjectName(QString::fromUtf8("floor_label"));
    floor_label->setText("Floors btn");
    floor_label->setFont(font);
    floor_label->setAlignment(Qt::AlignCenter);

    floors_layout->addWidget(floor_label);

    for (int i = 0; i < FLOORS_COUNT; ++i)
    {
        auto btn = new QPushButton(ui->centralwidget);
        btn->setMinimumSize(QSize(70, 60));
        btn->setMaximumSize(QSize(70, 60));
        btn->setFont(btn_font);
        btn->setText(QString::number(i + 1));

        floorButtons.push_back(btn);
    }

    for (auto & floor_button : std::ranges::reverse_view(floorButtons))
    {
        floors_layout->addWidget(floor_button);
    }

    horizontalLayout->addLayout(floors_layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
