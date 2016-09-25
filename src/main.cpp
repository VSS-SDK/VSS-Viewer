/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */
#include "iostream"
#include "graphics.h"
#include "boost.h"

using namespace std;

bool argParse(int argc, char** argv, bool *debug, string *camera, string *ip);

int main(int argc, char** argv){
	bool debug;
    string camera;
    string ip;

	argParse(argc, argv, &debug, &camera, &ip);

	Graphics graphics;
	graphics.init(argc, argv, debug, camera, ip);

	return 0;
}

bool argParse(int argc, char** argv, bool *debug, string *camera, string *ip){
    namespace bpo = boost::program_options;

    // Declare the supported options.
    bpo::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "(Optional) produce help message")
        ("camera,c", bpo::value<std::string>()->default_value("tv"), "(Optional) Specify the camera that you want, may be <tv> or <top>.")
        ("ip_state,i", bpo::value<std::string>()->default_value("localhost"), "(Optional) Specify the IP from pc it's running VSS-Vision.")
        ("debug,d", "(Optional) open the debug rotine");
    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    if (vm.count("help")){
        std::cout << desc << std::endl;
        return false;
    }

    if (vm.count("debug")){
        *debug = true;
    }

    *camera = vm["camera"].as<string>();

    *ip = vm["ip_state"].as<string>();

    return true;
}