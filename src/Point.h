#define POINT_CLASS 1

class Point {
    public:
        int x, y; 
        
        Point(int _x, int _y) {
            x = _x;
            y = _y;  
        };
        
        Point() {
            x = 0;
            y = 0;   
        }
        
        Point operator+(const Point &other) const{
            Point point(x + other.x, y + other.y);
            return (point);
        };
        
        Point operator-(const Point &other) const {
            Point point(x - other.x, y - other.y);
            return (point);
        };  
        
        bool operator==(const Point &other) const {
            return(x == other.x and y == other.y); 
        };
        
        Point operator*(const int scaler) {
            Point point(x * scaler, y * scaler);
            return (point);
        };
};