#include <iostream>

#include "address_book.hh"

ContactDetails::ContactDetails(const std::string& telephone_number,
                               const std::string& personal_email)
    : number_(telephone_number)
    , email_(personal_email)
{}

std::optional<ContactDetails>
ContactDetails::makeDetails(const std::string& telephone_number,
                            const std::string& personal_email)
{
    for (char car : telephone_number)
    {
        if (!std::isxdigit(car))
            return std::nullopt;
    }
    bool add = true;
    for (char car : personal_email)
    {
        if (car == '@')
            add = false;
    }
    if (add)
        return std::nullopt;

    return ContactDetails(telephone_number, personal_email);
}
std::ostream& operator<<(std::ostream& os,
                         const ContactDetails& contact_details)
{
    return os << contact_details.number_ << ", " << contact_details.email_
              << "\n";
}
