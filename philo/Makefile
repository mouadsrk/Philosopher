NAME = philo.a
EXNAME = philo

FILES = philo.c philo_utils.c rotine.c star.c time_utils.c 

CC = cc
FLG = -Wall -Wextra -Werror
AR = ar r
RM = rm -f

OBJ = $(FILES:.c=.o)
 		
all :  $(EXNAME)

$(EXNAME) : $(NAME)
	$(CC) $(FLG) philo.c $(NAME) -o $(EXNAME)

$(NAME) : $(OBJ)
	$(AR)  $(NAME) $(OBJ)
		
%.o :%.c philo.h
	$(CC) $(FLG)  -c $<

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME) $(EXNAME)

re : clean all 

.PHONY: clean  fclean 
