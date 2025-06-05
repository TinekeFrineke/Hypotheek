
#pragma once

class IHypotheek;

namespace hypotheek {

class AnnuitaireHypotheek;
class AflossingsvrijeHypotheek;

class IVisitor {
public:
    virtual ~IVisitor() = default;

    virtual void visit(const AnnuitaireHypotheek& hypotheek) = 0;
    virtual void visit(const AflossingsvrijeHypotheek& hypotheek) = 0;
};



} // namespace hypotheek