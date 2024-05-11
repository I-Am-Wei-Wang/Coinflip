#ifndef CHOOSELEVELWINDOW_H_
#define CHOOSELEVELWINDOW_H_
#include "PlayWindow.h"
#include<QMainWindow>
class QMediaPlayer;
class ChooseLevelWindow : public QMainWindow
{
	Q_OBJECT
public:
	ChooseLevelWindow(QWidget* parent = nullptr);
	void init();
signals:
	void chooseBack();
protected:
	void paintEvent(QPaintEvent* ev)override;
private:
	//游戏场景指针
	PlayWindow* m_play{};
	QMediaPlayer* m_player1{};
	QMediaPlayer* m_player2{};
};


#endif // !CHOOSELEVELWINDOW_H_
