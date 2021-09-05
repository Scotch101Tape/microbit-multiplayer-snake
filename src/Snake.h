#define SNAKE_CLASS 1

#ifndef POINT_CLASS 
    #include "Point.h"
#endif

#define SNAKE_LENGTH 7

enum Direction {
    up,
    down,
    left,
    right   
};

class Snake {
    private:
        Point body[SNAKE_LENGTH];
        Direction direction;
        int headIndex;
        
        
    public:
        void init(const Point &start) {
            for (int i = 0; i < SNAKE_LENGTH; i++) {
                body[i] = start;
            }
            headIndex = 0;
            direction = up;   
        }
        
        const Point move() {
            Point moveVector(0,0);
            switch(direction) {
                case up:
                    moveVector.y = -1;
                    break;
                case left:
                    moveVector.x = -1;
                    break;
                case right:
                    moveVector.x = 1;
                    break;
                case down:
                    moveVector.y = 1;
                    break;
            };
            const int headIndex = getHeadIndex();
            const int tailIndex = getTailIndex();
            const Point newPoint = body[headIndex] + moveVector;
            
            body[tailIndex] = newPoint;
            incrementIndex();
            return(newPoint);
        };
        
        void buttonA(MicroBitEvent) {
            switch (direction) {
                case up:
                    direction = left;
                    break;
                case down:
                    direction = left;
                    break;
                case left:
                    direction = down;
                    break;
                case right:
                    direction = up;
                    break;
            }
        };
        
        void buttonB(MicroBitEvent) {
            switch (direction) {
                case up:
                    direction = right;
                    break;
                case down:
                    direction = right;
                    break;
                case left:
                    direction = up;
                    break;
                case right:
                    direction = down;
                    break;
            }
        };
        
        Point getHead() const {
            return (body[headIndex]);
        };
        
        const Point* getBody() const {
            return (body);
        }
        
        bool onBody(const Point &point) {
            for (int i = 0; i < SNAKE_LENGTH; i++) {
                if (i != headIndex) {
                    if (point == body[i]) {
                        return (true);   
                    }
                }   
            }
            return (false);
        }
        
        void sendData(MicroBitRadioDatagram &datagram, int id) {
            PacketBuffer p = PacketBuffer(2 + SNAKE_LENGTH * 2);
            p[0] = id & 0xFF; //Little-endian
            p[1] = id >> 8;
            for (int i = 0; i < SNAKE_LENGTH; i++) {
                Point bodyPoint = body[i];
                p[i * 2 + 2] = (char) bodyPoint.x;
                p[i * 2 + 3] = (char) bodyPoint.y;
            }
            datagram.send(p);
        }
    
    private:
        int getHeadIndex() const {
            return (headIndex);
        };
        
        int getTailIndex() const {
            return ((((headIndex - 1) % SNAKE_LENGTH) + SNAKE_LENGTH) % SNAKE_LENGTH);
        };
        
        void incrementIndex() {
            headIndex = getTailIndex();
        };
};