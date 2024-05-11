#include "ChooseLevelWindow.h"
#include "MyPushButton.h"
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QMediaPlayer>
#include<QAudioOutput>
ChooseLevelWindow::ChooseLevelWindow(QWidget* parent)
	:QMainWindow(parent)
{
	init();
}

void ChooseLevelWindow::init()
{
	//设置窗口大小
	setFixedSize(320, 588);
	//设置窗口图标
	setWindowIcon(QIcon(":/Resource/Coin1.png"));
	//设置标题
	setWindowTitle("选择关卡场景");

	auto audio1 = new QAudioOutput; (this);
	auto audio2 = new QAudioOutput; (this);

	m_player1 = new QMediaPlayer(this);
	m_player1->setAudioOutput(audio1);
	m_player1->setSource(QUrl("qrc:/Resource/BackButtonSound.wav"));

	m_player2 = new QMediaPlayer(this);
	m_player2->setAudioOutput(audio2);
	m_player2->setSource(QUrl("qrc:/Resource/TapButtonSound.wav"));

	MyPushButton* backBtn = new MyPushButton;
	backBtn->setParent(this);
	backBtn->init(":/Resource/BackButton.png", ":/Resource/BackButtonSelected.png");
	backBtn->move(this->width() - backBtn->width(), this->height() - backBtn->height());
	//点击返回
	connect(backBtn, &QPushButton::clicked, [=]
		{
			m_player1->play();
			QTimer::singleShot(300, this, [=]
				{
					emit this->chooseBack();
				});
		});

	
	
	//创建选择关卡的按钮
	for (size_t i = 0; i < 20; i++)
	{
		MyPushButton* menuBtn = new MyPushButton;
		menuBtn->setParent(this);
		menuBtn->init(":/Resource/LevelIcon.png");
		menuBtn->move(25 + i % 4 * 70, 130 + i / 4 * 70);

		//监听每个按钮的点击事件
		connect(menuBtn, &QPushButton::clicked, [=]
			{
				//qDebug() << "点击了 ： " << i + 1 << " 关";
				//进入到游戏场景
				m_player2->play();
				m_play = new PlayWindow(i+1,this);
				QTimer::singleShot(300, this, [=]
					{
						m_play->setGeometry(this->geometry());
						this->hide();
						m_play->show();
					});
				connect(m_play, &PlayWindow::playBack, [=]
					{
						this->setGeometry(m_play->geometry());
						m_play->close();
						this->show();
					});
			});
		//数字
		QLabel* lab = new QLabel(this);
		lab->setFixedSize(menuBtn->size());
		lab->setText(QString::number(i+1));
		lab->move(25 + i % 4 * 70, 130 + i / 4 * 70);
		lab->setAlignment(Qt::AlignCenter);
		//设置让鼠标进行穿透
		lab->setAttribute(Qt::WA_TransparentForMouseEvents);
	}
}

void ChooseLevelWindow::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);
	QPixmap pix;
	//加载背景
	pix.load(":/Resource/OtherSceneBg.png");
	painter.drawPixmap(0, 0, this->width(),this->height(),pix);
	//加载标题
	pix.load(":/Resource/Title.png");
	painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(),pix.height(),pix);

}
