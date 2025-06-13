#pragma once


#include <vector>

#include "HypotheekData.h"
#include "IHypotheekVisitor.h"


namespace hypotheek {


class IEventCollection;

class OverzichtCreator:
    public IVisitor
{
public:
    // Inherited via IVisitor
    virtual void visit(const AnnuitaireHypotheek& hypotheek) override;
    virtual void visit(const AflossingsvrijeHypotheek& hypotheek) override;

    const std::vector<HypotheekData>& collection() const { return m_result; }

private:
    std::vector<HypotheekData> m_result;
};

} // namespace hypotheek