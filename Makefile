NAME=PmergeMe
CC=c++
CFLAGS=-Wall -Wextra -Werror -std=c++98 
D_BUILD=.build/

INC=inc/

SRC=	src/main.cpp  \
		src/PmergeMe.cpp

OBJS=	$(addprefix $(D_BUILD), $(SRC:.cpp=.o))

RM=rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I$(INC) -o $@ $^

$(D_BUILD)%.o:	%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	$(RM) $(D_BUILD)

fclean: clean
	$(RM) $(NAME)

cmake:
	make all
	make clean

re: fclean
	make all

DEPS=	$(addprefix $(D_BUILD), $(SRC:.cpp=.d))
-include $(DEPS)

.PHONY: clean fclean cmake re all
