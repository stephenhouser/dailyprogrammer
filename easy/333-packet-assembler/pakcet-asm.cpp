/* packet-asm - Packet Assembler Programmer Challenge
 *
 * [2017-09-26] Challenge #333 [Easy] Packet Assembler
 * 2017/10/03 Stephen Houser
 */
#include <iostream>	// cout
#include <iomanip>
#include <string>	// general string stuff
#include <cstdlib>	
#include <vector>	// vectors
#include <map>
#include <unistd.h>	// getopt

bool verbose = false;			// show progress and debug information
const char *program_name = "packet-asm";

void usage(const char * p_name = NULL) {
	const char *l_name = p_name ? p_name : program_name;
	std::cout << "Packet Assembler" << std::endl;
	std::cout << std::endl;
	std::cout << "usage: " << l_name << " [-h] [-v] >]" << std::endl;
	std::cerr << "\t-h\tprint help and usage" << std::endl;
	std::cerr << "\t-v\tprint verbose messages" << std::endl;
	std::cout << "The packet assembler reads simulated packets from stdin and output to stdout." << std::endl;
	std::cout << "Input is of the form (whitespace delimited):" << std::endl;
	std::cout << "\t<message-id> <packet-id> <num-packets> <text>" << std::endl;
	std::cout << "\t<message-id>  the unique message identifier" << std::endl;
	std::cout << "\t<packet-id>   the packet number within a message" << std::endl;
	std::cout << "\t<num-packets> the number of packets in a message" << std::endl;
	std::cout << "\t<text>        the text to be assembled into a message" << std::endl;
	std::cout << std::endl;
	std::cout << "Output is of the same form with packets printed in-order." << std::endl;
	std::cerr << std::endl;
}

std::string trim(const std::string& str,
	const std::string& whitespace = " \t") {
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos) {
		return ""; // no content
	}

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;
	return str.substr(strBegin, strRange);
}

class Packet {
	public:
		int message_id;
		int packet_id;
		int num_packets;
		std::string message_text;

		friend std::istream& operator>>(std::istream& is, Packet& p);
		friend std::ostream& operator<<(std::ostream& os, const Packet& dt);  
};

std::istream& operator>>(std::istream& is, Packet& p) {
	// parse packet
	std::string message_text;
	is >> p.message_id >> p.packet_id >> p.num_packets;
	std::getline(is, message_text);	// to end of line
	p.message_text = trim(message_text);
	// std::cout << "[" << p.message_text << "]" << std::endl;
	return is;
	}

std::ostream& operator<<(std::ostream& os, const Packet& p) {
	os << std::setw(4) << p.message_id  <<
		  std::setw(5) << p.packet_id   <<
		  "   " << std::left << std::setw(2) << p.num_packets << std::right;
	if (p.message_text.size() != 0) {
		os << "  " << p.message_text;
	}
	return os;
}	

class Message {
	public:
		int message_id;
		int num_packets;
		std::map<int, Packet> packets;

		Message() {}
		Message(int message_id, int num_packets) {
			this->message_id =message_id;
			this->num_packets = num_packets;
	   }
};

int main(int argc, char *argv[]){
	int option_char;	// getopt returned option character
	
	while ((option_char = getopt(argc, argv, "?hv")) != EOF) {
		switch(option_char) {
			case '?':
			case 'h': {
				usage();
				return 0;
			}
			case 'v': {
				verbose = true;
				break;
			}
		default:
				break;
		}
	}

	std::map<int, Message> messages;

	Packet p;
	while (std::cin >> p) {
		Message *m;
		if (messages.count(p.message_id) == 1) {
			m = &messages[p.message_id];
		} else {
			// m = new Message(p.message_id, p.num_packets);
			m = new Message();
			m->message_id = p.message_id;
			m->num_packets = p.num_packets;
		}

		m->packets[p.packet_id] = p;	// copy?
		messages[p.message_id] = *m;	// take ownership

		if (m->num_packets == m->packets.size()) {
			for (const auto &[packet_id, pkt] : m->packets) {
				std::cout << pkt << std::endl;
			}
			messages.erase(p.message_id);
		}
	}

	if (messages.size() != 0) {
		std::cout << std::endl << "Incomplete packets:" << std::endl;
		for (const auto &[message_id, msg] : messages) {
			for (const auto &[packet_id, pkt] : msg.packets) {
				std::cout << pkt << std::endl;
			}
		}
	}
}
