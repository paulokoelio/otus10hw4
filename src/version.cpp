/**
\file
\brief Реализация функции praddr::version() для вывода версии решения ДЗ

Версия решения ДЗ может быть определена в коде программы путем вызова 
функции praddr::version()
*/
#include "version.h"

namespace praddr
{

    const char *version()
    {
        return PROJECT_VERSION;
    }

} // namespace praddr