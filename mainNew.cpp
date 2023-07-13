#include<iostream>
#include<graphics.h>
#include<vector>
#include<string>
#include<tchar.h>
#include<ctime>

using namespace std;

// Ĭ�ϳ���
int gridSize = 40;									// ÿ�����ӵĴ�С(���Ϳ�)
int lines = 5, rows = 5;							// ����������
int width = rows * gridSize, height = lines * gridSize; // ���ڿ�Ⱥ͸߶�
int minesNum = 10;									// �׵�����
int normalGridsNum = lines * rows - minesNum;		// ����������ĸ�������
IMAGE grid, gridClicked, mine, gridFlag;			// ͼ��

// ������
class Grid {
public:
	int posX, posY; // �ø���������λ��(��λ:����)
	bool isFlag = false, isClicked = false, isMine = false;
	int posLine, posRow; // �ø����������к���λ��(��λ:����)
	int minesNumAround = 0; // �ø�����Χ�׵�����
	
	void show(int posLine,int posRow) {
		//��ʾ
		this->posLine = posLine;
		this->posRow = posRow;
		posX = (this->posRow - 1) * gridSize;
		posY = (this->posLine - 1) * gridSize;
		putimage(posX, posY, &grid);
	}
	void showMinesNumAround() {
		if (minesNumAround==0)
			return;
		else if (minesNumAround == 1)
			settextcolor(BLUE);
		else if (minesNumAround == 2)
			settextcolor(GREEN);
		else if (minesNumAround == 3)
			settextcolor(YELLOW);
		else if (minesNumAround == 4)
			settextcolor(RGB(255, 135, 35));
		else
			settextcolor(RED);
		char info = minesNumAround + 48;
		outtextxy(posX+int(gridSize*0.4), posY+int(gridSize*0.1), _T(info));
	}
	void onLeftButtonClick();
	void onRightButtonClick();
	void findMinesAround();
};

vector<vector<Grid>> playGround(lines+1,vector<Grid>(rows+1));	// ������������
vector<Grid> mines; // ����һ��vector�������׵ĸ���

/*����Grid��ļ�������*/
// ���������
void Grid::onLeftButtonClick() {
	if (!isClicked) { // ���û�б���������
		isClicked = true;
		normalGridsNum--;
		putimage(posX, posY, &gridClicked);
		
		findMinesAround();		// ������
		showMinesNumAround();	// ��ʾ������Χ����

		//������Χ(4��)�����׵ĸ���
		vector<vector<int>> minesPosAround = { {posLine - 1,posRow},{posLine,posRow - 1},{posLine,posRow + 1},{posLine + 1,posRow} };
		for (int i = 0; i < 4; i++) {
			if (minesPosAround[i][0] > 0 && minesPosAround[i][0] <= lines && minesPosAround[i][1] > 0 && minesPosAround[i][1] <= rows) {
				if (playGround[minesPosAround[i][0]][minesPosAround[i][1]].isMine == false) {
					playGround[minesPosAround[i][0]][minesPosAround[i][1]].onLeftButtonClick();
				}
			}
		}
	}
}
// ����Ҽ����
void Grid::onRightButtonClick() {
	if (!isFlag&&!isClicked) { // ���û�б��Ҽ������
		isFlag = true;
		putimage(posX, posY, &gridFlag);
	}
	else if(isFlag&&!isClicked) {
		isFlag = false;
		putimage(posX, posY, &grid);
	}
}
// Ѱ����Χ8��(��5��)�������׵�����
void Grid::findMinesAround() {
	if (isMine) { // ����ø������ף��򷵻�-1
		return;
	}
	else { // ����ø��Ӳ����ף�����
		for (int i = posLine - 1; i < posLine + 1; i++) {
			for (int j = posRow - 1; j < posRow + 1; j++) {
				if (i != posLine && j != posRow && playGround[i][j].isMine) {
					minesNumAround++;
				}
			}
		}
	}
}
// ��������
void splashScreen() {
	IMAGE splashImage;
	loadimage(&splashImage, "images/mineIcon.png",width,height);
	putimage(0, 0, &splashImage);
	Sleep(1500);

	BeginBatchDraw();
	for (int i = 0; i <= height; i+=3) {
		FlushBatchDraw();
		cleardevice();
		putimage(0, i, &splashImage);
		Sleep(1);
	}
	EndBatchDraw();
	cleardevice();
}
//������
int main(int argc, char* argv[]) {
	/*�������������еĲ���*/
	if (argc == 2 && argv[1] == "-h") { // ���������Ϣ
		cout << "����" << endl;
		cout << "-s:ÿ�����ӵĴ�С" << endl;
		cout << "-l:���̵�����" << endl << "-r:���̵�����" << endl;
		cout << "-n:�׵ĸ���" << endl;
	}
	else if (argc > 2) {
		for (int i = 1; i < argc-1; i++) {
			if (argv[i] == "-s") {
				gridSize = atoi(argv[i + 1]);
			}
			else if (argv[i] == "-l") {
				lines = atoi(argv[i + 1]);
			}
			else if (argv[i] == "-r") {
				rows = atoi(argv[i + 1]);
			}
			else if (argv[i] == "-n") {
				minesNum = atoi(argv[i + 1]);
			}
			else {
				cout << "��������" << endl;
			}
		}
	}
	/*��ʼ������*/
	initgraph(gridSize * rows, height);
	loadimage(&grid, "images/grid.png", gridSize, gridSize);
	loadimage(&gridClicked, "images/gridClicked.png", gridSize, gridSize);
	loadimage(&mine, "images/mine.png", gridSize, gridSize);
	loadimage(&gridFlag, "images/gridFlag.png", gridSize, gridSize);
	setbkmode(TRANSPARENT);
	settextstyle(int(gridSize*0.9), int(gridSize * 0.4), _T("΢���ź�"));
	setbkcolor(WHITE);
	cleardevice();
	/*��������*/
	splashScreen();
	/*��������*/
	// ��ʾ����
	for (int i = 1; i <= lines; i++) {
		for (int j = 1; j <= rows; j++) {
			playGround[i][j].show(i, j);
			Sleep(10);
		}
	}
	// �������
	srand(time(nullptr));
	for (int i = 0; i < minesNum; i++) {
		int x = rand() % rows + 1, y = rand() % lines + 1;
		playGround[x][y].isMine = true;
		mines.push_back(playGround[x][y]);
	}
	/*ѭ����������¼�*/
	while (true) {
		if (normalGridsNum == 0) {
			// ��ʾ��ʾ��Ϣ
			settextcolor(GREEN);

			BeginBatchDraw();
			for (int i = height; i >= 10; i -= 3) {
				FlushBatchDraw();
				cleardevice();
				outtextxy(10, i, "��Ӯ��");
				Sleep(1);
			}
			EndBatchDraw();

			Sleep(2500);
			return 0;
		}
		ExMessage msg = getmessage(EX_MOUSE);
		if (msg.message == WM_LBUTTONDOWN) {
			for (int i = 1; i <= lines; i++) {
				for (int j = 1; j <= rows; j++) {
					if (msg.x > playGround[i][j].posX&&msg.x< playGround[i][j].posX+gridSize&&msg.y>playGround[i][j].posY&&msg.y< playGround[i][j].posY+gridSize) {
						// �жϵ��������һ������
						if (playGround[i][j].isMine) { // �������
							putimage(playGround[i][j].posX, playGround[i][j].posY, &mine);
							for (int i = 0; i < minesNum; i++) {
								putimage(mines[i].posLine, mines[i].posRow, &mine);
							}
							// ��ʾ��ʾ��Ϣ
							settextcolor(RED);
							BeginBatchDraw();
							for (int i = height; i >= 10; i -= 3) {
								FlushBatchDraw();
								cleardevice();
								outtextxy(10, i, "������");
								Sleep(1);
							}
							EndBatchDraw();

							Sleep(2500); // ͣ�������
							return 0;
						}
						playGround[i][j].onLeftButtonClick();
					}
				}
			}
		}
		else if (msg.message == WM_RBUTTONDOWN) {
			for (int i = 1; i <= lines; i++) {
				for (int j = 1; j <= rows; j++) {
					if (msg.x > playGround[i][j].posX && msg.x< playGround[i][j].posX + gridSize && msg.y>playGround[i][j].posY && msg.y < playGround[i][j].posY + gridSize) {
						// �жϵ��������һ������
						playGround[i][j].onRightButtonClick();
					}
				}
			}
		}
	}
	/*�رջ�ͼ����*/
	closegraph();
	return 0;
}