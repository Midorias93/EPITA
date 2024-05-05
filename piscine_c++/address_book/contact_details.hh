#pragma once
#include <optional>
#include <string>

struct ContactDetails
{
public:
    static std::optional<ContactDetails>
    makeDetails(const std::string& telephone_number,
                const std::string& personal_email);

    std::string number_;
    std::string email_;
    friend std::ostream& operator<<(std::ostream& os,
                                    const ContactDetails& contact_details);

private:
    ContactDetails(const std::string& telephone_number,
                   const std::string& personal_email);
};

std::ostream& operator<<(std::ostream& os,
                         const ContactDetails& contact_details);
