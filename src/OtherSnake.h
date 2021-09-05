#define OTHERSNAKE_CLASS 1

#ifndef POINT_CLASS
    #include "Point.h"
#endif

#ifndef SNAKE_CLASS
    #include "Snake.h"
#endif

class OtherSnake {
    private:
        Point* body;
        int id;
        long unsigned int lastTime;
        
    public:
        OtherSnake(int _id) {
            id = _id;
            body = NULL;
        }
        
        ~OtherSnake() {
            delete[] body;   
        }
        
        void setBody(Point* _body, long unsigned int time) {
            if (body) {
                delete[] body;
            }   
            body = _body;
            lastTime = time;
        }
        
        int getId() const {
            return (id);
        }
        
        const Point* getBody() const {
            return (body);
        }
        
        long unsigned int getTime() const {
            return (lastTime);   
        }
};