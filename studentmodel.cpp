#include "studentmodel.h"
#include <QDebug>

StudentModel::StudentModel(QObject *parent) : QAbstractTableModel(parent)
{
    StuList.clear();

    S_STU *stu1 = new S_STU;
    stu1->m_check = false;
    stu1->m_name = QString("XiaoMing");
    stu1->m_gender = E_BOY;
    stu1->m_age = 12;
    stu1->m_score = 98;
    stu1->m_graduate = true;

    S_STU *stu2 = new S_STU;
    stu2->m_check = false;
    stu2->m_name = QString("XiaoHong");
    stu2->m_gender = E_GIRL;
    stu2->m_age = 10;
    stu2->m_score = 100;
    stu2->m_graduate = false;

    S_STU *stu3 = new S_STU;
    stu3->m_check = false;
    stu3->m_name = QString("LiLei");
    stu3->m_gender = E_BOY;
    stu3->m_age = 9;
    stu3->m_score = 60;
    stu3->m_graduate = false;

    StuList.append(stu1);
    StuList.append(stu2);
    StuList.append(stu3);

}

StudentModel::~StudentModel()
{
   for(int i=0;i<StuList.count();++i){
       delete StuList.at(i);
   }
}

int	StudentModel::columnCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return 6;
}

int	StudentModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return StuList.count();
}

QVariant StudentModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int nRow = index.row();
    int nColumn = index.column();

    S_STU *stu = StuList.at(nRow);
    switch(role){
        case Qt::TextColorRole:
            return QColor(Qt::black);
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
        case Qt::UserRole+COLUMN_CHECK:
        {
            if (nColumn == COLUMN_CHECK)
                return stu->m_check;
            return "";
        }
        case Qt::DisplayRole:
        {
            if (nColumn == COLUMN_NAME)
                return stu->m_name;
            if (nColumn == COLUMN_AGE)
                return stu->m_age;
            if (nColumn == COLUMN_SCORE)
                return stu->m_score;
            return "";
        }
        case Qt::UserRole+COLUMN_AGE:
        {
            if (nColumn == COLUMN_AGE)
                return stu->m_age;
            return "";
        }
        case Qt::UserRole+COLUMN_SCORE:
        {
            if (nColumn == COLUMN_SCORE)
                return stu->m_score;
            return "";
        }
        case Qt::UserRole+COLUMN_GENDER:
        {
            if (nColumn == COLUMN_GENDER)
                return stu->m_gender;
            return "";
        }
        case Qt::UserRole+COLUMN_GRADUATE:
        {
            if (nColumn == COLUMN_GRADUATE)
                return stu->m_graduate;
            return "";
        }
        default:
            return QVariant();
    }
    return QVariant();
}

bool StudentModel::setData(const QModelIndex & index, const QVariant & value, int role)
{
    if (!index.isValid())
        return false;

    int nRow = index.row();

    S_STU *stu = StuList.at(nRow);
    switch(role){
        case Qt::UserRole+COLUMN_CHECK:
        {
            stu->m_check = value.toBool();
            emit dataChanged(index, index);
            return true;
        }
        case Qt::UserRole+COLUMN_GENDER:
        {
            int val = value.toInt();
            if(val==0)
                stu->m_gender = E_BOY;
            else if(val==1)
                stu->m_gender = E_GIRL;

            emit dataChanged(index, index);
            return true;
        }
        case Qt::UserRole+COLUMN_AGE:
        {
            stu->m_age = value.toInt();
            emit dataChanged(index, index);
            return true;
        }
        case Qt::UserRole+COLUMN_SCORE:
        {
            stu->m_score = value.toInt();
            emit dataChanged(index, index);
            return true;
        }
        case Qt::UserRole+COLUMN_GRADUATE:
        {
            stu->m_graduate = value.toBool();
            emit dataChanged(index, index);
            return true;
        }
        default:
            return false;
    }
    return setData(index,value,role);
}

QVariant StudentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role)
    {
        case Qt::TextAlignmentRole:
            return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);
        case Qt::DisplayRole:
        {
            if(orientation == Qt::Horizontal){
                if (section == COLUMN_CHECK)
                    return QStringLiteral("Operate");
                if (section == COLUMN_NAME)
                    return QStringLiteral("Name");
                if (section == COLUMN_GENDER)
                    return QStringLiteral("Gender");
                if (section == COLUMN_AGE)
                    return QStringLiteral("Age");
                if (section == COLUMN_SCORE)
                    return QStringLiteral("Score");
                if (section == COLUMN_GRADUATE)
                    return QStringLiteral("Graduate");
            }
        }
        default:
            return QVariant();
    }
    return QVariant();
}

Qt::ItemFlags	StudentModel::flags(const QModelIndex & index) const
{
    if (!index.isValid())
        return QAbstractItemModel::flags(index);

    Qt::ItemFlags flags = QAbstractItemModel::flags(index);

    if(index.column() == COLUMN_CHECK){
        flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }else if(index.column() == COLUMN_GENDER){
        flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }else if(index.column() == COLUMN_AGE || index.column() == COLUMN_SCORE){
        flags |= Qt::ItemIsEditable;
    }else if(index.column() == COLUMN_GRADUATE){
        flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable;
    }

    return flags;
}

void StudentModel::showResult()
{
    for(int i=0;i<StuList.count();++i){
        S_STU *stu = StuList.at(i);
        if(stu->m_check)
            qDebug()<<stu->m_name<<":"<<stu->m_check<<stu->m_gender<<stu->m_age<<stu->m_score<<stu->m_graduate;
    }
}
