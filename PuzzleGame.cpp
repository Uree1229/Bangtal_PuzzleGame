#include <bangtal.h>
#include <stdlib.h>

struct POS {
	int x, y;
};
const POS position[9] = {              //퍼즐 생성위치
	{340, 460}, {540, 460}, {740, 460},
	{340, 260}, {540, 260}, {740, 260},
	{340,  60}, {540,  60}, {740,  60},
};

SceneID scene_back;
ObjectID createObject(const char* image, SceneID scene, POS position, bool shown) {

	ObjectID object = createObject(image);
	POS position = { x, y };
	locateObject(object, scene, x, y);


	if (shown) {
		showObject(object);
	}
	return object;
}




ObjectID puzzle[9];

puzzle[1] = createObject("Images/puzzle1.png", scene_back, );


int main() {
	scene_back = createScene("background", "Images/background.png");
	startGame(scene_back);
}