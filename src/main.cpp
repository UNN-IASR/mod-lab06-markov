// Copyright 2024 Maz
#include <iostream>
#include"textgen.h"

int main() {
std::map<prefix, std::vector<std::string> > state_tab;
state_tab = make_statetab();
generate(state_tab);
return 0;
}
