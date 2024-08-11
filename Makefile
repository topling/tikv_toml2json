CXXFLAGS += -std=c++17

tikv_toml2json: tikv_toml2json.o
	${CXX} $^ -o $@

