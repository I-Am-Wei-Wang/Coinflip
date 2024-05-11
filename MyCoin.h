#ifndef MYCOIN_H_
#define MYCOIN_H_

#include<QPushButton>
class QTimer;
class MyCoin : public QPushButton
{
	Q_OBJECT
public:
	MyCoin(const QString& btnImg, QPushButton* parent = nullptr);
	void changeFlag();
	int m_posX;
	int m_posY;
	int m_flag;
	bool m_isWin;
protected:
	void mousePressEvent(QMouseEvent* ev)override;

private:
	QTimer* m_timer1;
	QTimer* m_timer2;
	int m_min = 1;
	int m_max = 8;
	bool m_isAnimation;
};

#endif // !MYCOIN_H_
