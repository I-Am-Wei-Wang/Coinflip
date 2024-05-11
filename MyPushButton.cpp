#include "MyPushButton.h"

#include<QPropertyAnimation>
MyPushButton::MyPushButton(QPushButton* parent)
	:QPushButton(parent)
{
	
}

void MyPushButton::init(const QString& normalImg, QString pressImg)
{
	this->normalImgPath = normalImg;
	this->pressImgPath = pressImg;
	QPixmap pix;
	bool ret = pix.load(this->normalImgPath);
	if (!ret) {
		qDebug() << "图片加载失败";
		return;
	}
	//qDebug() << "图片大小 ： " << pix.size();
	//设置图片固定大小
	this->setFixedSize(pix.size());
	this->setStyleSheet("QPushButton{border:none;}");
	//设置图标
	this->setIcon(QIcon(pix));
	//设置图标大小
	this->setIconSize(pix.size());

}

void MyPushButton::zoomUp()
{
	//创建动态对象
	QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
	//设置动画时间间隔
	animation->setDuration(200);
	//起始位置
	animation->setStartValue(QRect(this->x(), this->y()+10, this->width(), this->height()));
	//结束位置
	animation->setEndValue(QRect(this->x(), this->y(),this->width(),this->height()));
	//设置弹跳曲线
	animation->setEasingCurve(QEasingCurve::OutBounce);
	//执行动画
	animation->start();
}

void MyPushButton::zoomDown()
{
	//创建动态对象
	QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
	//设置动画时间间隔
	animation->setDuration(200);
	//起始位置
	animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
	//结束位置
	animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
	//设置弹跳曲线
	animation->setEasingCurve(QEasingCurve::OutBounce);
	//执行动画
	animation->start();
}

void MyPushButton::mousePressEvent(QMouseEvent* ev)
{
	if (!this->pressImgPath.isEmpty()) {
		QPixmap pix;
		bool ret = pix.load(this->pressImgPath);
		if (!ret) {
			qDebug() << "图片加载失败";
			return;
		}
		//qDebug() << "图片大小 ： " << pix.size();
		//设置图片固定大小
		this->setFixedSize(pix.size());
		this->setStyleSheet("QPushButton{border:none;}");
		//设置图标
		this->setIcon(QIcon(pix));
		//设置图标大小
		this->setIconSize(pix.size());
	}
	//让父类执行其他的内容
	return QPushButton::mousePressEvent(ev);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent* ev)
{
	if (!this->pressImgPath.isEmpty()) {
		QPixmap pix;
		bool ret = pix.load(this->normalImgPath);
		if (!ret) {
			qDebug() << "图片加载失败";
			return; 
		}
		//qDebug() << "图片大小 ： " << pix.size();
		//设置图片固定大小
		this->setFixedSize(pix.size());
		this->setStyleSheet("QPushButton{border:none;}");
		//设置图标
		this->setIcon(QIcon(pix));
		//设置图标大小
		this->setIconSize(pix.size());
	}
	//让父类执行其他的内容
	return QPushButton::mouseReleaseEvent(ev);
}


