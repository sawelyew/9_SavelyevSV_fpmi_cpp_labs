enum class Colors{Black=1, White};
class MoveLogger;

class ChessPiece{
    protected:
        Colors color_;
        int x_curr_;
        int y_curr_;
    public:
        int getX(){return x_curr_;}
        int getY(){return y_curr_;}
        std::string getColor();
        void setX(int x){x_curr_=x;}
        void setY(int y){y_curr_=y;}
        ChessPiece() = default;
        ChessPiece(int x, int y, Colors color);
        virtual std::string GetInfo() = 0;
        virtual bool CanMove(uint16_t x, uint16_t y) = 0;
        virtual void Move(uint16_t x, uint16_t y, MoveLogger& logger) = 0;
        virtual ~ChessPiece();
        ChessPiece(ChessPiece&& rhs);
        virtual ChessPiece& operator=(ChessPiece&& rhs);
};

class Bishop: virtual public ChessPiece{
    public:
        Bishop(int x, int y, Colors color);
        Bishop(Bishop&& rhs);
        Bishop() = default;
        Bishop& operator=(Bishop&& rhs);
        std::string GetInfo()override;
        bool CanMove(uint16_t x, uint16_t y)override;
        void Move(uint16_t x, uint16_t y, MoveLogger& logger)override;
};

class Rook: virtual public ChessPiece{
    public:
        Rook(int x, int y, Colors color);
        Rook(Rook&& rhs);
        Rook& operator=(Rook&& rhs);
        Rook() = default;
        std::string GetInfo()override;
        bool CanMove(uint16_t x, uint16_t y)override;
        void Move(uint16_t x, uint16_t y, MoveLogger& logger)override;
};

class Queen: public Rook, public Bishop{
    public:
        Queen(int x, int y, Colors color);
        Queen(Queen&& rhs);
        Queen& operator=(Queen&& rhs);
        Queen() = default;
        std::string GetInfo()override;
        bool CanMove(uint16_t x, uint16_t y)override;
        void Move(uint16_t x, uint16_t y, MoveLogger& logger)override;
};
std::string GetLetterByNumChess(int x);