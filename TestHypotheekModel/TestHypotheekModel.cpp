// TestHypotheekModel.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>

#include <utilities/Bedrag.h>
#include <utilities/Date.h>

#include "AnnuitaireHypotheek.h"
#include "HypotheekEventCollection.h"
#include "OverzichtCreator.h"

namespace {
const Utils::Date startDate(Utils::Date::DDay(1), Utils::Date::MONTH::January, Utils::Date::DYear(2000));

std::unique_ptr<hypotheek::AnnuitaireHypotheek> createHypotheek(int bedrag, int rente, int periodes)
{
    std::unique_ptr<hypotheek::AnnuitaireHypotheek> hypotheek = std::make_unique< hypotheek::AnnuitaireHypotheek>();
    hypotheek->SetHypotheekBedrag(Finance::Bedrag(double(bedrag)));
    hypotheek->SetRentePercentage(hypotheek::Percentage(rente));
    hypotheek->SetNumberOfMonths(periodes);
    hypotheek->SetStartDate(Utils::Date(Utils::Date::DDay(1), Utils::Date::MONTH::January, Utils::Date::DYear(2000)));
    return std::move(hypotheek);
}

void TestCommon()
{
    auto hypotheek = createHypotheek(100000, 120, 1);
    //hypotheek::EventCollection collection;
    hypotheek::OverzichtCreator creator;
    creator.visit(*hypotheek);
    auto collection2(creator.collection()); (void)collection2;
}

}

int main()
{
    TestCommon();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
