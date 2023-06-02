#include"newwidget.h"
#include<qaction.h>
#include<qmenu.h>
#include<qdebug.h>
#include<qsqlrecord.h>
#include<qmessagebox.h>
#include<QTime>
#include<qdir.h>



NewWidget::NewWidget(QWidget* parent) 
	:QMainWindow(parent), m_selledNumber(0)
{
	ui.setupUi(this);
	this->setWindowTitle("");
	this->setFixedSize(800, 500);
	initDataBase();
	m_sqlTableModel = new QSqlTableModel(this);

	//���ť
	ui.toolButton->setPopupMode(QToolButton::InstantPopup);
	ui.toolButton_2->setPopupMode(QToolButton::InstantPopup);
	ui.toolButton->setText("ѡ ��");
	ui.toolButton_2->setText("ѡ ��");
	QMenu* menu = new QMenu(this);
	QMenu* menu2 = new QMenu(this);
	
	QAction* action1 = new QAction("��װ", this);
	QAction* action2 = new QAction("ʳƷ", this);
	QAction* action3 = new QAction("��װ",this);
	QAction* action4 = new QAction("ʳƷ", this);
	
	QActionGroup* group = new QActionGroup(this);
	group->addAction(action1);
	group->addAction(action2);
	group->addAction(action3);
	group->addAction(action4);
	group->setExclusive(true);
	action1->setCheckable(true);
	action2->setCheckable(true);
	action3->setCheckable(true);
	action4->setCheckable(true);
	menu->addAction(action1);
	menu->addAction(action2);
	menu2->addAction(action3);
	menu2->addAction(action4);
	ui.toolButton->setMenu(menu);
	ui.toolButton_2->setMenu(menu2);

	//�۸��Լ��������
	QDoubleValidator* validator = new QDoubleValidator(this);
	ui.lineEdit_2->setValidator(validator);
	ui.lineEdit_3->setValidator(validator);
	ui.textEdit->setReadOnly(true);
	ui.textEdit_2->setReadOnly(true);
	ui.textEdit_3->setReadOnly(true);
	ui.textEdit_4->setReadOnly(true);

	//�µ��Լ��۳���ť��ʼ����ѡ
	ui.pushButton_4->setCheckable(false);
	ui.pushButton_3->setCheckable(false);

	//���Ӳۺ���
	(void)connect(action1, &QAction::triggered, this, &NewWidget::on_fuzhuang_triggered);
	(void)connect(ui.pushButton, &QPushButton::clicked, this, &NewWidget::on_ruku_clicked);
	(void)connect(action2, &QAction::triggered, this, &NewWidget::on_shipin_triggered);
	(void)connect(ui.pushButton_2, &QPushButton::clicked, this, &NewWidget::on_qingkong_clicked);
	(void)connect(action3, &QAction::triggered, this, &NewWidget::on_fuzhuang2_triggered);
	(void)connect(action4, &QAction::triggered, this, &NewWidget::on_shipin2_triggered);
	(void)connect(ui.pushButton_5, &QPushButton::clicked, this, &NewWidget::on_ok_clicked);
	(void)connect(ui.pushButton_3, &QPushButton::clicked, this, &NewWidget::on_shouchu_clicked);
	(void)connect(ui.pushButton_4, &QPushButton::clicked, this, &NewWidget::on_xiadan_clicked);
	(void)connect(ui.spinBox_2, QOverload<int>::of(&QSpinBox::valueChanged), this, &NewWidget::on_spinBox_clicked);
}


//��ʼ�����ݿ�
void NewWidget::initDataBase() {
	bool ok;
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName("goods.db");
	//QMessageBox::information(this, "test", QDir::currentPath(), QMessageBox::Ok);
	ok = m_db.open();
	if (!ok)
		qDebug() << __FUNCTION__ << m_db.lastError().text();

}

//��ʼ��TableView
void NewWidget::initTableView() {
	if (ui.toolButton->text() == "��װ") {
		m_sqlTableModel->setTable("garment");
		//����Ϊ�ֶ��ύ
		m_sqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

		m_sqlTableModel->select();

		m_sqlTableModel->setHeaderData(0, Qt::Horizontal, "��װ����");
		m_sqlTableModel->setHeaderData(1, Qt::Horizontal, "����(��)");
		m_sqlTableModel->setHeaderData(2, Qt::Horizontal, "�ۼ�(��)");
		m_sqlTableModel->setHeaderData(3, Qt::Horizontal, "���");
	}
	else if (ui.toolButton->text() == "ʳƷ") {
		m_sqlTableModel->setTable("food");
		//QMessageBox::information(this, "test", QDir::currentPath(), QMessageBox::Ok);
		//����Ϊ�ֶ��ύ
		m_sqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

		m_sqlTableModel->select();

		m_sqlTableModel->setHeaderData(0, Qt::Horizontal, "ʳƷ����");
		m_sqlTableModel->setHeaderData(1, Qt::Horizontal, "����(��)");
		m_sqlTableModel->setHeaderData(2, Qt::Horizontal, "�ۼ�(��)");
		m_sqlTableModel->setHeaderData(3, Qt::Horizontal, "���");
	}

	//QHeaderView* header = this->horizontalHeader();
	//// ���ñ�ͷ�ĵ���ģʽΪ�̶�
	//header->setSectionResizeMode(QHeaderView::Fixed);

	ui.tableView->setModel(m_sqlTableModel);
}


void NewWidget::on_fuzhuang_triggered() {
	qDebug() << "��װ";
	ui.toolButton->setText("��װ");
	initTableView();
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.spinBox->setValue(0);
}

void NewWidget::on_shipin_triggered() {
	qDebug() << "ʳƷ";
	ui.toolButton->setText("ʳƷ");
	initTableView();
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.spinBox->setValue(0);
}



void NewWidget::on_ruku_clicked() {
	QString table = "";
	if (ui.toolButton->text() == "��װ") 
		table = "garment";
	else if (ui.toolButton->text() == "ʳƷ") 
		table = "food";
	if (table != "garment" && table != "food") {
		QMessageBox::information(this, "����", "δѡ���Ʒ����", QMessageBox::Ok);
		return;
	}
	m_sqlTableModel->setTable(table);
	QString gName = ui.lineEdit->text();
	QString gInPrice = ui.lineEdit_2->text();
	QString gOutPrice = ui.lineEdit_3->text();
	QString gInventory = ui.spinBox->text();

	// ��������ģ�͵Ĺ�������Ϊ��Ʒ����
	m_sqlTableModel->setFilter(QString("name = '%1'").arg(gName));
	// ��ѯ����
	if (!m_sqlTableModel->select()) {
		qDebug() << "Failed to select data:" << m_sqlTableModel->lastError().text();
		return;
	}

	// �ж��Ƿ����Ŀ������
	if (m_sqlTableModel->rowCount() > 0) {
		// ��ȡ��һ�У���0��ʼ������������
		QModelIndex index = m_sqlTableModel->index(0, 0);
		
		// �޸�����ģ���еļ۸�Ϳ��
		m_sqlTableModel->setData(m_sqlTableModel->index(index.row(), 1), gInPrice);
		m_sqlTableModel->setData(m_sqlTableModel->index(index.row(), 2), gOutPrice);
		gInventory = QString::number(gInventory.toInt() + m_sqlTableModel->index(index.row(), 3).data().toInt(), 'f', 0);
		m_sqlTableModel->setData(m_sqlTableModel->index(index.row(), 3), gInventory);
		// �ύ���ĵ����ݿ�
		if (!m_sqlTableModel->submitAll()) {
			qDebug() << "Failed to submit changes:" << m_sqlTableModel->lastError().text();
			return;
		}
		qDebug() << "Update data successfully";
	}
	else {
		// ����һ���¼�¼
		QSqlRecord record = m_sqlTableModel->record();
		record.setValue("name", gName);
		record.setValue("in_price", gInPrice);
		record.setValue("out_price", gOutPrice);
		record.setValue("inventory", gInventory);
		// �����¼�¼������ģ����
		if (!m_sqlTableModel->insertRecord(-1, record)) {
			qDebug() << "Failed to insert record:" << m_sqlTableModel->lastError().text();
			return;
		}
		// �ύ���ĵ����ݿ�
		if (!m_sqlTableModel->submitAll()) {
			qDebug() << "Failed to submit changes:" << m_sqlTableModel->lastError().text();
			return;
		}
		qDebug() << "Insert data successfully";
	}
	
	// �����������
	m_sqlTableModel->setFilter("");

	if(table=="garment")
		m_sqlTableModel->setHeaderData(0, Qt::Horizontal, "��װ����");
	else if(table == "food")
		m_sqlTableModel->setHeaderData(0, Qt::Horizontal, "ʳƷ����");
	m_sqlTableModel->setHeaderData(1, Qt::Horizontal, "����(��)");
	m_sqlTableModel->setHeaderData(2, Qt::Horizontal, "�ۼ�(��)");
	m_sqlTableModel->setHeaderData(3, Qt::Horizontal, "���");

	// ���ñ����ͼ������ģ��Ϊ�ոմ�����model
	ui.tableView->setModel(m_sqlTableModel);
	//�����һ������
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.spinBox->setValue(0);


}


void NewWidget::on_qingkong_clicked() {
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.spinBox->setValue(0);
	
	QSqlQuery sql;
	QString sqlString = "";
	if (ui.toolButton->text() == "��װ") {
		sqlString = "DELETE FROM garment";
	}
	else if (ui.toolButton->text() == "ʳƷ") {
		sqlString = "DELETE FROM food";
	}
	bool ok = sql.exec(sqlString);
	if (ok) {
		qDebug() << "�ɹ����";
		m_sqlTableModel->clear();
		return;
	}
	else {
		qDebug() << "���ʧ��" << sql.lastError().text();
		return;
	}
}

void NewWidget::on_fuzhuang2_triggered() {
	qDebug() << "��װ2";
	ui.toolButton_2->setText("��װ");
	//initTableView();
	ui.lineEdit_4->clear();
	ui.textEdit->clear();
	ui.textEdit_2->clear();
	ui.textEdit_3->clear();
	ui.spinBox_2->setValue(0);
}

void NewWidget::on_shipin2_triggered() {
	qDebug() << "ʳƷ2";
	ui.toolButton_2->setText("ʳƷ");
	//initTableView();
	ui.lineEdit_4->clear();
	ui.textEdit->clear();
	ui.textEdit_2->clear();
	ui.textEdit_3->clear();
	ui.spinBox_2->setValue(0);
}

void NewWidget::on_ok_clicked() {
	/*m_sqlTableModel = new QSqlTableModel(this);*/
	QString table1 = "";
	if (ui.toolButton_2->text() == "��װ")
		table1 = "garment";
	else if (ui.toolButton_2->text() == "ʳƷ")
		table1 = "food";
	if (table1 != "garment" && table1 != "food") {
		QMessageBox::information(this, "����", "δѡ���Ʒ����", QMessageBox::Ok);
		return;
	}
	m_sqlTableModel->setTable(table1);

	QString gName = ui.lineEdit_4->text();
	// ��������ģ�͵Ĺ�������Ϊ��Ʒ����
	m_sqlTableModel->setFilter(QString("name = '%1'").arg(gName));
	// ��ѯ����
	if (!m_sqlTableModel->select()) {
		qDebug() << "Failed to select data:" << m_sqlTableModel->lastError().text();
		return;
	}

	// �ж��Ƿ����Ŀ������
	if (m_sqlTableModel->rowCount() > 0) {

		// ��ȡ��һ�У���0��ʼ������������
		QModelIndex index = m_sqlTableModel->index(0, 0);
		QString name = m_sqlTableModel->index(index.row(), 0).data().toString();
		QString inPrice = m_sqlTableModel->index(index.row(), 1).data().toString();
		QString outPrice = m_sqlTableModel->index(index.row(), 2).data().toString();
		QString inventory = m_sqlTableModel->index(index.row(), 3).data().toString();

		ui.textEdit->setText(outPrice);
		ui.textEdit_2->setText(inventory);
		ui.textEdit_3->setText(QString::number(outPrice.toFloat() * ui.spinBox_2->value(), 'f', 0));

		/*if (inventory < ui.spinBox_2->value()) {
			ui.pushButton_3->setCheckable(false);
			return;
		}
		else {
			ui.pushButton_3->setCheckable(true);
		}*/
		ui.pushButton_3->setCheckable(true);
	}
	//Ŀ�����ݲ�����
	else {
		QMessageBox::information(this, "����","δ�ҵ�Ŀ���Ʒ", QMessageBox::Ok);
		ui.lineEdit_4->setText("");
		return;
	}
	//�����������
	m_sqlTableModel->setFilter("");
}

void NewWidget::on_shouchu_clicked() {
	if (!ui.pushButton_3->isCheckable()) return;
	if (ui.spinBox_2->text().toInt() > ui.textEdit_2->toPlainText().toInt()) {
		QMessageBox::information(this, "ʧ��", "��治��", QMessageBox::Ok);
		ui.pushButton_4->setCheckable(false);
		return;
	}
	QMessageBox::information(this, "�ɹ�", "�Ѽ��붩��", QMessageBox::Ok);
	
	ui.pushButton_4->setCheckable(true);
	QTime ct = QTime::currentTime();
	ui.textEdit_4->setText(ui.textEdit_4->toPlainText()+"\n------------------------\n");
	ui.textEdit_4->setText(ui.textEdit_4->toPlainText() + ct.toString("hh:mm:ss.zzz") + "\n" + "��Ʒ���ƣ�" + ui.lineEdit_4->text()
		+ "\n������" + ui.spinBox_2->text() + "\n���ۣ�" + ui.textEdit->toPlainText() + "\n�ܼۣ�" + ui.textEdit_3->toPlainText());
	m_selledNumber++;
	ui.pushButton_3->setCheckable(false);
}

void NewWidget::on_xiadan_clicked() {
	if (!ui.pushButton_4->isCheckable()) return;
	QMessageBox::information(this, "�ɹ�", "�µ��ɹ�", QMessageBox::Ok);
	QTime ct = QTime::currentTime();
	ui.textEdit_4->setText(ui.textEdit_4->toPlainText() + "\n------------------------\n");
	ui.textEdit_4->setText(ui.textEdit_4->toPlainText() + "���ڣ�" + ct.toString("hh:mm:ss.zzz") + "\n" + "�����ţ�" + QString::number(m_selledNumber, 'f', 0)
		+ "\nӦ�����ܶ" + ui.textEdit_3->toPlainText());
	QString gInventory = QString::number(ui.textEdit_2->toPlainText().toInt() - ui.spinBox_2->value());
	QSqlQuery query;
	if (m_sqlTableModel->tableName() == "garment") {
		query.prepare("UPDATE garment SET inventory = :inventory WHERE name = :name");
		query.bindValue(":inventory", gInventory);
		query.bindValue(":name", ui.lineEdit_4->text());
	}
	else if (m_sqlTableModel->tableName() == "food") {
		query.prepare("UPDATE food SET inventory = :inventory WHERE name = :name");
		query.bindValue(":inventory", gInventory);
		query.bindValue(":name", ui.lineEdit_4->text());
	}
	query.exec();
	ui.lineEdit_4->setText("");
	ui.textEdit->setText("");
	ui.textEdit_2->setText("");
	ui.textEdit_3->setText("");
	ui.spinBox_2->setValue(0);

	ui.pushButton_4->setCheckable(false);
}


//����Ʒ�����ı�ʱ�����ܼ�
void NewWidget::on_spinBox_clicked() {
	if (ui.pushButton_3->isCheckable()) {
		float num = ui.spinBox_2->value() * ui.textEdit->toPlainText().toFloat();
		ui.textEdit_3->setPlainText(QString::number(num));
	}
}

NewWidget::~NewWidget() {
	delete m_sqlTableModel;
}


