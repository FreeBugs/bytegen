#include <iostream>
#include <boost/program_options.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/hex.hpp>

using std::cout;
using std::endl;
using std::exception;
using std::cerr;
namespace bpo = boost::program_options;

bpo::options_description
getOptionsDescription(std::string *valuestr, std::string *ofstr, uint64_t *bs, uint64_t *count) {
    bpo::options_description description("Valid parameters");
    description.add_options()
            ("help", "go help yourself")
            ("value", bpo::value<std::string>(valuestr), "Required. The value to generate (e.g. 0xFF)")
            ("bs", bpo::value<uint64_t>(bs), "Block size in bytes.")
            ("count", bpo::value<uint64_t>(count), "Number of 1-Kbyte blocks to generate.");
    return description;
}

int main(int ac, char **av) {
    try {
        std::string valuestr;
        std::string ofstr;
        uint64_t bs;
        uint64_t count;
        auto description = getOptionsDescription(&valuestr, &ofstr, &bs, &count);

        bpo::variables_map variables_map;
        bpo::store(bpo::parse_command_line(ac, reinterpret_cast<const char *const *>(av), description), variables_map);
        bpo::notify(variables_map);

        if (variables_map.count("help")) {
            cout << description << endl;
            return 0;
        }

        if (variables_map.count("value")) {
        } else {
            cerr << "Parameter 'value' is required." << endl;
            return 1;
        }
        boost::replace_all(valuestr, "0x", "");
        uint16_t value;
        std::istringstream(valuestr) >> std::hex >> value;

        if (!variables_map.count("bs")) {
            cerr << "Parameter 'bs' is required." << endl;
            return 1;
        }

        uint64_t writeCount;
        if (!variables_map.count("count")) {
            cerr << "Parameter 'count' is required." << endl;
            return 1;
        } else {
            writeCount = count;
        }

        char *buf = new char[bs+1];
        memset(buf, value, bs);
        for (auto i = 0; i < writeCount; i++)
            cout << buf;
        delete [] buf;

    } catch (exception &ex) {
        cerr << "Error: " << endl << ex.what() << endl;
        return 1;
    } catch (...) {
        cerr << "Drink more coffee." << endl;
        return 1;
    }

    return 0;
}