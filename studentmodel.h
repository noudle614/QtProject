#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QColor>

#define COLUMN_CHECK        0
#define COLUMN_NAME         1
#define COLUMN_GENDER       2
#define COLUMN_AGE          3
#define COLUMN_SCORE        4
#define COLUMN_GRADUATE     5

enum E_Gender
{
    E_BOY,
    E_GIRL,
};

typedef struct S_Student
{
    bool m_check;
    QString m_name;
    int m_age;
    E_Gender m_gender;
    int m_score;
    bool m_graduate;
}S_STU;

class StudentModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    StudentModel(QObject *parent=0);
    ~StudentModel();

    int	columnCount(const QModelIndex & parent = QModelIndex()) const;
    int	rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant	data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    bool	setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    QVariant	headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    Qt::ItemFlags	flags(const QModelIndex & index) const;


private:
    QList<S_STU*> StuList;

private slots:
    void showResult();

};

#endif // STUDENTMODEL_H
