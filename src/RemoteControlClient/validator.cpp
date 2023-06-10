#include "validator.h"

bool Validator::is_valid_IP(QString ip)
{
    static QRegularExpression example_of_ip("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    if(ip.isEmpty() || !example_of_ip.match(ip).hasMatch())
        return false;
    return true;
}
