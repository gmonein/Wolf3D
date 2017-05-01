NAME = Wolf3D

CPP = gcc

SDLFLAGS = -framework SDL2 -framework SDL2_ttf -framework SDL2_image -F ./frameworks

SDL2_HEADER = -I frameworks/SDL2.framework/Headers/ \
				-I frameworks/SDL2_image.framework/Headers/ \
				-I frameworks/SDL2_ttf.framework/Headers/

SDL2_P = -rpath @loader_path/frameworks/

CFLAGS = -O3

HEADER = includes

SOURCES = main.c \
		parsing.c \
		raycast.c \
		filler.c \
		ft_fill_area.c \
		thread.c

DIR_O = obj

DIR_S = srcs

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))
OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: obj $(NAME)

${NAME}: $(OBJS)
	${CPP} $(CFLAGS) -o $@ $^ libft/libft.a $(SDL2_P) $(SDLFLAGS)

$(DIR_O)/%.o: $(DIR_S)/%.c
	$(CPP) $(CFLAGS) -I $(HEADER) $(SDL2_HEADER) -c -o $@ $<

obj:
	mkdir -p obj

clean:	
	rm -rf obj

.PHONY: all $(NAME)
