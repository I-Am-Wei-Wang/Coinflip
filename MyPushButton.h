#ifndef MYPUSHBUTTON_H_
#define MYPUSHBUTTON_H_

#include<QPushButton>

class MyPushButton : public QPushButton
{
	Q_OBJECT
public:

	MyPushButton(QPushButton* parent = nullptr);
	void init(const QString& normalImg,QString pressImg = "");
	void zoomUp();
	void zoomDown();

protected:
	void mousePressEvent(QMouseEvent* ev)override;
	void mouseReleaseEvent(QMouseEvent* ev)override;
private:
	QString normalImgPath;
	QString pressImgPath;

};

#endif // !MYPUSHBUTTON_H_
