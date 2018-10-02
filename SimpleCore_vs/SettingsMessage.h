#ifndef SETTINGS_MESSAGE_H
#define SETTINGS_MESSAGE_H
#include <string>
#include <sstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

struct Setting
{
  std::string name;
  double data;

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & name;
    ar & data;
  }

  std::string toXML() {
	  std::stringstream ss;
	  ss << "<setting name=\"" << name << "\">";
	  ss << data;
	  ss << "</setting>";
	  return ss.str();
  }
};

struct SettingsMessage
{
  int seq_id;
  Setting theSetting;

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & seq_id;
    ar & respRate;
  }

  std::string toXML() {
	  std::stringstream ss;
	  ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	  ss << "<settings_message sequence=\"" << seq_id << "\">";
	  ss << theSetting.toXML();
	  ss << "</settings_message>";
	  return ss.str();
  }

  SettingsMessage fromXML(std::string xmlStr) {
	std::stringstream ss;
	ss << xmlStr;
	SettingsMessage sm;
	using boost::property_tree::ptree;
    ptree pt;

    // Load the XML file into the property tree. If reading fails
    // (cannot open file, parse error), an exception is thrown.
	read_xml(ss,pt);
	sm.seq_id = pt.get<int>("settings_message.<xmlattr>.sequence");

	ptree::iterator it;
	for (it = pt.get_child("settings_message").begin(); it != pt.get_child("settings_message").end(); ++it ) {
		std::string tagName;
		tagName = it->first.data();
		if (tagName == "setting") {
			ptree const& setting = it->second;
			std::string settingName = setting.get<std::string>("<xmlattr>.name");
			//if (settingName == "RespRate") {
				sm.theSetting.data = std::atof((it->second.data()).c_str());
				sm.theSetting.name = settingName;
			//}
		}
	}
	return sm;
  }

};
#endif