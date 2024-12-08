NAME        =   philo

CC          =   cc
FLAGS       =   -Wall -Wextra -Werror -g3 -pthread

C_FILES     =   src/routine.c src/utils.c src/mutex.c src/init.c main.c

BUILD_DIR   =   .obj
OBJS        =   $(C_FILES:%.c=$(BUILD_DIR)/%.o)

DEFAULT     =   \033[0;39m
GREEN       =   \033[38;2;72;209;72m
YELLOW      =   \033[0;33m
CYAN    	=   \033[0;36m

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "${CYAN}[${NAME}] ${YELLOW}Compiling : $<...${DEFAULT}\r"
	@$(CC) $(FLAGS) -I. -c $< -o $@
	@printf "\033[K"

$(NAME):    $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully ! ✅$(DEFAULT)"

all:        $(NAME)

clean:
	@rm -rf $(BUILD_DIR)
	@echo "$(YELLOW)   $(NAME) object files cleaned ! 🧹🗑️$(DEFAULT)"

fclean:     clean
	@rm -f $(NAME)
	@echo "$(YELLOW)   $(NAME) executable files cleaned ! 🧹🗑️$(DEFAULT)"

re:         fclean all
	@echo "$(GREEN)✨ $(NAME) recompiled successfully ! ✨ $(DEFAULT)"

.PHONY:     all clean fclean re
