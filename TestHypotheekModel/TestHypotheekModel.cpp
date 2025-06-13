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
const Utils::Date startDate(Utils::Date::DDay(1), Utils::Date::MONTH::February, Utils::Date::DYear(2023));

std::unique_ptr<hypotheek::AnnuitaireHypotheek> createHypotheek(int bedrag, double rente, int periodes)
{
    std::unique_ptr<hypotheek::AnnuitaireHypotheek> hypotheek = std::make_unique< hypotheek::AnnuitaireHypotheek>();
    hypotheek->SetHypotheekBedrag(Finance::Bedrag(double(bedrag)));
    hypotheek->SetRentePercentage(hypotheek::Percentage(rente));
    hypotheek->SetNumberOfMonths(periodes);
    hypotheek->SetStartDate(startDate);
    return std::move(hypotheek);
}

void print(const std::vector<hypotheek::HypotheekData>& entries)
{
    std::cout << "Startdatum - Annuiteit - Betaling - Aflossing - Rente - Restschuld" << std::endl;
    for (const auto& entry : entries) {
        std::cout << entry.startDate << "   - " << entry.payment << " - " << (entry.repayment + entry.interest) << " - " << entry.repayment << " - " << entry.interest << " - " << entry.remainingDebt << std::endl;
    }
}

void TestCommon()
{
    std::cout << "*** TestCommon ***" << std::endl;
    auto hypotheek = createHypotheek(100000, 120, 1);
    hypotheek::OverzichtCreator creator;
    creator.visit(*hypotheek);
    print(creator.collection());
    std::cout << "*** TestCommon END ***" << std::endl;
}

void TestLonger()
{
    std::cout << "*** TestLonger ***" << std::endl;
    auto hypotheek = createHypotheek(100000, 120, 2);
    hypotheek::OverzichtCreator creator;
    creator.visit(*hypotheek);
    print(creator.collection());

    std::cout << "*** TestLonger END ***" << std::endl;
}

void TestNatasja()
{
    std::cout << "*** TestNatasja ***" << std::endl;
    auto hypotheek = createHypotheek(133000, 3.5, 360);
    hypotheek::OverzichtCreator creator;
    creator.visit(*hypotheek);
    print(creator.collection());

    std::cout << "*** TestNatasja END ***" << std::endl;
}

void TestNatasjaExtraPayment()
{
    std::cout << "*** TestNatasjaExtraPayment ***" << std::endl;
    auto hypotheek = createHypotheek(133000, 3.5, 360);
    hypotheek->setExtraAflossing(Utils::Date(Utils::Date::DDay(16), Utils::Date::MONTH::June, Utils::Date::DYear(2025)), Finance::Bedrag(10000.0));
    hypotheek::OverzichtCreator creator;
    creator.visit(*hypotheek);
    print(creator.collection());

    std::cout << "*** TestNatasjaExtraPayment END ***" << std::endl;
}

void TestExtraPayment()
{
    std::cout << "*** TestExtraPayment ***" << std::endl;
    auto hypotheek = createHypotheek(100000, 120, 2);
    hypotheek->setExtraAflossing(Utils::Date(Utils::Date::DDay(16), Utils::Date::MONTH::February, Utils::Date::DYear(2000)), Finance::Bedrag(25000.0));
    hypotheek::OverzichtCreator creator;
    creator.visit(*hypotheek);
    print(creator.collection());

    std::cout << "*** TestExtraPayment END ***" << std::endl;
}

}

int main()
{
    TestCommon();
    TestLonger();
    TestExtraPayment();
    TestNatasja();
    TestNatasjaExtraPayment();
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
