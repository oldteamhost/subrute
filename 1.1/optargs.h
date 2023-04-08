
struct opt_args{
    char* target; // target 
    const char* path_base; // path from base url
    const char* proxy; // proxy
    const char* timeout; // timeout ms
    const char* txt_path; // users path save txt
    const char* protocol; // http, https
    const char* custom; // for arg "set"
    const char* user_agent;

    // ON or OFF
    int txt_active; 
    int path_active;
    int proxy_active;
    int timeout_active;
    int custom_active; // for arg "set"
    int fast_active;
    int error_active;
    int debug_active;
    int user_agent_active;
    int protocol_active;
};
