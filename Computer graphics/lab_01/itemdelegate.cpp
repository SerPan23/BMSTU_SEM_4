#include "itemdelegate.h"
#include <QLineEdit>
#include <QLocale>

ItemDelegate::ItemDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *ItemDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);

    // QLocale locale (QLocale::English);
    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    auto validator = new QDoubleValidator;
    validator->setLocale(locale);

    editor->setValidator(validator);
    return editor;
}


void ItemDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *line = static_cast<QLineEdit*>(editor);
    line->setText(value);
}


void ItemDelegate::setModelData(QWidget *editor,
                                QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    QLineEdit *line = static_cast<QLineEdit*>(editor);
    QString value = line->text();
    model->setData(index, value);
}


void ItemDelegate::updateEditorGeometry(QWidget *editor,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
