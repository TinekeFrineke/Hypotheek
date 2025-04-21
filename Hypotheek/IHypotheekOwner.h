
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <HypotheekModel/IHypotheek.h>

class IHypotheekOwner
    : public IHypotheek
{
public:
    virtual ~IHypotheekOwner() = default;

    virtual std::string GetPand() const = 0;
    virtual std::vector<std::string> GetPanden() const = 0;
    virtual void SetPand(const std::string& pand) = 0;
    virtual void DeletePand(const std::string& pand) = 0;

    virtual void setHypotheek(std::unique_ptr<IHypotheek> hypotheek) = 0;
    virtual void resetHypotheek() = 0;
    virtual IHypotheek* getHypotheek() const = 0;
};