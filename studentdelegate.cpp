#include "studentdelegate.h"
#include "studentmodel.h"


StudentDelegate::StudentDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

StudentDelegate::~StudentDelegate()
{

}

QWidget *	StudentDelegate::createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    if(index.column() == COLUMN_GENDER){
        QComboBox *combox = new QComboBox(parent);
        combox->addItem("Boy");
        combox->addItem("Girl");
        return combox;
    }else if(index.column() == COLUMN_AGE || index.column() == COLUMN_SCORE ){
        QLineEdit *lineEdit = new QLineEdit(parent);
        return lineEdit;
    }
    return 0;
}

void	StudentDelegate::setEditorData(QWidget * editor, const QModelIndex & index) const
{
    if(index.column() == COLUMN_GENDER){
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        int value = index.model()->data(index, Qt::UserRole+COLUMN_GENDER).toUInt();
        comboBox->setCurrentIndex(value);
    }else if(index.column() == COLUMN_AGE || index.column() == COLUMN_SCORE){
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        QString value;
        if(index.column() == COLUMN_AGE)
            value = index.model()->data(index, Qt::DisplayRole).toString();
        else if(index.column() == COLUMN_SCORE)
            value = index.model()->data(index, Qt::DisplayRole).toString();
        lineEdit->setText(value);
    }
}

void	StudentDelegate::setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const
{
    if(index.column() == COLUMN_GENDER){
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        model->setData(index, comboBox->currentIndex(), Qt::UserRole+COLUMN_GENDER);
    }else if(index.column() == COLUMN_AGE || index.column() == COLUMN_SCORE ){
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        if(index.column() == COLUMN_AGE)
            model->setData(index, lineEdit->text(), Qt::UserRole+COLUMN_AGE);
        else if(index.column() == COLUMN_SCORE)
            model->setData(index, lineEdit->text(), Qt::UserRole+COLUMN_SCORE);
    }
}

void StudentDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem viewOption(option);
    initStyleOption(&viewOption, index);
    if (option.state.testFlag(QStyle::State_HasFocus))
        viewOption.state = viewOption.state ^ QStyle::State_HasFocus;
    QStyledItemDelegate::paint(painter, viewOption, index);

    if (index.column() == COLUMN_CHECK)
    {
        bool data = index.model()->data(index, Qt::UserRole + COLUMN_CHECK).toBool();

        QStyleOptionButton checkBoxStyle;
        checkBoxStyle.state = data ? QStyle::State_On : QStyle::State_Off;
        checkBoxStyle.state |= QStyle::State_Enabled;
        checkBoxStyle.iconSize = QSize(20, 20);
        checkBoxStyle.rect = option.rect;

        QCheckBox checkBox;
        QApplication::style()->drawPrimitive(QStyle::PE_IndicatorCheckBox, &checkBoxStyle, painter, &checkBox);
    }
    else if(index.column() == COLUMN_GRADUATE)
    {
        bool data = index.model()->data(index, Qt::UserRole + COLUMN_GRADUATE).toBool();
        QPixmap pixmap;
        if(data)
            pixmap = QPixmap(":/checked.png");
        else
            pixmap = QPixmap(":/unchecked.png");

        int height = (viewOption.rect.height() - 22) / 2;
        QRect decorationRect = QRect(viewOption.rect.left() + viewOption.rect.width() - 90, viewOption.rect.top() + height, 36, 22);
        painter->drawPixmap(decorationRect, pixmap);
    }
}

bool StudentDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    QRect decorationRect = option.rect;

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if (event->type() == QEvent::MouseButtonPress && decorationRect.contains(mouseEvent->pos()))
    {
        if (index.column() == COLUMN_CHECK)
        {
            bool data = model->data(index, Qt::UserRole+COLUMN_CHECK).toBool();
            model->setData(index, !data, Qt::UserRole+COLUMN_CHECK);
        }else if(index.column() == COLUMN_GRADUATE){
            bool data = model->data(index, Qt::UserRole+COLUMN_GRADUATE).toBool();
            model->setData(index, !data, Qt::UserRole+COLUMN_GRADUATE);
        }
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);
}
