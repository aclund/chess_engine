#include <ostream>
namespace Color {
    enum Code {
	FG_WHITE    = 101,
	FG_BLACK    = 30,
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
	BG_WHITE    = 47,
	BG_BLACK    = 100,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
            //return os << "\u001b[" << mod.code << "m";
        }
    };
}
