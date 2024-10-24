#include "operators.h"

namespace fmi {
namespace sdp {

struct powOperator : public Operator
{
public:
    powOperator() : Operator('^', 30)
    {}
    int apply(int l, int r) const override
    {
        return (int)pow(l, r);
    }
};
static operatorRegistrator<powOperator> _Reg;

}
}
