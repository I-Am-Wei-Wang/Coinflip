#include "MyCoin.h"
#include<QTimer>
MyCoin::MyCoin(const QString& btnImg, QPushButton* parent)
	:QPushButton(parent)
	,m_isAnimation(false)
	,m_isWin(false)
{
	QPixmap pix;
	bool ret = pix.load(btnImg);
	if (!ret) {
		qDebug() << "图片加载失败";
		return;
	}
	this->setFixedSize(pix.size());
	this->setStyleSheet("QPushButton{border:none;}");
	this->setIcon(pix);
	this->setIconSize(pix.size());

	//初始化定时器对象
	this->m_timer1 = new QTimer(this);
	connect(this->m_timer1, &QTimer::timeout, [=]
		{
			QPixmap pix;
			QString str = QString(":/Resource/Coin%1.png").arg(this->m_min++);
			pix.load(str);
			this->setIcon(pix);
			if (this->m_min > this->m_max) {
				this->m_min = 1;
				this->m_isAnimation = false;
				this->m_timer1->stop();
			}
		});
	this->m_timer2 = new QTimer(this);
	connect(this->m_timer2, &QTimer::timeout, [=]
		{
			QPixmap pix;
			QString str = QString(":/Resource/Coin%1.png").arg(this->m_max--);
			pix.load(str);
			this->setIcon(pix);
			if (this->m_max < this->m_min) {
				this->m_max = 8;
				this->m_isAnimation = false;
				this->m_timer2->stop();
			}
		});
}

void MyCoin::changeFlag()
{
	this->m_isAnimation = true;
	if (this->m_flag) {
		this->m_timer1->start(30);
		this->m_flag = 0;
		
	}
	else{
		this->m_timer2->start(30);
		this->m_flag = 1;
	}

}

void MyCoin::mousePressEvent(QMouseEvent* ev)
{
	if (this->m_isAnimation || this->m_isWin)return;//防止点的太快//防止赢了还按
	else return QPushButton::mousePressEvent(ev);//此处并不是返回值而是调用一下虚函数
}
