#include "config.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

void Config::setConfigs() {
    boost::property_tree::ptree pt;
    boost::property_tree::read_ini("/home/kuryga/projects/ep_bot/config.ini", pt);
    botToken = pt.get<std::string>("tokens.bot");
    apiToken = pt.get<std::string>("tokens.api");
    apiUrl = pt.get<std::string>("url.api");
}
