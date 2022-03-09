#pragma once
#define ORMPP_ENABLE_MYSQL
#include "mysql.hpp"
#include "dbng.hpp"
using namespace ormpp;
#include <string>


struct VideoCategory {
	std::string category_name;
};

REFLECTION(VideoCategory, category_name)
