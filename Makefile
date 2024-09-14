# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sguzman <sguzman@student.42barcelona.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 15:43:32 by sguzman           #+#    #+#              #
#    Updated: 2024/09/14 16:24:57 by santito          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Wunreachable-code -Ofast
DFLAGS      = -MMD -MF $(@:.o=.d)
AUTHORS		= Droied4 && San-tito
UNAME 		= $(shell uname)

ifeq ($(UNAME), Darwin)
    MLXFLAGS = -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(UNAME), Linux)
    MLXFLAGS = -ldl -lglfw -lm
else
    $(error Unsupported platform: $(UNAME))
endif

ifneq ($(SANITIZER),)
    CFLAGS += -fsanitize=$(SANITIZER)
endif

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_PATH    = ./src
OBJS_PATH    = ./build
INCLUDE_PATH = ./include
MLX_PATH     = ./libs/MLX42
MLX          = $(MLX_PATH)/libmlx42.a
LIBFTPRINTF_PATH = ./libs/libftprintf
LIBFTPRINTF		= $(LIBFTPRINTF_PATH)/libftprintf.a

SRCS         = callback.c cub3D.c dispose.c error.c general.c graphics.c map.c parse.c print.c scene.c xmalloc.c raycast.c minimap.c
MAIN         = cub3D.c

################################################################################
#                                  Makefile  objs                              #
################################################################################

OBJS        = $(addprefix $(OBJS_PATH)/, ${SRCS:.c=.o})
OBJS_MAIN   = $(addprefix $(OBJS_PATH)/, ${MAIN:.c=.o})
DEPS        = $(addprefix $(OBJS_PATH)/, ${SRCS:.c=.d})
DEPS_MAIN   = $(addprefix $(OBJS_PATH)/, ${MAIN:.c=.d})

################################################################################
#                                 Makefile logic                               #
################################################################################

SHELL := /bin/bash
RED    = \033[0;31m
GREEN  = \033[0;32m
YELLOW = \033[0;33m
BLUE   = \033[0;34m
PURPLE = \033[0;35m
CYAN   = \033[0;36m
RESET  = \033[m

define compile
    printf "%b%-46b" "$(BLUE)$(2) " "$(CYAN)$(@F)$(RESET)"; \
    OUTPUT=$$($(1) 2>&1); \
    RESULT=$$?; \
    if [ $$RESULT -ne 0 ]; then \
        printf "%b\n" "$(RED)[✗]$(RESET)"; \
	printf "%b\n" "$$OUTPUT"; \
    else  \
        printf "%b\n" "$(GREEN)[✓]$(RESET)"; \
    fi; \
    [ $$RESULT -eq 0 ]
endef

################################################################################
#                                 Makefile rules                               #
################################################################################

all: banner $(NAME) 

banner:
	@printf "%b" "$(GREEN)\n"
	@echo
	@echo "░▒█▀▀▄░█░▒█░█▀▀▄░█▀▀█░█▀▄"
	@echo "░▒█░░░░█░▒█░█▀▀▄░░▒▀▄░█░█"
	@echo "░▒█▄▄▀░░▀▀▀░▀▀▀▀░█▄▄█░▀▀░"
	@echo
	@printf "%b" "$(YELLOW)Name:           $(CYAN)$(NAME)\n$(RESET)"
	@printf "%b" "$(YELLOW)Authors:        $(CYAN)$(AUTHORS)\n$(RESET)"
	@printf "%b" "$(YELLOW)CC:             $(CYAN)$(CC)\n$(RESET)"
	@printf "%b" "$(YELLOW)Flags:          $(CYAN)$(CFLAGS)\n$(RESET)"
	@printf "%b" "\n$(RESET)"

-include $(DEPS) $(DEPS_MAIN)

$(MLX_PATH)/Makefile:
	@$(call compile,cmake -B $(MLX_PATH) $(MLX_PATH))

$(MLX): $(MLX_PATH)/Makefile
	@$(call compile,make -C $(MLX_PATH))

$(LIBFTPRINTF):
	@$(call compile,make -C $(LIBFTPRINTF_PATH))

$(NAME): $(OBJS) $(OBJS_MAIN) $(MLX) $(LIBFTPRINTF)
	@$(call compile,$(CC) $(CFLAGS) $^ $(MLXFLAGS) -o $@)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(dir $@)
	@$(call compile,$(CC) $(CFLAGS) $(DFLAGS) -c $< -o $@ -I $(INCLUDE_PATH) -I $(MLX_PATH)/include -I $(LIBFTPRINTF_PATH)/include)

clean: banner
	@make $@ -C $(LIBFTPRINTF_PATH) > /dev/null
	@make $@ -C $(MLX_PATH) > /dev/null
	@rm -rf $(OBJS_PATH)
	@printf "%-53b%b" "$(CYAN)$(@):" "$(GREEN)[✓]$(RESET)\n"

fclean: banner clean
	@make $@ -C $(LIBFTPRINTF_PATH) > /dev/null
	@rm -rf $(NAME)
	@printf "%-53b%b" "$(CYAN)$(@):" "$(GREEN)[✓]$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re header commit
