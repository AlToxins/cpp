#include "Calculator.h"
#include<qdebug.h>
#include<math.h>


Calculator::Calculator(QWidget* parent)
    : QMainWindow(parent), m_operatorClicked(false), m_string("0"), m_dotClicked(false), m_equalClicked(false)
{
    ui.setupUi(this);
    this->setWindowTitle("������");
    this->setWindowIcon(QIcon(":/image/calculate.png"));
 
    
    //����������
    ui.textEdit->setStyleSheet("border:none; background-color: transparent;font-size:45px;font-weight:500;font-family:΢���ź�");
    ui.textEdit_2->setStyleSheet("border:none; background-color: transparent;font-size:20px;font-weight:100;font-family:΢���ź�;color:rgb(135,135,135);");
    
    ui.textEdit->setAlignment(Qt::AlignRight);
    ui.textEdit_2->setReadOnly(true);
    ui.textEdit_2->setAlignment(Qt::AlignRight);

    ui.textEdit->setText("0");
    ui.textEdit->setAlignment(Qt::AlignRight);

    ui.verticalLayout->setStretchFactor(ui.textEdit, 1);
    ui.verticalLayout->setStretchFactor(ui.textEdit_2, 1);
    ui.verticalLayout->setStretchFactor(ui.gridLayout, 4);


    //���Ӳۺ���

    //���������
    connect(ui.pushButton_15, &QPushButton::clicked, this, &Calculator::on_negative_clicked);
    connect(ui.pushButton_25, &QPushButton::clicked, this, &Calculator::on_dot_clicked);
    connect(ui.pushButton_10, &QPushButton::clicked, this, &Calculator::on_delete_clicked);
    connect(ui.pushButton_8, &QPushButton::clicked, this, &Calculator::on_clear_clicked);
    connect(ui.pushButton_9, &QPushButton::clicked, this, &Calculator::on_clear_clicked);
    connect(ui.pushButton_29, &QPushButton::clicked, this, [=] {on_operator_clicked(ui.pushButton_29); });
    connect(ui.pushButton_28, &QPushButton::clicked, this, [=] {on_operator_clicked(ui.pushButton_28); });
    connect(ui.pushButton_27, &QPushButton::clicked, this, [=] {on_operator_clicked(ui.pushButton_27); });
    connect(ui.pushButton_26, &QPushButton::clicked, this, [=] {on_operator_clicked(ui.pushButton_26); });
    connect(ui.pushButton_16, &QPushButton::clicked, this, [=] {on_operator_clicked(ui.pushButton_16); });
    connect(ui.pushButton_21, &QPushButton::clicked, this, [=] {on_operator_clicked(ui.pushButton_21); });
    connect(ui.pushButton_30, &QPushButton::clicked, this, [=] {on_operator_clicked(ui.pushButton_30); });
    connect(ui.pushButton_4, &QPushButton::clicked, this, [=] {on_operator_clicked(ui.pushButton_4); });
    connect(ui.pushButton_11, &QPushButton::clicked, this, &Calculator::on_reciprocal_clicked);
    connect(ui.pushButton, &QPushButton::clicked, this, &Calculator::on_square_clicked);
    connect(ui.pushButton_2, &QPushButton::clicked, this, &Calculator::on_extract_clicked);
    connect(ui.pushButton_3, &QPushButton::clicked, this, &Calculator::on_absolute_clicked);
    connect(ui.pushButton_7, &QPushButton::clicked, this, &Calculator::on_percent_clicked);

    //���ְ�ť
    connect(ui.pushButton_18, &QPushButton::clicked, this, [=] { on_number_clicked(ui.pushButton_18); });
    connect(ui.pushButton_12, &QPushButton::clicked, this, [=] {on_number_clicked(ui.pushButton_12); });
    connect(ui.pushButton_13, &QPushButton::clicked, this, [=] {on_number_clicked(ui.pushButton_13); });
    connect(ui.pushButton_14, &QPushButton::clicked, this, [=] {on_number_clicked(ui.pushButton_14); });
    connect(ui.pushButton_17, &QPushButton::clicked, this, [=] {on_number_clicked(ui.pushButton_17); });
    connect(ui.pushButton_19, &QPushButton::clicked, this, [=] {on_number_clicked(ui.pushButton_19); });
    connect(ui.pushButton_22, &QPushButton::clicked, this, [=] {on_number_clicked(ui.pushButton_22); });
    connect(ui.pushButton_23, &QPushButton::clicked, this, [=] {on_number_clicked(ui.pushButton_23); });
    connect(ui.pushButton_24, &QPushButton::clicked, this, [=] {on_number_clicked(ui.pushButton_24); });
    connect(ui.pushButton_20, &QPushButton::clicked, this, [=] {on_number_clicked(ui.pushButton_20); });
}
 
Calculator::~Calculator()
{}


void Calculator::resizeEvent(QResizeEvent* event){
    QWidget::resizeEvent(event);    //���û���ĺ���
    //��д��������������
    int w = this->width();
    int h = this->height();

    ui.layoutWidget->setGeometry(QRect(0, 0, w, h));

    ui.verticalLayout->setGeometry(QRect(0, 0, w, h));
    qDebug() << w << h;

}

//����m_numberStack�еĺ�׺���ʽ���������������������ѹ��m_numberStack��
QString Calculator::calculate() {
    //ɨ�������
    QString Operator = m_numberStack.top();
    m_numberStack.pop();
    //ɨ������
    float num1 = m_numberStack.top().toFloat();
    m_numberStack.pop();
    float num2 = m_numberStack.top().toFloat();
    m_numberStack.pop();

    float result=0;
    if (Operator == "+")result = num1 + num2;
    else if (Operator == "-")result = num2 - num1;
    else if (Operator == "��")result = num2 * num1;
    else if (Operator == "��")result = num2 / num1;
    else if (Operator == "mod")result = (int)num2 % (int)num1;
    m_numberStack.push(QString::number(result,'f', 4)); //f��ʾ�ǿ�ѧ��������4��ʾ����С�����4λ
    return QString::number(result, 'f', 4);
}

//�ж�������Ƿ���ջ
bool Calculator::operatorInStack(QString text) {
    if (text == "(" || m_operatorStack.empty() || m_operatorStack.top() == "(") return true;
    //����������ȫ������ֱ��������
    else if (text == ")") return false;
    //��ջֱ�ӽ�������
    else if (text == "+" || text == "-"||text=="=")return false;
    else if ((text == "��" || text == "��"||text=="mod") && (m_operatorStack.top() == "��" || m_operatorStack.top() == "��"||m_operatorStack.top()=="mod"))return false;
    else return true;
}

//���+/-��ť
void Calculator::on_negative_clicked() {
    int size = ui.textEdit->toPlainText().size();
    float number = ui.textEdit->toPlainText().toFloat() * (-1);
    QString numString = QString::number(number, 'f', 4);
    ui.textEdit->setText(numString);
    ui.textEdit->setAlignment(Qt::AlignRight);
    m_string = m_string.left(m_string.size() - size) + numString;

}

//���������ť
void Calculator::on_reciprocal_clicked() {
    int size = ui.textEdit->toPlainText().size();
    if (ui.textEdit->toPlainText().toFloat() != 0) {
        float number = 1 / ui.textEdit->toPlainText().toFloat();
        QString numString = QString::number(number, 'f', 4);
        ui.textEdit->setText(numString);
        ui.textEdit->setAlignment(Qt::AlignRight);
        if (m_string.right(1) != ")")
            m_string = m_string.left(m_string.size() - size) + numString;
        else {
            m_string = m_string + "(rec)";
            m_numberStack.pop();
            m_numberStack.push(numString);
        }
    }
    else {
        ui.textEdit->setText("��������Ϊ��");
        ui.textEdit->setAlignment(Qt::AlignRight);
    }
}

//���.��ť
void Calculator::on_dot_clicked() {
    if (!m_dotClicked) {
        ui.textEdit->setText(ui.textEdit->toPlainText() + ".");
        ui.textEdit->setAlignment(Qt::AlignRight);
        m_string = m_string + ".";
        m_dotClicked = true;
    }
}

//ɾ����ť
void Calculator::on_delete_clicked() {
    if (!m_operatorClicked) {
        QString string = ui.textEdit->toPlainText().left(ui.textEdit->toPlainText().size() - 1);
        m_string = m_string.left(m_string.size() - 1);
        if (string == "") {
            ui.textEdit->setPlainText("0");
            ui.textEdit->setAlignment(Qt::AlignRight);
            
        }
        else {
            ui.textEdit->setText(string);
            ui.textEdit->setAlignment(Qt::AlignRight);
        }
    }
}

//��հ�ť
void Calculator::on_clear_clicked() {
    ui.textEdit->setText("0");
    ui.textEdit->setAlignment(Qt::AlignRight);
    ui.textEdit_2->setText("");
    ui.textEdit_2->setAlignment(Qt::AlignRight);
    m_operatorClicked = false;

    m_string = "0";
    //���ջ
    stack<QString>().swap(m_numberStack);
    stack<QString>().swap(m_operatorStack);
}

//ƽ����ť
void Calculator::on_square_clicked() {
    int size = ui.textEdit->toPlainText().size();
    float number = pow(ui.textEdit->toPlainText().toFloat(), 2);
    QString numString = QString::number(number, 'f', 4);
    ui.textEdit->setText(numString);
    ui.textEdit->setAlignment(Qt::AlignRight);
    if (m_string.right(1) != ")")
        m_string = m_string.left(m_string.size() - size) + numString;
    else {
        m_string = m_string + "(sqr)";
        m_numberStack.pop();
        m_numberStack.push(numString);
    }
}

//������ť
void Calculator::on_extract_clicked() {
    int size = ui.textEdit->toPlainText().size();
    if (ui.textEdit->toPlainText().toFloat() >= 0) {
        float number = pow(ui.textEdit->toPlainText().toFloat(), 0.5);
        QString numString = QString::number(number, 'f', 4);
        ui.textEdit->setText(numString);
        ui.textEdit->setAlignment(Qt::AlignRight);
        if (m_string.right(1) != ")")
            m_string = m_string.left(m_string.size() - size) + numString;
        else {
            m_string = m_string + "(ext)";
            m_numberStack.pop();
            m_numberStack.push(numString);
        }
    }
    else {
        ui.textEdit->setText("��Ч����");
        ui.textEdit->setAlignment(Qt::AlignRight);
    }
}


//����ֵ��ť
void Calculator::on_absolute_clicked() {
    int size = ui.textEdit->toPlainText().size();
    float number = abs(ui.textEdit->toPlainText().toFloat());
    QString numString = QString::number(number, 'f', 4);
    //QString originNumString = ui.textEdit->toPlainText();
    ui.textEdit->setText(numString);
    ui.textEdit->setAlignment(Qt::AlignRight);
    if (m_string.right(1) != ")")
        m_string = m_string.left(m_string.size() - size) + numString;
    else {
        m_string = m_string + "(abs)";
        m_numberStack.pop();
        m_numberStack.push(numString);
    }
}

//�ٷֺŰ�ť
void Calculator::on_percent_clicked() {
    int size = ui.textEdit->toPlainText().size();
    float number = ui.textEdit->toPlainText().toFloat()/100;
    QString numString = QString::number(number, 'f', 4);
    ui.textEdit->setText(numString);
    ui.textEdit->setAlignment(Qt::AlignRight);
    if (m_string.right(1) != ")")
        m_string = m_string.left(m_string.size() - size) + numString;
    else {
        m_string = m_string + "(%)";
        m_numberStack.pop();
        m_numberStack.push(numString);
    }
}

//�������ť
void Calculator::on_operator_clicked(QPushButton* button) {
    m_equalClicked = false;
    if (m_operatorClicked == false||button->text()=="(") {
        m_string = m_string + button->text();
        //����С���㰴ť
        m_dotClicked = false;
        m_operatorClicked = true;
        //�Ƚ�����ѹ��m_numberStack(ǰ������һ����ť������)
        if (button->text() != "(") {
            m_number = ui.textEdit->toPlainText();
            if (m_string[m_string.size() - 2] != ")")
                m_numberStack.push(m_number);
        }
        else if (button->text() == "(") {
            m_number = "0";
        }
        //��¼���
        QString result = m_number;

        if (button->text() != ")") {
            while (!operatorInStack(button->text())) {
                m_numberStack.push(m_operatorStack.top());
                //��������׺���ʽ
                result = calculate();
                m_operatorStack.pop();
            }
            m_operatorStack.push(button->text());
            if (button->text() == "=") {
                m_operatorClicked = false;
                m_equalClicked = true;
                stack<QString>().swap(m_numberStack);
                stack<QString>().swap(m_operatorStack);
            }

        }
        else if (button->text() == ")") {
            m_operatorClicked = false;
            while (m_operatorStack.top() != "(") {
                m_numberStack.push(m_operatorStack.top());
                //��������׺���ʽ
                result = calculate();
                m_operatorStack.pop();
            }
            m_operatorStack.pop();

        }

        ui.textEdit->setText(result);
        ui.textEdit->setAlignment(Qt::AlignRight);
        ui.textEdit_2->setText(m_string);
        ui.textEdit_2->setAlignment(Qt::AlignRight);

        if (button->text() == "=") m_string = result;
    }
}

//���ְ�ť
void Calculator::on_number_clicked(QPushButton* button) {
    if (m_string == "0")m_string = button->text();

    else m_string = m_string + button->text();
    //�������������֮ǰδ�����κ�����
    if (ui.textEdit->toPlainText() == "0" && !m_operatorClicked&&!m_equalClicked) {
        ui.textEdit->setPlainText("");
        ui.textEdit->setAlignment(Qt::AlignRight);

        ui.textEdit->setText(ui.textEdit->toPlainText() + button->text());
        ui.textEdit->setAlignment(Qt::AlignRight);
    }
    //�������������֮ǰ�Ѿ���������,�����������ֺ��������
    else if (ui.textEdit->toPlainText() != 0 && !m_operatorClicked&&!m_equalClicked) {
        ui.textEdit->setText(ui.textEdit->toPlainText() + button->text());
        ui.textEdit->setAlignment(Qt::AlignRight);
    }

    //���Ѿ����������
    else if (m_operatorClicked&&!m_equalClicked) {
        ui.textEdit->setText(button->text());
        ui.textEdit->setAlignment(Qt::AlignRight);
        m_operatorClicked = false;

    }
    if (m_equalClicked) {
        on_clear_clicked();
        m_string = m_string + button->text();
        ui.textEdit->setText(button->text());
        ui.textEdit->setAlignment(Qt::AlignRight);
        m_equalClicked = false;
    }
}

