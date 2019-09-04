#include "header.h"

void get_env_data(env_data *E) {
  E->user_name = getenv("USER");
  E->hostname = getenv("NAME");
  E->pwd = getcwd(E->pwd, MAX_PATH_LENGTH);
}