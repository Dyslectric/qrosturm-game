#include "qrosturm.h"

#define WIDTH 12
#define HEIGHT 8

const char world[] = {
	'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 
	'#', '#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', ' ', '#', 
	'#', '#', '#', '#', '#', ' ', ' ', '#', '#', ' ', ' ', '#', 
	'#', ' ', ' ', '#', '#', ' ', '#', '#', '#', '#', '#', '#', 
	'#', ' ', ' ', ' ', ' ', ' ', '#', '#', '#', '#', '#', '#', 
	'#', ' ', ' ', '#', '#', ' ', '#', ' ', ' ', '#', '#', '#', 
	'#', '#', '#', '#', '#', ' ', ' ', ' ', ' ', '#', '#', '#', 
	'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', 
};

int coord_to_index(int row, int column, int width) {
	return row * width + column;
}

int collides(int index) {
	if (index >= 0 && index < WIDTH * HEIGHT) {
		return world[index] == '#';
	}
	return true;
}

void print(int x, int y) {
	qrosturm::clear(' ');
	for (int row = 0; row < HEIGHT; row++) {
		qrosturm::set_print_coord(row, 0);
		for (int column = 0; column < WIDTH; column++) {
			std::string str;
			if (row == y && column == x) {
				str += ":)";
			}
			else {
				str += world[coord_to_index(row, column, WIDTH)];
				str += world[coord_to_index(row, column, WIDTH)];
			}
			qrosturm::print(str);
		}
	}
	qrosturm::refresh();
}

int main() {
	qrosturm::init();

	int player_x = 2;
	int player_y = 4;

	print(player_x, player_y);

	while (true) {
		qrosturm::Event event = qrosturm::poll_event();

		if (event.type != qrosturm::EventType::Key) {
			continue;
		} 
		else if (event.key.type != qrosturm::KeyEventType::Named) {
			continue;
		} 
		else if (event.key.state == qrosturm::ButtonState::Down) {
			continue;
		}
		else if (event.key.name == qrosturm::NamedKey::UpArrow) {
			if (!collides(coord_to_index(player_y - 1, player_x, WIDTH))) {
				player_y -= 1;
			}
		}
		else if (event.key.name == qrosturm::NamedKey::DownArrow) {
			if (!collides(coord_to_index(player_y + 1, player_x, WIDTH))) {
				player_y += 1;
			}
		}
		else if (event.key.name == qrosturm::NamedKey::LeftArrow) {
			if (!collides(coord_to_index(player_y, player_x - 1, WIDTH))) {
				player_x -= 1;
			}
		}
		else if (event.key.name == qrosturm::NamedKey::RightArrow) {
			if (!collides(coord_to_index(player_y, player_x + 1, WIDTH))) {
				player_x += 1;
			}
		}
		else if (event.key.name == qrosturm::NamedKey::Escape) {
			break;
		}

		print(player_x, player_y);
	}
}