#include "Enemy.hpp"
#include "Platform.hpp"

struct enemies{
    Enemy* e;
    enemies* next;
};
typedef struct enemies* p_enem;

class Enemies{
    public:
        Enemies();
        void generate();


    protected:
        p_enem current;
        p_enem first;
        p_enem last;
};