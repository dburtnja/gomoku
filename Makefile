SDL_LIBS = -lSDL2 -lSDL2_image

APP_NAME = gomoku

CXX = clang++

CFLAGS = ""

SRC = 	main.cpp \
		src/GomokuMainBoard.cpp \
		src/AiMove.cpp \
		src/ArtificialIntelligence.cpp \
		src/AvailableSpot.cpp \
		src/BoardState.cpp \
		src/SingleStone.cpp \
		src/View.cpp \
		src/SDLTextureClass.cpp


OBJ = $(SRC:.cpp=.o)


all:	$(APP_NAME)

$(APP_NAME): $(OBJ)
						@$(CXX) $(OBJ) -o $(APP_NAME) $(SDL_LIBS)
%.o: %.cpp
						@$(CXX) -c $(CFLAGS) -o $@ $<


clean:
						@rm -f $(OBJ)

fclean:
						@make clean
						@rm -f $(APP_NAME)

re:
						@make fclean
						@make all