#pragma once

constexpr int MAP_HEIGHT = 25;
constexpr int MAP_WIDTH  = 80;

namespace tar {
	class GameLevel;

	class Object {
		private:
			float x = 0.0f, y = 0.0f;
			float width = 0.0f, height = 0.0f;
			char c_type = ' ';
			
		public:
			Object() = default;
			Object(float x_pos, float y_pos, float w, float h, char type);
			virtual ~Object() = default;

			float getX() const { return x; }
			float getY() const { return y; }
			float getWidth() const { return width; }
			float getHeight() const { return height; }
			char getType() const { return c_type; }

			void setPos(float x_pos, float y_pos) { x = x_pos; y = y_pos; }

			void setType(char type) { c_type = type; }
			void changeX(float dx) { x += dx; }
			void changeY(float dy) { y += dy; }

			bool isCollision(const Object& other) const;
			void putOnMap(char (&map)[MAP_HEIGHT][MAP_WIDTH + 1]) const;
	};
	
	

	class Brick : public Object {
		public:
			Brick() = default;
			Brick(float x_pos, float y_pos, float w, float h, char type) 
				: Object(x_pos, y_pos, w, h, type) {}
	};

	class Moving : public Object {
		private:
			float horiz_speed = 0.2f;
			float vert_speed = 0.0f;
			bool is_fly = false;
			
		public:
			Moving() = default;
			Moving(float x_pos, float y_pos, float w, float h, char type) 
				: Object(x_pos, y_pos, w, h, type) {}
			
			float getVertSpeed() { return vert_speed; }
			float getHorizSpeed() { return horiz_speed; }
			bool getIsFly() const { return is_fly; }
			
			void setVertSpeed(float speed) { vert_speed = speed; }
			void setHorizSpeed(float speed) { horiz_speed = speed; }
			void setIsFly(bool fly) { is_fly = fly; }
				
			void vertMove(GameLevel& level, bool is_mario);
			void horizonMove(GameLevel& level);
			
	};
	
	class Mario : public Moving {	
		public:
			Mario() : Moving(39.0f, 10.0f, 3.0f, 3.0f, '@') {}
			
			void reset();
	};
}