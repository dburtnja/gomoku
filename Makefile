
SDL_LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf

APP_NAME = gomoku

OBJ_DIR = obj

CXX = clang++

CFLAGS = ""

SRC_DIR = src

SRC_FILES =	main.cpp \
			GomokuMainBoard.cpp \
			ArtificialIntelligence.cpp \
			AvailableSpot.cpp \
			BoardState.cpp \
			View.cpp \
			SDLTextureClass.cpp \
			Coordinates.cpp

SRC = $(patsubst %,$(SRC_DIR)/%, $(SRC_FILES))

OBJ = $(patsubst %,$(OBJ_DIR)/%, $(SRC_FILES:.cpp=.o))


all:	$(APP_NAME)

$(APP_NAME): $(OBJ)
						@$(CXX) $(OBJ) -o $(APP_NAME) $(SDL_LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
						@mkdir -p $(OBJ_DIR)
						$(CXX) -c $(CFLAGS) -o $@ $<

clean:
						@rm -rf $(OBJ_DIR)

fclean:
						@make clean
						@rm -f $(APP_NAME)

re:
						@make fclean
						@make all
