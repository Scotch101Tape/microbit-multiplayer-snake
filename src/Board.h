#define BOARD_CLASS 1

#ifndef POINT_CLASS
    #include "Point.h"
#endif

#ifndef SNAKE_CLASS
    #include "Snake.h"
#endif

#ifndef OTHERSNAKE_CLASS
    #include "OtherSnake.h"
#endif

class Board {
    private:
        bool board[15][15];
        
    public:
        void init() {
            for (int x = 0; x < 15; x++) {
                for (int y = 0; y < 15; y++) {
                    board[x][y] = false;   
                }
            }
        }
        
        void clearSnake(const Snake &snake) {
           setSnakePoints(snake, false);
        }
        
        void setSnake(const Snake &snake) {
            setSnakePoints(snake, true);
        }
        
         void clearSnake(const OtherSnake &snake) {
           setSnakePoints(snake, false);
        }
        
        void setSnake(const OtherSnake &snake) {
            setSnakePoints(snake, true);
        }
        
        void draw(const Point &center, MicroBitImage &image, const int brightness) {
            image.clear();
            for (int x = 0; x < 5; x++) {
                for (int y = 0; y <= 5; y++) {
                    if (pcc(Point(x + center.x - 2, y + center.y - 2))) {
                        image.setPixelValue(x, y, brightness);
                    }
                }
            }
        }
        
        bool pcc(const Point &point) {
            if (outOfRange(point)) {
                return(true);
            } else {
                return(board[point.x][point.y]);   
            }
        }
        
    private:
        void setSnakePoints(const Snake &snake, bool cellType) {
            const Point* body = snake.getBody();
            for (int i = 0; i < SNAKE_LENGTH; i++) {
                const Point point = body[i];
                if (not outOfRange(point)) {
                    board[point.x][point.y] = cellType;      
                }
            }
        }
        
        void setSnakePoints(const OtherSnake &snake, bool cellType) {
            const Point* body = snake.getBody();
            for (int i = 0; i < SNAKE_LENGTH; i++) {
                const Point point = body[i];
                if (not outOfRange(point)) {
                    board[point.x][point.y] = cellType;      
                }
            }
        }
        
        bool outOfRange(const Point &point) {
            return (point.x > 15 or point.y > 15 or point.x < 0 or point.y < 0);
        }
};