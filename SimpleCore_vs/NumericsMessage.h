#ifndef NUMERICS_MESSAGE_H
#define NUMERICS_MESSAGE_H

#include <string>
#include <sstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include "Constants.cpp"

struct Numeric
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
	  ss << "<numeric name=\"" << name << "\">";
	  ss << data;
	  ss << "</numeric>";
	  return ss.str();
  }
};

struct NumericsMessage
{
  int seq_id;
  Numeric peep;
  Numeric pMax;
  Numeric tv;
  Numeric rr;

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & seq_id;
    ar & respRate;
  }

  std::string toXML() {
	  std::stringstream ss;
	  ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	  ss << "<numerics_message sequence=\"" << seq_id << "\">";
	  ss << peep.toXML();
	  ss << pMax.toXML();
	  ss << tv.toXML();
	  ss << rr.toXML();
	  ss << "</numerics_message>";
	  return ss.str();
  }

  NumericsMessage fromXML(std::string xmlStr) {
	Constants constants;
	std::stringstream ss;
	ss << xmlStr;
	NumericsMessage sm;
	using boost::property_tree::ptree;
    ptree pt;

    // Load the XML file into the property tree. If reading fails
    // (cannot open file, parse error), an exception is thrown.
	read_xml(ss,pt);
	sm.seq_id = pt.get<int>("numerics_message.<xmlattr>.sequence");

	ptree::iterator it;
	for (it = pt.get_child("numerics_message").begin(); it != pt.get_child("numerics_message").end(); ++it ) {
		std::string tagName;
		tagName = it->first.data();
		if (tagName == "numeric") {
			ptree const& numeric = it->second;
			std::string numericName = numeric.get<std::string>("<xmlattr>.name");
			if (numericName == constants.PEEP_NUMERIC) {
				sm.peep.data = std::atof((it->second.data()).c_str());
				sm.peep.name = numericName;
			}
			else if (numericName == constants.BREATH_RATE_NUMERIC) {
				sm.rr.data = std::atof((it->second.data()).c_str());
				sm.rr.name = numericName;
			}
			else if (numericName == constants.PMAX_NUMERIC) {
				sm.pMax.data = std::atof((it->second.data()).c_str());
				sm.pMax.name = numericName;
			}
			else if (numericName == constants.TIDAL_VOLUME_NUMERIC) {
				sm.tv.data = std::atof((it->second.data()).c_str());
				sm.tv.name = numericName;
			}
		}
	}
	return sm;
  }

};
#endif