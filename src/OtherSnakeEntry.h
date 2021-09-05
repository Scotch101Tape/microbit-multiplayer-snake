#define OTHERSNAKEENTRY_CLASS 1

#ifndef OTHERSNAKE_CLASS
    #include "OtherSnake.h"
#endif

class OtherSnakeEntry {    
    private:
        OtherSnake* otherSnake;
        OtherSnakeEntry* next;

    public:
        OtherSnakeEntry(OtherSnake &_otherSnake) {
            otherSnake = &_otherSnake;
            next = NULL;
        }
        
        ~OtherSnakeEntry() {
            delete otherSnake;
        }
        
        void addNext(OtherSnakeEntry* _next) {
            next = _next;
        }
        
        OtherSnake& getSnake() {
            return(*otherSnake);
        }
        
        OtherSnakeEntry* getNext() {
            return(next);   
        }
};