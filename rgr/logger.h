#include <vector>
#include <string>
class ChessPiece;

class MoveLogger{
    static int next_id_;
    const int id_;
    std::vector<std::string> history;
public:
    MoveLogger();
    ~MoveLogger();
    void AddMove(ChessPiece* figure, int x, int y);
};