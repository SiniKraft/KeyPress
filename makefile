# ----------------------------
# Makefile Options
# ----------------------------

NAME = KEYPRESS
ICON = icon.png
DESCRIPTION = "The KeyPress Game by Nicklor !"
COMPRESSED = YES
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

DEPS = $(FONT_INC)

# ----------------------------

include $(shell cedev-config --makefile)

# ----------------------------