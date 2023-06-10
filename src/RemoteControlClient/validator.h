#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QString>
#include <QRegularExpression>

class Validator
{
public:
    bool is_valid_IP(QString);   // проверка валидности IP
};

#endif // VALIDATOR_H
