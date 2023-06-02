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

	//类别按钮
	ui.toolButton->setPopupMode(QToolButton::InstantPopup);
	ui.toolButton_2->setPopupMode(QToolButton::InstantPopup);
	ui.toolButton->setText("选 择");
	ui.toolButton_2->setText("选 择");
	QMenu* menu = new QMenu(this);
	QMenu* menu2 = new QMenu(this);
	
	QAction* action1 = new QAction("服装", this);
	QAction* action2 = new QAction("食品", this);
	QAction* action3 = new QAction("服装",this);
	QAction* action4 = new QAction("食品", this);
	
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

	//价格以及库存设置
	QDoubleValidator* validator = new QDoubleValidator(this);
	ui.lineEdit_2->setValidator(validator);
	ui.lineEdit_3->setValidator(validator);
	ui.textEdit->setReadOnly(true);
	ui.textEdit_2->setReadOnly(true);
	ui.textEdit_3->setReadOnly(true);
	ui.textEdit_4->setReadOnly(true);

	//下单以及售出按钮初始不可选
	ui.pushButton_4->setCheckable(false);
	ui.pushButton_3->setCheckable(false);

	//连接槽函数
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


//初始化数据库
void NewWidget::initDataBase() {
	bool ok;
	m_db = QSqlDatabase::addDatabase("QSQLITE");
	m_db.setDatabaseName("goods.db");
	//QMessageBox::information(this, "test", QDir::currentPath(), QMessageBox::Ok);
	ok = m_db.open();
	if (!ok)
		qDebug() << __FUNCTION__ << m_db.lastError().text();

}

//初始化TableView
void NewWidget::initTableView() {
	if (ui.toolButton->text() == "服装") {
		m_sqlTableModel->setTable("garment");
		//设置为手动提交
		m_sqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

		m_sqlTableModel->select();

		m_sqlTableModel->setHeaderData(0, Qt::Horizontal, "服装名称");
		m_sqlTableModel->setHeaderData(1, Qt::Horizontal, "进价(￥)");
		m_sqlTableModel->setHeaderData(2, Qt::Horizontal, "售价(￥)");
		m_sqlTableModel->setHeaderData(3, Qt::Horizontal, "库存");
	}
	else if (ui.toolButton->text() == "食品") {
		m_sqlTableModel->setTable("food");
		//QMessageBox::information(this, "test", QDir::currentPath(), QMessageBox::Ok);
		//设置为手动提交
		m_sqlTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

		m_sqlTableModel->select();

		m_sqlTableModel->setHeaderData(0, Qt::Horizontal, "食品名称");
		m_sqlTableModel->setHeaderData(1, Qt::Horizontal, "进价(￥)");
		m_sqlTableModel->setHeaderData(2, Qt::Horizontal, "售价(￥)");
		m_sqlTableModel->setHeaderData(3, Qt::Horizontal, "库存");
	}

	//QHeaderView* header = this->horizontalHeader();
	//// 设置表头的调整模式为固定
	//header->setSectionResizeMode(QHeaderView::Fixed);

	ui.tableView->setModel(m_sqlTableModel);
}


void NewWidget::on_fuzhuang_triggered() {
	qDebug() << "服装";
	ui.toolButton->setText("服装");
	initTableView();
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.spinBox->setValue(0);
}

void NewWidget::on_shipin_triggered() {
	qDebug() << "食品";
	ui.toolButton->setText("食品");
	initTableView();
	ui.lineEdit->clear();
	ui.lineEdit_2->clear();
	ui.lineEdit_3->clear();
	ui.spinBox->setValue(0);
}



void NewWidget::on_ruku_clicked() {
	QString table = "";
	if (ui.toolButton->text() == "服装") 
		table = "garment";
	else if (ui.toolButton->text() == "食品") 
		table = "food";
	if (table != "garment" && table != "food") {
		QMessageBox::information(this, "错误", "未选择产品类型", QMessageBox::Ok);
		return;
	}
	m_sqlTableModel->setTable(table);
	QString gName = ui.lineEdit->text();
	QString gInPrice = ui.lineEdit_2->text();
	QString gOutPrice = ui.lineEdit_3->text();
	QString gInventory = ui.spinBox->text();

	// 设置数据模型的过滤条件为商品名称
	m_sqlTableModel->setFilter(QString("name = '%1'").arg(gName));
	// 查询数据
	if (!m_sqlTableModel->select()) {
		qDebug() << "Failed to select data:" << m_sqlTableModel->lastError().text();
		return;
	}

	// 判断是否存在目标数据
	if (m_sqlTableModel->rowCount() > 0) {
		// 获取第一行（从0开始计数）的索引
		QModelIndex index = m_sqlTableModel->index(0, 0);
		
		// 修改数据模型中的价格和库存
		m_sqlTableModel->setData(m_sqlTableModel->index(index.row(), 1), gInPrice);
		m_sqlTableModel->setData(m_sqlTableModel->index(index.row(), 2), gOutPrice);
		gInventory = QString::number(gInventory.toInt() + m_sqlTableModel->index(index.row(), 3).data().toInt(), 'f', 0);
		m_sqlTableModel->setData(m_sqlTableModel->index(index.row(), 3), gInventory);
		// 提交更改到数据库
		if (!m_sqlTableModel->submitAll()) {
			qDebug() << "Failed to submit changes:" << m_sqlTableModel->lastError().text();
			return;
		}
		qDebug() << "Update data successfully";
	}
	else {
		// 创建一个新记录
		QSqlRecord record = m_sqlTableModel->record();
		record.setValue("name", gName);
		record.setValue("in_price", gInPrice);
		record.setValue("out_price", gOutPrice);
		record.setValue("inventory", gInventory);
		// 插入新记录到数据模型中
		if (!m_sqlTableModel->insertRecord(-1, record)) {
			qDebug() << "Failed to insert record:" << m_sqlTableModel->lastError().text();
			return;
		}
		// 提交更改到数据库
		if (!m_sqlTableModel->submitAll()) {
			qDebug() << "Failed to submit changes:" << m_sqlTableModel->lastError().text();
			return;
		}
		qDebug() << "Insert data successfully";
	}
	
	// 清除过滤条件
	m_sqlTableModel->setFilter("");

	if(table=="garment")
		m_sqlTableModel->setHeaderData(0, Qt::Horizontal, "服装名称");
	else if(table == "food")
		m_sqlTableModel->setHeaderData(0, Qt::Horizontal, "食品名称");
	m_sqlTableModel->setHeaderData(1, Qt::Horizontal, "进价(￥)");
	m_sqlTableModel->setHeaderData(2, Qt::Horizontal, "售价(￥)");
	m_sqlTableModel->setHeaderData(3, Qt::Horizontal, "库存");

	// 设置表格视图的数据模型为刚刚创建的model
	ui.tableView->setModel(m_sqlTableModel);
	//清空上一项数据
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
	if (ui.toolButton->text() == "服装") {
		sqlString = "DELETE FROM garment";
	}
	else if (ui.toolButton->text() == "食品") {
		sqlString = "DELETE FROM food";
	}
	bool ok = sql.exec(sqlString);
	if (ok) {
		qDebug() << "成功清仓";
		m_sqlTableModel->clear();
		return;
	}
	else {
		qDebug() << "清仓失败" << sql.lastError().text();
		return;
	}
}

void NewWidget::on_fuzhuang2_triggered() {
	qDebug() << "服装2";
	ui.toolButton_2->setText("服装");
	//initTableView();
	ui.lineEdit_4->clear();
	ui.textEdit->clear();
	ui.textEdit_2->clear();
	ui.textEdit_3->clear();
	ui.spinBox_2->setValue(0);
}

void NewWidget::on_shipin2_triggered() {
	qDebug() << "食品2";
	ui.toolButton_2->setText("食品");
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
	if (ui.toolButton_2->text() == "服装")
		table1 = "garment";
	else if (ui.toolButton_2->text() == "食品")
		table1 = "food";
	if (table1 != "garment" && table1 != "food") {
		QMessageBox::information(this, "错误", "未选择产品类型", QMessageBox::Ok);
		return;
	}
	m_sqlTableModel->setTable(table1);

	QString gName = ui.lineEdit_4->text();
	// 设置数据模型的过滤条件为商品名称
	m_sqlTableModel->setFilter(QString("name = '%1'").arg(gName));
	// 查询数据
	if (!m_sqlTableModel->select()) {
		qDebug() << "Failed to select data:" << m_sqlTableModel->lastError().text();
		return;
	}

	// 判断是否存在目标数据
	if (m_sqlTableModel->rowCount() > 0) {

		// 获取第一行（从0开始计数）的索引
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
	//目标数据不存在
	else {
		QMessageBox::information(this, "错误","未找到目标产品", QMessageBox::Ok);
		ui.lineEdit_4->setText("");
		return;
	}
	//清除过滤条件
	m_sqlTableModel->setFilter("");
}

void NewWidget::on_shouchu_clicked() {
	if (!ui.pushButton_3->isCheckable()) return;
	if (ui.spinBox_2->text().toInt() > ui.textEdit_2->toPlainText().toInt()) {
		QMessageBox::information(this, "失败", "库存不足", QMessageBox::Ok);
		ui.pushButton_4->setCheckable(false);
		return;
	}
	QMessageBox::information(this, "成功", "已加入订单", QMessageBox::Ok);
	
	ui.pushButton_4->setCheckable(true);
	QTime ct = QTime::currentTime();
	ui.textEdit_4->setText(ui.textEdit_4->toPlainText()+"\n------------------------\n");
	ui.textEdit_4->setText(ui.textEdit_4->toPlainText() + ct.toString("hh:mm:ss.zzz") + "\n" + "产品名称：" + ui.lineEdit_4->text()
		+ "\n数量：" + ui.spinBox_2->text() + "\n单价：" + ui.textEdit->toPlainText() + "\n总价：" + ui.textEdit_3->toPlainText());
	m_selledNumber++;
	ui.pushButton_3->setCheckable(false);
}

void NewWidget::on_xiadan_clicked() {
	if (!ui.pushButton_4->isCheckable()) return;
	QMessageBox::information(this, "成功", "下单成功", QMessageBox::Ok);
	QTime ct = QTime::currentTime();
	ui.textEdit_4->setText(ui.textEdit_4->toPlainText() + "\n------------------------\n");
	ui.textEdit_4->setText(ui.textEdit_4->toPlainText() + "日期：" + ct.toString("hh:mm:ss.zzz") + "\n" + "订单号：" + QString::number(m_selledNumber, 'f', 0)
		+ "\n应付款总额：" + ui.textEdit_3->toPlainText());
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


//当商品数量改变时更新总价
void NewWidget::on_spinBox_clicked() {
	if (ui.pushButton_3->isCheckable()) {
		float num = ui.spinBox_2->value() * ui.textEdit->toPlainText().toFloat();
		ui.textEdit_3->setPlainText(QString::number(num));
	}
}

NewWidget::~NewWidget() {
	delete m_sqlTableModel;
}


