#pragma once
#include "Student.h"

class UGStudent : public Student {
private:
    std::string advisorName;

public:
    UGStudent(const std::string& id = "", const std::string& n = "", const std::string& advisor = "");

    std::string getAdvisorInfo() const override;
    double calculateTuition() override;
    std::string getAdvisorName() const { return advisorName; }
    std::string getAdvisorNameOnly() const { return advisorName; }
};