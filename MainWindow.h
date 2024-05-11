#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include<QWidget>
class QMediaPlayer;
class ChooseLevelWindow;
namespace Ui { class MainWindow; }
class MainWindow : public QWidget
{
public:
	MainWindow(QWidget* parent = nullptr);
	void init();
	~MainWindow();
protected:
	void paintEvent(QPaintEvent* event)override;
private:
	Ui::MainWindow* ui{};
	ChooseLevelWindow* m_chooseWidget{};
	QMediaPlayer* m_player{};
};

#endif // !MAINWINDOW_H_
