#define OTHERSNAKES_CLASS 1

#ifndef OTHERSNAKE_CLASS
    #include "OtherSnake.h"
#endif

#ifndef OTHERSNAKEENTRY_CLASS 
    #include "OtherSnakeEntry.h"
#endif

class OtherSnakes {
    private:
        OtherSnakeEntry* first;
        
    public:
        OtherSnakes() {
            first = NULL;   
        }
        
        OtherSnake* operator[] (int id) {
            OtherSnakeEntry* current = first;
            while (current and current->getSnake().getId() != id) {
                current = current->getNext();
            };
            if (current) {
                return (&current->getSnake());
            } else {
                return (NULL);   
            }
        }
        
        void foreach(void (*function)(OtherSnake&)) {
            OtherSnakeEntry* current = first;
            while (current) {
                OtherSnakeEntry* next = current->getNext();
                (*function)(current->getSnake());
                
                current = next;
            };
        }
        
        void add(OtherSnake &otherSnake) {
            if (first) {
                OtherSnakeEntry* current = first;
                OtherSnakeEntry* next = current->getNext();
                while (next) {
                    current = next;
                    next = current->getNext();
                }
                OtherSnakeEntry* otherSnakeEntry = new OtherSnakeEntry(otherSnake);
                current->addNext(otherSnakeEntry);
            } else {
                OtherSnakeEntry* otherSnakeEntry = new OtherSnakeEntry(otherSnake);
                first = otherSnakeEntry;
            }
        }
        
        void remove(int id) {
            OtherSnakeEntry* one = NULL;
            OtherSnakeEntry* two = first;
            
            while (two) {
                if (two->getSnake().getId() == id) {
                    break;
                }
                
                OtherSnakeEntry* twoNext = two->getNext();
                one = two;
                two = twoNext;
            }
            
            if (one and two) {
                OtherSnakeEntry* three = two->getNext();
                one->addNext(three); //Link the chain
                delete two;
            } else if(two and two == first) {
                first = NULL;
                delete two;
            }
        }
};