#ifndef PLAYWINDOW_H_
#define PLAYWINDOW_H_

#include<QMainWindow>
class MyCoin;
class QMediaPlayer;
class PlayWindow : public QMainWindow
{
	Q_OBJECT
public:
	PlayWindow(const int index,QMainWindow* parent = nullptr);
	void init();
signals:
	void playBack();
protected:
	void paintEvent(QPaintEvent* ev)override;
private:

	int m_levelIndex;
	int m_gameArray[4][4];
	MyCoin* m_coinArr[4][4];
	QMediaPlayer* m_player1{};
	QMediaPlayer* m_player2{};
};


#endif // !PLAYWINDOW_H_
