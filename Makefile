# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 15:43:32 by sguzman           #+#    #+#              #
#    Updated: 2024/06/17 17:27:32 by deordone         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME		= cub3D
CC 		= cc
CFLAGS	= -Wall -Wextra -Werror
DFLAGS	= -MMD -MF $(@:.o=.d)

ifneq ($(SANITIZER),)
        CFLAGS+=-fsanitize=$(SANITIZER)
endif

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_PATH	= ./src

OBJS_PATH 	= ./build

INCLUDE_PATH	= ./include

MLX_PATH = ./libs/MLX42

MLX	= $(MLX_PATH)/build/libmlx42.a

HEADER	= $(INCLUDE_PATH)/cub3D.h

SRCS = 

MAIN = cub3D.c

################################################################################
#                                  Makefile  objs                              #
################################################################################

OBJS		= $(addprefix $(OBJS_PATH)/, ${SRCS:.c=.o})

OBJS_MAIN	= $(addprefix $(OBJS_PATH)/, ${MAIN:.c=.o})

DEPS		= $(addprefix $(OBJS_PATH)/, ${SRCS:.c=.d})

DEPS_MAIN	= $(addprefix $(OBJS_PATH)/, ${MAIN:.c=.d})

################################################################################
#                                 Makefile logic                               #
################################################################################

SHELL := /bin/bash
RED         	= \033[0;31m
GREEN       	= \033[0;32m
YELLOW      	= \033[0;33m
BLUE        	= \033[0;34m
PURPLE      	= \033[0;35m
CYAN        	= \033[0;36m
RESET       	= \033[m

define run_and_test
	printf "%b%-46b" "$(YELLOW)compiling " "$(RED)$(@F)$(RESET)"; \
	$(1); \
if [ $$RESULT -ne 0 ]; then \
	printf "%b\n" "$(RED)[✖]$(RESET)"; \
else  \
	printf "%b\n" "$(GREEN)[✓]$(RESET)"; \
fi; \
exit $$RESULT
endef

################################################################################
#                                 Makefile rules                               #
################################################################################

all: banner $(NAME) 

banner:
	@printf "%b" "$(PURPLE)"
	@echo
	@echo "Buen SEXO"
	@echo
	@printf "%b" "$(CYAN)Name:			$(RED)$(NAME)\n$(RESET)"
	@printf "%b" "$(CYAN)Author:		$(RED)Droied4\n$(RESET)"
	@printf "%b" "$(CYAN)Author:		$(RED)San-tito\n$(RESET)"
	@printf "%b" "$(CYAN)CC:			$(RED)$(CC)\n$(RESET)"
	@printf "%b" "$(CYAN)Flags:			$(RED)$(CFLAGS)\n$(RESET)"
	@printf "%b" "$(RESET)"

-include $(DEPS) $(DEPS_MAIN)

$(NAME):	$(OBJS) $(OBJ_MAIN)
			@$(call run_and_test,$(CC) $(CFLAGS) $(DFLAGS) -I $(INCLUDE_PATH) -o $@ $(OBJS) $(OBJ_MAIN))

$(OBJS_PATH)/%.o: 	$(SRCS_PATH)/%.c
			@mkdir -p $(dir $@)
			@$(call run_and_test,$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(INCLUDE_PATH))

clean:		banner
	        @rm -rf $(OBJS_PATH)
			@printf "%-53b%b" "$(GREEN)clean:" "$(GREEN)[✓]$(RESET)\n"

fclean:		banner clean
			@rm -rf $(NAME)
			@printf "%-53b%b" "$(GREEN)fclean:" "$(GREEN)[✓]$(RESET)\n"

re:			fclean all

.PHONY:		all clean fclean re header