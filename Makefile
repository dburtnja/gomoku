
NAME = gomoku

COM			=	g++ -std=c++11
FLAGS		=	-Wall -Wextra -Werror
OPTIMA		=	-O3

SRC_DIR		=	./src/
INC_DIR		=	./headers/
OBJ_DIR		=	./obj/


SRC_FILES =	main.cpp \
			GomokuMainBoard.cpp \
			ArtificialIntelligence.cpp \
			AvailableSpot.cpp \
			BoardState.cpp \
			View.cpp \
			SDLTextureClass.cpp \
			Coordinates.cpp\
			APlayer.cpp \
			ComputerPlayer.cpp \
			HumanPlayer.cpp \
			Widget.cpp \
			WidgetButton.cpp \
			WidgetButtonGroup.cpp \
			HumanVsCompute.cpp \
			WidgetMenuField.cpp \
			WidgetLabel.cpp \
			GomokuGame.cpp

INC_FILES = AiMove.hpp \
			APlayer.hpp \
			ArtificialIntelligence.hpp \
	AvailableSpot.hpp \
BoardState.hpp \
ComputerPlayer.hpp \
Coordinates.hpp \
GomokuMainBoard.hpp \
HumanPlayer.hpp \
MainHeader.hpp \
SDLTextureClass.hpp \
View.hpp \
Widget.hpp \
WidgetButton.hpp \
WidgetButtonGroup.hpp \
HumanVsCompute.hpp\
WidgetMenuField.hpp \
WidgetLabel.hpp \
GomokuGame.hpp


OBJ_FILES 	=	$(SRC_FILES:.cpp=.o)

SDL_DIR		=	./SDL
SDL_FRM		=	-F $(SDL_DIR)
SDL_LINK	=	-framework SDL2 -framework SDL2_image -framework SDL2_ttf

PWD			= 	$(shell pwd)
LIB_FLAG	=	-rpath $(PWD)/$(SDL_DIR)

SRCS 		=	$(addprefix $(SRC_DIR), $(SRC_FILES))
HDRS 		=	$(addprefix $(INC_DIR), $(INC_FILES))
OBJS 		= 	$(addprefix $(OBJ_DIR), $(OBJ_FILES))


all: obj $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o:$(SRC_DIR)%.cpp
	$(COM) $(FLAGS) $(OPTIMA) $(SDL_FRM) -c $< -o $@ -I $(INC_DIR)


$(NAME): $(OBJS) $(HDRS)
	@$(COM) $(FLAGS) $(OPTIMA) $(SDL_FRM) $(SDL_LINK) $(LIB_FLAG) $(OBJS) -o $(NAME)

clean:
						@ rm -rf $(OBJ_FILES)
						@ rm -rf $(OBJ_DIR)

fclean:
						@make clean
						@rm -f $(NAME)

re:
						@make fclean
						@make all

.PHONY: all clean fclean re
