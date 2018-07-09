#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tableView->setFocusPolicy(Qt::NoFocus);

    StudentModel *pModel = new StudentModel(this);
    StudentDelegate *pDelegate = new StudentDelegate(this);

//    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setHighlightSections(false);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->setShowGrid(false);
    ui->tableView->setFrameShape(QFrame::NoFrame);
//    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setModel(pModel);
    ui->tableView->setItemDelegate(pDelegate);

    // Make the combo boxes always displayed.
    for ( int i = 0; i < ui->tableView->model()->rowCount(); ++i )
    {
      ui->tableView->openPersistentEditor( pModel->index(i, 2) );
    }

    connect(this,SIGNAL(showResult()),pModel,SLOT(showResult()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    emit showResult();
}
