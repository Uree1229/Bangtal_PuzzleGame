#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES	1
#include <bangtal.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>
#include <string>
#include <string.h>



using namespace std;

SceneID scene_back;
ObjectID puzzle[10], puzzle_pos[10], mixButton, puzzle_blank, blank_back;

int blank, num_random, rd_pos[10], gametype = 0; // 빈 퍼즐의 숫자

struct POS {
	int x, y;
};
POS position[10] = { {0,0},            //퍼즐 생성위치
   {340, 460}, {540, 460}, {740, 460},
   {340, 260}, {540, 260}, {740, 260},
   {340,  60}, {540,  60}, {740,  60},

}, change_pos[9];

ObjectID create_Object(const char* image, SceneID scene, int x, int y, bool shown) {

	ObjectID object = createObject(image);
	locateObject(object, scene, x, y);

	if (shown) {
		showObject(object);
	}
	return object;
}
void game_set() {

	char image[20];
	for (int i = 1; i < 10; i++) {
		sprintf(image, "Images/Puzzle_%d.png", i);
		puzzle[i] = create_Object(image, scene_back, position[i].x, position[i].y, true);
		//puzzle_pos[i] = puzzle[i];
	}

}
void random_number() {
	int i, j;
	random_device rd;
	mt19937_64 Rd(rd());

	for (i = 1; i < 10; i++) {
		uniform_int_distribution<int> disn(1, 9);
		num_random = disn(Rd);
		rd_pos[i] = num_random;
		for (j = 0; j < i; j++) {
			if (rd_pos[i] == rd_pos[j]) {
				i--;
			}
		}

	}

}
void random_blank() {

	random_device rd;
	mt19937_64 Rd(rd());
	uniform_int_distribution<int> disN(1, 1);
	blank = disN(Rd);
	hideObject(puzzle[blank]);

}
void reset() {
	for (int i = 0; i < 9; i++) {
		showObject(puzzle[i]);
	}
}
void puzzle_mix() {

	char image[20];
	random_number();
	for (int i = 1; i < 10; i++) {
		sprintf(image, "Images/Puzzle_%d.png", rd_pos[i]);
		setObjectImage(puzzle[i], image);
		puzzle_pos[i] = puzzle[i];
		//locateObject(puzzle[i], scene_back, position[rd_pos[i]].x, position[rd_pos[i]].y);
		//change_pos[i] = position[rd_pos[i]];

	}


}
int game_index(ObjectID oid) {
	for (int i = 1; i < 10; i++) {
		if (puzzle_pos[i] == oid) {
			return i;
		}
	}
	return -1;
}
bool game_move(int index)
{
	if (index < 1) return false;
	if (index > 9) return false;

	if (index == (blank - 3) || index == (blank + 3) ||
		(index == (blank - 1) && (blank % 3) != 0) ||
		(index == (blank + 1) && (blank % 3) != 2)) {

		locateObject(puzzle[index], scene_back, position[blank].x, position[blank].y);
		locateObject(puzzle[blank], scene_back, position[index].x, position[index].y);

		ObjectID o = puzzle[blank];
		puzzle[blank] = puzzle[index];
		puzzle[index] = o;



		blank = index;

		return true;
	}

	return false;
}

void mouse_callback(ObjectID object, int x, int y, MouseAction action) {

	int a;
	string b;
	const char* c;

	if (gametype == 0) {
		if (object == mixButton) {
			game_set();
			puzzle_mix();
			random_blank();
			gametype = 1;
			hideObject(mixButton);
		}
	}
	else if (gametype == 1) {
		if (game_index(object)) {
			a = game_index(object);
			b = to_string(a);
			c = b.c_str();
			showMessage(c);
			char image1[20];
			char image2[20];
			if (blank == 1) {

				if (game_index(object) == 2) {

					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[2]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[1]);
					setObjectImage(puzzle[1], image1);
					setObjectImage(puzzle[2], image2);

					showObject(puzzle[blank]);
					blank = 2;
					hideObject(puzzle[blank]);

					int t = rd_pos[1];
					rd_pos[2] = rd_pos[1];
					rd_pos[1] = t;
				}
				else if (game_index(object) == 4) {

					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[4]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[1]);
					setObjectImage(puzzle[1], image1);
					setObjectImage(puzzle[4], image2);
					showObject(puzzle[blank]);
					blank = 4;
					hideObject(puzzle[blank]);

					int t = rd_pos[4];
					rd_pos[4] = rd_pos[1];
					rd_pos[1] = t;
				}
			}  //f //f
			else if (blank == 2) {
				if (game_index(object) == 1) {

					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[1]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[2]);
					setObjectImage(puzzle[2], image1);
					setObjectImage(puzzle[1], image2);

					showObject(puzzle[blank]);
					blank = 1;
					hideObject(puzzle[blank]);

					int t = rd_pos[2];
					rd_pos[2] = rd_pos[1];
					rd_pos[1] = t;

				}
				else if (game_index(object) == 3) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[3]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[2]);
					setObjectImage(puzzle[3], image1);
					setObjectImage(puzzle[2], image2);

					showObject(puzzle[blank]);
					blank = 3;
					hideObject(puzzle[blank]);

					int t = rd_pos[3];
					rd_pos[3] = rd_pos[2];
					rd_pos[2] = t;

				}

				else if (game_index(object) == 5) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[5]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[2]);
					setObjectImage(puzzle[2], image1);
					setObjectImage(puzzle[5], image2);

					showObject(puzzle[blank]);
					blank = 5;
					hideObject(puzzle[blank]);

					int t = rd_pos[5];
					rd_pos[5] = rd_pos[2];
					rd_pos[2] = t;
				}

			}
			else if (blank == 3) {
				if (game_index(object) == 2) {

					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[2]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[3]);
					setObjectImage(puzzle[2], image1);
					setObjectImage(puzzle[3], image2);

					showObject(puzzle[blank]);
					blank = 2;
					hideObject(puzzle[blank]);

					int t = rd_pos[2];
					rd_pos[2] = rd_pos[3];
					rd_pos[3] = t;

				}
				else if (game_index(object) == 6) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[6]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[3]);
					setObjectImage(puzzle[3], image1);
					setObjectImage(puzzle[6], image2);

					showObject(puzzle[blank]);
					blank = 6;
					hideObject(puzzle[blank]);
					int t = rd_pos[6];
					rd_pos[6] = rd_pos[3];
					rd_pos[3] = t;
				}


			}
			else if (blank == 4) {
				if (game_index(object) == 1) {

					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[1]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[4]);

					setObjectImage(puzzle[1], image1);
					setObjectImage(puzzle[4], image2);

					showObject(puzzle[blank]);
					blank = 1;
					hideObject(puzzle[blank]);

					int t = rd_pos[4];
					rd_pos[4] = rd_pos[1];
					rd_pos[1] = t;


				}
				else if (game_index(object) == 5) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[5]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[4]);
					setObjectImage(puzzle[5], image1);
					setObjectImage(puzzle[4], image2);


					showObject(puzzle[blank]);
					blank = 5;
					hideObject(puzzle[blank]);
					int t = rd_pos[4];
					rd_pos[4] = rd_pos[5];
					rd_pos[5] = t;
				}

				else if (game_index(object) == 7) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[7]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[4]);
					setObjectImage(puzzle[4], image1);
					setObjectImage(puzzle[7], image2);

					showObject(puzzle[blank]);
					blank = 7;
					hideObject(puzzle[blank]);
					int t = rd_pos[4];
					rd_pos[4] = rd_pos[7];
					rd_pos[7] = t;
				}

			}

			else if (blank == 5) {
				if (game_index(object) == 2) {

					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[2]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[5]);
					setObjectImage(puzzle[2], image1);
					setObjectImage(puzzle[5], image2);

					showObject(puzzle[blank]);
					blank = 2;
					hideObject(puzzle[blank]);
					int t = rd_pos[5];
					rd_pos[5] = rd_pos[2];
					rd_pos[2] = t;


				}
				else if (game_index(object) == 4) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[4]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[5]);
					setObjectImage(puzzle[5], image1);
					setObjectImage(puzzle[4], image2);

					showObject(puzzle[blank]);
					blank = 4;
					hideObject(puzzle[blank]);
					int t = rd_pos[4];
					rd_pos[4] = rd_pos[5];
					rd_pos[5] = t;
				}
				else if (game_index(object) == 6) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[6]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[5]);
					setObjectImage(puzzle[6], image1);
					setObjectImage(puzzle[5], image2);

					showObject(puzzle[blank]);
					blank = 6;
					hideObject(puzzle[blank]);
					int t = rd_pos[5];
					rd_pos[5] = rd_pos[6];
					rd_pos[6] = t;
				}

				else if (game_index(object) == 8) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[8]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[5]);
					setObjectImage(puzzle[5], image1);
					setObjectImage(puzzle[8], image2);

					showObject(puzzle[blank]);
					blank = 8;
					hideObject(puzzle[blank]);
					int t = rd_pos[8];
					rd_pos[8] = rd_pos[5];
					rd_pos[5] = t;
				}

			}
			else if (blank == 6) {
				if (game_index(object) == 3) {

					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[3]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[6]);
					setObjectImage(puzzle[3], image1);
					setObjectImage(puzzle[6], image2);

					showObject(puzzle[blank]);
					blank = 3;
					hideObject(puzzle[blank]);


				}
				else if (game_index(object) == 5) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[4]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[6]);
					setObjectImage(puzzle[6], image1);
					setObjectImage(puzzle[4], image2);

					showObject(puzzle[blank]);
					blank = 5;
					hideObject(puzzle[blank]);
				}

				else if (game_index(object) == 9) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[9]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[6]);
					setObjectImage(puzzle[6], image1);
					setObjectImage(puzzle[9], image2);

					showObject(puzzle[blank]);
					blank = 9;
					hideObject(puzzle[blank]);
				}

			}
			else if (blank == 7) {
				if (game_index(object) == 4) {

					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[7]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[4]);
					setObjectImage(puzzle[7], image1);
					setObjectImage(puzzle[4], image2);

					showObject(puzzle[blank]);
					blank = 4;
					hideObject(puzzle[blank]);


				}
				else if (game_index(object) == 8) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[8]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[7]);
					setObjectImage(puzzle[7], image1);
					setObjectImage(puzzle[8], image2);

					showObject(puzzle[blank]);
					blank = 8;
					hideObject(puzzle[blank]);
				}
			}
			else if (blank == 8) {
				if (game_index(object) == 5) {

					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[5]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[8]);
					setObjectImage(puzzle[8], image1);
					setObjectImage(puzzle[5], image2);

					showObject(puzzle[blank]);
					blank = 5;
					hideObject(puzzle[blank]);


				}
				else if (game_index(object) == 7) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[7]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[8]);
					setObjectImage(puzzle[8], image1);
					setObjectImage(puzzle[7], image2);

					showObject(puzzle[blank]);
					blank = 7;
					hideObject(puzzle[blank]);
				}

				else if (game_index(object) == 9) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[9]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[8]);
					setObjectImage(puzzle[8], image1);
					setObjectImage(puzzle[9], image2);

					showObject(puzzle[blank]);
					blank = 9;
					hideObject(puzzle[blank]);
				}

			}
			else if (blank == 9) {
				if (game_index(object) == 6) {

					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[9]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[6]);
					setObjectImage(puzzle[6], image1);
					setObjectImage(puzzle[9], image2);

					showObject(puzzle[blank]);
					blank = 6;
					hideObject(puzzle[blank]);


				}
				else if (game_index(object) == 8) {
					sprintf(image1, "Images/Puzzle_%d.png", rd_pos[8]);
					sprintf(image2, "Images/Puzzle_%d.png", rd_pos[9]);
					setObjectImage(puzzle[9], image1);
					setObjectImage(puzzle[8], image2);

					showObject(puzzle[blank]);
					blank = 8;
					hideObject(puzzle[blank]);
				}



			}
		}

	}

}



int main() {

	setMouseCallback(mouse_callback);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, 0);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, 0);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, 0);

	scene_back = createScene("background", "Images/back.png");
	blank_back = create_Object("Images/blank.png", scene_back, 340, 60, true);
	mixButton = create_Object("Images/mix.png", scene_back, 1100, 20, true);

	startGame(scene_back);


}