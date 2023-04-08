#ifdef __cplusplus
extern "C" {
#endif

// lib curl
struct adv_opt{
    int _user_agent;
    const char* user_agent;
};

long standart_get_responce_code(const char* node, int proxy_on, const char* proxy);

// custom delay cross platform :)
void delay_ms(int milliseconds);

// check net
void check_net(void);
void check_proxy(const char* proxy);
void user_agent_active(void);
void set_user_agent(const char* user_agent_);

#ifdef __cplusplus
}
#endif
