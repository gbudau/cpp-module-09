NAME = RPN
CPPFLAGS = -Wall -Werror -Wextra
CXX = clang++

OBJ = main.o RPN.o
DEPS = RPN.hpp

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -c -o $@ $<

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ) $(DEPS)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJ)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
