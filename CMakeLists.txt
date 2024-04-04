project(test)

file(GLOB TEST_SOURCES "*.cpp")

add_executable(loja Loja.cpp commons.cpp Estoque.cpp Usuario.cpp Carrinho.cpp ProductNode.cpp)