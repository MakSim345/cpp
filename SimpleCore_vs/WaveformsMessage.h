#ifndef WAVEFORMS_MESSAGE_H
#define WAVEFORMS_MESSAGE_H
#include <string>
#include <sstream>
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>

struct Waveform
{
  std::string name;
  int data[10];

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & name;
    ar & data;
  }

  std::string toXML() {
	  std::stringstream ss;
	  ss << "<waveform name=\"" << name << "\">";
	  for (int i=0; i < 9; i++) {
		ss << data[i] << ",";
	  }
	  ss << data[9];
	  ss << "</waveform>";
	  return ss.str();
  }
};

struct WaveformsMessage
{
  int seq_id;
  Waveform paw;
  Waveform vol;
  Waveform flow;

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int version)
  {
    ar & seq_id;
    ar & paw;
    ar & vol;
	ar & flow;
  }

  std::string toXML() {
	  std::stringstream ss;
	  ss << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
	  ss << "<waveform_message sequence=\"" << seq_id << "\">";
	  ss << paw.toXML();
	  ss << flow.toXML();
	  ss << vol.toXML();
	  ss << "</waveform_message>";
	  return ss.str();
  }

  WaveformsMessage fromXML(std::string xmlStr) {
	std::stringstream ss;
	ss << xmlStr;
	WaveformsMessage wm;
	using boost::property_tree::ptree;
    ptree pt;

    // Load the XML file into the property tree. If reading fails
    // (cannot open file, parse error), an exception is thrown.
	read_xml(ss,pt);
	wm.seq_id = pt.get<int>("waveform_message.<xmlattr>.sequence");

	ptree::iterator it;
	for (it = pt.get_child("waveform_message").begin(); it != pt.get_child("waveform_message").end(); ++it ) {
		std::string tagName;
		tagName = it->first.data();
		if (tagName == "waveform") {
			ptree const& waveform = it->second;
			std::string waveName = waveform.get<std::string>("<xmlattr>.name");
			if (waveName == "Paw") {
				setIntData(it->second.data(),wm.paw.data);
				wm.paw.name = "Paw";
			}
			else if (waveName == "Vol") {
				setIntData(it->second.data(),wm.vol.data);
				wm.vol.name="Vol";
			}
			else if (waveName == "Flow") {
				setIntData(it->second.data(),wm.flow.data);
				wm.flow.name = "Flow";
			}
		}
	}
	return wm;
  }

  // expects a string of 10 ints separated by commas
  void setIntData (std::string intData, int intArray[]) {
	std::istringstream ss(intData);
	for (int i=0; i < 10; i++) {
		std::string s;
		getline( ss, s, ',' );
		intArray[i] = std::atoi(s.c_str());
	}
  }
};
#endif