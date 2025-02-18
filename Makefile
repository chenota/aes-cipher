SRCDIR = src
OBJDIR = build
EXENAME = aes.out

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -Werror -c -o $@ $<

$(EXENAME): $(OBJDIR)/main.o
	$(CXX) $(CPPFLAGS) $(CFLAGS) -Werror -o $(EXENAME) $^