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

    const std::vector<HypotheekEntry>& collection() const { return m_eventData; }

private:
    std::vector<HypotheekEntry> m_eventData;
};

} // namespace hypotheek