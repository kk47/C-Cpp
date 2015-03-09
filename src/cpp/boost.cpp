#include "boost/program_options.hpp"
#include <iostream>
#include <string>

namespace {
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t SUCCESS = 0;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;
}

namespace po = boost::program_options;
void print_vm(po::options_description& opts, po::variables_map& vm);

int main(int argc, char* argv[])
{
    namespace po = boost::program_options;
    std::string filename;
    try{
        po::options_description kk("options");
        kk.add_options()
            ("help,h", "print help infoi\n a bit of long text")
            ("add,a", po::value<std::string>(&filename)->default_value("test"), "additional options")
            ("dir,D", po::value<std::vector<std::string> >()->multitoken(), "search dir")
            ("depth,d", po::value<int>()->implicit_value(5), "search depth");
        po::variables_map vm;
        try{
            po::store(po::parse_command_line(argc, argv, kk), vm);
            po::notify(vm);
            print_vm(kk, vm);
        } catch(po::error& e){
            std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
            std::cerr << kk << std::endl;
            return ERROR_IN_COMMAND_LINE;
        }
    } catch(std::exception& e){
        std::cerr << "Unhandled exception reached the top of main: " << e.what() << ", application will now exit" << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }
    return SUCCESS;
}

void print_vm(po::options_description& opts, po::variables_map& vm)
{
    if(vm.empty()){
        std::cout << opts << std::endl;
        return;
    }
    if(vm.count("help")){
        std::cout << opts << std::endl;
    }
    std::cout << "find opt:" << vm["filename"].as<std::string>() << std::endl;

    if(vm.count("dir")){
        std::cout << "dir opt:" << std::endl;
    }

    if(vm.count("depth")){
        std::cout << "depth opt:" << vm["depth"].as<int>() << std::endl;
    }
}
