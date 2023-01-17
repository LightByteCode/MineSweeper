#include<graphics.h>
#include<iostream>
#include<thread>
#include<ctime>

using namespace std;
//ȫ�ֱ���
MOUSEMSG msg;
IMAGE mine, grid, grid_motion, grid_down, flag, flag_motion;
const int width = 400, height = 400, grid_size = 40,mines_num_copy=10;
int all_num=0,grid_x = 0, grid_y = 0, mines_num = 10, layout_size = width / grid_size;

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
		//�ж��Լ���λ��(grids��ά�����¼��Χ8�����ӵ��к���)
		if (i == 0 && j == 0)
		{
			//���Ͻ�
			int grids[8][2] = { {0,1},{2,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2} };
			for (int a = 0; a < 8; a++) {
				this->grids[a][0] = grids[a][0];
				this->grids[a][1] = grids[a][1];
			}
		}

		else if (i == layout_size - 1 && j == layout_size - 1)
		{
			//���½�
			int grids[8][2] = { {layout_size - 1,layout_size - 2},{layout_size - 1,layout_size - 3},{layout_size - 2,layout_size - 1},{layout_size - 2,layout_size - 2},{layout_size - 2,layout_size - 3},{layout_size - 3,layout_size - 1},{layout_size - 3,layout_size - 2},{layout_size - 3,layout_size - 3} };
			for (int a = 0; a < 8; a++) {
				this->grids[a][0] = grids[a][0];
				this->grids[a][1] = grids[a][1];
			}
		}

		else if (i == 0 && j == layout_size - 1)
		{
			//���Ͻ�
			int grids[8][2] = { {0,layout_size - 2},{0,layout_size - 3},{1,layout_size - 1},{1,layout_size - 2},{1,layout_size - 3},{2,layout_size - 1},{2,layout_size - 2},{2,layout_size - 3} };
			for (int a = 0; a < 8; a++) {
				this->grids[a][0] = grids[a][0];
				this->grids[a][1] = grids[a][1];
			}
		}

		else if (i == layout_size - 1 && j == 0){
			//���½�
			int grids[8][2] = { {layout_size - 3,0},{layout_size - 3,1},{layout_size - 3,2},{layout_size - 2,0},{layout_size - 2,1},{layout_size - 2,2},{layout_size - 1,1},{layout_size - 1,2} };
			for (int a = 0; a < 8; a++) {
				this->grids[a][0] = grids[a][0];
				this->grids[a][1] = grids[a][1];
			}
		}
			
		else if (i == 0 && j > 0 && j < layout_size - 1) 
		{
			//��-��
			int grids[8][2] = { {0,j - 1},{0,j + 1},{1,j - 1},{1,j},{1,j + 1},{2,j - 1},{2,j},{2,j + 1} };
			for (int a = 0; a < 8; a++) {
				this->grids[a][0] = grids[a][0];
				this->grids[a][1] = grids[a][1];
			}
		}

		else if (i == layout_size - 1 && j > 0 && j < layout_size - 1) 
		{
			//��-��
			int grids[8][2] = { {layout_size - 1,j - 1},{layout_size - 1,j + 1} ,{layout_size - 2,j - 1} ,{layout_size - 2,j} ,{layout_size - 2,j + 1} ,{layout_size - 3,j - 1} ,{layout_size - 3,j} ,{layout_size - 3,j + 1} };
			for (int a = 0; a < 8; a++) {
				this->grids[a][0] = grids[a][0];
				this->grids[a][1] = grids[a][1];
			}
		}
			
		else if (j == 0 && i > 0 && i < layout_size - 1) 
		{
			//��-��
			int grids[8][2] = { {i - 1,0} ,{i - 1,1} ,{i - 1,2} ,{i,1} ,{i,2} ,{i + 1,0} ,{i + 1,1} ,{i + 1,2} };
			for (int a = 0; a < 8; a++) {
				this->grids[a][0] = grids[a][0];
				this->grids[a][1] = grids[a][1];
			}
		}

		else if (j == layout_size - 1 && i > 0 && i < layout_size - 1) 
		{
			//��-��
			int grids[8][2] = { {i - 1,layout_size - 1} ,{i - 1,layout_size - 2} ,{i - 1,layout_size - 3} ,{i,layout_size - 2} ,{i,layout_size - 3} ,{i + 1,layout_size - 1} ,{i + 1,layout_size - 2} ,{i + 1,layout_size - 3} };
			for (int a = 0; a < 8; a++) {
				this->grids[a][0] = grids[a][0];
				this->grids[a][1] = grids[a][1];
			}
		}

		else
		{
			//�Դ˸���Ϊ����
			int grids[8][2] = { {i - 1,j - 1} ,{i - 1,j} ,{i - 1,j + 1} ,{i,j - 1} ,{i,j + 1} ,{i + 1,j - 1} ,{i + 1,j} ,{i + 1,j + 1} };
			for (int a = 0; a < 8; a++) {
				this->grids[a][0] = grids[a][0];
				this->grids[a][1] = grids[a][1];
			}
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

	void find_0(Grid(&layout)[10][10]) {
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


int main() {
	//�����ʼ��
	bool is_mine;

	initgraph(width, height);
	setbkcolor(WHITE);
	cleardevice();
	//����ͼ��
	loadimage(&mine, "images/mine.png", grid_size, grid_size);
	loadimage(&grid, "images/grid.png", grid_size, grid_size);
	loadimage(&grid_motion, "images/grid_motion.png", grid_size, grid_size);
	loadimage(&grid_down, "images/grid_down.png", grid_size, grid_size);
	loadimage(&flag, "images/flag.png", grid_size, grid_size);
	loadimage(&flag_motion, "images/flag_motion.png", grid_size, grid_size);
	//����
	Grid layout[width / grid_size][height / grid_size];//���֣��ö�ά���飬�����1�����ף�0��û��

	srand(time(nullptr));
	for (int i = 0; i < layout_size; i++) {
		for (int j = 0; j < layout_size; j++) {
			is_mine = rand() % 2;
			
			if (is_mine && mines_num > 0 && i!=0 && j!=0) {
				layout[i][j].init(true, grid_x, grid_y, i, j);
				mines_num--;
			}
			else if (is_mine && mines_num <= 0)
				layout[i][j].init(false, grid_x, grid_y, i, j);
			else
				layout[i][j].init(false, grid_x, grid_y, i, j);

			grid_x += 40;
		}
		grid_y += 40;
		grid_x = 0;
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
			for (int i = 0; i < layout_size; i++) {
				for (int j = 0; j < layout_size; j++) {
					//ͨ����������ж����ĸ�����
					if (msg.x >= layout[i][j].x1 && msg.x <= layout[i][j].x2 && msg.y >= layout[i][j].y1 && msg.y <= layout[i][j].y2) {
						if (layout[i][j].is_click == false) {//�ж��Ƿ񱻵����
							layout[i][j].is_flag = false;
							//��������������
							if (layout[i][j].is_mine) {
								layout[i][j].change(mine);
								//��ʾ��ʾ��Ϣ
								setbkmode(TRANSPARENT);
								settextcolor(RED);
								settextstyle(50, 0, _T("Consolas"));
								outtextxy(width / 2 - 180, height / 2 - 30, _T("�����ˣ������˳�"));
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
						if (all_num == layout_size * layout_size - mines_num_copy) {
							//��ʾ��ʾ��Ϣ
							setbkmode(TRANSPARENT);
							settextcolor(GREEN);
							settextstyle(50, 0, _T("Consolas"));
							outtextxy(width / 2 - 180, height / 2 - 30, _T("��ʤ�������˳�"));
							Sleep(2500); //ͣ�������
							//�˳�
							return 0;
						}
					}
				}
			}
		}

		if (msg.message == WM_MOUSEMOVE) {
			for (int i = 0; i < layout_size; i++) {
				for (int j = 0; j < layout_size; j++) {
					//ͨ�������ж����ĸ�����
					if (msg.x >= layout[i][j].x1 && msg.x <= layout[i][j].x2 && msg.y >= layout[i][j].y1 && msg.y <= layout[i][j].y2) {
						if (layout[i][j].is_click) {
							layout[i][j].change(grid_down);
							layout[i][j].show_num();
						}
						else if (layout[i][j].is_click == false && layout[i][j].is_flag == false)
							layout[i][j].change(grid_motion);
						else if (layout[i][j].is_click == false && layout[i][j].is_flag == true)
							layout[i][j].change(flag_motion);
					}

					else {
						if (layout[i][j].is_click) {
							layout[i][j].change(grid_down);
							layout[i][j].show_num();
						}
						else if (layout[i][j].is_click == false && layout[i][j].is_flag == false)
							layout[i][j].change(grid);
						else if (layout[i][j].is_click == false && layout[i][j].is_flag)
							layout[i][j].change(flag);
					}

				}
			}
		}

		else if (msg.message == WM_RBUTTONDOWN) {
			for (int i = 0; i < layout_size; i++) {
				for (int j = 0; j < layout_size; j++) {
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