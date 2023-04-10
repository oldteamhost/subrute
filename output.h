#ifdef __cplusplus
extern "C" {
#endif

// main
int init_data_folder();
void init_main_folders();

// txt
int write_main_info_to_file(const char* path, const char* line);
int write_line_to_file(const char *path, const char *line);

#ifdef __cplusplus
}
#endif

