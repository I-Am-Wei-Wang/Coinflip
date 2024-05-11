#include "PlayWindow.h"
#include "MyPushButton.h"
#include "MyCoin.h"
#include "dataconfig.h"
#include<QPushButton>
#include<QPainter>
#include<QTimer>
#include<QEventLoop>
#include<QLabel>
#include<QPropertyAnimation>
#include<QMediaPlayer>
#include<QAudioOutput>
PlayWindow::PlayWindow(const int index, QMainWindow* parent)
	:QMainWindow(parent)
	,m_levelIndex(index)
{
	init();
}

void PlayWindow::init()
{
	//设置窗口大小
	setFixedSize(320, 588);
	//设置窗口图标
	setWindowIcon(QIcon(":/Resource/Coin1.png"));
	//设置标题
	setWindowTitle("翻金币");
	
	auto audio1 = new QAudioOutput; (this);
	auto audio2 = new QAudioOutput; (this);

	m_player1 = new QMediaPlayer(this);
	m_player1->setAudioOutput(audio1);
	m_player1->setSource(QUrl("qrc:/Resource/BackButtonSound.wav"));
	
	m_player2 = new QMediaPlayer(this);
	m_player2->setAudioOutput(audio2);
	m_player2->setSource(QUrl("qrc:/Resource/ConFlipSound.wav"));

	//返回按钮
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
					emit this->playBack();
				});
		});

	//显示当前关卡数
	QLabel* lab = new QLabel(this);
	QFont font;
	font.setFamily("JetBrains Mono");
	font.setPointSize(20);
	lab->setFont(font);
	lab->setText("Level:" + QString::number(this->m_levelIndex));
	lab->setGeometry(30, this->height() - 50, 130, 50);

	//初始化每个关卡的二维数组
	dataConfig config;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			this->m_gameArray[i][j] = config.mData[this->m_levelIndex][i][j];
		}
	}

	//胜利图片显示
	lab = new QLabel(this);
	QPixmap pix;
	pix.load(":/Resource/LevelCompletedDialogBg.png");
	lab->setFixedSize(pix.size());
	lab->setPixmap(pix);
	lab->move((this->width() - pix.width()) * 0.5, -pix.height());
	//显示金币背景图案
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			//绘制背景图片
			//QPixmap pix;
			pix.load(":/Resource/BoardNode.png");
			QLabel* lab = new QLabel(this);
			lab->setFixedSize(pix.size());
			lab->setPixmap(pix);
			lab->move(57 + i * 50, 200 + j * 50);

			//创建金币
			QString str;
			if (this->m_gameArray[i][j] == 1)str = ":/Resource/Coin1.png";
			else str = ":/Resource/Coin8.png";
			MyCoin* coin = new MyCoin(str);
			coin->setParent(this);
			m_coinArr[i][j] = coin;
			coin->move(59 + i * 50, 204 + j * 50);
			//给金币属性赋值
			coin->m_posX = i;
			coin->m_posY = j;
			coin->m_flag = this->m_gameArray[i][j];
		}
	}
	//判断点击
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			connect(this->m_coinArr[i][j], &QPushButton::clicked, [=]
				{
					m_player2->play();
					this->m_coinArr[i][j]->changeFlag();
					this->m_gameArray[i][j] = this->m_gameArray[i][j] ? 0 : 1;
					QEventLoop eventloop;
					QTimer::singleShot(150, &eventloop, &QEventLoop::quit);
					eventloop.exec();
					//反转周围
					{
						if (i) {//上
							this->m_coinArr[i - 1][j]->changeFlag();
							this->m_gameArray[i - 1][j] = this->m_gameArray[i - 1][j] ? 0 : 1;
						}
						if (i < 3) {
							this->m_coinArr[i + 1][j]->changeFlag();
							this->m_gameArray[i + 1][j] = this->m_gameArray[i + 1][j] ? 0 : 1;
						}
						if (j) {
							this->m_coinArr[i][j - 1]->changeFlag();
							this->m_gameArray[i][j - 1] = this->m_gameArray[i][j - 1] ? 0 : 1;
						}
						if (j < 3) {
							this->m_coinArr[i][j + 1]->changeFlag();
							this->m_gameArray[i][j + 1] = this->m_gameArray[i][j + 1] ? 0 : 1;
						}
					}
					//判断有没有赢
					int total = 0;
					for (size_t a = 0; a < 4; a++)
					{
						for (size_t b = 0; b < 4; b++)
						{
							if (this->m_gameArray[a][b])total++;
						}
					}
					if (total == 16) {
						m_player1->setSource(QUrl("qrc:/Resource/LevelWinSound.wav"));
						m_player1->play();
						//qDebug() << "WIN";
						this->m_coinArr[i][j]->m_isWin = true;
						//创建动态对象
						QPropertyAnimation* animation = new QPropertyAnimation(lab, "geometry");
						//设置动画时间间隔
						animation->setDuration(1000);
						//起始位置
						animation->setStartValue(QRect(lab->x(),lab->y(), lab->width(), lab->height()));
						//结束位置
						animation->setEndValue(QRect(lab->x(), lab->y() + 114, this->width(), lab->height()));
						//设置弹跳曲线
						animation->setEasingCurve(QEasingCurve::OutBounce);
						//执行动画
						animation->start();
					}
				});
		}

	}

}

void PlayWindow::paintEvent(QPaintEvent* ev)
{
	QPainter painter(this);
	QPixmap pix;
	//加载背景
	pix.load(":/Resource/PlayLevelSceneBg.png");
	painter.drawPixmap(0, 0, this->width(), this->height(), pix);
	//加载标题
	pix.load(":/Resource/Title.png");
	painter.drawPixmap((this->width() - pix.width()) * 0.5, 30, pix.width(), pix.height(), pix);
}
