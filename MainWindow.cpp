#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MyPushButton.h"
#include "ChooseLevelWindow.h"
#include<QPainter>
#include<QTimer>
#include<QMediaPlayer>
#include<QAudioOutput>
MainWindow::MainWindow(QWidget* parent)
	:QWidget(parent)
	,ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	init();
}
void MainWindow::init()
{
	//设置窗口大小
	setFixedSize(320, 588);
	//设置窗口图标
	setWindowIcon(QIcon(":/Resource/Coin1.png"));
	//设置标题
	setWindowTitle("翻金币");
	{
		//开始按钮
		MyPushButton* startBtn = new MyPushButton;
		startBtn->setParent(this);
		startBtn->init(":/Resource/MenuSceneStartButton.png");
		startBtn->move((this->width() - startBtn->width()) * 0.5, this->height() * 0.7);
		m_chooseWidget = new ChooseLevelWindow(this);
		m_player = new QMediaPlayer(this);
		auto audio = new QAudioOutput; (this);
		m_player->setAudioOutput(audio);
		m_player->setSource(QUrl("qrc:/Resource/TapButtonSound.wav"));
		connect(startBtn, &MyPushButton::clicked, [=]
			{
				/*Qt 6中的QMediaPlayer要求你使用setAudioOutput()和setVideoOutput()方法主动连接到音频和视频输出。
				不设置音频输出将意味着该媒体播放器不播放音频。*/
				m_player->play();
				startBtn->zoomDown();
				startBtn->zoomUp();
				//延时进入到选择关卡
				QTimer::singleShot(300,this, [=]
					{
						m_chooseWidget->setGeometry(this->geometry());
						//自身隐藏
						this->hide();
						//显示选择关卡场景
						m_chooseWidget->show();
					});

			});
	}
	connect(m_chooseWidget, &ChooseLevelWindow::chooseBack, [=]
		{
			this->setGeometry(m_chooseWidget->geometry());
			m_chooseWidget->hide();
			this->show();
		});
}
MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	//主背景
	painter.drawPixmap(0, 0, this->width(),this->height(), QPixmap(":/Resource/PlayLevelSceneBg.png"));
	//背景图标
	QPixmap pix;
	pix.load(":/Resource/Title.png");
	pix = pix.scaled(pix.size() * 0.5);
	painter.drawPixmap(10,30, pix);
	
}
