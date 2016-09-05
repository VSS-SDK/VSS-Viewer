/*
 * This file is part of the VSS-Viewer project.
 *
 * This Source Code Form is subject to the terms of the GNU GENERAL PUBLIC LICENSE,
 * v. 3.0. If a copy of the GPL was not distributed with this
 * file, You can obtain one at http://www.gnu.org/licenses/gpl-3.0/.
 */


#include "graphics.h"
#include "boost.h"

bool argParse(int argc, char** argv, bool *debug);

int main(int argc, char** argv){
	bool debug;

	argParse(argc, argv, &debug);

	Graphics graphics;
	graphics.init(argc, argv, debug);

	return 0;
}

bool argParse(int argc, char** argv, bool *debug){
    namespace bpo = boost::program_options;

    // Declare the supported options.
    bpo::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "(Optional) produce help message")
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

    return true;
}