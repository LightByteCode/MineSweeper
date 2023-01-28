#include<graphics.h>
#include<iostream>
#include<vector>
#include<string>

using namespace std;
//ȫ�ֱ���
MOUSEMSG msg;//ȫ�������Ϣ����
IMAGE mine, grid, grid_motion, grid_down, flag, flag_motion , mine_other;//����ͼ�����
//�������Ӵ�С(��λ������)���������������Ӳ��ֳ���(��λ������)�����ڿ�ȣ����ڸ߶�
int grid_size = 40, layout_size = 10, width = 400, height = 400;

int all_num = 0, grid_x = 0, grid_y = 0, mines_num = 10;

//�����࣬�߳�Ϊ40���ص�������
class Grid {
public:
	bool is_mine, is_click = false, is_flag = false;
	int num = 0;
	IMAGE mine;
	int x1, x2, y1, y2;//���ӵ��ĸ��Ƕ����λ��
	int i, j;
	int grids[8][2] = { 0 };

	void init(bool is_mine, int x, int y, int i, int j) {
		//��ʼ��
		this->is_mine = is_mine;
		x1 = x; x2 = x + grid_size;
		y1 = y; y2 = y + grid_size;
		this->i = i; this->j = j;
		//����
		change(grid);
		//�Դ˸���Ϊ����
		int grids[8][2] = { {i - 1,j - 1} ,{i - 1,j} ,{i - 1,j + 1} ,{i,j - 1} ,{i,j + 1} ,{i + 1,j - 1} ,{i + 1,j} ,{i + 1,j + 1} };
		for (int a = 0; a < 8; a++) {
			this->grids[a][0] = grids[a][0];
			this->grids[a][1] = grids[a][1];
		}
	}

	void change(IMAGE image) {
		putimage(x1, y1, &image);
	}

	void show_num() {
		if (num == 0)
			return;
		else if (num == 1)
			settextcolor(BLUE);
		else if (num == 2)
			settextcolor(GREEN);
		else if (num == 3)
			settextcolor(YELLOW);
		else if (num == 4)
			settextcolor(RGB(255, 135, 35));
		else
			settextcolor(RED);
		setbkmode(TRANSPARENT);
		settextstyle(45, 0, _T("Consolas"));
		char info = num + 48;
		outtextxy(x1 + 6, y1 - 3, _T(info));
	}

	void find_0(vector<vector<Grid>> &layout) {
		for (int a = 0; a < 8; a++) {//����grids����Χ���ӣ�
			int i = grids[a][0], j = grids[a][1];
			if (layout[i][j].num == 0 && layout[i][j].is_click == false && layout[i][j].is_mine == false) {
				//ģ��������
				layout[i][j].is_flag = false;
				layout[i][j].change(grid_down);
				layout[i][j].is_click = true;
				all_num++;
				layout[i][j].find_0(layout);
			}
		}
	}
};

class Button {
public:
	int x, y, width, height;
	const char* text="NULL";

	void show(const char* text, int x, int y, int width, int height, COLORREF color1 = WHITE)
	{
		this->x = x; this->y = y;
		this->width = width; this->height = height;
		this->text = text;

		setlinecolor(color1);//���ÿ����ɫ
		setbkmode(TRANSPARENT);//�������屳��͸��
		setfillcolor(color1);//���������ɫ
		fillroundrect(x, y, x + width, y + height, 10, 10);//��һ����ť��

		settextcolor(BLACK);
		settextstyle(40, 0, "����");
		int tx = x + (width - textwidth(text)) / 2;
		int ty = y + (height - textheight(text)) / 2;
		outtextxy(tx, ty, text);
	}

	void change(COLORREF color2=RGB(237, 237, 237)) {
		setlinecolor(color2);//���ÿ����ɫ
		setfillcolor(color2);//���������ɫ
		fillroundrect(x, y, x + width, y + height, 10, 10);//��һ����ť��

		settextcolor(BLACK);
		settextstyle(40, 0, "����");
		int tx = x + (width - textwidth(text)) / 2;
		int ty = y + (height - textheight(text)) / 2;
		outtextxy(tx, ty, text);
	}
};

void settings() {
	int temp=0;
	cout << "���ø��Ӵ�С(��λ������)" << endl;
	cin >> grid_size;
	cout << "�������̱߳�(��λ������)" << endl;
	cin >> layout_size;
	width = height = layout_size * grid_size;
	cout << width << ' ' << height << endl;
	cout << "��������" << endl;
	cin >> temp;
	if (temp >= layout_size * layout_size)
		cout << "���õ���̫����" << endl;
	else {
		mines_num = temp;
		cout << "OK ��ʼ��" << endl;
		return;
	}
}

void start() {
	//�����ʼ��
	initgraph(width, height);
	setbkcolor(BLACK);
	cleardevice();
	setbkcolor(WHITE);
	//�������ð�ť

	Button btn1;
	btn1.show("����", 150, 100, 100, 50);
	Button btn2;
	btn2.show("��ʼ", 150, 200, 100, 50);
	//��ѭ��
	while (true) {
		ExMessage msg = getmessage(EX_MOUSE);

		if (msg.message == WM_LBUTTONDOWN) {
			if (msg.x >= btn1.x && msg.x <= btn1.x + btn1.width && msg.y >= btn1.y && msg.y <= btn1.y + btn1.height) {
				btn1.change();
				settings();
				cleardevice();
				initgraph(width, height);
				return;
			}

			else if (msg.x >= btn2.x && msg.x <= btn2.x + btn2.width && msg.y >= btn2.y && msg.y <= btn2.y + btn2.height) {
				btn2.change();
				cleardevice();
				return;
			}
		}
	}
}

int main() {
	//�����ʼ��
	start();
	//����ͼ��
	loadimage(&mine, "images/mine.png", grid_size, grid_size);
	loadimage(&grid, "images/grid.png", grid_size, grid_size);
	loadimage(&grid_down, "images/grid_down.png", grid_size, grid_size);
	loadimage(&flag, "images/flag.png", grid_size, grid_size);
	//����
	vector<vector<Grid>> layout(layout_size+2, vector<Grid>(layout_size+2));//���֣��ö�ά���飬�����1�����ף�0��û��

	srand(time(nullptr));
	//��ʼ��
	for (int i = 1; i < layout_size+1; i++) {
		for (int j = 1; j < layout_size+1; j++) {
			layout[i][j].init(false, grid_x, grid_y, i, j);
			grid_x += grid_size;
		}
		grid_y += grid_size;
		grid_x = 0;
	}
	//�������ʵ��
	int x = 0, y = 0, count = 0;
	for (count = 0; count < mines_num;){
		x = 1 + rand() % layout_size+1;
		y = 1 + rand() % layout_size+1;
		if (layout[x][y].is_mine == false){
			layout[x][y].is_mine = true;
			count++;//ÿ�β��ú�һ����֮��,�Ż����
		}
	}

	for (int i = 0; i < layout_size; i++) {
		for (int j = 0; j < layout_size; j++) {
			//ÿ�����ӻ�ȡ��Χ���ӵ�����
			for (int a = 0; a < 8; a++) {
				if (layout[layout[i][j].grids[a][0]][layout[i][j].grids[a][1]].is_mine) {
					layout[i][j].num++;
				}
			}
		}
	}
	/*�����������
	for (int i = 0; i < layout_size; i++) {
		for (int j = 0; j < layout_size; j++) {
			cout << layout[i][j].is_mine << ' ';
		}
		cout << endl;
	}*/
	//��ѯ�������¼�
	while (true) {
		//���������
		ExMessage msg = getmessage(EX_MOUSE);

		if (msg.message == WM_LBUTTONDOWN) {
			for (int i = 1; i < layout_size+1; i++) {
				for (int j = 1; j < layout_size+1; j++) {
					//ͨ����������ж����ĸ�����
					if (msg.x >= layout[i][j].x1 && msg.x <= layout[i][j].x2 && msg.y >= layout[i][j].y1 && msg.y <= layout[i][j].y2) {
						if (layout[i][j].is_click == false) { //�ж��Ƿ񱻵����
							layout[i][j].is_flag = false;
							//��������������
							if (layout[i][j].is_mine) {
								layout[i][j].change(mine);
								//��ʾ��ʾ��Ϣ
								for (int x = 0; x < layout_size; x++) {
									for (int y = 0; y < layout_size; y++) {
										if (layout[x][y].is_mine && x != i && y != j)
											layout[x][y].change(mine_other);
									}
								}
								cout << "���ף������˳�";
								Sleep(2500); //ͣ�������
								//�˳�����
								return 0;
							}

							else {
								layout[i][j].change(grid_down);
								//��ʾ������Χ������
								layout[i][j].show_num();
								//�����������0
								if (layout[i][j].num == 0)
									layout[i][j].find_0(layout);
							}
							layout[i][j].is_click = true;
							all_num++;
						}
						//�ж�δ�㿪�ĸ��������Ӷ��ж���Ӯ
						if (all_num == layout_size * layout_size - mines_num) {
							//��ʾ��ʾ��Ϣ
							for (int x = 0; x < layout_size; x++) {
								for (int y = 0; y < layout_size; y++) {
									if (layout[x][y].is_mine && x != i && y != j)
										layout[x][y].change(flag);
								}
							}
							cout<<"��ʤ�������˳�";
							Sleep(2500); //ͣ�������
							//�˳�
							return 0;
						}
					}
				}
			}
		}

		else if (msg.message == WM_RBUTTONDOWN) {
			for (int i = 1; i < layout_size+1; i++) {
				for (int j = 1; j < layout_size+1; j++) {
					//ͨ����������ж����ĸ�����
					if (msg.x >= layout[i][j].x1 && msg.x <= layout[i][j].x2 && msg.y >= layout[i][j].y1 && msg.y <= layout[i][j].y2) {
						//����Ѿ�����Ǿ�ȡ�����
						if (layout[i][j].is_flag) {
							layout[i][j].is_flag = false;
							layout[i][j].change(grid);
						}
						//���û�б���Ǿͱ����
						else if (layout[i][j].is_flag == false && layout[i][j].is_click == false) {
							layout[i][j].is_flag = true;
							layout[i][j].change(flag);
						}
					}
				}
			}
		}
	}

	closegraph();
	return 0;
}