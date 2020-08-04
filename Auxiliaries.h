//
// Created by avira on 04/08/2020.
//

#ifndef MTM_FINALPROJECT_AUXILIARIES_H
#define MTM_FINALPROJECT_AUXILIARIES_H
#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <memory>
#include <set>
#include <utility>


typedef void func_t();
typedef std::map<std::string, func_t*> strfmap_t;



const strfmap_t func_map=
        {
                {"reset", reset},
                {"who", printWho}
        };

template<class Application>
void execute(Application func);









#endif //MTM_FINALPROJECT_AUXILIARIES_H
