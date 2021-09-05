#include "MicroBit.h"
#define MICROBIT_BLE_ENABLED 0 //Turn off bluetooth and allow for Radio, this code is repetitive and shown for comment purposes only

#ifndef SNAKE_CLASS 
    #include "Snake.h"
#endif

#ifndef POINT_CLASS
    #include "Point.h"
#endif

#ifndef BOARD_CLASS
    #include "Board.h"
#endif

#ifndef OTHERSNAKE_CLASS
    #include "OtherSnake.h"
#endif

#ifndef OTHERSNAKES_CLASS
    #include "OtherSnakes.h"
#endif

#define TURN_PAUSE 500
#define GROUP 1
#define POWER 5
#define BRIGHTNESS 50
#define KICK_TIME 5000

//Globals
MicroBit uBit;
Snake snake;
Board board;
OtherSnakes otherSnakes;


//Functions
void initSnake();
void foreach(OtherSnake &otherSnake);
void onRadio(MicroBitEvent);

int main() {
    //Inits
    uBit.init();
    uBit.seedRandom();
    
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_A, MICROBIT_BUTTON_EVT_CLICK, &snake, &Snake::buttonA, MESSAGE_BUS_LISTENER_IMMEDIATE);
    uBit.messageBus.listen(MICROBIT_ID_BUTTON_B, MICROBIT_BUTTON_EVT_CLICK, &snake, &Snake::buttonB, MESSAGE_BUS_LISTENER_IMMEDIATE);
    
    uBit.display.setDisplayMode(DISPLAY_MODE_BLACK_AND_WHITE);
    uBit.display.setBrightness(BRIGHTNESS);
    
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onRadio, MESSAGE_BUS_LISTENER_QUEUE_IF_BUSY);
    uBit.radio.enable();
    uBit.radio.setGroup(GROUP);
    uBit.radio.setTransmitPower(POWER);
    
    board.init();
    
    initSnake();
    
    const int id = uBit.random(0x7FFF);
    
    //Loop
    unsigned long int lastTime = 0;
    while (true) {
        if (uBit.systemTime() - lastTime >= TURN_PAUSE) {
            lastTime = uBit.systemTime();
            
            otherSnakes.foreach(&foreach);
            
            board.clearSnake(snake); //Clearing old snake
            const Point newPoint = snake.move(); //Move the snake and get the new point it moved to
            
            //Check death
            if (board.pcc(newPoint) or snake.onBody(newPoint)) {
                board.clearSnake(snake);
                uBit.sleep(1000);
                initSnake();
            } else {
                board.setSnake(snake);
                board.draw(snake.getHead(), uBit.display.image, BRIGHTNESS);      
            }
            snake.sendData(uBit.radio.datagram, id);
        }
        uBit.sleep(50);
    } 
}

void initSnake() {
    Point startPoint(-1, -1);
    while (board.pcc(startPoint)) {
        startPoint.x = uBit.random(15);
        startPoint.y = uBit.random(15);
    }
    snake.init(startPoint);
};

void foreach(OtherSnake &otherSnake) {
    if (uBit.systemTime() - otherSnake.getTime() >= KICK_TIME) {
        board.clearSnake(otherSnake);
        otherSnakes.remove(otherSnake.getId());   
    }
}

void onRadio(MicroBitEvent) {
    PacketBuffer p = uBit.radio.datagram.recv();
    
    int id = p[0] | (p[1] << 8);
    Point* body = new Point[SNAKE_LENGTH];
    for (int i = 0; i < SNAKE_LENGTH; i++) {
        body[i].x = (int) p[i * 2 + 2];  
        body[i].y = (int) p[i * 2 + 3];
    }
    
    OtherSnake* current = otherSnakes[id];
    if (current) {
        board.clearSnake(*current);
        current->setBody(body, uBit.systemTime());
        board.setSnake(*current);
    } else {
        OtherSnake* otherSnake = new OtherSnake(id);
        otherSnake->setBody(body, uBit.systemTime());
        otherSnakes.add(*otherSnake);
        board.setSnake(*otherSnake);
    }
}