# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkuchyna <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/05/21 19:51:08 by nkuchyna          #+#    #+#              #
#    Updated: 2018/06/03 18:05:52 by nkuchyna         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 	RTv1
CCLIB = libft/libft.a
CCMLX = -L  /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
CCFLAGC = -Wall -Wextra -Werror
SRCDIR = src
OBJDIR = obj
INCDIR = includes libft

SRC  =  main.c ft_pretrace_img.c ft_obj_inter.c ft_render_light.c\
		ft_define_scene.c fill_obj_and_lights_fields.c ft_fill_vector_fields.c\
		ft_atof.c ft_strstr_new.c add_default_params.c check_obj_point.c\
		ft_calc_cam_vector.c check_color_and_light.c ft_key_action.c

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS  = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
INCS  =  $(addprefix -I, $(INCDIR))

all: $(NAME)

$(NAME): build $(OBJS)
		@make -C libft/
		@gcc $(CCLIB) $(CCMLX) -o $(NAME) $(OBJS)

build:
		@mkdir -p $(OBJDIR)

clean:
		rm -f $(OBJS)
		make clean -C libft

fclean: clean
		rm -f $(NAME)
		make fclean -C libft

re: fclean all

$(OBJDIR)/%.o : $(SRCDIR)/%.c
				gcc -c $(CCFLAGS) $(INCS) -o $@ $< 

.PHONY: clean fclean make re
