#include<graphics.h>
#include<iostream>
#include<string>
#include<ctime>
using namespace std;
//ȫ�ֱ���
MOUSEMSG msg;
IMAGE mine,grid,grid_motion,grid_down,flag,flag_motion;
const int width = 400, height = 400, grid_size = 40;
int grid_x,grid_y;

//�����࣬�߳�Ϊ40���ص�������
class Grid {
	public:
		bool is_mine,is_click=false,is_flag=false;
		int num=0;
		IMAGE mine;
		int x1, x2, y1, y2;//���ӵ��ĸ��Ƕ����λ��

		void init(bool is_mine,int x,int y,int a,int b) {
			//��ʼ��
			this->is_mine = is_mine;
			x1 = x; x2 = x + grid_size;
			y1 = y; y2 = y + grid_size;
			//����
			change(grid);
		}

		void change(IMAGE image) {
			putimage(x1, y1, &image);
		}

		void show_num() {
			settextcolor(YELLOW);
			setbkmode(TRANSPARENT);
			settextstyle(50, 0, _T("Consolas"));
			char info = num + 48;
			outtextxy(x1, y1, _T(info));
		}
};

int main() {
	//�����ʼ��
	int grid_x = 0, grid_y = 0, mines_num = 10,layout_size= width / grid_size;
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
	//���֣��ö�ά���飬�����1�����ף�0��û��
	Grid layout[width / grid_size][height / grid_size];
	//����
	for (int i = 0; i <layout_size; i++) {
		for (int j = 0; j < layout_size; j++) {
			is_mine = rand() % 2 + 0;
			layout[i][j].init(is_mine, grid_x, grid_y, i, j);
			/*
			if (is_mine&&mines_num>0) {
				layout[i][j].init(true, grid_x,grid_y,i,j);
				mines_num--;
			}
			else if(is_mine&&mines_num<=0)
				layout[i][j].init(false, grid_x,grid_y,i,j);
			else if(is_mine==false)
				layout[i][j].init(false, grid_x, grid_y, i, j);
			*/
			grid_x += 40;
		}
		grid_y += 40;
		grid_x = 0;
	}
	/*�����������*/
	for (int i = 0; i < layout_size; i++) {
		for (int j = 0; j < layout_size; j++) {
			cout<<layout[i][j].is_mine << ' ';
		}
		cout << endl;
	}
	
	//��ѯ�������¼�
	while (true) {
		//���������
		ExMessage msg=getmessage(EX_MOUSE);

		if (msg.message == WM_LBUTTONDOWN) {
			for (int i = 0; i < layout_size; i++) {
				for (int j = 0; j < layout_size; j++) {
					//ͨ����������ж����ĸ�����
					if (msg.x >= layout[i][j].x1 && msg.x <= layout[i][j].x2 && msg.y >= layout[i][j].y1 && msg.y <= layout[i][j].y2) {
						layout[i][j].is_click = true;
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
							//�жϸ�����Χ������
							if (i == 0 && j == 0) {
								//���Ͻ�
								Grid grids[8] = { layout[0][1],layout[2][2],layout[1][0],layout[1][1],layout[1][2],layout[2][0],layout[2][1],layout[2][2] };
								for (int a = 0; a < 8; a++) {
									if (grids[a].is_mine)
										layout[i][j].num++;
								}
							}
							else if (i == layout_size-1 && j == layout_size-1) {
								//���Ͻ�
								Grid grids[8] = { layout[layout_size - 1][1],layout[layout_size - 1][2],layout[layout_size - 2][0],layout[layout_size - 2][1],layout[layout_size - 2][2],layout[layout_size - 3][0],layout[layout_size - 3][1],layout[layout_size - 3][2] };
								for (int a = 0; a < 8; a++) {
									if (grids[a].is_mine)
										layout[i][j].num++;
								}
							}
							else if (i == 0 && j == layout_size-1) {
								//���½�
								
							}
							else if (i == layout_size-1 && j == 0) {
								//���½�
								
							}
							else if(i>0&&i<9&&j>0&&j<9){
								//�Դ˸���Ϊ����
								Grid grids[8] = { layout[i - 1][j - 1],layout[i - 1][j],layout[i - 1][j + 1],layout[i][j - 1],layout[i][j + 1],layout[i + 1][j - 1],layout[i + 1][j],layout[i + 1][j + 1] };
								for (int a = 0; a < 8; a++) {
									if (grids[a].is_mine)
										layout[i][j].num++;
								}
							}
							layout[i][j].show_num();
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
						else if(layout[i][j].is_click==false&& layout[i][j].is_flag)
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