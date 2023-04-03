NAME = PmergeMe
CPPFLAGS = -Wall -Werror -Wextra
CXX = c++

OBJ = main.o PmergeMe.o
DEPS = algorithm.hpp PmergeMe.hpp

%.o: %.cpp $(DEPS)
	$(CXX) $(CPPFLAGS) -c -o $@ $<

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CPPFLAGS) $(OBJ) -o $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJ)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
