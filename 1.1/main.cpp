#include <ostream>
#include <stdio.h>
#include "input.h"
#include <getopt.h>
#include "menu.h"
#include "optargs.h"
#include "output.h"
#include <stdlib.h>
#include <string.h>
#include "codealg.h"
#include <iostream>
#include "parse.h"
#include <chrono>
#include <iomanip>
#include <sstream>

struct opt_args opa;
file_import fi;

void help_menu();
const char* run;

int main(int argc, char** argv){

    // for help menu
    run = argv[0];

    // for "set" arg
    std::string custom_convert;

    // if custom_base
    std::string custom_path_result;

    const char* short_options = "hvT::p:Ps";
    const struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'v'}, 
        {"proxy", required_argument, 0, 'p'},
        {"timeout", optional_argument, 0, 'T'},
        {"txt", required_argument, 0, 1},
        {"db", no_argument, 0, 3},
        {"protocol", required_argument, 0, 4},
        {"base", required_argument, 0, 8},
        {"user-agent", required_argument, 0, 9},
        {"error", no_argument, 0, 5},
        {"set", required_argument, 0, 's'},
        {0,0,0,0}}; 

        if (argc <= 1){
            help_menu();
            return 0; 
        } 
        else {

        // init folders
        init_main_folders();

        int rez;
        int option_index = 0;
        while((rez = getopt_long(argc, argv, short_options, long_options, &option_index)) != EOF){
            switch (rez) {
                case 'h':
                    help_menu();
                    return 0;
                    break;
                case 'v':
                    printf("oldteam & %sv\n", version());
                    return 0;
                    break;
                case 'p':
                    opa.proxy_active = 1;
                    opa.proxy = optarg; break;
                case 'T':
                    opa.timeout_active = 1;
                    if (optarg != NULL) 
                        opa.timeout = optarg;
                    else
                        waring_timeout();
                        opa.timeout = "80";
                    break;
                case 's':
                    opa.custom_active = 1;
                    custom_convert = optarg;
                    break;
                case 1:
                    opa.txt_active = 1;
                    opa.txt_path = optarg;
                    break;
                case 3:
                    opa.debug_active = 1;
                    break;
                case 4:
                    opa.protocol_active = 1;
                    opa.protocol = optarg;
                    break;
                case 5:
                    opa.error_active = 1;
                    break;
                case 7:
                   opa.fast_active = 1;
                   opa.proxy_active = 0;
                   break; 
                case 8:
                {
                   opa.path_active = 1;
                   std::string optarg_convert = optarg;
                   if (optarg_convert == "max"){
                        custom_path_result = "bases/max.txt";
                   }
                   else if (optarg_convert == "standart"){
                        custom_path_result = "bases/standart.txt";
                   }
                   else if (optarg_convert == "mini"){
                        custom_path_result = "bases/mini.txt";
                   }
                   else {
                        custom_path_result = "bases/" + optarg_convert;
                   }
                   break;
                }
                case 9:
                    opa.user_agent_active = 1;
                    opa.user_agent = optarg;
                    break;
               case '?':
                default:
                    help_menu();
                    return 0;
                    break;
            }
        }
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now); char datetime[20];

    strftime(datetime, sizeof(datetime), "%Y-%m-%d %H:%M:%S", t);
    std::cout << "Starting Subrute " << version() << " at " << datetime << std::endl;

    check_net();

    if (opa.proxy_active){
        check_proxy(opa.proxy);
    }
    
    // protocol
    if (opa.protocol_active){
        std::string protocol_convert = opa.protocol;
        if (protocol_convert == "http" || protocol_convert == "http://"){
            opa.protocol = "http://";
        }
        else if (protocol_convert == "https" || protocol_convert == "https://"){
            opa.protocol = "https://";
        }
        else {
            std::cout << "ERROR: protocol only (http, https)\n";
            return EOF;
        }
        std::cout << "Using protocol is: " << opa.protocol << "\n";
    }
    else {
        std::cout << "Subrute using default protocol (https)\n";
        opa.protocol = "https://";
    } 

    // parse names 
    if (optind < argc){
        opa.target = argv[optind];
    }

    std::vector<std::string> names = split_names(opa.target); // names

    // file init
    std::vector<std::string> urls;

    if (opa.path_active != 1){
        fi.import_file("bases/standart.txt", urls);     
    }
    else {
        fi.import_file(custom_path_result.c_str(), urls);     
    }

    int i; // names count
    int success_count = 0; // success count
    std::string result[10000]; // names
    clock_t start, end; // time
    double cpu_time_used; // result time

    // alg code
    start = clock();

    if (opa.proxy_active){
        std::cout << "Subrute: proxy is active: ( " << opa.proxy << " )\n";
    } 

    if (opa.txt_active && opa.debug_active){
        write_main_info_to_file(opa.txt_path, "\nStarting Subrute (mode DEBUG) at ");
    }
    else if (opa.txt_active && opa.debug_active != 1){
        write_main_info_to_file(opa.txt_path, "\nStarting Subrute (mode NORMAL) at ");
    }

    // for user agent
    if (opa.user_agent_active){
        user_agent_active();
        set_user_agent(opa.user_agent);
        std::cout << "Subrute using user-agent: (" << opa.user_agent << ")\n";
    }

    // for "set"
    if (opa.custom_active){
        if (custom_convert == "a"){
           std::cout << "Subrute using mode (a): prtcl://dns + paths (breacher)\n\n";
        }
        else if (custom_convert == "b"){
            std::cout << "Subrute using mode (b): prtcl://paths + dns (bypass)\n\n";
        }
        else {
            std::cout << "ERROR: mode only (a, b)\n\n";
            return EOF;
        }
    }
    else {
        std::cout << "Subrute using default mode: prtcl://dns + paths (breacher)\n\n";
    }

    // parse user set
    for (i = 0; i < names.size(); i++){

        // for txt save
        if (opa.txt_active){
            std::string name_scan_txt = "\n\tChecking host: " + names[i];
            write_line_to_file(opa.txt_path, name_scan_txt.c_str());
        }

        

        // main print
        std::cout << "Checking host " << names[i] << ":" << std::endl;
        std::cout << "CODE\tSTATE\tURL\n";

        for(int o = 0; o < urls.size(); o++){
            long code_temp; // standart
          
            if (opa.custom_active){
                if (custom_convert == "a"){
                    result[i] = opa.protocol + names[i] + urls[o]; // urls
                }
                else if (custom_convert == "b"){
                    result[i] = opa.protocol + urls[o] + names[i]; // urls
                }
            }
            else {
                result[i] = opa.protocol + names[i] + urls[o]; // urls
            } 

            std::string result_str_txt = "\t\t" + std::to_string(code_temp) + "\t\t\t" + result[i].c_str();
            
            // timeout            
            if (opa.timeout_active){
                delay_ms(atoi(opa.timeout));
            }

            // code alg
            if (opa.fast_active != 1){
                code_temp = standart_get_responce_code(result[i].c_str(), 0, "");
            }
            if (opa.fast_active != 1 && opa.proxy_active == 1){
                code_temp = standart_get_responce_code(result[i].c_str(), 1, opa.proxy);
            }

            if(code_temp == 200){
                std::cout << code_temp << "\tappear\t" << result[i] << std::endl;
                
                // for txt
                if (opa.txt_active)
                    write_line_to_file(opa.txt_path, result_str_txt.c_str());
                
                success_count++;
            }

            if (opa.error_active){
                if (code_temp == 0){
                    std::cout << code_temp << "\terror\t" << result[i] << std::endl;
                }
            }
            
            // debug print
            if (opa.debug_active){
                // for txt
                if (opa.txt_active)
                    write_line_to_file(opa.txt_path, result_str_txt.c_str());

                if (code_temp == 404){
                    std::cout << code_temp << "\tfailed\t" << result[i] << std::endl;
                }
                else if (code_temp == 301){
                    std::cout << code_temp << "\tfilter\t" << result[i] << std::endl;
                }
                else if (code_temp == 302){
                    std::cout << code_temp << "\tfilter\t" << result[i] << std::endl;
                }
           }
        }
        std::cout << std::endl;
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    std::ostringstream oss;
    oss << "Subrute done: " << success_count << " successful in "
        << std::fixed << std::setprecision(1) << cpu_time_used << "s";

    std::string result_scan = oss.str();
    std::string result_scan_txt = "\n" + result_scan;

    std::cout << result_scan << std::endl;

    // txt save
    if (opa.txt_active){
        write_line_to_file(opa.txt_path, result_scan_txt.c_str());
    }

    return 0;
}

void help_menu(){
    std::cout << "Subrute: bruteforce URL.\n\n";

    std::cout << "usage: " << run << " [TARGETS (1,2,3) ] [ARGUMENTS]\n\n\n";


    std::cout << "arguments main:\n";
    std::cout << "  -h, --help            Show this help message and exit.\n";
    std::cout << "  -v, --version         Display version information and dependencies.\n";
    std::cout << "  --db, --debug         Saving and outputting even pages that are not working.\n";
    std::cout << "  -T, --timeout<MS>     Set a delay when receiving a page.\n";
    std::cout << "  --protocol <PROTOCOL> Set custom web protocol.\n";
    std::cout << "  --error               Display errors.\n\n";

    std::cout << "arguments save:\n";
    std::cout << "  --txt <FILE>          Save output to txt.\n\n";

    std::cout << "arguments user:\n";
    std::cout << "  -s, --set <MODE>      Set style link (see github).\n";
    std::cout << "  --base <PATH>         Specify your file with links.\n";
    std::cout << "  --user-agent <agent>  Set your user-agent.\n";
}
