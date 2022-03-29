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

struct Video {
	std::string video_id;
	std::string video_name;
	std::string uploader;
	std::string cover_image;
	std::string source;
	std::string category;
	std::string upload_date;
	std::string describe;
};

REFLECTION(Video, video_id, video_name, uploader, cover_image, source, category, upload_date, describe)
