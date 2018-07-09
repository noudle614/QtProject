#ifndef STUDENTDELEGATE_H
#define STUDENTDELEGATE_H

#include <QObject>
#include <QApplication>
#include <QStyledItemDelegate>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPainter>

class StudentDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    StudentDelegate(QObject *parent = 0);
    ~StudentDelegate();

    QWidget *	createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    void	setEditorData(QWidget * editor, const QModelIndex & index) const;
    void	setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
};

#endif // STUDENTDELEGATE_H
